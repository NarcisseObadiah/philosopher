/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narcisse <narcisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:58:09 by narcisse          #+#    #+#             */
/*   Updated: 2023/10/09 11:15:19 by narcisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
// void	ft_putnbr_fd(int n, int fd)
// {
// 	unsigned int	nbr;
// 	int				sign;

// 	if (n < 0)
// 	{
// 		ft_putchar_fd('-', fd);
// 		sign = -1;
// 		nbr = (unsigned int)(n * sign);
// 	}
// 	else
// 		nbr = (unsigned int)n;
// 	if (nbr >= 10)
// 		ft_putnbr_fd(nbr / 10, fd);
// 	ft_putchar_fd((char)(nbr % 10 + '0'), fd);
// }


void	ft_putnbr_fd(long int ln, int fd)
{
	if (ln < 0)
	{
		ln *= -1;
		ft_putchar_fd('-', fd);
	}
	if (ln >= 10)
	{
		ft_putnbr_fd(ln / 10, fd);
		ft_putnbr_fd(ln % 10, fd);
	}
	else
	{
		if (fd >= 0)
			ft_putchar_fd(ln + 48, fd);
	}
}
