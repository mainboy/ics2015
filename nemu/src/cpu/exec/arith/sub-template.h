#include "cpu/exec/template-start.h"

#define instr sub

static void do_execute() {
	panic("Please Implement me.");
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
