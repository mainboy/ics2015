#include "cpu/exec/template-start.h"

#define instr lea

static void do_execute() {
	if (op_src->size == DATA_BYTE)
		REG(op_dest->reg) = op_src->addr;
	else 
		REG(op_dest->reg) = (uint16_t)(op_src->addr&0x0000ffff);

	print_asm_template2();
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
