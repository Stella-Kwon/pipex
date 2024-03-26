/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_add_slush.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:20:08 by suminkwon         #+#    #+#             */
/*   Updated: 2024/03/26 22:03:51 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t count_words(char *str, char c)
{
    size_t i;

    i = 0;
    while (*str)
    {
        if (*str != c)
        {
            i++;
            while (*str && *str != c)
                str++;
        }
        else
            str++;
    }
    return (i);
}

static size_t get_each_strlen(char **str, char c)
{
    size_t i;

    i = 0;
    while (**str && **str == c)
        (*str)++;
    while ((*str)[i])
    {
        if ((*str)[i] == c)
            break;
        i++;
    }
    return (i + 1);
}

char **all_free(char ***res)
{
    int i;

    i = 0;
    while ((*res)[i])
    {
        free((*res)[i]);
        (*res)[i] = NULL;
        i++;
    }
    free(*res);
    *res = NULL;
    return (NULL);
}

static char **get_res(char *str, char c)
{
    char **res;
    size_t each_strlen;
    size_t i;
    size_t res_len;

    res_len = count_words(str, c);
    res = (char **)malloc((res_len + 1) * sizeof(char *));
    if (!res)
        return (NULL);
    i = 0;
    while (i < res_len)
    {
        each_strlen = get_each_strlen(&str, c);
        res[i] = (char *)malloc((each_strlen + 1) * sizeof(char));
        if (!res[i])
            return (all_free(&res));
        ft_strlcpy(res[i], str, each_strlen);
        ft_strlcat(res[i] + (each_strlen -1), "/", each_strlen + 1);
        str += each_strlen -1;
        i++;
    }
    res[i] = NULL;
    return (res);
}

char **ft_split_add_slush(char const *s, char c)
{
    char **res;
    char *str;

    if (!s)
        return (NULL);
    str = (char *)s;
    res = get_res(str, c);
    free(str);
    str = NULL;
    return (res);
}
