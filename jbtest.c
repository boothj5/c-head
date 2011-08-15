#include <stdio.h>
#include "jbtest.h"

#define MAX_NAME_LEN 50

int last_result = 0 ;

typedef struct {
    void (*test)(void) ;
    char name[MAX_NAME_LEN] ;
} Test ;

void run_tests(Test *tests, int ntests)
{
    int i ;
    for (i = 0 ; i < ntests ; i++) {
        printf("%s... ", tests[i].name) ;
        (*tests[i].test)() ;
    }
        
}

void assert_true(int expression)
{
    if (expression) {
        printf("SUCCESS\n") ;
        last_result = 1 ;
    }
    else { 
        printf("FAILURE\n") ;
        last_result = 0 ;
    }
}


