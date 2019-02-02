#include "cpu/instr.h"

static void instr_execute_1op(){
	OPERAND top;
	top.data_size=data_size;
	top.addr=cpu.esp;
	top.type=OPR_MEM;
	top.sreg=SREG_SS;
	
	operand_read(&top);
	
	opr_src.val=top.val;
	operand_write(&opr_src);

	cpu.esp+=4;
}

make_instr_impl_1op(pop,r,v)

/*
make_instr_func(pop_2eax_v){
	OPERAND src,r;
	src.data_size=data_size;
	src.addr=cpu.esp;
	src.type=OPR_MEM;
	src.sreg=SREG_SS;
	
	operand_read(&src);

	r.data_size=data_size;
	r.type=OPR_REG;
	r.addr=REG_EAX;
	r.val=src.val;
	operand_write(&r);

	cpu.esp+=4;

	return 1;
}

make_instr_func(pop_2ecx_v){
	OPERAND src,r;
	src.data_size=data_size;
	src.addr=cpu.esp;
	src.type=OPR_MEM;
	src.sreg=SREG_SS;
	operand_read(&src);

	r.data_size=data_size;
	r.type=OPR_REG;
	r.addr=REG_ECX;
	r.val=src.val;
	operand_write(&r);

	cpu.esp+=4;

	return 1;
}

make_instr_func(pop_2edx_v){
	OPERAND src,r;
	src.data_size=data_size;
	src.addr=cpu.esp;
	src.type=OPR_MEM;
	src.sreg=SREG_SS;
	operand_read(&src);

	r.data_size=data_size;
	r.type=OPR_REG;
	r.addr=REG_EDX;
	r.val=src.val;
	operand_write(&r);

	cpu.esp+=4;

	return 1;
}

make_instr_func(pop_2ebx_v){
	OPERAND src,r;
	src.data_size=data_size;
	src.addr=cpu.esp;
	src.type=OPR_MEM;
	src.sreg=SREG_SS;
	operand_read(&src);

	r.data_size=data_size;
	r.type=OPR_REG;
	r.addr=REG_EBX;
	r.val=src.val;
	operand_write(&r);

	cpu.esp+=4;

	return 1;
}

make_instr_func(pop_2esp_v){
	OPERAND src,r;
	src.data_size=data_size;
	src.addr=cpu.esp;
	src.type=OPR_MEM;
	src.sreg=SREG_SS;
	operand_read(&src);

	r.data_size=data_size;
	r.type=OPR_REG;
	r.addr=REG_ESP;
	r.val=src.val;
	operand_write(&r);

	cpu.esp+=4;

	return 1;
}

make_instr_func(pop_2ebp_v){
	OPERAND src,r;
	src.data_size=data_size;
	src.addr=cpu.esp;
	src.type=OPR_MEM;
	src.sreg=SREG_SS;
	operand_read(&src);

	r.data_size=data_size;
	r.type=OPR_REG;
	r.addr=REG_EBP;
	r.val=src.val;
	operand_write(&r);

	cpu.esp+=4;

	return 1;
}

make_instr_func(pop_2esi_v){
	OPERAND src,r;
	src.data_size=data_size;
	src.addr=cpu.esp;
	src.type=OPR_MEM;
	src.sreg=SREG_SS;
	operand_read(&src);

	r.data_size=data_size;
	r.type=OPR_REG;
	r.addr=REG_ESI;
	r.val=src.val;
	operand_write(&r);

	cpu.esp+=4;

	return 1;
}

make_instr_func(pop_2edi_v){
	OPERAND src,r;
	src.data_size=data_size;
	src.addr=cpu.esp;
	src.type=OPR_MEM;
	src.sreg=SREG_SS;
	operand_read(&src);

	r.data_size=data_size;
	r.type=OPR_REG;
	r.addr=REG_EDI;
	r.val=src.val;
	operand_write(&r);
	
	cpu.esp+=4;


	return 1;
}
*/
