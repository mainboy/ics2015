#include "cpu/exec/template-start.h"

#define instr movzx

static void do_execute() {
	
	REG(op_dest->reg) = (DATA_TYPE)op_src->val;
	print_asm_template2();

	panic("Please ");
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
