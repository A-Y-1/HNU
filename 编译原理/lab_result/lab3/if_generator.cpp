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
    auto module = new Module("if");                 
    auto builder = new IRBuilder(nullptr, module);                      //ʹ��IRBuilder����ָ��
    //����main����
    Type *Int32Type = Type::get_int32_type(module);
    auto mainTy = FunctionType::get(Int32Type, {});                     //����ֵΪi32������Ϊ��
    auto main = Function::create(mainTy, "main", module);
    auto BBEntry = BasicBlock::create(module, "entry" , main);
    builder->set_insert_point(BBEntry); 
    //entryBasicBlock����ָ��
    Type *FloatType = Type::get_float_type(module);                     //��������
    auto aP = builder->create_alloca(FloatType);                        //Ϊfloat a����ռ䲢����ָ��
    builder->create_store(CONST_FP(5.555),aP);                          //a = 5.555
    auto a = builder->create_load(aP);                                  //ȡ��a
    auto fcmp = builder->create_fcmp_gt(a, CONST_FP(1.0));              //fcmp = if a>1
    //����true, false��Ӧ��BasicBlock
    auto BBTrue = BasicBlock::create(module, "true" , main);
    auto BBFalse = BasicBlock::create(module, "false", main);
    builder->create_cond_br(fcmp, BBTrue, BBFalse);                     //br��תָ��
    //true��false��Ӧ��BasicBlock����ָ��
    builder->set_insert_point(BBTrue);
    builder->create_ret(CONST_INT(233));
    builder->set_insert_point(BBFalse);
    builder->create_ret(CONST_INT(0));
    //ָ�������
    std::cout << module->print();
    delete module;
    return 0;
}