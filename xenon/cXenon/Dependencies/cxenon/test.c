#include "cxenon.h"

int main(void)
{
    
    struct functionaddr* funcA = malloc(sizeof(struct functionaddr));
    if (funcA == NULL) 
    {
        printf("\nfailed to allocate memory");
        return -1;
    }
    
    struct functionaddr funcreturn = GetFunctionVA(funcA);
    if(!funcreturn)
    {
        fprintf(stderr,"\n\afailed to retrive function addresses");
        free(funcA);
        return -1;
    }
    
    return 0;
    
}