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

int main() {
    auto module = new Module("Assign");                 
    auto builder = new IRBuilder(nullptr, module);                      //ʹ��IRBuilder����ָ��
    //����������BasicBlock
    Type *Int32Type = Type::get_int32_type(module);
    auto mainTy = FunctionType::get(Int32Type, {});                     //����ֵΪi32������Ϊ��
    auto main = Function::create(mainTy, "main", module);            
    auto BB = BasicBlock::create(module, "BasicBlock1" , main);
    builder->set_insert_point(BB);                                      //���ò���ָ���BasicBlock
    //����.ll�ж�Ӧ��ָ��
    auto *arrayType = ArrayType::get(Int32Type, 10);                    //���������Ϊ[10 x i32]
    auto a = builder->create_alloca(arrayType);                         //��������
    auto a0P = builder->create_gep(a, {CONST_INT(0), CONST_INT(0)});    //����a[0]��ַ
    auto a1P = builder->create_gep(a, {CONST_INT(0), CONST_INT(0)});    //����a[1]��ַ
    builder->create_store({CONST_INT(10)}, a0P);                        //a[0] = 10
    auto a0 = builder->create_load(a0P);                                //ȡ��a[0]
    auto temp = builder->create_imul(a0, CONST_INT(2));                 //a[0]*2
    builder->create_store(temp, a1P);                                   //a1 = a[0]*2
    auto a1 = builder->create_load(a1P);       
    builder->create_ret(a1);                                            //return a1 = a[0]*2
    //ָ�������
    std::cout << module->print();
    delete module;
    return 0;
}