#include "cpu/exec/template-start.h"

#define instr lea

static void do_execute() {
	Log("%x\n%x\n",op_src->val, op_dest->val);
	Log("ecx %x\n eax %x\n",cpu.eax, cpu.ecx);
	

	panic("Please");
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
