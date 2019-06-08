#include <iostream>
#include <string.h>

#include "../src/Stack.h"

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#define N_OPTR 9 //操作符总数
typedef enum {ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE} Operator;
//加、减、乘、除、乘方、阶乘、左括号、右括号、起始符与终止符

const char pri[N_OPTR][N_OPTR] = {
    /*        |---------------当前操作符------------------| */
    /*          +    -    *     /   ^    !    (    )   \0   */
    /* -- + */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
    /* 栈 - */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
    /* 顶 * */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
    /* 运 / */ '>', '>', '>', '>', '<', '<', '<', '>', '>',
    /* 算 ^ */ '>', '>', '>', '>', '>', '<', '<', '>', '>',
    /* 符 ! */ '>', '>', '<', '<', '<', '<', ' ', '>', '>',
    /* -- ( */ '<', '<', '<', '<', '<', '<', '<', '=', ' ',
    /* -- ) */ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    /* - \0 */ '<', '<', '<', '<', '<', '<', '<', ' ', '=',
};

Operator optr2rank(char op) {
    switch (op) {
    case '+' : return ADD;
    case '-' : return SUB;
    case '*' : return MUL;
    case '/' : return DIV;
    case '^' : return POW;
    case '!' : return FAC;
    case '(' : return L_P;
    case ')' : return R_P;
    case '\0' :return EOE;
    default:
        exit(-1);
    }
}

char orderBetween(char op1, char op2) {
    return pri[optr2rank(op1)][optr2rank(op2)];
}

void readNumber(char*& p, Stack<float>& stk) {
    stk.push((float)(*p - '0'));
    while (isdigit(*(++p))) {
        stk.push(stk.pop() * 10 + (float)(*p - '0'));
    }
    if ('.' != *p) return;
    float fraction = 1;
    while (isdigit(*(++p))) {
        stk.push(stk.pop() + (float)(*p - '0')*(fraction  /= 10));
    }
}

void append(char*& rpn, float opnd) {
    size_t n = 0;
    if (rpn) n = strlen(rpn);
    char buf[64];
    if (opnd != (float)(int)opnd) sprintf(buf, "%.2f ", opnd);//float
    else                          sprintf(buf, "%d ", (int)opnd); // int
    rpn = (char*) realloc(rpn, sizeof(char) * (n + strlen(buf) + 1));
    strcat(rpn, buf);
}

void append(char*& rpn, char optr) {
    size_t n = 0;
    if (rpn) n = strlen(rpn);
    rpn = (char*) realloc(rpn, sizeof(char) * (n + 3));
    sprintf(rpn + n, "%c ", optr);
    rpn[n+2] = '\0';
}

void skipWhitespace(char* &p){
    while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')
        p++;
}

float calcu(float opnd1, char op, float opnd2)
{
    switch (op) {
    case '+' : return opnd1 + opnd2;
    case '-' : return opnd1 - opnd2;
    case '*' : return opnd1 * opnd2;
    case '/' : return opnd1 / opnd2;
    case '^' : {
        for (int i = 0; i < (int)opnd2; i++) {
            opnd1 *= opnd1;
        }
        return opnd1;
    }
    default:
        exit(-1);
   }
}
float calcu(char op, float opnd)
{
    switch (op) {
    case '!' : {
        float result = 1;
        for (int i = 1; i < (int)opnd; i++) {
            result *= (float)i;
        }
        return result;
    }
    default:
        exit(-1);
    }
}

float evaluate(char* S, char*& RPN) { //对表达式S求值，并转换为逆波兰式RPN
    Stack<float> opnd;
    Stack<char> optr;
    optr.push('\0');
    while (!optr.empty()) {
        skipWhitespace(S);
        if (isdigit(*S)) {
            readNumber(S, opnd);
            append(RPN, opnd.top());
            skipWhitespace(S);
        } else {
            skipWhitespace(S);
            switch(orderBetween(optr.top(), *S)) {
            case '<':
                optr.push(*S);
                S++;
                break;
            case '=':
                optr.pop(); S++;
                break;
            case '>': {
                char op = optr.pop();
                append(RPN, op);
                if ('!' == op) {
                    float pOpnd = opnd.pop();
                    opnd.push(calcu(op,pOpnd));
                } else {
                    float pOpnd2 = opnd.pop();
                    float pOpnd1 = opnd.pop();
                    opnd.push(calcu(pOpnd1, op, pOpnd2));
                }
                break;
            }
            default:
                exit(-1);
            } // switch
        } // else
    } //while
    return opnd.pop();
}

using std::cout;
using std::cin;
using std::endl;
int main()
{
    while(true) {
        char S[128];
        char *rpn = NULL;
        cout << "please input express:(q to exit)\n";
        cin.getline(S,sizeof(S));
        if (S[0] == 'q'){
            break;
        }
        cout << S << " = " << evaluate(S,rpn) << endl;
        cout << rpn << endl;
        free(rpn);
    }
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
