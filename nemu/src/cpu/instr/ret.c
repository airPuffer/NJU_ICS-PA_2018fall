#include "cpu/instr.h"

make_instr_func(ret_near){
	OPERAND caller;
	caller.data_size=data_size;
	caller.type=OPR_MEM;
	caller.addr=cpu.esp;
	caller.sreg=SREG_SS;
	
	operand_read(&caller);
	
	cpu.esp+=4;
	cpu.eip=caller.val;
	
	return 0;
}

make_instr_func(ret_near_imm16){
	OPERAND caller;
	caller.data_size=32;
	caller.type=OPR_MEM;
	caller.addr=cpu.esp;
	caller.sreg=SREG_SS;

	operand_read(&caller);
	cpu.esp+=4;
	cpu.eip=caller.val;
	
	OPERAND imm;
	imm.type=OPR_IMM;
	imm.sreg=SREG_CS;
	imm.data_size=16;
	imm.addr=eip+1;
	operand_read(&imm);
	cpu.esp+=imm.val;
	
	return 0;
}
