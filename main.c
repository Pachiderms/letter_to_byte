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
#include <string.h>

int **char_to_bin(char *msg)
{
    int     **out;
    int     byte;
    int     bit;

    byte = 0;
    out = malloc((strlen(msg)) * sizeof(int*));
    if (!out)
        return (0);
    while (msg[byte] != '\0')
    {
        bit = 7;
        out[byte] = malloc(8 * sizeof(int));
        if (!out[byte])
            break;
        while (bit>=0)
        {
            out[byte][7-bit] = (msg[byte] >> bit) & 1;
            bit--;
        }
        byte++;
    }
    out[byte] = NULL;
    return (out);
}

char    bin_to_char(int **msg_to_bin)
{
    char    c = 0;
    for (int i=0;msg_to_bin[i]!=NULL;++i)
    {
        c = 0;
        for (int b=0;b<8;++b)
        {
            if (msg_to_bin[i][b]==1)
                c = (c << 1) | 1;
            else
                c = c << 1;
        }
        printf("%c ", c);
    }
    printf("\n");
    return (c);
}

int main(int argc, char **argv)
{
    int    **msg_to_bin;

    //char to binary
    msg_to_bin = char_to_bin(argv[1]);
    for (int i=0; i<strlen(argv[1]);++i)
    {
        for (int j=0;j<8;++j)
            printf("%d",msg_to_bin[i][j]);
        printf("\n");
    }
    //binary to char
    char c = bin_to_char(msg_to_bin);
    return (0);
}