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

int main() {
    auto module = new Module("Assign");                 
    auto builder = new IRBuilder(nullptr, module);                      //使用IRBuilder创建指令
    //创建函数与BasicBlock
    Type *Int32Type = Type::get_int32_type(module);
    auto mainTy = FunctionType::get(Int32Type, {});                     //返回值为i32，参数为空
    auto main = Function::create(mainTy, "main", module);            
    auto BB = BasicBlock::create(module, "BasicBlock1" , main);
    builder->set_insert_point(BB);                                      //设置插入指令的BasicBlock
    //插入.ll中对应的指令
    auto *arrayType = ArrayType::get(Int32Type, 10);                    //数组的类型为[10 x i32]
    auto a = builder->create_alloca(arrayType);                         //分配数组
    auto a0P = builder->create_gep(a, {CONST_INT(0), CONST_INT(0)});    //计算a[0]地址
    auto a1P = builder->create_gep(a, {CONST_INT(0), CONST_INT(0)});    //计算a[1]地址
    builder->create_store({CONST_INT(10)}, a0P);                        //a[0] = 10
    auto a0 = builder->create_load(a0P);                                //取出a[0]
    auto temp = builder->create_imul(a0, CONST_INT(2));                 //a[0]*2
    builder->create_store(temp, a1P);                                   //a1 = a[0]*2
    auto a1 = builder->create_load(a1P);       
    builder->create_ret(a1);                                            //return a1 = a[0]*2
    //指令创建结束
    std::cout << module->print();
    delete module;
    return 0;
}