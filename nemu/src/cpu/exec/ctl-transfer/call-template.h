#include "cpu/exec/template-start.h"

#define instr call

static void do_execute() {
	Log("%x\n",cpu.eip);
	cpu.esp -= DATA_BYTE;
	MEM_W(cpu.esp, cpu.eip + DATA_BYTE);
	uint32_t test = MEM_R(cpu.esp);
	Log("%x\n",test);

	cpu.eip = (cpu.eip+op_src->val);
	if (DATA_BYTE == 2)
		cpu.eip = cpu.eip&0x0000ffff;

	print_asm_template1();
}

make_instr_helper(i)

#include "cpu/exec/template-end.h"
