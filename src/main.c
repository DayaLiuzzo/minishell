/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:49:17 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/05 17:08:12 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int ac, char **av, char **env)
{
    // t_lexbuf *tokens;
    t_input input;
    t_args *myenv;
    char **test;
    (void)av;
    char buffer[4096];
    
    if(ac != 1)
        exit(1);
    //  Fonction pour ignorer Ctrl z etc... ignore_signals;
    while(1)
    {
        myenv = get_env(env);
        init_struct(&input);
    //     while(input.again)
    //     {
            
    //         input.again = 0;
    // // creer fonction pour savoir quel prompt donner.
    // // printf("%s", getprompt());
    //         input.linebuffer = NULL;
    //         input.len = 0;
    //         // input.nread = getline(&input.linebuffer, &input.nread, stdin);
    //         // if (input.nread <= 0 && errno == EINTR)
    //         //     input.again = 1;   
    //     }
        input.linebuffer = readline(buffer);
        add_history(input.linebuffer);
        // printf("%s\n", av[0]);
        test = minishell_split(input.linebuffer);
        print_tab(test);
        print_env(myenv);
        free(input.linebuffer);
        test = split_error(test);
        // tokens = build_tokens(&input);
        // analyse_token(tokens);
    // ft_free(&input, tokens, 0);
    }
    // si l utilisateur fait control D alors on arrete
    // creer liste de tokens en fonction de input (linebuffer)
    // build_tokens();
    free(input.linebuffer);
    // Fonction pour demander un input set_prompt("")
}