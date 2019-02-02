#include <stdlib.h>
#include <time.h>
#include "memory/cache.h"
#include "memory/memory.h"


CacheLine cache[1024];

void init_cache(){
	for(int i=0;i<1024;i++)
		cache[i].valid_bit=0;
}

uint32_t cache_read(paddr_t paddr,size_t len,CacheLine *cache){
	srand(time(0));
	uint32_t ret=0;
	uint32_t grp=(paddr>>6)&0x7F;
	uint32_t mark=(paddr>>13)&0x7FFFF;
	uint8_t inaddr=paddr&0x3F;
	int i=0;
	for(;i<8;i++)
		if(cache[grp*8+i].valid_bit==1 &&
	           cache[grp*8+i].mark==mark)
			break;
	if(i==8){
		i=0;
		for(;i<8;i++)
			if(cache[grp*8+i].valid_bit==0)
				break;
		if(i==8)
			i=rand()%8;
		cache[grp*8+i].valid_bit=1;
		cache[grp*8+i].mark=mark;
		memcpy(cache[grp*8+i].data,hw_mem+(paddr&0xFFFFFFC0),64);
	}
	if((len+inaddr)>64){
		size_t extra=len+inaddr-64;
		uint32_t high_ret=cache_read(paddr+len-extra,extra,cache);
		memcpy(&ret,&cache[grp*8+i].data[inaddr],len-extra);
		ret=ret|(high_ret<<((len-extra)*8));
	}
	else
		memcpy(&ret,&cache[grp*8+i].data[inaddr],len);
	return ret;
}

void cache_write(paddr_t paddr,size_t len,uint32_t data,CacheLine *cache){
	uint32_t grp=(paddr>>6)&0x7F;
	uint32_t mark=(paddr>>13)&0x7FFFF;
	uint8_t inaddr=paddr&0x3F;
	int i=0;
	for(;i<8;i++)
		if(cache[grp*8+i].valid_bit==1 &&
	           cache[grp*8+i].mark==mark)
			break;
	if(i<8){
		if((len+inaddr)>64){
			size_t extra=len+inaddr-64;
			memcpy(hw_mem+paddr,&data,len-extra);
			cache_write(paddr+len-extra,extra,data>>((len-extra)*8),cache);
			memcpy(&cache[grp*8+i].data[inaddr],&data,len-extra);
	    }
	    else{
			memcpy(&cache[grp*8+i].data[inaddr],&data,len);
			memcpy(hw_mem+paddr,&data,len);
		}
	}
	else if((len+inaddr)>64){
			size_t extra=len+inaddr-64;
			memcpy(hw_mem+paddr,&data,len-extra);
			cache_write(paddr+len-extra,extra,data>>((len-extra)*8),cache);
	}
	else
		memcpy(hw_mem+paddr,&data,len);
	
}
