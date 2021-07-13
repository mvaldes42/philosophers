/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_g.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 12:31:31 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/13 12:39:16 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_putchar_fd(char c)
{
	write(1, (unsigned char *)(&c), 1);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i]);
		i++;
	}
}

void	ft_putnbr(int n)
{
	long	n_long;

	n_long = n;
	if (n_long < 0)
	{
		ft_putchar_fd('-');
		n_long = n_long * -1;
	}
	if (n_long >= 10)
		ft_putnbr(n_long / 10);
	ft_putchar_fd(n_long % 10 + '0');
}
