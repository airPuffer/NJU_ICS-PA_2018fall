#include "cpu/instr.h"

make_instr_func(lidt){
	OPERAND rm;
	rm.data_size=data_size;
	int len=1;
	len+=modrm_rm(eip+1,&rm);
	
	operand_read(&rm);

	cpu.idtr.limit=rm.val&0xFFFF;

	rm.addr+=2;
	operand_read(&rm);
	cpu.idtr.base=rm.val;


	return len;
}
