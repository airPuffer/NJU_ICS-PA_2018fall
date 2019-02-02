#include "cpu/instr.h"

make_instr_func(iret){
	
	//pop EIP	
	OPERAND m_eip;
	m_eip.data_size=32;
	m_eip.addr=cpu.esp;
	m_eip.type=OPR_MEM;
	m_eip.sreg=SREG_SS;
	operand_read(&m_eip);
	cpu.esp+=4;
	cpu.eip=m_eip.val;

	//pop CS
	OPERAND m_cs;
	m_cs.data_size=32;
	m_cs.addr=cpu.esp;
	m_cs.type=OPR_MEM;
	m_cs.sreg=SREG_SS;
	operand_read(&m_cs);
	cpu.esp+=4;

	cpu.cs.val=m_cs.val;
	//load_sreg(1);
	//assert(0);

	//pop Eflags
	OPERAND m_eflags;
	m_eflags.data_size=32;
	m_eflags.addr=cpu.esp;
	m_eflags.type=OPR_MEM;
	m_eflags.sreg=SREG_SS;
	operand_read(&m_eflags);
	cpu.esp+=4;
	cpu.eflags.val=m_eflags.val;
	
	return 0;
}
