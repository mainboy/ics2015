#include "cpu/exec/template-start.h"

#define instr test

static void do_execute() {
	Log("%s\n%x\n%x\n",REG_NAME(op_dest->reg),REG(op_src->reg),REG(op_dest->reg));
	panic("Please implement me.");
}

make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"
