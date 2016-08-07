#include "cpu/exec/template-start.h"

#define instr setne

static void do_execute() {

	if (!cpu.EFLAGS.ZF) {
		if (op_dest->type == OP_TYPE_REG)
			REG(op_dest->reg) = 1;
		else if (op_dest->type == OP_TYPE_MEM)
			OPERAND_W(op_dest, 1);
	} else {
		if (op_dest->type == OP_TYPE_REG)
			REG(op_dest->reg) = 0;
		else if (op_dest->type == OP_TYPE_MEM)
			OPERAND_W(op_dest, 0);
	}

	print_asm_template1();

}

make_instr_helper(rm)

#include "cpu/exec/template-end.h"
