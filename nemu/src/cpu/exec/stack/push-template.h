#include "cpu/exec/template-start.h"

#define instr push

static void do_execute() {
		if (DATA_BYTE == 2) {
		cpu.esp = cpu.esp - 2;
		MEM_W(cpu.ss.val+cpu.esp, REG(op_src->reg));
	} else if (DATA_BYTE == 4) {
		cpu.esp = cpu.esp - 4;
		MEM_W(cpu.ss.val+cpu.esp, REG(op_src->reg));
	}
	swaddr_t data = MEM_R(cpu.ss.val+cpu.esp);
	Log("%x\n%x\n",cpu.ss.val+cpu.esp,data);
	print_asm_template1();
	panic("hello world");
}

make_instr_helper(r)

#include "cpu/exec/template-end.h"
