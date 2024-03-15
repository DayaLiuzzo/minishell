/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:51:08 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/15 13:41:55 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexbuf *split_expands(t_lexbuf **old_list_head, t_input * input)
{
    t_lexbuf *new_list_head;
    t_lexbuf *current_old;
    t_lexbuf *old_next;
    t_lexbuf *new_node;
    char **new_strs;
    
    current_old = *old_list_head;
    new_list_head = NULL;
    new_node = NULL;
    while(current_old)
    {
        old_next = current_old->next;
        if(current_old->value && current_old->value[0] != '\0')
        {
            new_strs = ft_split(current_old->value, -32);
            new_node = create_tmp_list(new_strs, current_old, old_list_head, input);
        }
        else
        {
            new_node = new_tokens_pexpand(current_old->value, current_old->type, old_list_head, input);
        }
        add_back(&new_list_head, new_node);
        current_old = old_next;
    }
    return(new_list_head);
}

// void split_expands(t_lexbuf **tokens, t_input *input)
// {
//     t_lexbuf *tmp_listhead;
//     t_lexbuf *current;
//     t_lexbuf *tmp_listend;
//     t_lexbuf *tmp;
    
//     char **new_strs;
//     current = *tokens;
//     while(current)
//     {

//         tmp = current->next;
//         if(current->value && current->value[0] != '\0')
//         {   
//             new_strs = ft_split(current->value, -32);
//             tmp_listhead = create_tmp_list(new_strs, current, tokens, input); 
//             print_stack(tmp_listhead);
//             tmp_listend = get_last(tmp_listhead);
//             tmp_listend->next = tmp;
//             current = tmp_listhead;
//             // print_stack(*tokens);
//         }
//         current = tmp;
//     }
// }
t_lexbuf	*new_tokens_pexpand(char *s, int type, t_lexbuf **tokens, t_input *input)
{
	t_lexbuf	*new;

	new = malloc(sizeof(t_lexbuf));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->next = NULL;
    new->value = ft_strdup(s);
    if (!new->value)
        ft_free("malloc error at new_tokens_pexpand",input, tokens, 1);
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
		tmpp = new_tokens_pexpand(new_strs[i], tmp->type, tokens, input);
		if(tmpp == NULL)
			ft_free("Alloc Failure in new_tokens", input, tokens, 1);
		add_back(&newtokens, tmpp);
        i++;
	}
    return(newtokens);
}