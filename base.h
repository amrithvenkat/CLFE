#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

class Base
{
    public:
        //Constructor and destructor
        Base();
        ~Base();

        // Attributes
        static int Count;//instance counter
        static char LogFile[256];  
        char Msg[256]; 

        // Methods/Functions
        int AppendLog(char* str);
};

#endif // BASE_H_INCLUDED
