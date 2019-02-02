#include "cpu/instr.h"

make_instr_func(pusha){
	uint32_t original_esp=cpu.esp;
	push_r_v(eip,0x50);
	push_r_v(eip,0x51);
	push_r_v(eip,0x52);
	push_r_v(eip,0x53);

	OPERAND opr_src;
	cpu.esp-=4;
	opr_src.val=original_esp;
	opr_src.data_size=data_size;
	opr_src.addr=cpu.esp;
	opr_src.type=OPR_MEM;
	opr_src.sreg=SREG_SS;
	operand_write(&opr_src);
	
	push_r_v(eip,0x55);
	push_r_v(eip,0x56);
	push_r_v(eip,0x57);

	return 1;

}
