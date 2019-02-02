#include "cpu/instr.h"

make_instr_func(popa){
	pop_r_v(eip,0x57);
	pop_r_v(eip,0x56);
	pop_r_v(eip,0x55);

	cpu.esp+=4;

	pop_r_v(eip,0x53);
	pop_r_v(eip,0x52);
	pop_r_v(eip,0x51);
	pop_r_v(eip,0x50);

	return 1;

}
