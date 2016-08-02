#include "cpu/exec/template-start.h"

#define instr test

static void do_execute() {
	if (op_src->val & op_dest->val) {
		cpu.EFLAGS.ZF=0;
	}else {
		cpu.EFLAGS.ZF=1;
	}
	cpu.EFLAGS.CF=0;
	cpu.EFLAGS.OF=0;
	print_asm_template2();
}

make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"
