#include "cpu/exec/template-start.h"

#define instr movs

make_helper(concat(movs_m_, SUFFIX)) {
	MEM_W(reg_l(R_EDI), MEM_R(reg_l(R_ESI)));
	if (cpu.EFLAGS.DF) {
		reg_l(R_EDI) -= DATA_BYTE;
		reg_l(R_ESI) -= DATA_BYTE;
	} else {
		reg_l(R_EDI) += DATA_BYTE;
		reg_l(R_ESI) += DATA_BYTE;
	}

	print_asm("movs");
	return 1;
}

#include "cpu/exec/template-end.h"
