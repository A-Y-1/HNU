#include "cminusf_builder.hpp"
#include "logging.hpp"

// use these macros to get constant value
#define CONST_INT(num) \
    ConstantInt::get((int)num, module.get())
#define CONST_FP(num) \
    ConstantFP::get((float)num, module.get())
#define CONST_ZERO(type) \
    ConstantZero::get(type, module.get())
#define INT32_Type \
 Type::get_int32_type(module.get())   
#define FLOAT_Type \
 Type::get_float_type(module.get())


// You can define global variables here
// to store state
Value* ret;
Value* arg;
bool ifAssign = false;
/*
 * use CMinusfBuilder::Scope to construct scopes
 * scope.enter: enter a new scope
 * scope.exit: exit current scope
 * scope.push: add a new binding to current scope
 * scope.find: find and return the value bound to the name
 */

void CminusfBuilder::visit(ASTProgram &node) { 
    LOG(DEBUG) << "Program\n";
    //语义检查
    if(node.declarations.size()==0){
        std::cout << "ERROR: 该程序中没有声明。\n";
        return;
    }
    if(!(node.declarations.back()->id=="main"&& node.declarations.back()->type==TYPE_VOID)){
        std::cout << "ERROR: 最后一个声明不是void main(void)\n";
        return;
    }
    //访问declarations子节点
    for(auto dec: node.declarations)
        dec->accept(*this);
    return;
}

void CminusfBuilder::visit(ASTNum &node) { 
    LOG(DEBUG) << "Num\n";
    if(node.type == TYPE_INT)
        ret = CONST_INT(node.i_val);
    else if(node.type == TYPE_FLOAT)
        ret = CONST_FP(node.f_val);
    return;  //没有子节点，直接返回
}

void CminusfBuilder::visit(ASTVarDeclaration &node) { 
    LOG(DEBUG) << "VarDeclaration\n";
    Type *varType;
    if(node.type==TYPE_INT)
        varType = INT32_Type;
    else if(node.type==TYPE_FLOAT)
        varType = FLOAT_Type;
    else 
        std::cout <<"ERROR: 在变量声明中，只有整型和浮点型可以使用\n";
    //对变量进行空间分配
    if(scope.in_global()){           //全局变量
        if(node.num==nullptr){       //非数组
            auto initializer = CONST_ZERO(varType);
            auto globalVar = GlobalVariable::create(node.id, module.get(), varType, false, initializer);
            scope.push(node.id, globalVar);
        }
        else{
            if(node.num->i_val>0){
                auto *array = ArrayType::get(varType, node.num->i_val);
                auto initializer = CONST_ZERO(array);
                auto globalVar = GlobalVariable::create(node.id, module.get(), array, false, initializer);
                scope.push(node.id, globalVar);
            }
            else
                std::cout << "ERROR: 数组长度必须大于0\n";
        }
    }
    else{                          //局部变量
        if(node.num==nullptr){     //非数组
             auto localVar = builder->create_alloca(varType);
             scope.push(node.id, localVar);
        }
        else{
            if(node.num->i_val>0){
                auto *array = ArrayType::get(varType, node.num->i_val);
                auto localVar = builder->create_alloca(array);
                scope.push(node.id, localVar);
            }
            else
                std::cout << "ERROR: 数组长度必须大于0\n";
        }
    }
}

