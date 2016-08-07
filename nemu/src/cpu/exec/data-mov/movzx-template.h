#include "cpu/exec/template-start.h"

#define instr movzx

static void do_execute() {
	
	REG(op_dest->reg) = (DATA_TYPE)op_src->val;
	Log("%x %x\n", op_src->size, op_dest->size);
	print_asm_template2();

}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
