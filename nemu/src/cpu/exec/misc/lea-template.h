#include "cpu/exec/template-start.h"

#define instr lea

static void do_execute() {
	Log("%x\n%x\n",op_src->val,op_src->addr);
	REG(op_dest->reg) = op_src->addr;
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
