/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <mhalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 05:27:35 by mhalli            #+#    #+#             */
/*   Updated: 2021/12/21 21:47:51 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	overlong(long result, long sign)
{
	if (result > 2147483648 && sign == -1)
		return (0);
	if (result > 2147483647 && sign == 1)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	result;
	long	sign;

	sign = 1;
	result = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (*str < 48 || *str > 57)
			return (result * sign);
		result = (result * 10) + (*str - '0');
		if ((result > 2147483648 && sign == -1)
			|| (result > 2147483647 && sign == 1))
			return (overlong(result, sign));
		str++;
	}
	return (result * sign);
}
