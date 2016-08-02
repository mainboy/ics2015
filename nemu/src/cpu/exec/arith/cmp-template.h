#include "cpu/exec/template-start.h"

#define instr cmp

static void do_execute() {
	Log("%s\n%x\n",REG_NAME(op_dest->reg),op_src->val);
	panic("Please Implement me.");
}

make_instr_helper(i2rm)

#include "cpu/exec/template-end.h"
