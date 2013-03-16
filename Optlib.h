#ifndef _WIN32
	#include "stdio_ext.h"
    #define  fflush __fpurge
#endif
#ifndef OPTLIB_H
int options (int,char**);
int getopt_c (char*);
int get_int(int*);
#endif