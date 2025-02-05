/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:53:55 by pnaessen          #+#    #+#             */
/*   Updated: 2025/02/05 20:53:55 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*str;
	size_t	i;

	i = 0;
	len = 0;
	while (s[len]) // BUG 5: Copie toute la chaîne
		len++;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	if (len == 0) // BUG 1: Leak pour chaîne vide
		return (malloc(1));
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	len2 = 0;
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	while (s2[len2] != '\n' && s2[len2] != '\0')
		len2++;
	str = malloc(len1 + len2); // BUG 5: Oubli du +1
	if (!str)
		return (NULL); // BUG 2: Ne free pas s1
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	return (str); // BUG 2: Fuite de s1
}

void	ft_update(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] && str[i++] != '\n') // BUG 4: Incrément mal placé
		;
	while (str[i])
		str[j++] = str[i++];
	// str[j] = '\0'; // BUG 4: Chaîne non terminée
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d == s)
		return (dst);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}