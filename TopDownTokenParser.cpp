#include <iostream>
#include <cstdio>

// implementing recursive top-down token expression parser

long long value;
enum TOKEN {NONE, NUM, ADD, SUB, MUL, DIV} token;

long long getExpression(void);
long long calculateFirstLayer(void);
long long calculateSecondLayer(void);
long long calculateThirdLayer(void);
long long getFactor(void);
void getToken(void);

TOKEN priority[4] = {ADD, MUL, SUB, DIV};


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
    
    while(token == priority[3])
    {
        TOKEN save = token;
        getToken();
        
        switch(save)
        {
            case ADD:
            result += calculateFirstLayer();
            break;
            
            case SUB:
            result -= calculateFirstLayer();
            break;
            
            case MUL:
            result *= calculateFirstLayer();
            break;
            
            case DIV:
            result /= calculateFirstLayer();
            break;
        }
    }
    
    return result;
}


long long calculateFirstLayer(void)
{
    long long result = calculateSecondLayer();
    
    while(token == priority[2])
    {
        TOKEN save = token;
        getToken();
        
        switch(save)
        {
            case ADD:
            result += calculateSecondLayer();
            break;
            
            case SUB:
            result -= calculateSecondLayer();
            break;
            
            case MUL:
            result *= calculateSecondLayer();
            break;
            
            case DIV:
            result /= calculateSecondLayer();
            break;
        }
    }
    
    return result;
}


long long calculateSecondLayer(void)
{
    long long result = calculateThirdLayer();
    
    while(token == priority[1])
    {
        TOKEN save = token;
        getToken();
        
        switch(save)
        {
            case ADD:
            result += calculateThirdLayer();
            break;
            
            case SUB:
            result -= calculateThirdLayer();
            break;
            
            case MUL:
            result *= calculateThirdLayer();
            break;
            
            case DIV:
            result /= calculateThirdLayer();
            break;
        }
    }
    
    return result;
}


long long calculateThirdLayer(void)
{
    long long result = getFactor();
    
    while(token == priority[0])
    {
        TOKEN save = token;
        getToken();
        
        switch(save)
        {
            case ADD:
            result += getFactor();
            break;
            
            case SUB:
            result -= getFactor();
            break;
            
            case MUL:
            result *= getFactor();
            break;
            
            case DIV:
            result /= getFactor();
            break;
        }
    }
    
    return result;
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
