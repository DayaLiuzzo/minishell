/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:49:17 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/14 16:30:47 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//CHAR BY CHAR PARSING

int main (int ac, char **av, char **env)
{
    t_input input;
    t_lexbuf *mytokens;
    // t_command_table *mycommands;
    (void)av;
    (void)env;
    
    // char str[2] = {-32, -34};
    if(ac != 1)
        exit(1);
    while(1)
    {
        init_struct(&input);
        input.linebuffer = readline("minishell >");
        add_history(input.linebuffer);
        mytokens = token_recognition(input.linebuffer, &input, 0, env);
        // mycommands = build_commands(&input, &mytokens);
        split_expands(&mytokens, &input);
        printf("MAIN\n");
        print_stack(mytokens);
        // new = remove_quotes(mytokens->value);
        ft_free("", &input, &mytokens, 0);
    }
}
//NEGATIVE LES DOUBLE QUOTE DU MOT ORIGINAL PR LES DELETE POST EXPAND
//ET CONSERVER LES QUOTE DE LEXPAND
// t_command_table *build_commands(t_input *input, t_lexbuf **tokens)
// {
    
// }





