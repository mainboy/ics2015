#include "cpu/exec/template-start.h"

#define instr push

static void do_execute() {
	if (DATA_BYTE == 2) {
		cpu.esp = cpu.esp - 2;
		MEM_W(cpu.ss.val+cpu.esp, op_src->val);
	} else if (DATA_BYTE == 4) {
		cpu.esp = cpu.esp - 4;
		MEM_W(cpu.ss.val+cpu.esp, op_src->val);
	}
	print_asm_template1();
}

make_instr_helper(rm)
make_instr_helper(r)
make_instr_helper(i)

#include "cpu/exec/template-end.h"
