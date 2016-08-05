#include "cpu/exec/template-start.h"

#define instr leave

static void do_execute() {
	cpu.esp = cpu.ebp;
	cpu.ebp = MEM_R(cpu.esp);
	cpu.esp += DATA_BYTE;

	//Log("%x\n",cpu.eip);
	//panic("hello world");
	//print_asm_template1();
}

make_instr_helper(i)

#include "cpu/exec/template-end.h"
