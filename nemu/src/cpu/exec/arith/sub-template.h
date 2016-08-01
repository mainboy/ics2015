#include "cpu/exec/template-start.h"

#define instr sub

static void do_execute() {
	Log("%x\n", REG(op_dest->reg) - op_src->simm);
	OPERAND_W(op_dest,REG(op_dest->reg)-op_src->simm);
	print_asm_template2();
	panic("Please Implement me.");
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(si2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
