#include "cpu/instr.h"
#include "device/port_io.h"
make_instr_func(out_b){
	OPERAND al;
	al.data_size=8;
	al.type=OPR_REG;
	al.addr=REG_AL;
	operand_read(&al);

	OPERAND port;
	port.data_size=16;
	port.type=OPR_REG;
	port.addr=REG_DX;
	operand_read(&port);

	pio_write(port.val,1,al.val);	
	return 1;
}

make_instr_func(out_v){
	OPERAND eax;
	eax.data_size=data_size;
	eax.type=OPR_REG;
	eax.addr=REG_EAX;
	operand_read(&eax);

	OPERAND port;
	port.data_size=16;
	port.type=OPR_REG;
	port.addr=REG_DX;
	operand_read(&port);

	pio_write(port.val,data_size/8,eax.val);	
	return 1;
}
