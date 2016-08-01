#include "cpu/exec/template-start.h"

#define instr call

static void do_execute() {
	if (DATA_BYTE == 2){
		cpu.eip = (cpu.eip+op_src->val) & 0x0000ffff;
	} else if (DATA_BYTE == 4) {
		cpu.eip = cpu.eip+op_src->val;
	}

	print_asm("call" " 0x%x", cpu.eip+1);
}

make_instr_helper(i)

#include "cpu/exec/template-end.h"
