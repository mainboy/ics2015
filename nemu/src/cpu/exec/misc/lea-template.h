#include "cpu/exec/template-start.h"

#define instr lea

static void do_execute() {
	Log("%x\n",op_dest->val==REG(op_dest->reg));
	Log("%x\n",op_src->val);
	if (op_src->size == DATA_BYTE)
		op_dest->val = op_src->addr;
	else 
		op_dest->val = (uint16_t)(op_src->addr&0x0000ffff);

	print_asm_template2();
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
