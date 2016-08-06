#include "cpu/exec/template-start.h"

#define instr leave

make_helper(concat(leave_, SUFFIX)) {
	cpu.esp = cpu.ebp;
	cpu.ebp = MEM_R(cpu.esp);
	cpu.esp += DATA_BYTE;
	
	Log("leave %x\n", cpu.eip);
	print_asm_template1();

	return 0;
}

#include "cpu/exec/template-end.h"