void CminusfBuilder::visit(ASTFunDeclaration &node) { 
    LOG(DEBUG) << "FunDeclaration\n";
    Type *retType;                 //函数返回类型
    std::vector<Type *> paramType; //参数类型
    FunctionType *funType;         //函数类型
    //语义检查
    if(node.id=="main" && node.params.size()>0)
      std::cout << "ERROR: main函数必须为void main(void)形式\n";
    //确定函数的返回类型
    if(node.type==TYPE_INT)
        retType = INT32_Type;
    else if(node.type==TYPE_FLOAT)
        retType = FLOAT_Type;
    else if(node.type==TYPE_VOID)
        retType = Type::get_void_type(module.get());
    //确定函数的参数类型
    for(auto param : node.params){
        if(param->isarray){       //参数为数组，则参数为数组的首地址指针
            if(param->type==TYPE_INT)
                paramType.push_back(Type::get_int32_ptr_type(module.get()));
            else if(param->type==TYPE_FLOAT)
                paramType.push_back(Type::get_int32_ptr_type(module.get()));
        }
        else{                    //参数为整型或浮点型
            if (param->type==TYPE_INT)       
                paramType.push_back(INT32_Type);
            else if(param->type==TYPE_FLOAT)
                paramType.push_back(FLOAT_Type);     
        }
    }
    //创建函数
    funType = FunctionType::get(retType, paramType);
    auto func = Function::create(funType, node.id, module.get());
    scope.push(node.id, func);   //将函数加入全局作用域
    scope.enter();               //进入函数作用域
    auto entryBB = BasicBlock::create(module.get(), node.id + "entry", func);
    builder->set_insert_point(entryBB);     //插入指令
    //visit参数节点
    std::vector<Value*> args;    //存储参数
    for (auto arg = func->arg_begin();arg != func->arg_end();arg++) {
        args.push_back(*arg);    
    }
    for (int i = 0;i < node.params.size();i++) {
        auto param = node.params[i];
        arg = args[i];
        param->accept(*this);           
    }
    //处理函数体内的语句
    node.compound_stmt->accept(*this);
    //如果BasicBlock最后没有终止指令，创建返回指令
    if (builder->get_insert_block()->get_terminator() == nullptr) {
        if (func->get_return_type()->is_void_type())
            builder->create_void_ret();
        else if (func->get_return_type()->is_float_type())
            builder->create_ret(CONST_FP(0.));
        else
            builder->create_ret(CONST_INT(0));
    }
    scope.exit();
}

void CminusfBuilder::visit(ASTParam &node) {   
    LOG(DEBUG) << "Param\n";    
    Value* paramP; 
    if (node.isarray) {          //数组
        if (node.type==TYPE_INT)        
            paramP = builder->create_alloca(Type::get_int32_ptr_type(module.get()));
        else if (node.type==TYPE_FLOAT) 
            paramP = builder->create_alloca(Type::get_float_ptr_type(module.get()));
    }
    else {                       //非数组
        if (node.type==TYPE_INT)       
            paramP = builder->create_alloca(INT32_Type);
        else if (node.type==TYPE_FLOAT)
            paramP = builder->create_alloca(FLOAT_Type);
    }
    builder->create_store(arg, paramP);         //存储参数
    scope.push(node.id, paramP);                //加入作用域
}

void CminusfBuilder::visit(ASTCompoundStmt &node) { 
    LOG(DEBUG) << "CompoundStmt\n";
    //访问局部声明的节点和语句节点
    for(auto local_declaration: node.local_declarations)
        local_declaration->accept(*this);
    for(auto statement: node.statement_list)
        statement->accept(*this);
}

void CminusfBuilder::visit(ASTExpressionStmt &node) { 
    LOG(DEBUG) << "ExpressionStmt\n";
	if (node.expression != nullptr)
		node.expression->accept(*this);
}

void CminusfBuilder::visit(ASTSelectionStmt &node) { 
    LOG(DEBUG) << "SelectionStmt\n";
    //处理条件表达式
    auto func = builder->get_insert_block()->get_parent();
    node.expression->accept(*this);
    auto retType = ret->get_type();
    Value* ifExpression;                         //条件表达式的结果             
    //根据返回类型处理, 生成比较语句
    if(retType->is_integer_type())
        ifExpression = builder->create_icmp_gt(ret, CONST_ZERO(INT32_Type));
    else
        ifExpression = builder->create_fcmp_gt(ret, CONST_ZERO(FLOAT_Type));
    //生成BasicBlock
    auto ifBB = BasicBlock::create(module.get(), "ifBasicBlock", func);
    auto elseBB = BasicBlock::create(module.get(), "elseBasicBlock", func);
    auto afterIfBB = BasicBlock::create(module.get(), "afterIfBasicBlock", func);
    //创建br指令
    if(node.else_statement==nullptr)             //没有else
        builder->create_cond_br(ifExpression, ifBB, afterIfBB);
    else
        builder->create_cond_br(ifExpression, ifBB, elseBB);
    //为ifBB添加IR
    builder->set_insert_point(ifBB);
    node.if_statement->accept(*this);
	if (builder->get_insert_block()->get_terminator() == nullptr)
		builder->create_br(afterIfBB);
    //为elseBB添加IR
    if(node.else_statement!=nullptr){
        builder->set_insert_point(elseBB);
        node.else_statement->accept(*this);
	    if (builder->get_insert_block()->get_terminator() == nullptr)
		builder->create_br(afterIfBB);        
    }
    else
        elseBB->erase_from_parent();
    //后面的语句块的IR在新的BasicBlock中
    builder->set_insert_point(afterIfBB);
}

