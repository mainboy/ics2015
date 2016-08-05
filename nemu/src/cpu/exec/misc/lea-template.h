#include "cpu/exec/template-start.h"

#define instr lea

static void do_execute() {
	Log("%x\n%x\n",op_src->val, op_dest->val);
	Log("%s eax %x\n",REG_NAME(op_dest->reg), cpu.eax);
	
	REG(op_dest->reg) = op_src->val;

	panic("Please");
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
