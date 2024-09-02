/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pachiderms <pachiderms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:59:49 by pachiderms            #+#    #+#             */
/*   Updated: 2024/09/02 12:59:49 by pachiderms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SIGUSR1 1
#define SIGUSR2 0

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int  can_receive = 0;

void    sig_handler(int signum, siginfo_t *info, void *context)
{
    static int  i;

    (void)info;
    (void)context;
    can_receive = 1;
    if (signum == SIGUSR2)
        i++;
    else if (signum == SIGUSR1)
        printf("received %d\n", i/8);
}

void   char_to_bin(char c, int server_pid)
{
    int     itr;
    int     bit;

    bit = 7;
    while (bit >= 0)
    {
        if ((c >> bit) & 1)
            kill(server_pid, SIGUSR1);
        else
            kill(server_pid, SIGUSR2);
        bit--;
        itr = 0;
        while (can_receive == 0)
        {
            if (itr == 50)
            {
                printf("server not responding\n");
                exit (-1);
            }
            itr++;
            usleep(100);
        }
        can_receive = 0;
    }
}

int main(int argc, char **argv)
{
    struct sigaction    action;
    int                 byte;
    int                 server_pid;

    if (argc != 3)
        return (0);
    byte = 0;
    server_pid = atoi(argv[1]);
    signal(SIGUSR1, sig_handler);
    signal(SIGUSR2, sig_handler);
    while (argv[2][byte] != NULL)
    {
        char_to_bin(argv[2][byte], server_pid);
        byte++;
    }
    char_to_bin('\0', server_pid);
    return (0);
}