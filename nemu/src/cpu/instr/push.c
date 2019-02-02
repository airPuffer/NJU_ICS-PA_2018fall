#include "cpu/instr.h"

static void instr_execute_1op(){
	operand_read(&opr_src);
	cpu.esp-=4;
	opr_src.addr=cpu.esp;
	opr_src.type=OPR_MEM;
	opr_src.sreg=SREG_SS;
	operand_write(&opr_src);
}

make_instr_impl_1op(push,r,v)
make_instr_impl_1op(push,rm,v)
make_instr_impl_1op(push,i,v)

/*
make_instr_impl_1op(push,eax,v)
make_instr_impl_1op(push,ecx,v)
make_instr_impl_1op(push,edx,v)
make_instr_impl_1op(push,ebx,v)
make_instr_impl_1op(push,esp,v)
make_instr_impl_1op(push,ebp,v)
make_instr_impl_1op(push,esi,v)
make_instr_impl_1op(push,edi,v)
*/

make_instr_func(push_i_b){
	OPERAND imm;
	imm.type=OPR_IMM;
	imm.data_size=8;
	imm.addr=eip+1;
	imm.sreg=SREG_CS;
	operand_read(&imm);

	imm.val=sign_ext(imm.val,8);
	imm.data_size=32;
	cpu.esp-=4;
	imm.addr=cpu.esp;
	imm.type=OPR_MEM;
	imm.sreg=SREG_SS;
	operand_write(&imm);

	return 2;
}


