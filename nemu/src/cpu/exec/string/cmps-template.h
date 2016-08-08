#include "cpu/exec/template-start.h"

#define instr cmps

#define eflags(tmp, des, src);\
	cpu.EFLAGS.CF= des < src;\
        cpu.EFLAGS.ZF= (tmp==0);\
        cpu.EFLAGS.SF= (MSB((DATA_TYPE_S)tmp) == 1);\
        cpu.EFLAGS.OF= (MSB(des)!=MSB(src)) && (MSB(tmp)==MSB(src));\
        cpu.EFLAGS.PF= 1;\
	while(tmp){\
		cpu.EFLAGS.PF = !cpu.EFLAGS.PF;\
		tmp = tmp & (tmp-1);\
	}


make_helper(concat(cmps_m_, SUFFIX)) {
	uint32_t des = MEM_R(reg_l(R_ESI));
	uint32_t src = MEM_R(reg_l(R_EDI));
	uint32_t result = des-src;

	eflags(result,des,src);
	if (cpu.EFLAGS.DF) {
		reg_l(R_EDI) -= DATA_BYTE;
		reg_l(R_ESI) -= DATA_BYTE;
	} else {
		reg_l(R_EDI) += DATA_BYTE;
		reg_l(R_ESI) += DATA_BYTE;
	}

	print_asm("cmps");
	return 1;
}

#include "cpu/exec/template-end.h"
