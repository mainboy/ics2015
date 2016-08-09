#include "cpu/exec/template-start.h"

#define instr cwd

make_helper(concat(cwd_, SUFFIX)) {
	if (DATA_BYTE == 2) {
		if (((DATA_TYPE_S)reg_w(R_AX)) < 0) {
			reg_w(R_DX) = 0xffff;
		} else {
			reg_w(R_DX) = 0;
		}
	} else if (DATA_BYTE == 4) {
		if (((DATA_TYPE_S)reg_l(R_EAX)) < 0) {
			reg_l(R_EDX) = 0xffffffff;
		} else {
			reg_l(R_EDX) = 0;
		}
	}

	print_asm("cwd");
	return 1;
}

#include "cpu/exec/template-end.h"
