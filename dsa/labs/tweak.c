#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define bool int
#define false 0
#define true 1

int op_preced(const char c) {
	switch(c) {
		case '|':
			return 6;
		case '&':
			return 5;
		case '!':
			return 4;
	}
	return 0;
}

int op_left_assoc(const char c) {
	switch(c)    {
		// left to right
		case '|': case '&':
			return 1;
		// right to left
		case '!':
			return 0;
	}
	return 0;
}

int op_arg_count(const char c) {
	switch(c)  {
		case '&': case '|':
			return 2;
		case '!':
			return 1;
		default:
			return c - 'A';
	}
	return 0;
}

#define is_operator(c)  (c == '!' || c == '&' || c == '|')
#define is_ident(c)     ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))

int convert_to_postfix(const char *input, char *output) {
	const char *strpos = input, *strend = input + strlen(input);
	char c, *outpos = output;

	char stack[32];
	unsigned int sl = 0; 
	char sc; 

	while(strpos < strend)   {
		c = *strpos;
		
		if(c != ' ')    {
			if(is_ident(c))  {
				*outpos = c; ++outpos;
			}
		
			else if(is_operator(c))  {
				while(sl > 0)    {
					sc = stack[sl - 1];
					if(is_operator(sc) &&
						((op_left_assoc(c) && (op_preced(c) >= op_preced(sc))) ||
						   (op_preced(c) > op_preced(sc))))   {
						*outpos = sc;
						++outpos;
						sl--;
					}
					else   {
						break;
					}
				}
				stack[sl] = c;
				++sl;
			}
			else if(c == '(')   {
				stack[sl] = c;
				++sl;
			}
			else if(c == ')')    {
				int pe = 0;
				while(sl > 0)     {
					sc = stack[sl - 1];
					if(sc == '(')    {
						pe = 1;
						break;
					}
					else  {
						*outpos = sc;
						++outpos;
						sl--;
					}
				}
				sl--;
				if(sl > 0)   {
					sc = stack[sl - 1];
				}
			}
		}
		++strpos;
	}

	while(sl > 0)  {
		sc = stack[sl - 1];
		*outpos = sc;
		++outpos;
		--sl;
	}
	*outpos = 0; 
	return 1;
}


bool evalBoolExpr(char * expr)  {
    char output[500] = {0};
    char * op;
    bool tmp;
    char part1[250], part2[250];

    strcpy(output, expr);
 
  
    while (strlen(output) > 1) {
        op = &output[0];
        while (!is_operator(*op) && *op != '\0')
          op++;
        if (*op == '\0') {
        	printf("dead");
        	return false;  // oops - zero operators found
        }
        else if (*op == '!') {
            tmp = !(*(op-1) - 48);
            *(op-1) = '\0';
        }
        else if(*op == '&') {
            tmp = (*(op-1) - 48) && (*(op-2) - 48);
            *(op-2) = '\0';
        }
        else if (*op == '|') {
            tmp = (*(op-1) - 48) || (*(op-2) - 48);
            *(op-2) = '\0';
        }
 
        memset(part1, 0, sizeof(part1));
        memset(part2, 0, sizeof(part2));
        strcpy(part1, output);
        strcpy(part2, op+1);
        memset(output, 0, sizeof(output));
        strcat(output, part1);
        strcat(output, ((tmp==false) ? "0" : "1"));
        strcat(output, part2);
    }
    return *output - 48;
}









int main() {
	char op[5000];
	//convert_to_postfix("(!1) & (0) & (!1 | 1)", op);
	printf("%d\n", evalBoolExpr("00+"));
	//printf("%s\n", op);
}	

