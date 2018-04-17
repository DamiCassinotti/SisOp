//#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[]);
void ln1(const char* file, const char* link);
int fileExists(const char* file);
