/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:49:17 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/15 13:44:38 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//CHAR BY CHAR PARSING

int main (int ac, char **av, char **env)
{
    t_input input;
    t_lexbuf *mytokens;
    t_lexbuf *new_tokens;
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
        new_tokens = split_expands(&mytokens, &input);
        // mycommands = build_commands(&input, &mytokens);
        print_stack(new_tokens);
        // new = remove_quotes(mytokens->value);
        ft_free("", &input, &mytokens, 0);
    }
}
//NEGATIVE LES DOUBLE QUOTE DU MOT ORIGINAL PR LES DELETE POST EXPAND
//ET CONSERVER LES QUOTE DE LEXPAND
// t_command_table *build_commands(t_input *input, t_lexbuf **tokens)
// {
    
// }





