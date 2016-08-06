#include "cpu/exec/template-start.h"

#define instr or

#define eflags(tmp, des, src);\
	cpu.EFLAGS.CF= 0;\
        cpu.EFLAGS.ZF= (tmp==0);\
        cpu.EFLAGS.SF= (MSB((DATA_TYPE_S)tmp) == 1);\
        cpu.EFLAGS.OF= 0;\
        cpu.EFLAGS.PF= 1;\
        while(tmp){\
		cpu.EFLAGS.PF = !cpu.EFLAGS.PF;\
		tmp = tmp & (tmp-1);\
	}

static void do_execute () {
	DATA_TYPE result = op_dest->val | op_src->val;
	OPERAND_W(op_dest, result);

	/* TODO: Update EFLAGS. */
	eflags(result, op_dest->val, op_src->val);

	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
