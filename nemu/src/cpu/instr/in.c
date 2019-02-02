#include "cpu/instr.h"
#include "device/port_io.h"
make_instr_func(in_b){
	OPERAND port;
	port.data_size=16;
	port.type=OPR_REG;
	port.addr=REG_DX;
	operand_read(&port);

	uint8_t data=pio_read(port.val,1);

	OPERAND al;
	al.data_size=8;
	al.type=OPR_REG;
	al.addr=REG_AL;
	al.val=data;
	operand_write(&al);
	return 1;
}

make_instr_func(in_v){
	OPERAND port;
	port.data_size=16;
	port.type=OPR_REG;
	port.addr=REG_DX;
	operand_read(&port);

	uint32_t data=pio_read(port.val,data_size/8);

	OPERAND eax;
	eax.data_size=data_size;
	eax.type=OPR_REG;
	eax.addr=REG_EAX;
	eax.val=data;
	operand_write(&eax);
	return 1;
}
