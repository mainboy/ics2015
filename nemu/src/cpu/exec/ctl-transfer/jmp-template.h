#include "cpu/exec/template-start.h"

#define instr jmp

static void do_execute() {
	Log("%x\n",op_src->val);
	panic("Please");
}


make_instr_helper(i)

#include "cpu/exec/template-end.h"
