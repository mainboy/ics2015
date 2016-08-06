#include "cpu/exec/template-start.h"

#define instr lea

static void do_execute() {
	Log("%x\n",op_dest->val==REG(op_dest->reg));
	Log("%s\n",REG_NAME(op_dest->reg));
	if (op_src->size == DATA_BYTE)
		op_dest->val = op_src->addr;
	else 
		op_dest->val = (uint16_t)(op_src->addr&0x0000ffff);

	print_asm_template2();
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
