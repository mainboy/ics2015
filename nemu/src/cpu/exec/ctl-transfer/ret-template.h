#include "cpu/exec/template-start.h"

#define instr ret

static void do_execute() {
	cpu.eip = swaddr_read(cpu.esp, DATA_BYTE);
	cpu.esp += DATA_BYTE;
	if (DATA_BYTE == 2) 
		cpu.eip = cpu.eip & 0x0000ffff;

	Log("%x\n",cpu.eip);
	print_asm_template1();
}

make_instr_helper(i)

#include "cpu/exec/template-end.h"
