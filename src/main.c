/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:49:17 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/06 16:50:45 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int ac, char **av, char **env)
{
    t_input input;
    // t_args *myargs;
    t_lexbuf *mytokens;
    t_command_table *commands;
    char **test;
    (void)av;
    (void)env;
    
    if(ac != 1)
        exit(1);
    while(1)
    {
        init_struct(&input);
        input.linebuffer = readline("minishell >");
        add_history(input.linebuffer);
        test = minishell_split(input.linebuffer);
        mytokens = build_tokens(&input, test);
        print_stack(mytokens);
        commands = create_command_table(mytokens);
        // // myargs = get_args(args, test);
        // // print_args(myargs);
        // test = split_error(test);
        
        // ft_free(&input, mytokens, 0);
    }
}