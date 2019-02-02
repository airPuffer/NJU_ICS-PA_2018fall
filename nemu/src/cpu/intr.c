#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void raise_intr(uint8_t intr_no) {
#ifdef IA32_INTR
	//printf("Please implement raise_intr()");
	//assert(0);

	//push EFlags
	OPERAND m_eflags;
	m_eflags.val=cpu.eflags.val;
	m_eflags.data_size=32;
	cpu.esp-=4;
	m_eflags.addr=cpu.esp;
	m_eflags.type=OPR_MEM;
	m_eflags.sreg=SREG_SS;
	operand_write(&m_eflags);

	//push CS
	OPERAND m_cs;
	m_cs.val=cpu.cs.val;
	m_cs.data_size=32;
	cpu.esp-=4;
	m_cs.addr=cpu.esp;
	m_cs.type=OPR_MEM;
	m_cs.sreg=SREG_SS;
	operand_write(&m_cs);

	//push EIP
	OPERAND m_eip;
	m_eip.val=cpu.eip;
	m_eip.data_size=32;
	cpu.esp-=4;
	m_eip.addr=cpu.esp;
	m_eip.type=OPR_MEM;
	m_eip.sreg=SREG_SS;
	operand_write(&m_eip);
	
	//find IDT entry
	GateDesc gateDesc;
	uint32_t gateDesc_addr=cpu.idtr.base+intr_no*8;

	gateDesc.val[0]=laddr_read(gateDesc_addr,4);
	gateDesc.val[1]=laddr_read(gateDesc_addr+4,4);
	
	//printf("base:%x ==== no:%x\n",cpu.idtr.base,intr_no);
	//assert(0); 
	//clear IF
	if(gateDesc.type==0xE)
		cpu.eflags.IF=0x0;
	
	//set EIP
	//assert(gateDesc.selector<6);
	//cpu.eip=cpu.segReg[gateDesc.selector].base+gateDesc.offset_15_0		+(gateDesc.offset_31_16<<16);

	SegDesc segDesc;
	uint32_t segDesc_addr=cpu.gdtr.base+gateDesc.selector*8;

	segDesc.val[0]=laddr_read(segDesc_addr,4);
	segDesc.val[1]=laddr_read(segDesc_addr+4,4);
	
	cpu.eip=(segDesc.base_15_0|(segDesc.base_23_16<<16)|(segDesc.base_31_24<<24))+gateDesc.offset_15_0+(gateDesc.offset_31_16<<16);
	
#endif
}

void raise_sw_intr(uint8_t intr_no) {
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
