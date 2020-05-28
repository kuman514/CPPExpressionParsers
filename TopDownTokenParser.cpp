#include <iostream>
#include <cstdio>

// implementing recursive top-down token expression parser

int value;
enum TOKEN {NONE, NUM, ADD, SUB, MUL, DIV} token;

long long getFactor(void);
void getToken(void);
long long getLayer(int level, TOKEN curop);

TOKEN priority[4] = {ADD, MUL, SUB, DIV};


int main(void)
{
    getToken();
    //long long result = getExpression();
    long long result = getLayer(0, priority[0]);
    std::cout << result << std::endl;
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


long long getLayer(int level, TOKEN curop)
{
    if(level < 3)
    {
        // layer level
        long long result = getLayer(level + 1, priority[level + 1]);
    
        while(token == curop)
        {
            TOKEN save = token;
            getToken();
            
            switch(save)
            {
                case ADD:
                result += getLayer(level + 1, priority[level + 1]);
                break;
                
                case SUB:
                result -= getLayer(level + 1, priority[level + 1]);
                break;
                
                case MUL:
                result *= getLayer(level + 1, priority[level + 1]);
                break;
                
                case DIV:
                result /= getLayer(level + 1, priority[level + 1]);
                break;
            }
        }
    
        return result;
    }
    else
    {
        // factor level
        long long result = getFactor();
    
        while(token == curop)
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
}
