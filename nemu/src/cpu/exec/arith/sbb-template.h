#include "cpu/exec/template-start.h"

#define instr sbb

#define eflags(tmp, des, src);\
	cpu.EFLAGS.CF= des < src;\
	cpu.EFLAGS.ZF= (tmp==0);\
	cpu.EFLAGS.SF= (MSB((DATA_TYPE_S)tmp) == 1);\
	cpu.EFLAGS.OF= (MSB(des)!=MSB(src)) && (MSB(tmp)==MSB(src));\
	cpu.EFLAGS.PF= 1;\
	while(tmp){\
		cpu.EFLAGS.PF = !cpu.EFLAGS.PF;\
		tmp = tmp & (tmp-1);\
	}\

static void do_execute() {
	if (op_src->type == OP_TYPE_SIMM) {
		OPERAND_W(op_dest, op_dest->val - (op_src->simm+cpu.EFLAGS.CF));
		DATA_TYPE tmp = op_dest->val - (op_src->simm+cpu.EFLAGS.CF);
		eflags(tmp, op_dest->val, (op_src->simm+cpu.EFLAGS.CF));
	} else {
		OPERAND_W(op_dest, op_dest->val - (op_src->val+cpu.EFLAGS.CF));
		DATA_TYPE tmp = op_dest->val - (op_src->val+cpu.EFLAGS.CF);
		eflags(tmp, op_dest->val, (op_src->val+cpu.EFLAGS.CF));
	}
	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(si2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
