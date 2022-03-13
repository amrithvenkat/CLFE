#include "base.h"

#include<stdio.h>
#include<string.h>

int     Base::Count          = 0;
char    Base::LogFile[256]   = {0};


//call constructor

Base::Base()
{
    if(!LogFile[0]) strcpy(LogFile,"Output.log");

    Count++;

    sprintf(Msg,"> %d instance(s) created\n",Count);

    AppendLog(Msg);
}

Base::~Base()
{
    Count--;

    sprintf(Msg,"> %d instance(s) available\n",Count);

    AppendLog(Msg);
}

int Base::AppendLog(char* pStr)
{
    printf("%s",pStr);


    FILE* fileptr = fopen(LogFile,"a");
    

    if(fileptr)
    {
        fprintf(fileptr,"%s",pStr);
        fclose(fileptr);
        return 1;
    }
    return 0;
}


