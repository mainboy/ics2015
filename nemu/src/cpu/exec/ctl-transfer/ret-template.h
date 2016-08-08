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
	uint16_t imm = instr_fetch(cpu.eip+1, 2);
	cpu.eip = MEM_R(cpu.esp);
	cpu.esp += DATA_BYTE;
	if (DATA_BYTE == 2) 
		cpu.eip = cpu.eip & 0x0000ffff;

	cpu.esp += imm;

	print_asm("ret %x", imm);
	cpu.eip -= 1;

	return 1;
}

#include "cpu/exec/template-end.h"
