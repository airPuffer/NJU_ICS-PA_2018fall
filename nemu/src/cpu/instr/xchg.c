#include "cpu/instr.h"

static void instr_execute_2op(){
	operand_read(&opr_dest);
	operand_read(&opr_src);
	uint32_t temp=opr_dest.val;
	opr_dest.val=opr_src.val;
	opr_src.val=temp;
	operand_write(&opr_dest);
	operand_write(&opr_src);
}

make_instr_impl_2op(xchg,ecx,eax,v)
make_instr_impl_2op(xchg,edx,eax,v)
make_instr_impl_2op(xchg,ebx,eax,v)
make_instr_impl_2op(xchg,esp,eax,v)
make_instr_impl_2op(xchg,ebp,eax,v)
make_instr_impl_2op(xchg,esi,eax,v)
make_instr_impl_2op(xchg,edi,eax,v)

make_instr_func(xchg_rm2r_b){
	OPERAND r,rm;
	r.data_size=8;
	rm.data_size=8;
	int len=1;
	len+=modrm_r_rm(eip+1,&r,&rm);
	operand_read(&r);
	operand_read(&rm);

	uint8_t temp=r.val;
	r.val=rm.val;
	rm.val=temp;
	operand_write(&r);
	operand_write(&rm);

	return len;
}

make_instr_func(xchg_rm2r_v){
	OPERAND r,rm;
	r.data_size=data_size;
	rm.data_size=data_size;
	int len=1;
	len+=modrm_r_rm(eip+1,&r,&rm);
	operand_read(&r);
	operand_read(&rm);

	uint32_t temp=r.val;
	r.val=rm.val;
	rm.val=temp;
	operand_write(&r);
	operand_write(&rm);

	return len;
}
