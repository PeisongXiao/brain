/*------------------------------------------------------------------------------
 * Project: brain
 * Version: 0.1.0
 * File: messages.h
 * Purpose: a) Handles exit codes
 *          b) Prints helpful messages
 * Author: Peisong Xiao
 * E-mail: peisong.xiao.xps@gmail.com
 *----------------------------------------------------------------------------*/

#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#define EXIT_UNDEFINED_EXIT_CODE       -1
#define EXIT_SUCCESS                    0
#define EXIT_FILE_NOT_FOUND             1
#define EXIT_SYNTAX_ERR                 2
#define EXIT_INVALID_PARAM              3
#define EXIT_INVALID_SOURCE_FILE        4
#define EXIT_INVALID_CNT_PARAM          5
#define EXIT_FILE_READ_ERR              6
#define EXIT_FILE_WRITE_ERR             7

// exit_message(exit_code) produce the appropriate exit message based
// on exit_code. Should only be called when the program terminates.
// requires: exit_code is defined in status.h
// effects: writes to stdout and/or stderr
int exit_message(int exit_code);

// msg_help() displays the manual page (help message)
// effects: writes to stdout
void msg_help(void);

// msg_version() displays information about tennis
// effects: writes to stdout
void msg_version(void);

#endif
