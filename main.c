/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pachiderms <pachiderms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:00:52 by pachiderms            #+#    #+#             */
/*   Updated: 2024/09/01 20:00:52 by pachiderms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    (void)argc;
    char            out[8];

    for (int i=7; i>=0;--i)
    {
        out[i] = (argv[1][0]>>(7-i)) & 1;
    }
    for (int i=0; i<8;++i)
    {
        printf("%d", out[i]);
    }
    printf("\n");
    return (0);
}