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
    auto module = new Module("while");                 
    auto builder = new IRBuilder(nullptr, module);                      //使用IRBuilder创建指令
    //创建main函数和4个BasicBlock
    Type *Int32Type = Type::get_int32_type(module);
    auto mainTy = FunctionType::get(Int32Type, {});                     //返回值为i32，参数为空
    auto main = Function::create(mainTy, "main", module);
    auto BBEntry = BasicBlock::create(module, "entry" , main);
    auto BBWhile = BasicBlock::create(module, "while" , main);
    auto BBTrue = BasicBlock::create(module, "true" , main);
    auto BBFalse = BasicBlock::create(module, "false" , main);
    //entryBasicBlock插入指令
    builder->set_insert_point(BBEntry);
    auto aP = builder->create_alloca(Int32Type);                        //分配a的空间，返回指针aP
    auto iP = builder->create_alloca(Int32Type);                        //分配i的空间，返回指针iP
    builder->create_store(CONST_INT(0), iP);                            //i = 0
    builder->create_store(CONST_INT(10), aP);                           //a = 10
    builder->create_br(BBWhile);                                        //br跳转到while循环的判断BasicBlock
    //whileBasicBlock插入指令
    builder->set_insert_point(BBWhile);
    auto temp = builder->create_load(iP);
    auto icmp = builder->create_icmp_lt(temp, CONST_INT(10));
    builder->create_cond_br(icmp, BBTrue, BBFalse);                     //br跳转到True或False的BasicBlock
    //TrueBasicBlock插入指令
    builder->set_insert_point(BBTrue);
    auto newi = builder->create_iadd(temp, CONST_INT(1));               //i + 1
    builder->create_store(newi, iP);                                    //i = i + 1
    auto a = builder->create_load(aP);
    auto newa = builder->create_iadd(newi, a);                          //a + i
    builder->create_store(newa, aP);                                    //a = a + i
    builder->create_br(BBWhile);                                         //br跳转到while循环的判断BasicBlock
    //FalseBasicBlock插入指令
    builder->set_insert_point(BBFalse);
    builder->create_ret(newa);                                          //return a
    //指令创建结束
    std::cout << module->print();
    delete module;
    return 0;
}