#include "types.h"
#include "user.h"

int test = 114514;

void a_thread(int *arg) {
    int i ;

    //printf(1, "i addr:%x\n", &i);

    //printf(1, "thread global addr:%x value:%d\n", &test, test);

    //printf(1, "thread arg addr:%x value:%d\n", arg, *arg);

    i = *arg;

    //printf(1, "i at start %d\n", i);

    for (; i < 20; i++)
        printf(1, "T%d\n", i);
    
    //printf(1, "T Test %d\n", test);
    test = 0;
    //printf(1, "T Test %d\n", test);

    exit();
}

int main(void)
{
    int p = 10;
    int pid;
    int i ;

    //printf(1, "main global addr:%x value:%d\n", &test, test);

    //printf(1, "main arg addr:%x value:%d\n", &p, p);

    pid = thread_create(a_thread, &p);
    printf(1, "thread pid:%d\n", pid);
    

    for (i = 0; i < 10; i++)
        printf(1, "M%d\n", i);
    
    printf(1, "M Test %d\n", test);
    while (test) {
        printf(1, "M Test %d\n", test);
    };
    printf(1, "M Test %d\n", test);

    exit();
}
