/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:08:36 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/06 14:38:11 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_failure(t_innkeper *innkeeper)
{
	if (innkeeper->philo)
		free(innkeeper->philo);
	exit(EXIT_FAILURE);
}

void	exit_success(t_innkeper *innkeeper)
{
	if (innkeeper->philo)
		free(innkeeper->philo);
	exit(EXIT_SUCCESS);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i])
			i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		size;
	int		i;

	if (s1 == NULL)
		return (NULL);
	size = 0;
	while (s1[size])
		size++;
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	count;
	size_t	size;
	char	*tab;

	count = 0;
	if (!(s))
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	tab = (char *)malloc((len + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (count < len)
	{
		tab[count] = s[start + count];
		count++;
	}
	tab[count] = '\0';
	return (tab);
}