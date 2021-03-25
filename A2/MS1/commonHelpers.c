#include <stdio.h>
#include <time.h>

int currentYear(void)
{
    time_t currentTime = time(NULL);
    return localtime(&currentTime)->tm_year + 1900;
}

void clearStandardInputBuffer(void)
{
    while (getchar() != '\n')
    {
        ; // On purpose: do nothing
    }
}

int getInteger()
{   
    char newline = 'x';
    int number, success;
    do{
        newline = 'x';
        success = scanf("%d%c", &number, &newline);
        if(newline!='\n') clearStandardInputBuffer();
        if(success!=2 || newline!='\n') printf("ERROR: Value must be an integer: ");
    }while(success!=2 || newline!='\n');
    return number;
}
int getPositiveInteger()
{
    char newline = 'x';
    int number, success;
    do{
        newline = 'x';
        success = scanf("%d%c", &number, &newline);
        if(newline!='\n') clearStandardInputBuffer();
        if(success!=2 || number<=0 || newline!='\n') printf("ERROR: Value must be a positive integer greater than zero: ");
    }while(success!=2 || number<=0 || newline!='\n');
    return number;
}

int getIntFromRange(int lower, int upper)
{
    char newline = 'x';
    int number, success, valid=0;
    do{
        newline = 'x';
        success = scanf("%d%c", &number, &newline);
        if(newline!='\n') clearStandardInputBuffer();
        if(success!=2) printf("ERROR: Value must be an integer: ");
        else if(number<lower || number>upper  || newline!='\n')
            printf("ERROR: Value must be between %d and %d inclusive: ",  lower, upper);
        else valid=1; 
    }while(!valid);
    return number;
}

double getDouble()
{
    char newline = 'x';
    double number;
    int success;
    do{
        newline = 'x';
        success = scanf("%lf%c", &number, &newline);
        if(newline!='\n') clearStandardInputBuffer();
        if(success!=2 || newline!='\n') printf("ERROR: Value must be a double floating-point number: ");
    }while(success!=2 || newline!='\n');
    return number;
}

double getPositiveDouble()
{
    char newline = 'x';
    double number;
    int success;
    do{
        newline = 'x';
        success = scanf("%lf%c", &number, &newline);
        if(newline!='\n') clearStandardInputBuffer();
        if(success!=2 || number<=0 || newline!='\n')
		{
			if (success!=2)
         		printf("ERROR: Value must be a double floating-point number: ");
         	else printf("ERROR: Value must be a positive double floating-point number: ");
        }
    }while(success!=2 || number<=0 || newline!='\n');
    return number;
}

char getCharOption(const char* input)
{
    char in;
    int charFound=0;
    do{
        charFound=0;
        in = getchar();
        if (getchar() != '\n')
            clearStandardInputBuffer();
        else
        {
            int i;
            for(i=0; input[i]!='\0'; i++)
                if(input[i]==in)
                {
                    charFound=1;
                    break;
                }
        }
        if(!charFound) printf("ERROR: Character must be one of [%s]: ", input);
    }while(!charFound);
    return in;
}

void getCString(char* str, int min, int max)
{
    if(min>max) return;

    int valid=0; 
    do{   
        int ChrCnt= 0;
        char curr;
        while((curr=getchar())!='\n')
        {
            if(ChrCnt<max)  str[ChrCnt] = curr;
            ChrCnt++;

        }
        if(ChrCnt<=max) str[ChrCnt]='\0';

        if(ChrCnt>max || ChrCnt<min)
        {
            if(max==min) printf("ERROR: String length must be exactly %d chars: ", max);
            else if(ChrCnt>max) printf("ERROR: String length must be no more than %d chars: ", max);
            else printf("ERROR: String length must be between %d and %d chars: ", min, max);
        }
        else valid = 1;
    }while(!valid);
}