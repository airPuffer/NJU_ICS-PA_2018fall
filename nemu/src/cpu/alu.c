#include "cpu/cpu.h"

uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_add(src, dest, data_size);
#else
	uint32_t res=0;
	res=dest+src;

	uint32_t result=res,temp_dest=dest,temp_src=src;

	result=sign_ext(res&(0xFFFFFFFF>>(32-data_size)),data_size);
	temp_src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.CF=result<temp_src;

	int bit_count=0;
	for(int i=0;i<=7;i++)
		if((res>>i)&0x1)
			bit_count++;
	if(bit_count%2)
		cpu.eflags.PF=0;
	else cpu.eflags.PF=1;

	result=res&(0xFFFFFFFF>>(32-data_size));
	cpu.eflags.ZF=(result==0);

	result=sign_ext(res&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.SF=sign(result);

	switch(data_size){
		case 8:
			result=sign_ext(res&0xFF,8);
			temp_src=sign_ext(src&0xFF,8);
			temp_dest=sign_ext(dest &0xFF,8);
			break;
		case 16:result=sign_ext(res&0xFFFF,16);
			temp_src=sign_ext(src&0xFFFF,16);
			temp_dest=sign_ext(dest&0xFFFF,16);
			break;
		default:break;
	}
	if(sign(temp_src)==sign(temp_dest)){
		if(sign(temp_src)!=sign(result))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
	}else{
		cpu.eflags.OF=0;
	}

	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
	uint32_t res=0;
	res=src+dest+cpu.eflags.CF;

	uint32_t result=res,temp_src=src,temp_dest=dest;

        result=sign_ext(res&(0xFFFFFFFF>>(32-data_size)),data_size);
	temp_src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	if(cpu.eflags.CF==0){
		cpu.eflags.CF=result<temp_src;
	}
	else{
		cpu.eflags.CF=(result<=temp_src);
	}

	int bit_count=0;
	for(int i=0;i<=7;i++)
		if((res>>i)&0x1)
			bit_count++;
	if(bit_count%2)
		cpu.eflags.PF=0;
	else cpu.eflags.PF=1;

	result=res&(0xFFFFFFFF>>(32-data_size));
	cpu.eflags.ZF=(result==0);

	result=sign_ext(res&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.SF=sign(result);

	switch(data_size){
		case 8:
			result=sign_ext(res&0xFF,8);
			temp_src=sign_ext(src&0xFF,8);
			temp_dest=sign_ext(dest &0xFF,8);
			break;
		case 16:result=sign_ext(res&0xFFFF,16);
			temp_src=sign_ext(src&0xFFFF,16);
			temp_dest=sign_ext(dest&0xFFFF,16);
			break;
		default:break;
	}
	if(sign(temp_src)==sign(temp_dest)){
		if(sign(temp_src)!=sign(result))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
	}else{
		cpu.eflags.OF=0;
	}

	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}


uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_sub(src, dest, data_size);
#else
	uint32_t res=0;
	res=dest-src;

	uint32_t result=res,temp_src=src,temp_dest=dest;

    result=sign_ext(res&(0xFFFFFFFF>>(32-data_size)),data_size);
	temp_src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	temp_dest=sign_ext(dest&(0xFFFFFFFF>>(32-data_size)),data_size);

	if(temp_dest<temp_src)
		cpu.eflags.CF=1;
	else cpu.eflags.CF=0;

	int bit_count=0;
	for(int i=0;i<=7;i++)
		if((res>>i)&0x1)
			bit_count++;
	if(bit_count%2)
		cpu.eflags.PF=0;
	else cpu.eflags.PF=1;

	result=res&(0xFFFFFFFF>>(32-data_size));
	cpu.eflags.ZF=(result==0);

	result=sign_ext(res&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.SF=sign(result);

	switch(data_size){
		case 8:
			result=sign_ext(res&0xFF,8);
			temp_src=sign_ext(src&0xFF,8);
			temp_dest=sign_ext(dest &0xFF,8);
			break;
		case 16:result=sign_ext(res&0xFFFF,16);
			temp_src=sign_ext(src&0xFFFF,16);
			temp_dest=sign_ext(dest&0xFFFF,16);
			break;
		default:break;
	}
	if(sign(temp_src)!=sign(temp_dest)){
		if(sign(temp_dest)!=sign(result))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
	}else{
		cpu.eflags.OF=0;
	}

	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_sbb(src, dest, data_size);
#else
	uint32_t res=0;
	res=dest-src-cpu.eflags.CF;

	uint32_t result=res,temp_src=src,temp_dest=dest;

        result=sign_ext(res&(0xFFFFFFFF>>(32-data_size)),data_size);
	temp_src=sign_ext(src&(0xFFFFFFFF>>(32-data_size)),data_size);
	temp_dest=sign_ext(dest&(0xFFFFFFFF>>(32-data_size)),data_size);
	if(cpu.eflags.CF==0){
		if(temp_dest<temp_src)
			cpu.eflags.CF=1;
		else cpu.eflags.CF=0;
	}
	else{
		if((temp_src&(0xFFFFFFFF>>(32-data_size)))==(0xFFFFFFFF>>(32-data_size)))
			cpu.eflags.CF=1;
		else if(temp_dest<(temp_src+1))
			cpu.eflags.CF=1;
		else cpu.eflags.CF=0;		
	}

	int bit_count=0;
	for(int i=0;i<=7;i++)
		if((res>>i)&0x1)
			bit_count++;
	if(bit_count%2)
		cpu.eflags.PF=0;
	else cpu.eflags.PF=1;

	result=res&(0xFFFFFFFF>>(32-data_size));
	cpu.eflags.ZF=(result==0);

	result=sign_ext(res&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.SF=sign(result);

	switch(data_size){
		case 8:
			result=sign_ext(res&0xFF,8);
			temp_src=sign_ext(src&0xFF,8);
			temp_dest=sign_ext(dest &0xFF,8);
			break;
		case 16:result=sign_ext(res&0xFFFF,16);
			temp_src=sign_ext(src&0xFFFF,16);
			temp_dest=sign_ext(dest&0xFFFF,16);
			break;
		default:break;
	}
	if(cpu.eflags.CF!=0){
		if((temp_dest&(0xFFFFFFFF<<(data_size-1)))!=(0xFFFFFFFF<<(data_size-1)))
			temp_dest=temp_dest+1;
		else if((temp_src&(0xFFFFFFFF>>(33-data_size)))!=(0xFFFFFFFF>>(33-data_size)))
			temp_src=temp_src+1;
		else ;
	}
	if(sign(temp_src)!=sign(temp_dest)){
		if(sign(temp_dest)!=sign(result))
			cpu.eflags.OF=1;
		else
			cpu.eflags.OF=0;
		}else{
			cpu.eflags.OF=0;
		}
		

	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}


uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
	uint64_t product=0;
	product=((uint64_t)src)*((uint64_t)dest);
	switch(data_size){
		case 8:
			if(product&0xFF00){
				cpu.eflags.CF=1;
				cpu.eflags.OF=1;
			}
			else{
			       	cpu.eflags.CF=0;
				cpu.eflags.OF=0;
			}
			break;
		case 16:
			if(product&0xFFFF0000){
				cpu.eflags.CF=1;
				cpu.eflags.OF=1;
			}
			else {
				cpu.eflags.CF=0;
				cpu.eflags.OF=0;
			}
			break;
		case 32:
			if(product&0xFFFFFFFF00000000){
				cpu.eflags.CF=1;
				cpu.eflags.OF=1;
			}
			else {
				cpu.eflags.CF=0;
				cpu.eflags.OF=0;
			}
			break;
	}
	return product;
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
	int64_t product=0;
	product=((int64_t)src)*((int64_t)dest);
	switch(data_size){
		case 8:
			if(product&0xFF00)
				cpu.eflags.CF=1;
			else cpu.eflags.CF=0;
			if((product&0x80)>>7){
				if((product&0xFF00)==0xFF00)
					cpu.eflags.OF=0;
				else cpu.eflags.OF=1;
			}
			else{
				if((product&0xFF00)==0)
					cpu.eflags.OF=0;
				else cpu.eflags.OF=1;
			
			}
			break;
		case 16:
			if(product&0xFFFF0000)
				cpu.eflags.CF=1;
			else cpu.eflags.CF=0;
			if((product&0x8000)>>15){
				if((product&0xFFFF0000)==0xFFFF0000)
					cpu.eflags.OF=0;
				else cpu.eflags.OF=1;
			}
			else{
				if((product&0xFFFF0000)==0)
					cpu.eflags.OF=0;
				else cpu.eflags.OF=1;
			}
			break;
		case 32:
			if(product&0xFFFFFFFF00000000)
				cpu.eflags.CF=1;
			else cpu.eflags.CF=0;
			if((product&0x80000000)>>31){
				if((product&0xFFFFFFFF00000000)==0xFFFFFFFF00000000)
					cpu.eflags.OF=0;
				else cpu.eflags.OF=1;
			}
			else{
				if((product&0xFFFFFFFF00000000)==0)
					cpu.eflags.OF=0;
				else cpu.eflags.OF=1;
			
			}
			break;
	}
	return product;
#endif
}

uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
	dest=dest&(0xFFFFFFFFFFFFFFFF>>(64-data_size));
	src=src&(0xFFFFFFFFFFFFFFFF>>(64-data_size));
	uint32_t res=0;
	res=dest/src;
	return res;
#endif
}

