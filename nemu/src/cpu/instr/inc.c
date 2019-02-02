#include "cpu/instr.h"

static void instr_execute_1op(){
	operand_read(&opr_src);
	uint32_t four_bits_low=opr_src.val&0xF;

	uint32_t origin_CF=cpu.eflags.CF;
	opr_src.val=alu_add(0x1,sign_ext(opr_src.val,data_size),data_size);
	cpu.eflags.CF=origin_CF;

	if(four_bits_low==0xF)
		cpu.eflags.AF=0x1;
	else
		cpu.eflags.AF=0x0;

	operand_write(&opr_src);
}

make_instr_impl_1op(inc,rm,v)
make_instr_impl_1op(inc,r,v)

make_instr_impl_1op(inc,eax,v)
make_instr_impl_1op(inc,ecx,v)
make_instr_impl_1op(inc,edx,v)
make_instr_impl_1op(inc,ebx,v)
make_instr_impl_1op(inc,esp,v)
make_instr_impl_1op(inc,ebp,v)
make_instr_impl_1op(inc,esi,v)
make_instr_impl_1op(inc,edi,v)

