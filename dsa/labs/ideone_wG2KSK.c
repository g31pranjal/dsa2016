#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define bool int
#define false 0
#define true 1
////////////////////////////


int op_preced(const char c) {
	switch(c) {
		case '|':
			return 6;
		case '&':
			return 5;
		case '!':
			return 4;
		case '*':  case '/': case '%':
			return 3;
		case '+': case '-':
			return 2;
		case '=':
			return 1;
	}
	return 0;
}

bool op_left_assoc(const char c) {
	switch(c)    {
		// left to right
		case '*': case '/': case '%': case '+': case '-': case '|': case '&':
			return true;
		// right to left
		case '=': case '!':
			return false;
	}
	return false;
}

unsigned int op_arg_count(const char c)
{
	switch(c)  {
		case '*': case '/': case '%': case '+': case '-': case '=': case '&': case '|':
			return 2;
		case '!':
			return 1;
		default:
			return c - 'A';
	}
	return 0;
}

#define is_operator(c)  (c == '+' || c == '-' || c == '/' || c == '*' || c == '!' || c == '%' || c == '=' || c == '&' || c == '|')
#define is_function(c)  (c >= 'A' && c <= 'Z')
#define is_ident(c)     ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z'))

bool shunting_yard(const char *input, char *output)
{
	const char *strpos = input, *strend = input + strlen(input);
	char c, *outpos = output;

	char stack[32];       // operator stack
	unsigned int sl = 0;  // stack length
	char     sc;          // used for record stack element

	while(strpos < strend)   {
		// read one token from the input stream
		c = *strpos;
		if(c != ' ')    {
			// If the token is a number (identifier), then add it to the output queue.
			if(is_ident(c))  {
				*outpos = c; ++outpos;
			}
			// If the token is a function token, then push it onto the stack.
			else if(is_function(c))   {
				stack[sl] = c;
				++sl;
			}
			// If the token is a function argument separator (e.g., a comma):
			else if(c == ',')   {
				bool pe = false;
				while(sl > 0)   {
					sc = stack[sl - 1];
					if(sc == '(')  {
						pe = true;
						break;
					}
					else  {
						// Until the token at the top of the stack is a left parenthesis,
						// pop operators off the stack onto the output queue.
						*outpos = sc;
						++outpos;
						sl--;
					}
				}
				// If no left parentheses are encountered, either the separator was misplaced
				// or parentheses were mismatched.
				if(!pe)   {
					printf("Error: separator or parentheses mismatched\n");
					return false;
				}
			}
			// If the token is an operator, op1, then:
			else if(is_operator(c))  {
				while(sl > 0)    {
					sc = stack[sl - 1];
					if(is_operator(sc) &&
						((op_left_assoc(c) && (op_preced(c) >= op_preced(sc))) ||
						   (op_preced(c) > op_preced(sc))))   {
						// Pop op2 off the stack, onto the output queue;
						*outpos = sc;
						++outpos;
						sl--;
					}
					else   {
						break;
					}
				}
				// push op1 onto the stack.
				stack[sl] = c;
				++sl;
			}
			// If the token is a left parenthesis, then push it onto the stack.
			else if(c == '(')   {
				stack[sl] = c;
				++sl;
			}
			// If the token is a right parenthesis:
			else if(c == ')')    {
				bool pe = false;
				// Until the token at the top of the stack is a left parenthesis,
				// pop operators off the stack onto the output queue
				while(sl > 0)     {
					sc = stack[sl - 1];
					if(sc == '(')    {
						pe = true;
						break;
					}
					else  {
						*outpos = sc;
						++outpos;
						sl--;
					}
				}
				// If the stack runs out without finding a left parenthesis, then there are mismatched parentheses.
				if(!pe)  {
					printf("Error: parentheses mismatched\n");
					return false;
				}
				// Pop the left parenthesis from the stack, but not onto the output queue.
				sl--;
				// If the token at the top of the stack is a function token, pop it onto the output queue.
				if(sl > 0)   {
					sc = stack[sl - 1];
					if(is_function(sc))   {
						*outpos = sc;
						++outpos;
						sl--;
					}
				}
			}
			else  {
				printf("Unknown token %c\n", c);
				return false; // Unknown token
			}
		}
		++strpos;
	}
	// When there are no more tokens to read:
	// While there are still operator tokens in the stack:
	while(sl > 0)  {
		sc = stack[sl - 1];
		if(sc == '(' || sc == ')')   {
			printf("Error: parentheses mismatched\n");
			return false;
		}
		*outpos = sc;
		++outpos;
		--sl;
	}
	*outpos = 0; // Null terminator
	return true;
}

