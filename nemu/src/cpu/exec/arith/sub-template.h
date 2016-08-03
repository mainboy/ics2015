#include "cpu/exec/template-start.h"

#define instr sub

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
		OPERAND_W(op_dest, REG(op_dest->reg)-op_src->simm);
		DATA_TYPE tmp = REG(op_dest->reg) - op_src->simm;
		eflags(tmp, REG(op_dest->reg), op_src->simm);
	} else {
		OPERAND_W(op_dest,REG(op_dest->reg)-op_src->val);
		DATA_TYPE tmp = REG(op_dest->reg) - op_src->val;
		eflags(tmp, REG(op_dest->reg), op_src->val);
	}
	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(si2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
