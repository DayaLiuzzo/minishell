/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:58:02 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/11 17:36:46 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand(t_lexbuf **tokens, t_input *input, char **env)
{
	t_lexbuf *tmp;
    int start;
    char *envar;
    char *new_value;
    
	tmp = (*)tokens;
    while(tmp)
    {
        if((start = find_envar(tmp->value)) != -1)
        {
            while(start = find_envar(tmp->value) != -1)
            {
                envar = get_envar(tmp->value[start], env, input, tokens);
                new_value = concatene_envar(tmp->value, envar, input, tokens);
                free(tmp->value);
                tmp->value = new_value;
                free(new_value);
            }
        }
        tmp = tmp->next;
    }
}
char *get_envar(char *value, char **env, t_input *input, t_lexbuf **tokens)
{
    int i;
    int j;
    char *varname;
    char *varcontent;
    
    i = 0;
    j = 0;
    varcontent = NULL;
    varname = get_varname(value, input, tokens);
    if(!varname)
        return NULL;
    while(env[i])
    {
        if(ft_strncmpp(varname, env[i], ft_strlen(varname)) == 1)
        {
            while(env[i][j] && env[i][j] != '=')
                j++;
            if (varcontent = get_varcontent(env[i][j], input, tokens) == NULL)
                return NULL;
        }
        i++;
    }
    if(varname)
        free(varname);
    return(varcontent);
}

char *expand_left(char *value, char *envar, t_input *input, t_lexbuf** tokens)
{
    int i;
    int j;
    int k;
    int start;
    char *tmp;
    
    j = 0;
    k = 0;
    start = find_envar(value) - 1;
    i = start;
    tmp = NULL;
    while(value[i] && (is_alnum(value[i])  || value[i] == '_'))
        i++;
    j = ft_strlen(envar);
    if(tmp = (char *)malloc(sizeof(char) * start + j) == NULL)
        ft_free("Alloc error concatene_envar", input, tokens, 1);
    i = 0;
    while(i < start)
    {
        tmp[i] = value[i];
        i++; 
    }
    while(i < start + j)
    {
        tmp[i] = envar[k];
        i++;
        k++;
    }
    return (tmp[i] = 0);
}
char *concatene_envar(char *value, char *envar, t_input *input, t_lexbuf** tokens)
{
    char *tmp;
    char *new_value;
    t_utils utils;
    int i;
    
    new_value = NULL;
    i = find_envar(value);
    tmp = expand_left(value, envar, input, tokens);
    while(value[i] && (is_alnum(value[i])  || value[i] == '_'))
        i++;
    new_value = ft_strjoin(tmp, value[i]);
    if(tmp)
    free(tmp);
    if(value)
    free(value);
    return new_value;
}