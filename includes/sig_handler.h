/**
 * @file sig_handler.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief 
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SIG_HANDLER_H_
#define SIG_HANDLER_H_

#include <signal.h>

typedef struct signal_handler_s {
    int _signal;
    const char *_response;
} signal_handler_t;

static const signal_handler_t SIGNAL_HANDLER[] = {
    { SIGABRT, "Process aborted" },
    { SIGBUS, "Bus error" },
    { SIGFPE, "Floating exception" },
    { SIGHUP, "Hangup signal" },
    { SIGILL, "Illegal instruction" },
    { SIGINT, "Interrupt signal" },
    { SIGKILL, "Killed signal" },
    { SIGPIPE, "Broken pipe" },
    { SIGQUIT, "Quit signal" },
    { SIGSEGV, "Segmentation fault" },
    { SIGTERM, "Terminated signal" },
    { SIGUSR1, "User-defined signal 1" },
    { SIGUSR2, "User-defined signal 2" },
    { SIGTRAP, "Trace/breakpoint trap" },
    { SIGSYS, "Bad system call" },
};

#endif /* !SIG_HANDLER_H_ */
