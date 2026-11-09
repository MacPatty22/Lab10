/*********************************************************************
* @file signal_segfault.c
* @brief installs a SIGSEGV handler that returns without fixing the fault
* @author Mac Patterson
* @date 11/05/2026
*********************************************************************/
#include <signal.h>
#include <stdio.h>

void handle_segv(int sig)
{
    (void)sig;
    printf("Segmentation fault received\n");
}

int main (int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    // Register the handler for SIGSEGV
    signal(SIGSEGV, handle_segv);

    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);
    return 0;
}