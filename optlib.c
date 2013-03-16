#include "Optlib.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#define OPTLIB_H 1

int display_usage(void);

int options(int argc, char **argv)
{
    int no_arguments_needed = 1, i = 0, sem_number = 0;
    char *arg = NULL;
    if (argc < 2)
        printf("No arguments found. Use -h for help.\n");
    for (i = 1; i < argc; i++) {
        arg = *(argv + i);
        switch (getopt_c(arg)) {
        case 0:
            if (no_arguments_needed) {
                printf("Unknown command %s.\n", arg);
                return 0;
            }
            if (strlen(arg) > 1)
                return 0;
            sem_number = *arg - '0';
            no_arguments_needed = 1;
            break;
        case 1:
            if (no_arguments_needed == 0)
                return 0;
            switch (*arg) {
            case 'h':
                no_arguments_needed = 1;
                display_usage();
                break;
            case 's':
                no_arguments_needed = 0;
                break;
            default:
                printf("Unknown command -%s.\n", arg);
                return 0;
                break;
            }
            break;
        default:
            printf("Unknown command %s.\n", arg);
            return 0;
            break;
        }
    }
    return sem_number;
}

int getopt_c(char *arg)
{
    int arg_type = 0, i = 1;
    while (*arg == '-') {
        arg_type++;
        *(arg) = *(arg + 1);
        while (*(arg + i - 1)) {
            *(arg + i) = *(arg + i + 1);
            i++;
        }
        i = 1;
    }
    return arg_type;
}

int display_usage(void)
{
    int i = 0;
    char *help[2] = { "-h", "-s <number>" };
    char *help_def[2] = { "Displays usage information",
        "Defines sem number(1 or 2)"
    };
    printf("Usage: lab2 [options]\n");
    for (i = 0; i < 2; i++)
        printf("%-12s %s\n", help[i], help_def[i]);
    return 1;
}

int get_int(int *target)
{
    char tmp = 'a';
    char buff[10];
    int i = 0, output = 0;
    fgets(buff, 8, stdin);
    if ((tmp = buff[i]) == '\n')
        return 0;
    do {
        if (tmp > '9')
            return 0;
        output = output * 10 + (tmp - '0');
        i++;
        tmp = buff[i];
    } while (tmp && tmp != '\n');
    *target = output;
    return 1;
}