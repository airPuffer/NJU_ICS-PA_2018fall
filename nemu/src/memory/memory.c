#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "device/mm_io.h"
#include <memory.h>
#include <memory/cache.h>

extern CacheLine cache[];
uint8_t hw_mem[MEM_SIZE_B];

uint32_t hw_mem_read(paddr_t paddr, size_t len) {
	uint32_t ret = 0;
	memcpy(&ret, hw_mem + paddr, len);
	//printf("%x\n",len);	
	//printf("%x\n\n",ret);
	return ret;
}

void hw_mem_write(paddr_t paddr, size_t len, uint32_t data) {
	memcpy(hw_mem + paddr, &data, len);
}

uint32_t paddr_read(paddr_t paddr, size_t len) {
	uint32_t ret = 0;
#ifdef CACHE_ENABLED
	ret=cache_read(paddr,len,cache);
#else
	if(is_mmio(paddr)==-1){
		ret = hw_mem_read(paddr, len);
	}
	else{
		ret = mmio_read(paddr,len,is_mmio(paddr));
	}
#endif
	return ret;
}

void paddr_write(paddr_t paddr, size_t len, uint32_t data) {
#ifdef CACHE_ENABLED
	cache_write(paddr,len,data,cache);
#else
	if(is_mmio(paddr)==-1){
		hw_mem_write(paddr, len, data);
	}
	else{
		mmio_write(paddr,len,data,is_mmio(paddr));	
	}
#endif
}


uint32_t laddr_read(laddr_t laddr, size_t len) {
	assert(len ==1 || len ==2 ||len == 4);
#ifdef IA32_PAGE
	//printf("%x\n",laddr);
//printf("laddr ====%x\n",laddr);
//printf("cr0.PE= %x   ======    \n", cpu.cr0.PE);
//printf("cr0.PG ==== %x\n",cpu.cr0.PG);
	uint32_t paddr=laddr;
	if(cpu.cr0.PG==1&&cpu.cr0.PE==1){
		if(((laddr&0xFFF)+len)>0x1000){
			//printf("laddr == %x,len == %x\n",laddr,len);
			//assert(0);
			uint32_t data_l=0x0,data_h=0x0;
			size_t len_l,len_h;
			len_h=(laddr&0xFFF)+len-0x1000;
			len_l=len-len_h;
			if(len_l==0x3){
				uint32_t data_l_1,data_l_2;
				size_t len_l_1=0x1,len_l_2=0x2;
				data_l_1=laddr_read(laddr,len_l_1);
				data_l_2=laddr_read(laddr+0x1,len_l_2);
				data_l=data_l_1|(data_l_2<<8);
			}
			else{
				data_l=laddr_read(laddr,len_l);
			}
			if(len_h==0x3){
				uint32_t data_h_1,data_h_2;
				size_t len_h_1=0x1,len_h_2=0x2;
				data_h_1=laddr_read(laddr+len_l,len_h_1);
				data_h_2=laddr_read(laddr+len_l+0x1,len_h_2);
				data_h=data_h_1|(data_h_2<<8);
			}
			else{
				data_h=laddr_read(laddr+len_l,len_h);
			}
			return data_l|(data_h<<(0x8*len_l));
		}
		else
			paddr=page_translate(laddr);
	}
	//printf("read laddr >> paddr: %x >> %x\n\n",laddr,paddr);
	return paddr_read(paddr,len);
#else
	return paddr_read(laddr, len);
#endif
}

void laddr_write(laddr_t laddr, size_t len, uint32_t data) {
#ifdef IA32_PAGE
	uint32_t paddr=laddr;
	//printf("%x\n     ===",laddr);
	//printf("edi  === %x\n",cpu.edi);
	//assert(laddr<0xc0092010 || laddr > 0xc7000000);
	//printf("cr0 = %x   ======    ", cpu.cr0.PG);
	if(cpu.cr0.PG==1&&cpu.cr0.PE==1){
		if(((laddr&0xFFF)+len)>0x1000){
			size_t len_l,len_h;
			len_h=(laddr&0xFFF)+len-0x1000;
			len_l=len-len_h;
			if(len_l==0x3){
				laddr_write(laddr,1,data);
				laddr_write(laddr+1,2,data>>8);
			}
			else{
				laddr_write(laddr,len_l,data);
			}
			if(len_h==0x3){
				laddr_write(laddr+len_l,1,data>>(8*len_l));
				laddr_write(laddr+len_l+1,2,data>>(8*(len_l+1)));
			}
			else{
				laddr_write(laddr+len_l,len_h,data>>(8*len_l));
			}
			return;
		}
		else
			paddr=page_translate(laddr);
	//printf("had open     ");
	//assert(0);
 	}
	//printf("Write laddr 0x%x, Paddr: %x ,data: %x\n\n",laddr, paddr, data);
	paddr_write(paddr,len,data);
#else
	paddr_write(laddr, len, data);
#endif
}


uint32_t vaddr_read(vaddr_t vaddr, uint8_t sreg, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
#ifndef IA32_SEG
	return laddr_read(vaddr, len);
#else
	uint32_t laddr=vaddr;
	if(cpu.cr0.PE==1){
		laddr=segment_translate(vaddr,sreg);
	}
	assert(laddr==vaddr);
	return laddr_read(laddr,len);
#endif
}

void vaddr_write(vaddr_t vaddr, uint8_t sreg, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
#ifndef IA32_SEG
	laddr_write(vaddr, len, data);
#else
	uint32_t laddr=vaddr;
	if(cpu.cr0.PE==1){
		laddr=segment_translate(vaddr,sreg);
	}
	assert(laddr==vaddr);
	laddr_write(laddr,len,data);
#endif
}

void init_mem() {
	// clear the memory on initiation
	init_cache();
	memset(hw_mem, 0, MEM_SIZE_B);

#ifdef TLB_ENABLED
	make_all_tlb();
	init_all_tlb();
#endif
}

uint32_t instr_fetch(vaddr_t vaddr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return vaddr_read(vaddr, SREG_CS, len);
}

uint8_t * get_mem_addr() {
	return hw_mem;
}
