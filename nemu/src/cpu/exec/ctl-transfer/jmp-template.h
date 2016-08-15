#include "cpu/exec/template-start.h"

#define instr jmp

static void do_execute() {
	if (op_src->type == OP_TYPE_IMM) {
		cpu.eip = cpu.eip + op_src->val;
	} else {
		cpu.eip = op_src->val;
		cpu.eip -= 2;
	}

	if (DATA_BYTE == 2) {
		cpu.eip &= 0x0000ffff;
	}

	print_asm_template1();

}

make_instr_helper(i)
make_instr_helper(rm)

make_helper(concat(ljmp_, SUFFIX)) {
	cpu.eip = instr_fetch(eip+1, 4);
	cpu.cs = instr_fetch(eip+5, 2);

	print_asm("ljmp" str(SUFFIX) " $0x%x,$0x%x", cpu.cs, cpu.eip);
	
	return 0;
}


#include "cpu/exec/template-end.h"
