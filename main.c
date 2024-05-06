/*------------------------------------------------------------------------------
 * Project: brain
 * Version: 0.1.0
 * File: main.c
 * Purpose: a) Process the given arguments
 *          b) Call the main compiling code
 * Author: Peisong Xiao
 * E-mail: peisong.xiao.xps@gmail.com
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "compile.h"
#include "messages.h"
#include "utils.h"

int main(int argc, char **argv) {

    if (argc == 1) {
        fprintf(stderr, "You must specify source file!\n");
        return exit_message(EXIT_INVALID_CNT_PARAM);
    }

    if (strlen(argv[1]) == 2) {
        if (argv[1][0] == '-' && argv[1][1] == 'v') {
            msg_version();
            return exit_message(EXIT_SUCCESS);
        } else if (argv[1][0] == '-' && argv[1][1] == 'h') {
            msg_help();
            return exit_message(EXIT_SUCCESS);
        }
    }

    if (argc == 2) {
        return exit_message(EXIT_INVALID_CNT_PARAM);
    }

    FILE *src = fopen(argv[1], "r");

    if (src == NULL) {
        fprintf(stderr, "Unable to open file: %s\n", argv[1]);
        return exit_message(EXIT_FILE_READ_ERR);
    }

    chain *orders = NULL;
    int exit_code = EXIT_SUCCESS;

    for (int i = 2; i < argc; ++i) {
        if (argv[i][0] != '-' || strlen(argv[i]) != 2) {
            fprintf(stderr, "Invalid argument No. %d: %s\n", i, argv[i]);
            exit_code = EXIT_INVALID_PARAM;
            goto RETURN;
        }

        switch (argv[i][1]) {
        case 'o':
        case 'a': {
            if (i + 1 == argc) {
                fprintf(stderr, "Invalid number of arguments!\n");
                exit_code = EXIT_INVALID_CNT_PARAM;
                goto RETURN;
            }

            chain *tmp = (chain *)malloc(sizeof(chain));
            tmp->next = orders;
            orders = tmp;
            orders->var = malloc(sizeof(output_file));
            ((output_file *)orders->var)->mode = get_mode(argv[i][1]);
            ((output_file *)orders->var)->file_name = argv[++i];
            break;
        }

        case 'v':
            msg_version();
            break;

        case 'h':
HELP:
            msg_help();
            break;

        default: {
            fprintf(stderr, "Invalid argument No. %d: %s\n", i, argv[i]);
            exit_code = EXIT_INVALID_PARAM;
            goto RETURN;
        }
        }
    }

    if (orders) {
        exit_code = compile(src, orders);

        if (exit_code == EXIT_SUCCESS)
            orders = NULL;
    }

RETURN:
    chain_var_delete(orders);
    fclose(src);
    return exit_message(exit_code);
}
