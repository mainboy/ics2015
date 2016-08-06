#include "cpu/exec/template-start.h"

#define instr ret

make_helper(concat(ret_, SUFFIX)) {
	cpu.eip = MEM_R(cpu.esp);
	cpu.esp += DATA_BYTE;
	if (DATA_BYTE == 2) 
		cpu.eip = cpu.eip & 0x0000ffff;

	Log("eip=%x\n",cpu.eip);
	print_asm_template1();
	cpu.eip -= 1;

	return 1;
}

#include "cpu/exec/template-end.h"