int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
	int32_t res=0;
	res=dest/src;
	return res;
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest) {
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
	uint32_t res=0;
	res=dest%src;
	return res;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest) {
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
	int32_t res=0;
	res=dest%src;
	return res;
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
	uint32_t res=0;
	res=src&dest;
	
	uint32_t result=res;

	cpu.eflags.CF=0;

	int bit_count=0;
	for(int i=0;i<=7;i++)
		if((res>>i)&0x1)
			bit_count++;
	if(bit_count%2)
		cpu.eflags.PF=0;
	else cpu.eflags.PF=1;

	result=res&(0xFFFFFFFF>>(32-data_size));
	cpu.eflags.ZF=(result==0);

	result=sign_ext(res&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.SF=sign(result);

	cpu.eflags.OF=0;

	return res&(0xFFFFFFFF>>(32-data_size));

#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
	uint32_t res=0;
	res=src^dest;
	
	uint32_t result=res;

	cpu.eflags.CF=0;

	int bit_count=0;
	for(int i=0;i<=7;i++)
		if((res>>i)&0x1)
			bit_count++;
	if(bit_count%2)
		cpu.eflags.PF=0;
	else cpu.eflags.PF=1;

	result=res&(0xFFFFFFFF>>(32-data_size));
	cpu.eflags.ZF=(result==0);

	result=sign_ext(res&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.SF=sign(result);

	cpu.eflags.OF=0;

	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
	uint32_t res=0;
	res=src|dest;
	
	uint32_t result=res;

	cpu.eflags.CF=0;

	int bit_count=0;
	for(int i=0;i<=7;i++)
		if((res>>i)&0x1)
			bit_count++;
	if(bit_count%2)
		cpu.eflags.PF=0;
	else cpu.eflags.PF=1;

	result=res&(0xFFFFFFFF>>(32-data_size));
	cpu.eflags.ZF=(result==0);

	result=sign_ext(res&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.SF=sign(result);

	cpu.eflags.OF=0;

	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
	uint32_t res=dest;
	for(int i=1;i<=src;i++)
	{
		cpu.eflags.CF=((res&(0x1<<(data_size-1)))!=0);
		res=res<<1;
	}
	if(src==1){
		cpu.eflags.OF=(cpu.eflags.CF!=((res&(0x1<<(data_size-1))>>(data_size-1))));
	}
	
	uint32_t result=0;

	int bit_count=0;
	for(int i=0;i<=7;i++)
		if((res>>i)&0x1)
			bit_count++;
	if(bit_count%2)
		cpu.eflags.PF=0;
	else cpu.eflags.PF=1;

	result=res&(0xFFFFFFFF>>(32-data_size));
	cpu.eflags.ZF=(result==0);

	result=sign_ext(res&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.SF=sign(result);	

	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
	uint32_t res=dest&(0xFFFFFFFF>>(32-data_size));
	for(int i=1;i<=src;i++)
	{
		cpu.eflags.CF=res&0x1;
		res=res>>1;
	}
	if(src==1){
		cpu.eflags.OF=res&(0x1<<(data_size-1))>>(data_size-1);
	}
	
	uint32_t result=0;

	int bit_count=0;
	for(int i=0;i<=7;i++)
		if((res>>i)&0x1)
			bit_count++;
	if(bit_count%2)
		cpu.eflags.PF=0;
	else cpu.eflags.PF=1;

	result=res&(0xFFFFFFFF>>(32-data_size));
	cpu.eflags.ZF=(result==0);

	result=sign_ext(res&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.SF=sign(result);	

	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);	
#else
	uint32_t res=dest&(0xFFFFFFFF>>(32-data_size));
	uint32_t MSB=0;
	switch(data_size){
		case 8:
			MSB=0x80&dest;
			for(int i=1;i<=src;i++){
				cpu.eflags.CF=res&0x01;
				res=res>>1;
				res=res+MSB;
			}
			break;
		case 16:
			MSB=0x8000&dest;
			for(int i=1;i<=src;i++){
				cpu.eflags.CF=res&0x01;
				res=res>>1;
				res=res+MSB;
			}
			break;
		case 32:
			MSB=0x80000000&dest;
			for(int i=1;i<=src;i++){
				cpu.eflags.CF=res&0x01;
				res=res>>1;
				res=res+MSB;
			}
			break;
	}

	uint32_t result;

	if(src==1)	
		cpu.eflags.OF=0;

	int bit_count=0;
	for(int i=0;i<=7;i++)
		if((res>>i)&0x1)
			bit_count++;
	if(bit_count%2)
		cpu.eflags.PF=0;
	else cpu.eflags.PF=1;

	result=res&(0xFFFFFFFF>>(32-data_size));
	cpu.eflags.ZF=(result==0);

	result=sign_ext(res&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.SF=sign(result);	
		
	return res;
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size) {
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
	uint32_t res=dest;
	for(int i=1;i<=src;i++)
	{
		cpu.eflags.CF=((res&(0x1<<(data_size-1)))!=0);
		res=res<<1;
	}
	if(src==1){
		cpu.eflags.OF=(cpu.eflags.CF!=((res&(0x1<<(data_size-1))>>(data_size-1))));
	}
	
	uint32_t result=0;

	int bit_count=0;
	for(int i=0;i<=7;i++)
		if((res>>i)&0x1)
			bit_count++;
	if(bit_count%2)
		cpu.eflags.PF=0;
	else cpu.eflags.PF=1;

	result=res&(0xFFFFFFFF>>(32-data_size));
	cpu.eflags.ZF=(result==0);

	result=sign_ext(res&(0xFFFFFFFF>>(32-data_size)),data_size);
	cpu.eflags.SF=sign(result);	

	return res&(0xFFFFFFFF>>(32-data_size));
#endif
}
