#include "cpu/instr.h"

static void instr_execute_2op(){
	operand_read(&opr_src);
	operand_read(&opr_dest);
	if(opr_src.data_size==8&&opr_dest.data_size==8)
		alu_and(sign_ext(opr_src.val,8),sign_ext(opr_dest.val,8),8);
	else if(opr_src.data_size==8)
		alu_and(sign_ext(opr_src.val,8),sign_ext(opr_dest.val,data_size),data_size);
	else alu_and(sign_ext(opr_src.val,data_size),sign_ext(opr_dest.val,data_size),data_size);
}

make_instr_impl_2op(test,i,rm,v)
make_instr_impl_2op(test,i,rm,b)
make_instr_impl_2op(test,i,a,v)
make_instr_impl_2op(test,i,a,b)


make_instr_func(test_r2rm_v){
	OPERAND rm;
	rm.data_size=data_size;
	int len=1;
	len+=modrm_rm(eip+1,&rm);
	operand_read(&rm);
	alu_and(rm.val,rm.val,data_size);
	return len;
}

make_instr_func(test_r2rm_b){
	OPERAND rm;
	rm.data_size=data_size;
	int len=1;
	len+=modrm_rm(eip+1,&rm);
	operand_read(&rm);
	alu_and(rm.val,rm.val,8);
	return len;
}