void CminusfBuilder::visit(ASTIterationStmt &node) {
    LOG(DEBUG) << "IterationStmt\n";
    //创建BasicBlock
    auto func = builder->get_insert_block()->get_parent();
    auto ifBB = BasicBlock::create(module.get(), "ifBasicBlock", func);
    auto loopBB = BasicBlock::create(module.get(), "loopBasicBlock", func);
    auto afterWhileBB = BasicBlock::create(module.get(), "afterWhileBasicBlock", func);
    //跳转到条件表达式判断的BasicBlock
    builder->create_br(ifBB);
    //为ifBB添加IR, 判断条件表达式的结果
    builder->set_insert_point(ifBB);
    node.expression->accept(*this);
    auto retType = ret->get_type();
    Value* ifExpression;                         //条件表达式的结果             
    //根据返回类型处理, 生成比较语句
    if(retType->is_integer_type())
        ifExpression = builder->create_icmp_gt(ret, CONST_ZERO(INT32_Type));
    else
        ifExpression = builder->create_fcmp_gt(ret, CONST_ZERO(FLOAT_Type));
    //条件跳转
    builder->create_cond_br(ifExpression, loopBB, afterWhileBB);
    //为loopBB添加IR
    builder->set_insert_point(loopBB);
    node.statement->accept(*this);
    if (builder->get_insert_block()->get_terminator() == nullptr)
        builder->create_br(ifBB);
    //后面的语句块的IR在新的BasicBlock中
    builder->set_insert_point(afterWhileBB);
}

void CminusfBuilder::visit(ASTReturnStmt &node) { 
    LOG(DEBUG) << "ReturnStmt\n";
    if(node.expression==nullptr){
        builder->create_void_ret();
        return;
    }
    node.expression->accept(*this);
    //处理返回值，产生返回的IR
    auto func = builder->get_insert_block()->get_parent();
    auto retType = func->get_return_type();
    auto resType = ret->get_type();
    if (retType->is_integer_type() && resType->is_float_type())
        ret = builder->create_fptosi(ret, INT32_Type);
    else if(retType->is_float_type() && resType->is_integer_type())
        ret = builder->create_sitofp(ret, FLOAT_Type);
    builder->create_ret(ret);
}

