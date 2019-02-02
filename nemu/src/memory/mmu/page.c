#include "cpu/cpu.h"
#include "memory/memory.h"
#include "memory/mmu/page.h"

extern uint8_t hw_mem[];
// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr) {
#ifndef TLB_ENABLED
	PDE *page_DIR_ENTRY=(PDE *)((cpu.cr3.PDBR<<12)+(uint32_t)hw_mem);	
	page_DIR_ENTRY+=((laddr>>22)&0x3FF);
	assert(page_DIR_ENTRY->present==1);
	PTE *page_TBL_ENTRY=(PTE *)((page_DIR_ENTRY->page_frame<<12)+(uint32_t)hw_mem);
	page_TBL_ENTRY+=((laddr>>12)&0x3FF);
	assert(page_TBL_ENTRY->present==1);

	return (page_TBL_ENTRY->page_frame<<12)|(laddr&0xFFF);

	/*
	uint32_t paddr = laddr & 0xFFF;
	
	uint32_t dir = (laddr >> 22) & 0x3FF;
	uint32_t page = (laddr >> 12) & 0x3FF;
	
	uint32_t pde_addr = (cpu.cr3.val & 0xFFFFF000) + (dir << 2);
	PDE pde;
	pde.val= paddr_read(pde_addr,4);

	uint32_t pte_addr = (pde.val & 0xFFFFF000) + (page << 2);
	PTE pte;
	pte.val = paddr_read(pte_addr,4);
	
	paddr += (pte.val & 0xFFFFF000);
	assert(pde.present == 1 && pte.present == 1);
	return paddr;*/
#else	
	return tlb_read(laddr) | (laddr & PAGE_MASK);
#endif
}
