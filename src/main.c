/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:49:17 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/07 14:51:33 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int ac, char **av, char **env)
{
    t_input input;
    // t_args *myargs;
    t_lexbuf *mytokens;
    // t_command_table *commands;
    char **test;
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
        test = minishell_split(input.linebuffer);
        // print_tab(test);
        mytokens = build_tokens(&input, test);
        // separate_commands(mytokens)
        print_stack(mytokens);
        // commands = create_command_table(mytokens);
        // myargs = get_args(args, test);
        // print_args(myargs);
        // test = split_error(test);
        ft_free(&input, mytokens, 0);
    }
}

// char *ft_strscpy(char *src, char *dest, int start)
// {
    
// }

// void    separate_commands(t_lexbuf *tokens)
// {
//     t_lexbuf *current;
//     t_lexbuf *tmp;
//     t_split split;
//     size_t i;
//     char *str;
//     char *left;
//     char *pipe;
    
//     current = tokens;
//     tmp = tokens;
//     str = NULL;
//     init_split_count(&split);
//     while(current)
//     {
//         while(current->value[split.i])
//         {
//             if((split.dquote == 0 && split.squote ==  0 ) || 
//             ((split.dquote != 0 && split.dquote % 2 == 0)
//             || (split.squote != 0 && split.squote % 2 == 0)))
//             {
//                 if (current->value[split.i] && current->value[split.i] == '|')
//                 {
//                     if (split.i > 0)
//                     {
//                         str = (char *)malloc(sizeof(char) * split.i);
//                         str = ft_strlcpy(current->value, str, split.i);
//                     }
//                     pipe = (char *)malloc(sizeof(char) * 2);
//                     pipe = ft_strjoin(str, "|");
//                 }
//                 else if(current->value[split.i] && current->value[split.i]== 39)
//                     ft_single_loop(&split, current->value);
//                 else if(current->value[split.i] && current->value[split.i]== '"')
//                     ft_double_loop(&split, current->value);
//                 else 
//                     split->i++;
//             }
//         }
//     }
// }
// 1234|6789