bool evalBoolExpr(char * expr)  {
	char output[500] = {0};
	char * op;
	bool tmp;
	char part1[250], part2[250];

	if(!shunting_yard(expr, output))
	  return false;  // oops can't convert to postfix form

	while (strlen(output) > 1) {
		op = &output[0];
		while (!is_operator(*op) && *op != '\0')
		  op++;
		if (*op == '\0') {
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
	char a[5000],q[5000];
	int z[5000];
	gets(a);
	char * boolString[2] = {"FALSE", "TRUE"};
	int l = strlen(a),i,j,k=0,n=0,x,b[30]={0},r=0;
	
	// Counts the nummber of variables
	for(i=0;i<l;i++) {
		q[i] = a[i];
		if((a[i] >= 'A' && a[i] <= 'Z') || (a[i] <= 'z' && a[i] >= 'a')) {
			n++;
		}
	}

	
	int t = pow(2,n-1);
	
	for(i=0;i<pow(2,n);i++)
	{   x=i;
		k=0;
			for(r=0;r<l;r++)
			{	
				q[r]=a[r];
			//	printf("%c ",q[r]);
			}
		
		while(x>0)
		{
			b[k++]=x%2;
			x=x/2;
		}
		while(k<26)
		{
			b[k++]=0;
		}
	//b[25]=1;
	k=0;
	
		for(j=0;j<l;j++)
		{		//printf("%c ",a[j]);
			for(k=0;k<26;k++)
			{	
				if(q[j]=='A'+k)
				{	//printf("%c %d ",q[j],b[25-k]);
				if(b[n-k-1]==1)
				q[j]='1';
				else q[j]='0';
				
				//break;
			//	printf("%c ",a[j]);
				}		
			}	
		}
		q[l]='\0';
	
   // char * expr = "!((1 | 0) & (1 & ((1 & !0) | 0)))";
	char expr[5000];
	for(r=0;r<l;r++)
	{	if(q[r]=='+')
	expr[r]='|';
		else if(q[r]=='*')
		expr[r]='&';
		else if(q[r]=='-')
		expr[r]='!';
		else
		expr[r]=q[r];
	}
	expr[l]='\0';
	puts(expr);
	bool result = evalBoolExpr(expr);
	//printf("Boolean expr. %s is %s", expr, );
	
	if(result==1)
	z[t-1]=1;
	else z[t-1]=0;
	
	t++;
		//printf("stoop",i);
	}
	if(n==2)
	{printf("0000001");
		return 0;
	}
	int e=n;
		while(1)
		{	
			
		t=pow(2,e-1);
		for(i=t-1;i<t;i=i+2)
		{
			if(k==0)
			{	if(z[i]>z[i+1])
				z[(i+1)/2]=z[i];
				else z[(i+1)/2]=z[i+1];
			}
			else
			{	if(z[i]<z[i+1])
				z[(i+1)/2]=z[i];
				else z[(i+1)/2]=z[i+1];
			}
			
		}	
		e--;
		if(e<0)
		break;
		if(k==0)
		k=1;
		else 
		k=0;
		}
			for(i=0;i<n;i++)
			printf("%d ",z[i]);
	
	return 0;
}	

