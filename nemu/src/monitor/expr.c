#include "nemu.h"
#include "cpu/reg.h"
#include "memory/memory.h"
#include "cpu/operand.h"

#include <stdlib.h>
#include <string.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256, EQ, NUM, REG, SYMB

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// white space
	{"\\+", '+'},
	{"\\-", '-'},
	{"\\(", '('},
	{"\\)", ')'},
	{"\\*", '*'},
	{"/",'/'},
	{"==", EQ},
	{"[0-9]+", NUM},
	{"\\$e[acdb]x", REG},
	{"\\$e[sb]p", REG},
	{"\\$e[sd]i", REG},
	{"[a-zA-Z_]+[a-zA-Z0-9_]*", SYMB},
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for more times.
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
			assert(ret != 0);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

bool match_parentheses(char *);
bool check_parentheses(Token *,Token *);
uint32_t eval(Token *,Token *);
uint32_t look_up_symtab(char *,bool *);

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

				//printf("match regex[%d] at position %d with len %d: %.*s", i, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */


				switch(rules[i].token_type) {
					case REG:
					case SYMB:
					case EQ:
					case NUM: tokens[nr_token].type = rules[i].token_type;
						  strncpy(tokens[nr_token].str,substr_start,substr_len);
						  nr_token++;
						  break;
					case NOTYPE: break;
					default: tokens[nr_token].type = rules[i].token_type;
							 nr_token ++;
				}

				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}
	if(nr_token==0)
		return false;

	return true; 
}

uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}

	if(!match_parentheses(e)) {
		*success = false;
		return 0;
	}
	*success = true;
	return eval(&tokens[0],&tokens[nr_token-1]);
}

uint32_t eval(Token *p,Token *q) {
	if(p>q) {
		assert(0);	
	}
	else if(p==q) {
		if(p->type==NUM){
			return atoi(p->str);
		}
		else if(p->type==SYMB){
			bool success=false;
			uint32_t addr=look_up_symtab(p->str,&success);
			if(!success){
				printf("'%s' not found\n",p->str);
				return -1;
			}
			else return addr;
		}
		else{
			OPERAND r;
			r.data_size=32;
			r.type=OPR_REG;
			if(!strcmp(p->str,"$eax"))
				r.addr=REG_EAX;
			else if(!strcmp(p->str,"$edx"))
				r.addr=REG_EDX;
			else if(!strcmp(p->str,"$ecx"))
				r.addr=REG_ECX;
			else if(!strcmp(p->str,"$ebx"))
				r.addr=REG_EBX;
			else if(!strcmp(p->str,"$esp"))
				r.addr=REG_ESP;
			else if(!strcmp(p->str,"$ebp"))
				r.addr=REG_EBP;
			else if(!strcmp(p->str,"$esi"))
				r.addr=REG_ESI;
			else 
				r.addr=REG_EDI;
			operand_read(&r);
			return r.val;
		}
	}
	else if(check_parentheses(p,q)==true){
		return eval(p+1,q-1);
	}
	else {
		Token *op=NULL;
		if(p->type=='-')
			return -eval(p+1,q);
		if(p->type=='*'){
			uint32_t addr=eval(p+1,q);
			return vaddr_read(addr,SREG_DS,1);
		}
		Token *cur=p;
		while(cur!=q){
			switch(cur->type){
				case EQ :op=cur;break;
				case '+':
				case '-':if(op==NULL||(op->type!=EQ))
						 op=cur;
					 break;
				case '*':
				case '/':if(op==NULL||op->type=='*'||op->type=='/')
						 op=cur;
					 else;
					 break;
				case '(':for(int num=0;;cur++){
					 	if(cur->type=='(')
							num++;
						else if(cur->type==')')
							num--;
						else;
						if(num==0){
							cur--;
							break;
						}
						else;
					 }
					 break;
				default:break;
			}
			cur++;
		}
		uint32_t val1=eval(p,op-1);
		uint32_t val2=eval(op+1,q);
		switch(op->type){
			case '+':return val1+val2;break;
			case '-':return val1-val2;break;
			case '*':return val1*val2;break;
			case '/':return val1/val2;break;
			case EQ:return val1==val2;break;
			default:return 0;break;
		}
		
	}
}

bool check_parentheses(Token *p,Token *q) {
	if(p->type!='(')
		return false;
	else {
		int num=1;
		Token *cur=p;
		while(num){
			cur++;
			if(cur->type=='(')
				num++;
			else if(cur->type==')')
				num--;
			else;
		}
		if(cur==q)
			return true;
		else return false;
	}
}

bool match_parentheses(char *expr){
	int i=0,num=0;
	while(expr[i]!='\0'){
		if(expr[i]=='(')
			num++;
		else if(expr[i]==')'){
			num--;
			if(num<0)
				return false;
		}
		else;
		i++;
	}
	if(num!=0)
		return false;
	return true;
}
