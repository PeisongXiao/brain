/*------------------------------------------------------------------------------
 * Project: brain
 * Version: 0.1.0
 * File: compile.h
 * Purpose: a) compile
 * Author: Peisong Xiao
 * E-mail: peisong.xiao.xps@gmail.com
 *----------------------------------------------------------------------------*/

#ifndef __COMPILE_H__
#define __COMPILE_H__

#include <stdio.h>
#include "utils.h"

#define COMPILE_UNKNOWN         0
#define COMPILE_BINARY          1
#define COMPILE_ASSEMBLY        2

typedef struct output_file {
    int mode;
    const char *file_name;
} output_file;

// compile(src, output_orders, include_paths) compiles src based on
//  output_orders
// effects: may write to stdout, stderr and/or disk
// requires: src != NULL, output_orders != NULL, include_paths != NULL
int compile(FILE *src, chain *output_orders);

// compile_pseudo(src, include_paths, dest) compiles src to a temporary
//  file in pseudo-assembly
// effects: may write to stdout, stderr and/or disk
// requires: src != NULL, include_paths != NULL
int compile_pseudo(FILE *src, FILE *dest);

// compile_binary(src, include_paths) compiles pseudo src to a binary
// effects: may write to stdout, stderr and/or disk
// requires: src != NULL, include_paths != NULL
int compile_binary(FILE *src, const char *filename);

// compile_pseudo(src, include_paths) compiles pseudo src to assembly
// effects: may write to stdout, stderr and/or disk
// requires: src != NULL, include_paths != NULL
int compile_assembly(FILE *src, const char *filename);

int next_command(FILE *src, char *const command);

int match_brackets(FILE *src);

int get_mode(char c);

#endif
