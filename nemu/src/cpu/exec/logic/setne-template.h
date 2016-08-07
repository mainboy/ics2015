#include "cpu/exec/template-start.h"

#define instr setne

static void do_execute() {

	Log("%s\n",REG_NAME(op_dest->reg));
	/*
	if (!cpu.EFLAGS.ZF) {
		if (op_dest)
		op_dest->val = 
	}
*/

	print_asm_template1();

	panic("hello");
}

make_instr_helper(rm)

#include "cpu/exec/template-end.h"
