/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:51:08 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/13 21:07:24 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void split_expands(t_lexbuf **tokens, t_input *input)
{
    t_lexbuf *tmp_list;
    t_lexbuf *tmp;
    t_lexbuf *nextone;
    char **new_strs;
    tmp = *tokens;
    while(tmp)
    {
        if(tmp->value)
        {   
            // if(quoted spaces== 1)
            // {
                nextone = tmp->next;
                // new_value = remove_quotes(tmp->value);
                new_strs = ft_split(tmp->value, -32);
                print_tab(new_strs);
                tmp_list = create_tmp_list(new_strs, tmp, tokens, input);
                print_stack(tmp_list);
                free(tmp->value);
                free(tmp);
                tmp = tmp_list;
                tmp->next = nextone;

            // }
        }
        tmp = tmp->next;
    }
}
t_lexbuf	*new_tokens_pexpand(char *s, int type, t_lexbuf **tokens)
{
	t_lexbuf	*new;

	new = malloc(sizeof(t_lexbuf));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->next = NULL;
    new->value = ft_strdup(s);
    if (!new->value)
        exit(1);
    if(tokens)
        printf("\n");
    return (new);
}
t_lexbuf  *create_tmp_list(char **new_strs, t_lexbuf *tmp, t_lexbuf **tokens, t_input *input)
{
    int i;
    t_lexbuf *newtokens;
    t_lexbuf *tmpp;
    
    i = 0;
    newtokens = NULL;
    tmpp = NULL;
    while(new_strs[i])
    {
		newtokens = new_tokens_pexpand(new_strs[i], tmp->type, tokens);
		if(newtokens == NULL)
			ft_free("Alloc Failure in new_tokens", input, tokens, 1);
		if (newtokens->value[0])
				add_back(&tmpp, newtokens);
        i++;
	}
    return(newtokens);
}