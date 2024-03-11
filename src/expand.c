/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dliuzzo <dliuzzo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:58:02 by dliuzzo           #+#    #+#             */
/*   Updated: 2024/03/11 19:51:20 by dliuzzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(t_lexbuf **tokens, t_input *input, char **env)
{
	t_lexbuf *tmp;
    t_utils utils;
    char *envar;
    char *new_value;
    
    init_utils(&utils);
	tmp = (*tokens);
    while(tmp)
    {
        if((utils.start = find_envar(tmp->value)) != -1)
        {
            while(tmp->value && (utils.start = find_envar(tmp->value)) != -1)
            {
                envar = get_envar(tmp->value, env, input, tokens, &utils);
                printf("envar ---->%s\n", envar);
                new_value = concatene_envar(tmp->value, envar, input, tokens, &utils);
                if(tmp->value)
                    free(tmp->value);
                tmp->value = new_value;
                if(new_value)
                    free(new_value);
            }
        }
        tmp = tmp->next;
    }
}
char *get_envar(char *value, char **env, t_input *input, t_lexbuf **tokens, t_utils *utils)
{
    int i;
    int j;
    char *varname;
    char *varcontent;
    
    i = 0;
    j = 0;
    varcontent = NULL;
    varname = get_varname(value, input, tokens, utils);
    printf("varname ---> %s\n", varname);
    if(!varname)
        return NULL;
    while(env[i])
    {
        if(ft_strncmpp(varname, env[i], utils->varname_len) == 1)
        {
            while(env[i][j] && env[i][j] != '=')
                j++;
            utils->varcontent_start = j;
            if ((varcontent = get_varcontent(env[i], input, tokens, utils)) == NULL)
                return NULL;
            if(varname)
            free(varname);
            return(varcontent);
        }
        i++;
    }
    return(varcontent);
}

char *expand_left(char *value, char *envar, t_input *input, t_lexbuf** tokens, t_utils *utils)
{
    int i;
    int k;
    char *tmp;
    
    k = 0;
    utils->start += -1;
    i = utils->start;
    tmp = NULL;
    while(value[i] && (ft_isalnum(value[i])  || value[i] == '_'))
        i++;
    if((tmp = (char *)malloc(sizeof(char) * (utils->start + utils->varcontent_len))) == NULL)
        ft_free("Alloc error concatene_envar", input, tokens, 1);
    i = 0;
    while(i < utils->start)
    {
        tmp[i] = value[i];
        i++; 
    }
    while(i < utils->start + utils->varcontent_len)
    {
        tmp[i] = envar[k];
        i++;
        k++;
    }
    tmp[i] = 0;
    return (tmp);
}
char *concatene_envar(char *value, char *envar, t_input *input, t_lexbuf** tokens, t_utils *utils)
{
    char *tmp;
    char *new_value;
    int i;
    char *tmp2;
    
    new_value = NULL;
    i = find_envar(value);
    tmp = expand_left(value, envar, input, tokens, utils);
    while(value[i] && (ft_isalnum(value[i])  || value[i] == '_'))
        i++;
    tmp2 = &value[i];
    new_value = ft_strjoin(tmp, tmp2);
    if(tmp)
    free(tmp);
    if(value)
    free(value);
    return (new_value);
}