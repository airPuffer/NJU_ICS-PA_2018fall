#include"cpu/instr.h"

make_instr_func(call_near){
	OPERAND rel;
	rel.type=OPR_IMM;
	rel.data_size=data_size;
	rel.addr=eip+1;
	rel.sreg=SREG_CS;
	operand_read(&rel);
	int offset = sign_ext(rel.val, data_size);

	OPERAND next_instr;
	next_instr.data_size=32;
	next_instr.type=OPR_MEM;
	cpu.esp-=4;
	next_instr.addr=cpu.esp;
	next_instr.sreg=SREG_SS;
	next_instr.val=eip+1+data_size/8;
	operand_write(&next_instr);

	cpu.eip+=offset;
	cpu.eip+=(1+data_size/8);

	return 0;
}
make_instr_func(call_near_indirect){
	OPERAND rm;
	rm.data_size=data_size;
	int len=1;
	len+=modrm_rm(eip+1,&rm);
	operand_read(&rm);

	OPERAND next_instr;
	next_instr.data_size=32;
	next_instr.type=OPR_MEM;
	cpu.esp-=4;
	next_instr.addr=cpu.esp;
	next_instr.sreg=SREG_SS;
	next_instr.val=eip+len;
	operand_write(&next_instr);

	cpu.eip=rm.val;

	return 0;
}
