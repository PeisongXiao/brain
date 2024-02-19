/*------------------------------------------------------------------------------
 * Project: brain
 * Version: 0.1.0
 * File: utils.h
 * Purpose: a) some useful utilities
 * Author: Peisong Xiao
 * E-mail: peisong.xiao.xps@gmail.com
 *----------------------------------------------------------------------------*/

#ifndef __UTILS_H__
#define __UTILS_H__

// check_extension(src, ext) Checks if the last characters of src
//  matches ext. If they match, return 0; else return 1.
int check_extension(const char *src, const char *ext);

// a struct used for chaining data together
// CAUTION: DO NOT EMBED CHAINS WITHOUT EXPLICIT EXPLAINATION
typedef struct chain {
    void *var;
    struct chain *next;
} chain;

typedef struct stack {
    struct stack *next;
    unsigned int val;
} stack;

int stack_top(stack *s);

void stack_push(stack **s, unsigned int n);

void stack_pop(stack **s);

void stack_delete(stack **s);

// chain_delete(head) free the entire chain
// effects: may free up heap memory
void chain_delete(chain *head);

// chain_delete(head) free the entire chain and its variables
// effects: may free up heap memory
void chain_var_delete(chain *head);

#endif
