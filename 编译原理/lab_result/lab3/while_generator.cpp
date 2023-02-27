#include "BasicBlock.h"
#include "Constant.h"
#include "Function.h"
#include "IRBuilder.h"
#include "Module.h"
#include "Type.h"
#include <iostream>
#include <memory>

#ifdef DEBUG  // ���ڵ�����Ϣ,��ҿ����ڱ��������ͨ��" -DDEBUG"��������һѡ��
#define DEBUG_OUTPUT std::cout << __LINE__ << std::endl;  // ����кŵļ�ʾ��
#else
#define DEBUG_OUTPUT
#endif

#define CONST_INT(num) \
    ConstantInt::get(num, module)

#define CONST_FP(num) \
    ConstantFP::get(num, module) // �õ�����ֵ�ı�ʾ,����������õ�

int main(){
    auto module = new Module("while");                 
    auto builder = new IRBuilder(nullptr, module);                      //ʹ��IRBuilder����ָ��
    //����main������4��BasicBlock
    Type *Int32Type = Type::get_int32_type(module);
    auto mainTy = FunctionType::get(Int32Type, {});                     //����ֵΪi32������Ϊ��
    auto main = Function::create(mainTy, "main", module);
    auto BBEntry = BasicBlock::create(module, "entry" , main);
    auto BBWhile = BasicBlock::create(module, "while" , main);
    auto BBTrue = BasicBlock::create(module, "true" , main);
    auto BBFalse = BasicBlock::create(module, "false" , main);
    //entryBasicBlock����ָ��
    builder->set_insert_point(BBEntry);
    auto aP = builder->create_alloca(Int32Type);                        //����a�Ŀռ䣬����ָ��aP
    auto iP = builder->create_alloca(Int32Type);                        //����i�Ŀռ䣬����ָ��iP
    builder->create_store(CONST_INT(0), iP);                            //i = 0
    builder->create_store(CONST_INT(10), aP);                           //a = 10
    builder->create_br(BBWhile);                                        //br��ת��whileѭ�����ж�BasicBlock
    //whileBasicBlock����ָ��
    builder->set_insert_point(BBWhile);
    auto temp = builder->create_load(iP);
    auto icmp = builder->create_icmp_lt(temp, CONST_INT(10));
    builder->create_cond_br(icmp, BBTrue, BBFalse);                     //br��ת��True��False��BasicBlock
    //TrueBasicBlock����ָ��
    builder->set_insert_point(BBTrue);
    auto newi = builder->create_iadd(temp, CONST_INT(1));               //i + 1
    builder->create_store(newi, iP);                                    //i = i + 1
    auto a = builder->create_load(aP);
    auto newa = builder->create_iadd(newi, a);                          //a + i
    builder->create_store(newa, aP);                                    //a = a + i
    builder->create_br(BBWhile);                                         //br��ת��whileѭ�����ж�BasicBlock
    //FalseBasicBlock����ָ��
    builder->set_insert_point(BBFalse);
    builder->create_ret(newa);                                          //return a
    //ָ�������
    std::cout << module->print();
    delete module;
    return 0;
}