void CminusfBuilder::visit(ASTVar &node) { 
    LOG(DEBUG) << "Var\n";
    //先在作用域找到变量
    auto var = scope.find(node.id);
    if(var==nullptr)
        std::cout << "ERROR: 未声明的变量" << node.id << "\n";
    //处理不是数组的情况
    if(node.expression==nullptr){
        if(ifAssign){                             //直接返回地址
            ret = var;
            ifAssign = false;
        }
        else{
            //数组的指针即a[]类型就返回数组的起始地址，否则load取值
            if(var->get_type()->get_pointer_element_type()->is_array_type())
                ret = builder->create_gep(var, {CONST_INT(0), CONST_INT(0)});
            else
                ret = builder->create_load(var);
        }
        return;
    }
    //处理数组的情况
    node.expression->accept(*this);
    Value *idx = ret;                             //下标
    if(idx->get_type()->is_float_type())          //如果为浮点类型，转换为整型
        idx = builder->create_fptosi(idx, INT32_Type);
    auto func = builder->get_insert_block()->get_parent();
    auto ifNegative = builder->create_icmp_lt(idx, CONST_INT(0));
    //创建exitBasicBlock和正常继续的BasicBlock
    auto exitBB = BasicBlock::create(module.get(), node.id + "exit", func);
    auto nextBB = BasicBlock::create(module.get(), node.id + "next", func);
    //条件跳转指令
    builder->create_cond_br(ifNegative, exitBB, nextBB);
    //向exitBB插入退出程序的指令
    builder->set_insert_point(exitBB);
    auto fail = scope.find("neg_idx_except");               
    builder->create_call(static_cast<Function*>(fail), {}); 
    builder->create_br(nextBB);
    //向nextBB插入正常执行的指令
    builder->set_insert_point(nextBB);
    //如果var的值是指向数组的指针，需要两个偏移取地址
    if(var->get_type()->get_pointer_element_type()->is_array_type())
        builder->create_gep(var, { CONST_INT(0), idx });
    else if(var->get_type()->get_pointer_element_type()->is_pointer_type()){
        //从var中取出数组的起始地址
        var = builder->create_load(var);          //a[]的地址
        var = builder->create_gep(var, { idx });  //a[idx]的地址
    }
    else
        std::cout << "ERROR: 变量" << node.id << "不是一个数组\n";
    //判断是赋值还是变量引用
    if(ifAssign){                             //直接返回地址
        ret = var;
        ifAssign = false;
    }
    else
        ret = builder->create_load(var);
}

void CminusfBuilder::visit(ASTAssignExpression &node) { 
    LOG(DEBUG) << "AssignExpression\n";
    ifAssign = true;
    node.var->accept(*this);
    auto varAdd = ret;
    node.expression->accept(*this);
    //确认表达式结果类型与变量类型相同，不同则进行转换
    auto varType = varAdd->get_type()->get_pointer_element_type();
    auto valueType = ret->get_type();
    Value* value = ret;
    if(varType!=valueType){
        if(varType==INT32_Type)
            value = builder->create_fptosi(ret, INT32_Type);
        else
            value = builder->create_sitofp(ret, FLOAT_Type);
    }
    builder->create_store(value, varAdd);
}

void CminusfBuilder::visit(ASTSimpleExpression &node) { 
    LOG(DEBUG) << "SimpleExpression\n";
    bool ifInt = true;                      //表达式结果类型
    Value *resL, *resR;
    Type *resLType, *resRType;
    //计算两个加法表达式
    if(node.additive_expression_l!=nullptr){
        node.additive_expression_l->accept(*this);
        resL = ret;
        resLType = ret->get_type();
    }
    if(node.additive_expression_r!=nullptr){
        node.additive_expression_r->accept(*this);
        resR = ret;
        resRType = ret->get_type();
    }
    //如果只有一个加法表达式, 直接返回表达式的值
    if(!(node.additive_expression_l!=nullptr && node.additive_expression_r!=nullptr)){
        ret = (node.additive_expression_l!=nullptr) ? resL : resR;
        return;
    }
    //如果有两个加法表达式, 为关系运算
    //先统一类型
    if(resLType!=resRType){
        ifInt = false;
        if(resLType->is_float_type())        //左表达式为浮点型，则右表达式从整型转换为浮点型
            resL = builder->create_sitofp(resL, FLOAT_Type);
        else                                 //左表达式为整型，转换为浮点型
            resR = builder->create_sitofp(resR, FLOAT_Type);
    }
    //根据关系运算类型，创建指令
    switch (node.op)
    {
    case OP_LE:
        if(ifInt)
            ret = builder->create_icmp_le(resL, resR);
        else
            ret = builder->create_fcmp_le(resL, resR);
        break;
    case OP_LT:
        if(ifInt)
            ret = builder->create_icmp_lt(resL, resR);
        else
            ret = builder->create_fcmp_lt(resL, resR);
        break;
    case OP_GT:
        if(ifInt)
            ret = builder->create_icmp_gt(resL, resR);
        else
            ret = builder->create_fcmp_gt(resL, resR);
        break;
    case OP_GE:
        if(ifInt)
            ret = builder->create_icmp_ge(resL, resR);
        else
            ret = builder->create_fcmp_ge(resL, resR);
        break;
    case OP_EQ:
        if(ifInt)
            ret = builder->create_icmp_eq(resL, resR);
        else
            ret = builder->create_fcmp_eq(resL, resR);
        break;
    case OP_NEQ:
        if(ifInt)
            ret = builder->create_icmp_ne(resL, resR);
        else
            ret = builder->create_fcmp_ne(resL, resR);
        break;
    default:
        break;
    }
    //结果为整型
    ret = builder->create_zext(ret, INT32_Type);
}

