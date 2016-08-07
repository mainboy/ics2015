#include "cpu/exec/template-start.h"

#define instr lea

static void do_execute() {
	if (op_src->size == DATA_BYTE)
		OPERAND_W(op_dest, op_src->addr);
	else 
		OPERAND_W(op_dest, (uint16_t)(op_src->addr&0x0000ffff));

	print_asm_template2();
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
