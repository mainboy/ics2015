#include "cpu/exec/template-start.h"

#define instr ret

static void do_execute() {
	cpu.eip = MEM_R(cpu.esp);
	Log("%x\n",cpu.esp==reg_l(R_ESP));
	cpu.esp += DATA_BYTE;
	Log("%x\n",cpu.esp==reg_l(R_ESP));
	if (DATA_BYTE == 2) 
		cpu.eip = cpu.eip & 0x0000ffff;

	cpu.eip -= 1;

	print_asm_template1();
}

make_instr_helper(i)

#include "cpu/exec/template-end.h"
