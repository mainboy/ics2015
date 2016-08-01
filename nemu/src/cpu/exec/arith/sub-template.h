#include "cpu/exec/template-start.h"

#define instr sub

static void do_execute() {
	Log("%x\n%d\n", op_dest->reg,REG(op_dest->reg));
	//OPERAND_W(op_dest, op_src);
	print_asm_template2();
	panic("Please Implement me.");
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(si2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
