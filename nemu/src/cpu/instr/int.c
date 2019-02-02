#include "cpu/instr.h"
#include "cpu/intr.h"

make_instr_func(int_){
	OPERAND imm;
	imm.type=OPR_IMM;
	imm.addr=eip+1;
	imm.data_size=8;
	imm.sreg=SREG_CS;
	
	operand_read(&imm);
	raise_sw_intr(imm.val);

	return 0;
};
