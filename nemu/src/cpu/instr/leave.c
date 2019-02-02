#include "cpu/instr.h"

make_instr_func(leave){

	OPERAND r_esp,r_ebp,m;
	r_esp.data_size=data_size;
	r_esp.type=OPR_REG;
	r_esp.addr=REG_ESP;

	r_ebp.data_size=data_size;
	r_ebp.type=OPR_REG;
	r_ebp.addr=REG_EBP;
	operand_read(&r_ebp);

	r_esp.val=r_ebp.val;
	operand_write(&r_esp);

	m.data_size=data_size;
	m.addr=cpu.esp;
	m.type=OPR_MEM;
	m.sreg=SREG_SS;
	operand_read(&m);

	r_ebp.val=m.val;
	operand_write(&r_ebp);

	cpu.esp+=4;

	return 1;
}
