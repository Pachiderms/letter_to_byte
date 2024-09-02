/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pachiderms <pachiderms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:02:37 by pachiderms            #+#    #+#             */
/*   Updated: 2024/09/02 13:02:37 by pachiderms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SIGUSR1 1
#define SIGUSR2 0

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void    bin_to_char(int signum, char *c)
{
    if (signum == SIGUSR1)
        *c = (*c << 1) | 1;
    else if (signum == SIGUSR2)
        *c = *c << 1;
}

void    sig_handler(int signum, siginfo_t *info, void *context)
{
    static int  i;
    static int  client_pid;
    static char c;

    (void)context;
    i = 0;
    if (client_pid == 0)
        client_pid = info->si_pid;
    bin_to_char(signum, &c);
    if (++i == 8)
    {
        i = 0;
        if (!c)
        {
            kill(client_pid, SIGUSR1);
            client_pid = 0;
            return ;
        }
        printf("%c\n", c);
    }
    kill(client_pid, SIGUSR2);
}

int main(void)
{
    struct sigaction action;

    printf("SERVER PID: %d\n", getpid());
    sigemptyset(&action);
    action.sa_flags = SA_RESTART | SA_SIGINFO;
    action.sa_sigaction = sig_handler;
    sigaction(SIGUSR1, sig_handler);
    sigaction(SIGUSR2, sig_handler);
    while (1)
    {
        pause ();
    }
    return (0);
}