void CminusfBuilder::visit(ASTAdditiveExpression &node) { 
    LOG(DEBUG) << "AdditiveExpression\n";
    bool ifInt = true;                        //两个表达式类型
    //如果只有乘法表达式
    if(node.additive_expression==nullptr){
        node.term->accept(*this);
        return;
    }
    //有乘法表达式和加法表达式，创建加法或减法指令
    node.additive_expression->accept(*this);  //处理加法表达式
    auto addRes = ret;
    auto addType = addRes->get_type();
    node.term->accept(*this);                 //处理乘法表达式
    auto mulRes = ret;
    auto mulType = mulRes->get_type();
    //确认类型相同
    if(addType!=mulType){
        ifInt = false;
        if(addType->is_float_type())
            mulRes = builder->create_sitofp(mulRes, FLOAT_Type);
        else
            addRes = builder->create_sitofp(addRes, INT32_Type);
    }
    //指令
    if(node.op==OP_PLUS){
        if(ifInt)
            ret = builder->create_iadd(addRes, mulRes);     //addRes在左!
        else
            ret = builder->create_fadd(addRes, mulRes);  
    }
    else{
        if(ifInt)
            ret = builder->create_isub(addRes, mulRes);
        else
            ret = builder->create_fsub(addRes, mulRes);        
    }
}

void CminusfBuilder::visit(ASTTerm &node) { 
    LOG(DEBUG) << "Term\n";
    bool ifInt = true;                        //因子和乘法表达式结果类型
    //如果只有因子
    if(node.term==nullptr){
        node.factor->accept(*this);
        return;
    }
    //有乘法表达式和因子，创建乘法或除法指令
    node.term->accept(*this);                 //处理乘法表达式
    auto mulRes = ret;
    auto mulType = mulRes->get_type();
    node.factor->accept(*this);               //处理因子
    auto factorRes = ret;
    auto factorType = factorRes->get_type();
    //确认类型相同
    if(factorType!=mulType){
        ifInt = false;
        if(factorType->is_float_type())
            mulRes = builder->create_sitofp(mulRes, FLOAT_Type);
        else
            factorRes = builder->create_sitofp(factorRes, INT32_Type);
    }
    //指令
    if(node.op==OP_MUL){
        if(ifInt)
            ret = builder->create_imul(mulRes, factorRes);
        else
            ret = builder->create_fmul(mulRes, factorRes);
    }
    else{
        if(ifInt)
            ret = builder->create_isdiv(mulRes, factorRes);
        else
            ret = builder->create_fdiv(mulRes, factorRes);        
    }
}

void CminusfBuilder::visit(ASTCall &node) { 
    LOG(DEBUG) << "Call\n";
    auto func = static_cast<Function*>(scope.find(node.id));
    auto paramType = func->get_function_type()->param_begin();
    if(func==nullptr)
        std::cout << "ERROR: 函数" << node.id << "未定义\n";
    //处理参数
    Value *temp;
    std::vector<Value*> args;
    for(auto arg: node.args){
        arg->accept(*this);                   //获取参数值
        temp = ret;
        auto argType = ret->get_type();       //处理类型
        if(argType!=*paramType)
            if((*paramType)->is_integer_type())
                temp = builder->create_fptosi(ret, INT32_Type);
            else
                temp = builder->create_sitofp(ret, FLOAT_Type);
        args.push_back(temp); 
        paramType++;
    }
    ret = builder->create_call(func, args);
}
