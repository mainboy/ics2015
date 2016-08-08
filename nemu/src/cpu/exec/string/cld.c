#include "cpu/exec/helper.h"

#define instr cld

make_helper(cld) {
	cpu.EFLAGS.DF = 0;
	print_asm("cld");
	return 1;
}

#include "cpu/exec/template-end.h"
