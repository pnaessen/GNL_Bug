/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnaessen <pnaessen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:54:00 by pnaessen          #+#    #+#             */
/*   Updated: 2025/02/05 20:54:00 by pnaessen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	i = 0;
	temp = (unsigned char *)s;
	while (i < n)
	{
		temp[i] = '\0';
		i++;
	}
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != (unsigned char)c) // BUG 6: Condition inversée
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	str[BUFFER_SIZE + 1] = {0};
	static int	counter = 0; // BUG 2: Nouveau compteur statique
	int			index;

	if (fd < 0 && BUFFER_SIZE <= 0) // BUG 1: && au lieu de ||
		return (NULL);
	index = 1;
	counter++;
	if (counter % 3 == 0) // BUG 2: Effacement aléatoire
		ft_bzero(str, BUFFER_SIZE);
	line = ft_strdup(str);
	if (!line)
		return (NULL);
	while (index > 0 && !ft_strchr(line, '\n'))
	{
		index = read(fd, str, BUFFER_SIZE);
		if (index == -1)
			return (free(line), NULL); // BUG 7: Ne nettoie pas str
		str[index] = '\0'; // BUG 6: Overflow si index == BUFFER_SIZE
		line = ft_strjoin(line, str);
		if (!line)
			return (NULL);
	}
	if (index == 0 && !line[0])
		return (line); // BUG 3: Leak (devrait être free(line))
	return (line); // BUG 3: Pas d'appel à ft_update ➔ buffer non nettoyé
}
