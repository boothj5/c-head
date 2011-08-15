#ifndef JBTEST_H
#define JBTEST_H

#define MAX_NAME_LEN 50

typedef struct {
    void (*test)(void) ;
    char name[MAX_NAME_LEN] ;
} Test ;

Test make_test(void (*test)(void), char *name) ;
void assert_true(int expression) ;
void run_tests(Test *tests, int ntests) ;

#endif
