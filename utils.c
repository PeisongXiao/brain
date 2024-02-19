/*------------------------------------------------------------------------------
 * Project: brain
 * Version: 0.1.0
 * File: utils.h
 * Author: Peisong Xiao
 * E-mail: peisong.xiao.xps@gmail.com
 *----------------------------------------------------------------------------*/

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_extension(const char *src, const char *ext) {
    int src_len = strlen(src);
    int ext_len = strlen(ext);

    if (ext_len > src_len)
        return 1;

    for (int i = 1; i <= ext_len; ++i)
        if (ext[ext_len - i] != src[src_len - i])
            return 1;

    return 0;
}

void chain_delete(chain *head) {
    chain *tmp;

    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void chain_var_delete(chain *head) {
    chain *tmp;

    while (head) {
        tmp = head;
        head = head->next;
        free(tmp->var);
        free(tmp);
    }
}

int stack_top(stack *s) {
    return s->val;
}

void stack_push(stack **s, unsigned int n) {
    stack *tmp = (stack *)malloc(sizeof(stack));
    tmp->next = *s;
    tmp->val = n;
    *s = tmp;
}

void stack_pop(stack **s) {
    stack *tmp = (*s)->next;
    free(*s);
    *s = tmp;
}

void stack_delete(stack **s) {
    while (*s)
        stack_pop(s);
}
