#include "cpu/exec/template-start.h"

#define instr cmp

static void do_execute() {
	Log("%s\n%x\n",REG_NAME(op_dest->reg),op_src->val);
	if (REG(op_dest->reg)-op_src->val==0) {
		cpu.EFLAGS.ZF = 1;
	} else {
		cpu.EFLAGS.ZF = 0;
		if (REG(op_dest->reg)-op_src->val<0) {
			cpu.EFLAGS.CF = 1;
		}else{
			cpu.EFLAGS.CF = 0;
		}
	}

	print_asm_template2();
}

make_instr_helper(si2rm)

#include "cpu/exec/template-end.h"
