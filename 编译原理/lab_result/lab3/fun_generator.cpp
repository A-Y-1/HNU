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
    auto module = new Module("fun");
    auto builder = new IRBuilder(nullptr, module);
    //����callee����
    Type *Int32Type = Type::get_int32_type(module);
    auto calleeTy = FunctionType::get(Int32Type, {Int32Type});            //����ֵΪi32��һ��i32���͵Ĳ���
    auto callee = Function::create(calleeTy, "callee", module); 
    auto BB = BasicBlock::create(module, "callee_BasicBlock" , callee);
    builder->set_insert_point(BB);
    //����callee��ָ��
    std::vector<Value *> args;                                            //��ȡ�������β�,ͨ��Function�е�iterator
    for (auto arg = callee->arg_begin(); arg != callee->arg_end(); arg++) {
        args.push_back(*arg);                                             //* ��������Ǵӵ�������ȡ����������ǰָ���Ԫ��
    }
    auto mul = builder->create_imul(args[0], CONST_INT(2));             //mul = a*2
    builder->create_ret(mul);
    //����main����
    auto mainTy = FunctionType::get(Int32Type, {});
    auto main = Function::create(mainTy, "main", module); 
    auto BB1 = BasicBlock::create(module, "main_BasicBlock" , main);
    builder->set_insert_point(BB1);
    //����main��ָ��
    auto callret = builder->create_call(callee, {CONST_INT(110)});
    builder->create_ret(callret);
    //ָ�������
    std::cout << module->print();
    delete module;
    return 0;
}