#include "BasicBlock.h"
#include "Constant.h"
#include "Function.h"
#include "IRBuilder.h"
#include "Module.h"
#include "Type.h"
#include <iostream>
#include <memory>

#ifdef DEBUG  // 用于调试信息,大家可以在编译过程中通过" -DDEBUG"来开启这一选项
#define DEBUG_OUTPUT std::cout << __LINE__ << std::endl;  // 输出行号的简单示例
#else
#define DEBUG_OUTPUT
#endif

#define CONST_INT(num) \
    ConstantInt::get(num, module)

#define CONST_FP(num) \
    ConstantFP::get(num, module) // 得到常数值的表示,方便后面多次用到

int main(){
    auto module = new Module("fun");
    auto builder = new IRBuilder(nullptr, module);
    //创建callee函数
    Type *Int32Type = Type::get_int32_type(module);
    auto calleeTy = FunctionType::get(Int32Type, {Int32Type});            //返回值为i32，一个i32类型的参数
    auto callee = Function::create(calleeTy, "callee", module); 
    auto BB = BasicBlock::create(module, "callee_BasicBlock" , callee);
    builder->set_insert_point(BB);
    //插入callee的指令
    std::vector<Value *> args;                                            //获取函数的形参,通过Function中的iterator
    for (auto arg = callee->arg_begin(); arg != callee->arg_end(); arg++) {
        args.push_back(*arg);                                             //* 号运算符是从迭代器中取出迭代器当前指向的元素
    }
    auto mul = builder->create_imul(args[0], CONST_INT(2));             //mul = a*2
    builder->create_ret(mul);
    //创建main函数
    auto mainTy = FunctionType::get(Int32Type, {});
    auto main = Function::create(mainTy, "main", module); 
    auto BB1 = BasicBlock::create(module, "main_BasicBlock" , main);
    builder->set_insert_point(BB1);
    //插入main的指令
    auto callret = builder->create_call(callee, {CONST_INT(110)});
    builder->create_ret(callret);
    //指令创建结束
    std::cout << module->print();
    delete module;
    return 0;
}