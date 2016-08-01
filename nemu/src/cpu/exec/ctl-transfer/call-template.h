#include "cpu/exec/template-start.h"

#define instr call

static void do_execute() {
	Log("%x\n",op_src->val);
	panic("Please Implement me.");
}


make_instr_helper(i)


#include "cpu/exec/template-end.h"
