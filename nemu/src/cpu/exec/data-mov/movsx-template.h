#include "cpu/exec/template-start.h"

#define instr movsx

static void do_execute() {
	
	OPERAND_W(op_dest, (DATA_TYPE_S)op_src->val);
	print_asm_template2();
	
	//panic("Please implement me");
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
