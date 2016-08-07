#include "cpu/exec/template-start.h"

#define instr movs

make_helper(concat(movs_rm2rm_, SUFFIX)) {

	return 1;
}

#include "cpu/exec/template-end.h"
