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
    }

    return 0;
}

static int cmd_x(char *args) {
    char* num = strtok(args, " ");
    args = num + strlen(num) + 1;
    swaddr_t addr;
    sscanf(args, "%x\n",&addr);
    int len = atoi(num),i;
    printf("%8x:    ", addr);
    for (i=0; i<len; i++){
	printf("%02x ",instr_fetch(addr, 1));
	addr = addr+1;
    }
    printf("\n");
    return 0;
}

static int cmd_expr(char *args) {
    bool success;
    expr(args, &success);

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
    { "expr", "Test expr", cmd_expr },


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
