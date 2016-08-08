#include "cpu/exec/template-start.h"

#define instr ret

make_helper(concat(ret_, SUFFIX)) {
	cpu.eip = MEM_R(cpu.esp);
	cpu.esp += DATA_BYTE;
	if (DATA_BYTE == 2) 
		cpu.eip = cpu.eip & 0x0000ffff;

	print_asm("ret");
	cpu.eip -= 1;

	return 1;
}

make_helper(concat(ret_i_, SUFFIX)) {
	cpu.eip = MEM_R(cpu.esp);
	cpu.esp += DATA_BYTE;
	if (DATA_BYTE == 2) 
		cpu.eip = cpu.eip & 0x0000ffff;

	Log("%x\n", op_src->val);
	cpu.esp += op_src->val;

	panic("Please implement me");

	print_asm("ret");
	cpu.eip -= 1;

	return 1;
}

#include "cpu/exec/template-end.h"
