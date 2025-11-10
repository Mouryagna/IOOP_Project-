#include<string>

class Protection{

    public:
        static const char* generateSalt(int length=8);
        static const char* HashPass(const char* pass,const char* salt);

};