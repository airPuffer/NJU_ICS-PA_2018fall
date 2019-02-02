#include "cpu/instr.h"

static void instr_execute_2op(){
	operand_read(&opr_src);
	operand_read(&opr_dest);
	if(opr_src.data_size==8&&opr_dest.data_size==8)
		opr_dest.val=alu_and(sign_ext(opr_src.val,8),sign_ext(opr_dest.val,8),8);
	else if(opr_src.data_size==8)
		opr_dest.val=alu_and(sign_ext(opr_src.val,8),sign_ext(opr_dest.val,data_size),data_size);
	else opr_dest.val=alu_and(sign_ext(opr_src.val,data_size),sign_ext(opr_dest.val,data_size),data_size);
	operand_write(&opr_dest);
}

make_instr_impl_2op(and,i,rm,v)
make_instr_impl_2op(and,i,rm,bv)
make_instr_impl_2op(and,i,a,v)
make_instr_impl_2op(and,i,a,b)
make_instr_impl_2op(and,rm,r,v)
make_instr_impl_2op(and,rm,r,b)
make_instr_impl_2op(and,r,rm,v)
make_instr_impl_2op(and,r,rm,b)
make_instr_impl_2op(and,i,rm,b)
