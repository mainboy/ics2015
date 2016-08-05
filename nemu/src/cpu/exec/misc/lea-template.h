#include "cpu/exec/template-start.h"

#define instr lea

static void do_execute() {
	Log("%x\n%x\n",op_src->val,op_src->addr);
	
	if (op_src->size == DATA_BYTE)
		op_dest->val = op_src->val;
	else 
		op_dest->val = (uint16_t)(op_src->val&0x0000ffff);
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
