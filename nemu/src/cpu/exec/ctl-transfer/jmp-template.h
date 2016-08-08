#include "cpu/exec/template-start.h"

#define instr jmp

make_helper(concat(jmp_i_, SUFFIX)) {
	cpu.eip = cpu.eip + op_src->val;
	if (DATA_BYTE == 2) {
		cpu.eip &= 0x0000ffff;
	}

	print_asm_template1();
	cpu.eip -= 1;

	return 1;
}

make_helper(concat(jmp_rm_, SUFFIX)) {
	cpu.eip = op_src->val;
	if (DATA_BYTE == 2) {
		cpu.eip &= 0x0000ffff;
	}

	print_asm_template1();
	cpu.eip -= 1;

	return 1;
}

#include "cpu/exec/template-end.h"
