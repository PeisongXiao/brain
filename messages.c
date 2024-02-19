/*------------------------------------------------------------------------------
 * Project: brain
 * Version: 0.1.0
 * File: messages.c
 * Author: Peisong Xiao
 * E-mail: peisong.xiao.xps@gmail.com
 *----------------------------------------------------------------------------*/

#include "messages.h"

#include <stdio.h>

void msg_version(void) {
    printf("brain version: 0.1.0\n");
}

void msg_help(void) {
    printf(
        "Usage: ./brain SRC [options]\n\
Options:\n\
  -o FILENAME Output the result of compilation as a binary executable\n\
  -a FILENAME Output the result of compilation as x86 assembly\n\
  -v          Outputs the current version\n\
  -h          Displays the manual page\n"
    );
}

int exit_message(int exit_code) {
    const char format[] = "brain exited with exit code %d: %s\n";
    const char code_name[9][30] = {
        "EXIT_SUCCESS",
        "EXIT_FILE_NOT_FOUND",
        "EXIT_SYNTAX_ERR",
        "EXIT_INVALID_PARAM",
        "EXIT_INVALID_SOURCE_FILE",
        "EXIT_INVALID_CNT_PARAM",
        "EXIT_FILE_READ_ERR",
        "EXIT_FILE_WRITE_ERR"
    };

    if (exit_code >= 1 && exit_code <= 7) {
        if (exit_code == EXIT_INVALID_CNT_PARAM ||
            exit_code == EXIT_INVALID_PARAM) {
            printf("\n\n");
            msg_help();
            printf("\n\n");
        }

        fprintf(stderr, format, exit_code, code_name[exit_code]);
    } else if (exit_code == 0) {
        fprintf(stdout, format, exit_code, code_name[exit_code]);
    } else {
        fprintf(stderr, "Undefined exit code: %d\n", exit_code);
    }

    return exit_code;
}
