#include "cpu/exec/template-start.h"

#define instr stos

make_helper(concat(stos_m_, SUFFIX)) {
	MEM_W(reg_l(R_EDI), reg_l(R_EAX));
	if (cpu.EFLAGS.DF) {
		reg_l(R_EDI) -= DATA_BYTE;
	} else {
		reg_l(R_EDI) += DATA_BYTE;
	}

	print_asm("stos");
	return 1;
}

#include "cpu/exec/template-end.h"
