/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:49:17 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/02/29 14:59:53 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int ac, char **env)
{
    t_lexbuf tokens;
    t_input input;
    if(ac != 1)
        exit(1);
    init_struct(&input);
    //  Fonction pour ignorer Ctrl z etc... ignore_signals;
    while(input.again)
    {
        input.again = 0;
    // creer fonction pour savoir quel prompt donner.
    // printf("%s", getprompt());
        input.linebuffer = NULL;
        input.len = 0;
        input.nread = getline(&input.linebuffer, &input.nread, stdin);
        if (input.nread <= 0 && errno == EINTR)
        {
            input.again = 1;   
        }
    }
    build_tokens(&tokens, &input);

    // if(input.linebuffer)
    // {
    //     printf("LINEBUFFER---->%s\n", input.linebuffer);
    //     printf("input.nread--->%zu\n", input.nread);
    //     printf("ENV--->%s\n", env[0]);
    // }
    //si l utilisateur fait control D alors on arrete
    //creer liste de tokens en fonction de input (linebuffer)
    // build_tokens();
    // free(input.linebuffer)
    // Fonction pour demander un input set_prompt("")
}