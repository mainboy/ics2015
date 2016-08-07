#include "cpu/exec/template-start.h"

#define instr movsx

static void do_execute() {
	
	REG(op_dest->reg) = (DATA_TYPE_S)op_src->val;
	Log("%x\n",op_src->size);
	print_asm_template2();
	
	panic("Please implement me");
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
