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
    auto module = new Module("if");                 
    auto builder = new IRBuilder(nullptr, module);                      //使用IRBuilder创建指令
    //创建main函数
    Type *Int32Type = Type::get_int32_type(module);
    auto mainTy = FunctionType::get(Int32Type, {});                     //返回值为i32，参数为空
    auto main = Function::create(mainTy, "main", module);
    auto BBEntry = BasicBlock::create(module, "entry" , main);
    builder->set_insert_point(BBEntry); 
    //entryBasicBlock插入指令
    Type *FloatType = Type::get_float_type(module);                     //浮点类型
    auto aP = builder->create_alloca(FloatType);                        //为float a分配空间并返回指针
    builder->create_store(CONST_FP(5.555),aP);                          //a = 5.555
    auto a = builder->create_load(aP);                                  //取出a
    auto fcmp = builder->create_fcmp_gt(a, CONST_FP(1.0));              //fcmp = if a>1
    //创建true, false对应的BasicBlock
    auto BBTrue = BasicBlock::create(module, "true" , main);
    auto BBFalse = BasicBlock::create(module, "false", main);
    builder->create_cond_br(fcmp, BBTrue, BBFalse);                     //br跳转指令
    //true和false对应的BasicBlock插入指令
    builder->set_insert_point(BBTrue);
    builder->create_ret(CONST_INT(233));
    builder->set_insert_point(BBFalse);
    builder->create_ret(CONST_INT(0));
    //指令创建结束
    std::cout << module->print();
    delete module;
    return 0;
}