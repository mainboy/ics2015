#include "cpu/exec/template-start.h"

#define instr push

static void do_execute() {
	Log("%d\n%d\n",op_src->reg,op_dest->reg);
	panic("Please Implement me.");
}

make_instr_helper(r)

#include "cpu/exec/template-end.h"
