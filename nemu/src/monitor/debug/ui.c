#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <cpu/helper.h>

void cpu_exec(uint32_t);

/* We use the ``readline'' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

static int cmd_help(char *args);

static int cmd_si(char *args) {
	cpu_exec(NULL==args?1:atoi(args));
	return 0;
}

static int cmd_info(char *args) {
	if (strcmp(args, "r")==0 || strcmp(args, "reg")==0){
		printf("eax	0x%x\n",cpu.eax);
		printf("ecx	0x%x\n",cpu.ecx);
		printf("edx	0x%x\n",cpu.edx);
		printf("ebx	0x%x\n",cpu.ebx);
		printf("esp	0x%x\n",cpu.esp);
		printf("ebp	0x%x\n",cpu.ebp);
		printf("esi	0x%x\n",cpu.esi);
		printf("edi	0x%x\n",cpu.edi);
	} else if (strcmp(args, "w")==0 || strcmp(args, "watchpoints")==0){
		print_wp();	
	}

	return 0;
}

static int cmd_x(char *args) {
	char* num = strtok(args, " ");
	args = num + strlen(num) + 1;
	bool success=true;
	uint32_t val = expr(args, &success);
	if (success == false) {
		Log("Regular expression has errors.");
		return 0;
	}
	int len = atoi(num),i;
	for (i=0; i<len; i++){
		printf("%02x ",instr_fetch(val, 1));
		val = val+1;
	}
	printf("\n");
	return 0;
}

static int cmd_p(char *args) {
	bool success=true;
	int val = expr(args, &success);
	if (success == false) {
		Log("Regular expression has errors.");
		return 0;
	}
	printf("%d	    0x%x\n",val, val);
	return 0;
}

static int cmd_w(char *args) {
	WP *p= new_wp();
	strcpy(p->str,args);
	bool success=true;
	int val = expr(args, &success);
	if (success == false) {
		Log("Regular expression has errors.");
		return 0;
	}
	p->val = val;
	printf("Hardware watchpoint %d: %s\n",p->NO,p->str);
	return 0;
}

static int cmd_d(char *args) {
	WP *p = malloc(sizeof(WP));
	p->NO = atoi(args);
	free_wp(p);
	return 0;
}

bool get_func(swaddr_t addr, char *str);

static int cmd_bt(char *args) {
	if (NULL != args) {
		printf("Don't need input anything else.\n");
		return 0;
	}

	swaddr_t addr = cpu.eip;
	swaddr_t tmp = cpu.ebp;

	char name[32];
	int i=0,index=0;

	while(get_func(addr,name)) {
		name[31]= '\0';
		printf("#%d  0x%08x  %s (",i++,addr,name);
		for (index=2; index < 5; index++) {
			printf("%x,",swaddr_read(tmp+4*index,4));
		}
		printf("%x",swaddr_read(tmp+4*index,4));
		printf(")\n");
		addr = swaddr_read(tmp+4,4);
		tmp = addr;
	}

	return 0;
}

static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
	{ "q", "Exit NEMU", cmd_q },
	{ "si", "Step once or more", cmd_si },
	{ "info", "Print state of registers or infomation of watchpoints", cmd_info },
	{ "x", "Scan instructions in memory", cmd_x },
	{ "p", "Test expr", cmd_p },
	{ "w", "Add watchpoints", cmd_w },
	{ "d", "Delete watchpoints", cmd_d },
	{ "bt", "Print stack frame chain", cmd_bt },

	/* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}

void ui_mainloop() {
	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) { continue; }

		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) { return; }
				break;
			}
		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}
