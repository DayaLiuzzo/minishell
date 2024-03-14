/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:51:08 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/14 17:54:49 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void split_expands(t_lexbuf **tokens, t_input *input)
{
    t_lexbuf *tmp_listhead;
    t_lexbuf *current;
    t_lexbuf *tmp_listend;
    t_lexbuf *tmp;
    t_lexbuf *tmp2;
    t_lexbuf *tmp3;
    int i = 0;
    
    char **new_strs;
    current = *tokens;
    tmp3 = *tokens;
    while(current)
    {
        tmp = current;
        if(current->value)
        {   
            // if(quoted spaces== 1)
            // {
                if (current->value[0] != '\0')
                {
                    i++;
                    if (current->prev)
                        tmp2 = current->prev;
                    new_strs = ft_split(current->value, -32);
                    // print_tab(new_strs);
                    tmp_listhead = create_tmp_list(new_strs, current, tokens, input); 
                    ft_addprev(tmp_listhead);
                    tmp_listend = get_last(tmp_listhead);
                    tmp_listend->next = tmp->next;
                    // printf("current ---> %s\ni ---->%i\n", current->value, i);
                    if (current->prev)
                    {
                        tmp_listhead->prev = tmp2;
                        tmp2->next = tmp_listhead;
                    }
                    else if(!current->prev)
                        *tokens = tmp_listhead;
                    current = tmp_listhead;
                    print_stack(current);
                }
            // }
        }
        current = tmp->next;
    }
    // print_stack(tmp3);
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
        printf("1\n");
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
		tmpp = new_tokens_pexpand(new_strs[i], tmp->type, tokens);
		if(tmpp == NULL)
			ft_free("Alloc Failure in new_tokens", input, tokens, 1);
		add_back(&newtokens, tmpp);
        i++;
	}
    return(newtokens);
}