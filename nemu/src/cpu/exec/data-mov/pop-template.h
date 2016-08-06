#include "cpu/exec/template-start.h"

#define instr pop

static void do_execute() {
	REG(op_src->reg) = MEM_R(cpu.esp);
	cpu.esp += DATA_BYTE;

	Log("%s\n",REG_NAME(op_src->reg));
	panic("hello");
	print_asm_template1();
}

make_instr_helper(rm)
make_instr_helper(r)
make_instr_helper(i)

#include "cpu/exec/template-end.h"
