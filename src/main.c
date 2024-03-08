/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:49:17 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/08 13:08:47 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//CHAR BY CHAR PARSING
int main (int ac, char **av, char **env)
{
    t_input input;
    t_lexbuf *mytokens;
    (void)av;
    (void)env;
    int i;
    if(ac != 1)
        exit(1);
    while(1)
    {
        i = 0;
        init_struct(&input);
        input.linebuffer = readline("minishell >");
        add_history(input.linebuffer);
        mytokens = token_recognition(input.linebuffer, &input);
        free(input.linebuffer);
        print_stack(mytokens);
        ft_free("", &input, mytokens, 0);
    }
}