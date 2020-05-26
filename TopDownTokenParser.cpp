#include <iostream>
#include <cstdio>

// implementing recursive top-down token expression parser

long long value;
enum TOKEN {NONE, NUM, ADD, SUB, MUL, DIV} token;

long long getExpression(void);
long long calculateFirstLayer(void);
long long calculateSecondLayer(void);
long long getFactor(void);
void getToken(void);

int main(void)
{
    getToken();
    long long result = getExpression();
    std::cout << result << std::endl;
    return 0;
}


long long getExpression(void)
{
    long long result = calculateFirstLayer();
    
    while(token == ADD || token == SUB)
    {
        TOKEN save = token;
        getToken();
        
        if(save == ADD)
        {
            result += calculateFirstLayer();
        }
        else if(save == SUB)
        {
            result -= calculateFirstLayer();
        }
    }
    
    return result;
}


long long calculateFirstLayer(void)
{
    long long result = getFactor();
    
    while(token == MUL || token == DIV)
    {
        TOKEN save = token;
        getToken();
        
        if(save == MUL)
        {
            result *= getFactor();
        }
        else if(save == DIV)
        {
            result /= getFactor();
        }
    }
    
    return result;
}


long long calculateSecondLayer(void)
{
    // empty yet
    return 0;
}


long long getFactor(void)
{
    long long result = 0;
    
    while(token == NUM)
    {
        result *= 10;
        result += value;
        getToken();
    }
    
    return result;
}


void getToken(void)
{
    char ch = getchar();
    
    switch(ch)
    {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        token = NUM;
        value = ch - '0';
        break;
        
        case '+':
        token = ADD;
        break;
        
        case '-':
        token = SUB;
        break;
        
        case '*':
        token = MUL;
        break;
        
        case '/':
        token = DIV;
        break;
        
        default:
        token = NONE;
    }
}
