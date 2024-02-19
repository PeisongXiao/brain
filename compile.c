/*------------------------------------------------------------------------------
 * Project: brain
 * Version: 0.1.0
 * File: compile.c
 * Author: Peisong Xiao
 * E-mail: peisong.xiao.xps@gmail.com
 *----------------------------------------------------------------------------*/

#include "compile.h"
#include "messages.h"
#include <stdlib.h>
#include <stdio.h>

int compile(FILE *src, chain *output_orders) {
    FILE *pseudo = NULL;
    int exit_code = EXIT_SUCCESS;

    pseudo = tmpfile();
    exit_code = compile_pseudo(src, pseudo);

    if (exit_code != EXIT_SUCCESS) {
        fprintf(stderr, "brain terminated due to compilation error!\n");
        goto RETURN;
    }

    while (output_orders) {
        const char *filename = ((output_file *)output_orders->var)->file_name;
        FILE *dest = fopen(filename, "w");

        if (dest == NULL) {
            fprintf(stderr, "Cannot open file: %s\nCompilation terminated!\n",
                    ((output_file *)output_orders->var)->file_name);
            fprintf(stdout, "Note: previous files have been compiled!\n");
            exit_code = EXIT_FILE_WRITE_ERR;
            goto RETURN;
        }

        fclose(dest);

        switch (((output_file *)output_orders->var)->mode) {
        case COMPILE_ASSEMBLY:
            exit_code = compile_assembly(pseudo, filename);
            break;

        case COMPILE_BINARY:
            exit_code = compile_binary(pseudo, filename);
            break;

        default:
            exit_code = EXIT_INVALID_PARAM;
            break;
        }

        free(output_orders->var);
        output_orders->var = NULL;
        chain *tmp = output_orders->next;
        free(output_orders);
        output_orders = tmp;

        if (exit_code != EXIT_SUCCESS) {
            fprintf(stdout, "Note: previous files have been compiled!\n");
            goto RETURN;
        }
    }

RETURN:
    fclose(pseudo);
    return exit_code;
}

int compile_pseudo(FILE *src, FILE *dest) {
    int exit_code = EXIT_SUCCESS;

    if ((exit_code = match_brackets(src))) {
        fprintf(stderr, "Unmatched bracket(s) exists!\n");
        return exit_code;
    }

    rewind(src);

    unsigned int label_no = 0;
    stack *labels = NULL;

    const char *const section_data =
        "section .data\n   head TIMES 32768 DB 0\n";
    const char *const section_text_header =
        "section .text\n   global _start\n_start:\n   MOV ecx, head\n";

    fprintf(dest, section_data);

    fprintf(dest, section_text_header);

    char cmd;

    while ((exit_code = next_command(src, &cmd)) == EXIT_SUCCESS &&
           !feof(src)) {
        switch (cmd) {
        case '>':
            fprintf(dest, "   ADD ecx, 1\n");
            break;

        case '<':
            fprintf(dest, "   SUB ecx, 1\n");
            break;

        case '+':
            fprintf(dest, "   INC BYTE [ecx]\n");
            break;

        case '-':
            fprintf(dest, "   DEC BYTE [ecx]\n");
            break;

        case '.':
            fprintf(dest,
                    "   MOV edx, 1\n   MOV ebx, 1\n\
   MOV eax, 4\n   int 0x80\n");
            break;

        case ',':
            fprintf(dest,
                    "   MOV edx, 1\n   MOV ebx, 2\n\
   MOV eax, 3\n   int 0x80\n");
            break;

        case '[':
            fprintf(dest,
                    "   CMP BYTE [ecx], 0\n   JE jmp_f_0x%08x\njmp_b_0x%08x:\n",
                    label_no, label_no);

            stack_push(&labels, label_no);
            ++label_no;

            break;

        case ']':
            fprintf(dest,
                    "   CMP BYTE [ecx], 0\n   JNE jmp_b_0x%08x\njmp_f_0x%08x:\n",
                    stack_top(labels), stack_top(labels));
            stack_pop(&labels);
            break;
        }

        fprintf(dest, "\n");
    }

    fprintf(dest, "   MOV eax, 1\n   MOV ebx, 0\n   int 0x80\n");

    if (exit_code == EXIT_SUCCESS)
        fprintf(stdout, "Source successfully compiled!\n");

    stack_delete(&labels);
    return exit_code;
}

int match_brackets(FILE *src) {
    int brackets = 0;
    char ch;

    while (!feof(src)) {
        ch = getc(src);

        if (ch == '[')
            ++brackets;
        else if (ch == ']') {
            if (brackets > 0)
                --brackets;
            else
                return EXIT_SYNTAX_ERR;
        }
    }

    return brackets ? EXIT_SYNTAX_ERR : EXIT_SUCCESS;
}

int compile_assembly(FILE *src, const char *filename) {
    rewind(src);
    FILE *dest = fopen(filename, "w");
    char ch = getc(src);

    while (!feof(src)) {
        putc(ch, dest);
        ch = getc(src);
    }

    fclose(dest);
    return EXIT_SUCCESS;
}

int compile_binary(FILE *src, const char *filename) {
    compile_assembly(src, ".tmp.asm");

    char cmd[1024];
    system("nasm -f elf .tmp.asm");

    sprintf(cmd, "ld -m elf_i386 -s -o %s .tmp.o", filename);
    system(cmd);

    system("rm .tmp.asm");
    return EXIT_SUCCESS;
}

int get_mode(char c) {
    switch (c) {
    case 'a':
        return COMPILE_ASSEMBLY;

    case 'o':
        return COMPILE_BINARY;
    }

    return COMPILE_UNKNOWN;
}

int next_command(FILE *src, char *const command) {
    char ch = getc(src);

    while (!feof(src) &&
           ch != '<' && ch != '>' &&
           ch != '+' && ch != '-' &&
           ch != '.' && ch != ',' &&
           ch != '[' && ch != ']')
        ch = getc(src);

    if (feof(src)) {
        *command = 0;
        return EXIT_SUCCESS;
    } else {
        *command = ch;
        return EXIT_SUCCESS;
    }
}
