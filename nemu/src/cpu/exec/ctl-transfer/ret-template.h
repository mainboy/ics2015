#include "cpu/exec/template-start.h"

#define instr ret

/*
static void do_execute() {
	cpu.eip = MEM_R(cpu.esp);
	cpu.esp += DATA_BYTE;
	if (DATA_BYTE == 2) 
		cpu.eip = cpu.eip & 0x0000ffff;

	Log("eip=%x\n",cpu.eip);
	cpu.eip -= DATA_BYTE;

	print_asm_template1();
}
*/

make_helper(concat(ret_, SUFFIX)) {
	panic("hh");
	return 1;
}

#include "cpu/exec/template-end.h"
