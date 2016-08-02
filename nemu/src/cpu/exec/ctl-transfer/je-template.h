#include "cpu/exec/template-start.h"

#define instr je

static void do_execute() {
	Log("%x\n%x\n",op_src->val,DATA_BYTE);
	panic("Please Implement me.");
}

make_instr_helper(i)

#include "cpu/exec/template-end.h"
