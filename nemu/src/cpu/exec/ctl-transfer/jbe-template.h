#include "cpu/exec/template-start.h"

#define instr jbe

static void do_execute() {
	if(cpu.EFLAGS.CF==1 || cpu.EFLAGS.ZF==1) {
		cpu.eip = cpu.eip+(DATA_TYPE_S)op_src->val;
		Log("%x\n",cpu.eip);
		if(DATA_BYTE == 2) {
			cpu.eip = cpu.eip&0x0000ffff;
		}
	}

	print_asm_template1();
	panic("Please");
}

make_instr_helper(i)

#include "cpu/exec/template-end.h"
