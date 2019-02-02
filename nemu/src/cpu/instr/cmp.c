#include "cpu/instr.h"

static void instr_execute_2op(){
	operand_read(&opr_dest);
	operand_read(&opr_src);

	if(opr_src.data_size==8&&opr_dest.data_size==8)
		alu_sub(sign_ext(opr_src.val,8),sign_ext(opr_dest.val,8),8);
	else if(opr_src.data_size==8)
		alu_sub(sign_ext(opr_src.val,8),sign_ext(opr_dest.val,data_size),data_size);
	else alu_sub(sign_ext(opr_src.val,data_size),sign_ext(opr_dest.val,data_size),data_size);
}

make_instr_impl_2op(cmp,i,rm,b)
make_instr_impl_2op(cmp,i,rm,v)
make_instr_impl_2op(cmp,i,a,v)
make_instr_impl_2op(cmp,i,a,b)
make_instr_impl_2op(cmp,r,rm,v)
make_instr_impl_2op(cmp,r,rm,b)
make_instr_impl_2op(cmp,rm,r,v)
make_instr_impl_2op(cmp,rm,r,b)
make_instr_impl_2op(cmp,i,rm,bv)


