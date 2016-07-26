#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
    NOTYPE = 256, EQ, NUM, NEG, NEQ, AND, OR

	/* TODO: Add more token types */

};

static struct rule {
    char *regex;
    int token_type;
} rules[] = {

    /* TODO: Add more rules.
     * Pay attention to the precedence level of different rules.
     */

    {" +",	NOTYPE},				// spaces
    {"\\-[0-9]+", NEG},					// negative number
    {"\\+", '+'},					// plus/add
    {"\\-", '-'},					// minus/subtract
    {"\\*", '*'},					// times/multiply
    {"\\/", '/'},					// by/divide
    {"\\(", '('},					// 
    {"\\)", ')'},					// 
    {"[0-9]+", NUM},					// number
    {"==", EQ},						// equal
    {"!=", NEQ},					// not equal
    {"&&", AND},					// and
    {"\\|\\|", OR},						// or
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
    int i;
    char error_msg[128];
    int ret;

    for(i = 0; i < NR_REGEX; i ++) {
	ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
	if(ret != 0) {
	    regerror(ret, &re[i], error_msg, 128);
	    Assert(ret == 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
	}
    }
}

typedef struct token {
    int type;
    char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
    int position = 0;
    int i;
    regmatch_t pmatch;

    nr_token = 0;

    while(e[position] != '\0') {
	/* Try all rules one by one. */
	for(i = 0; i < NR_REGEX; i ++) {
	    if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
		char *substr_start = e + position;
		int substr_len = pmatch.rm_eo;

		Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
		position += substr_len;

		/* TODO: Now a new token is recognized with rules[i]. Add codes
		 * to record the token in the array ``tokens''. For certain 
		 * types of tokens, some extra actions should be performed.
		 */

		switch(rules[i].token_type) {
		    case NOTYPE:
			break;
		    case '+':
			tokens[nr_token++].type= '+';
			break;
		    case '-':
			if (nr_token == 0){
			    tokens[nr_token].type = NUM;
			    strcpy(tokens[nr_token++].str,"0");
			}
			tokens[nr_token++].type= '-';
			break;
		    case '*':
			tokens[nr_token++].type= '*';
			break;
		    case '/':
			tokens[nr_token++].type= '/';
			break;
		    case '(':
			tokens[nr_token++].type= '(';
			break;
		    case ')':
			tokens[nr_token++].type= ')';
			break;
		    case NUM:
			tokens[nr_token].type= NUM;
			if (substr_len >= 32)
			    assert(0);
			strncpy(tokens[nr_token].str, substr_start, substr_len);
			nr_token++;
			break;
		    case NEG:
			if (tokens[nr_token-1].type == NUM || tokens[nr_token-1].type == NEG) {
			    tokens[nr_token++].type = '-';
			    tokens[nr_token].type= NUM;
			    if (substr_len >= 32)
				assert(0);
			    strncpy(tokens[nr_token].str, substr_start+1, substr_len-1);
			    nr_token++;
			} else {
			    tokens[nr_token].type = NEG;
			    if (substr_len >= 32)
				assert(0);
			    strncpy(tokens[nr_token].str, substr_start+1, substr_len-1);
			    nr_token++;
			}
			break;
		    case EQ:
			tokens[nr_token++].type = EQ;
			break;
		    case NEQ:
			tokens[nr_token++].type = NEQ;
			break;
		    case AND:
			tokens[nr_token++].type = AND;
			break;
		    case OR:
			tokens[nr_token++].type = OR;
			break;
		    default: panic("please implement me");
		}

		break;
	    }
	}

	if(i == NR_REGEX) {
	    printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
	    return false;
	}
    }

    return true; 
}

bool check_parentheses(int p, int q) {
    if (tokens[p].type != '(' || tokens[q].type != ')') {
	return false;
    }
    p++,q--;
    int i, cur=0;
    for (i=p; i<=q; i++) {
	if (tokens[i].type == '(') {
	    cur++;
	}else if (tokens[i].type == ')') {
	    cur--;
	}
	if (cur < 0)
	    return false;
    }

    if (cur != 0) {
	return false;
    }
    return true;
}

int found_op(int p, int q) {
	int op_type=0, cur=0, top=0, i;
	for(i=p; i<=q; i++) {
	    if (tokens[i].type == EQ || tokens[i].type == NEQ || tokens[i].type == AND || tokens[i].type == OR) {
		op_type = i;
		return op_type;
	    }
	    if (tokens[i].type == '+' || tokens[i].type == '-') {
		    op_type = i;
		    cur = top;
		    break;
	    }else if (tokens[i].type == '*' || tokens[i].type == '/') {
		    op_type = i;
		    cur = top;
		    break;
	    }else if (tokens[i].type == '(') {
		top++;
	    }else if (tokens[i].type == ')') {
		top--;
	    }
	}
	for( ; i<=q; i++) {
	    if (tokens[i].type == EQ || tokens[i].type == NEQ || tokens[i].type == AND || tokens[i].type == OR) {
		op_type = i;
		return op_type;
	    }
	    if (tokens[i].type == '+' || tokens[i].type == '-') {
		if (top <= cur) {
		    op_type = i;
		    cur = top;
		}
	    }else if (tokens[i].type == '*' || tokens[i].type == '/') {
		if (top <= cur) {
		    op_type = i;
		    cur = top;
		}
	    }else if (tokens[i].type == '(') {
		top++;
	    }else if (tokens[i].type == ')') {
		top--;
	    }
	}

	return op_type;
}

int eval(int p, int q, bool *success) {
    if (p > q) {
	Log("Bad expression");
	*success = false;
	return 0;
    } else if (p == q) {
	if (tokens[p].type != NUM && tokens[p].type != NEG) {
	    Log("Bad expression");
	    *success = false;
	    return 0;
	}else {
	    int number;
	    sscanf(tokens[p].str,"%d",&number);
	    if (tokens[p].type == NEG)
		return -number;
	    return number; 
	}
    } else if (check_parentheses(p, q)) {
	return eval(p+1, q-1, success);
    } else {
	int op_type=found_op(p, q);
	int val1 = eval(p, op_type -1, success);
	if (*success==false) return 0;
	int val2 = eval(op_type + 1, q, success);
	if (*success==false) return 0;

	switch(tokens[op_type].type) {
	    case '+': return val1 + val2;
	    case '-': return val1 - val2;
	    case '*': return val1 * val2;
	    case '/': return val1 / val2;
	    case EQ : return val1 == val2;
	    case NEQ: return val1 != val2;
	    case AND: return val1 && val2;
	    case OR : return val1 || val2;
	    default : assert(0);
	}

    }

}

uint32_t expr(char *e, bool *success) {
    if(!make_token(e)) {
	*success = false;
	return 0;
    }

    /* TODO: Insert codes to evaluate the expression. */
    return eval(0, nr_token-1, success);
}

