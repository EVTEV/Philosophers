/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaes <acaes@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:01:55 by acaes             #+#    #+#             */
/*   Updated: 2025/05/02 12:01:55 by acaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* ============================= LIBFT_UTILS ================================ */

#include "../inc/philo.h"

/* Convert string to integer (simple atoi implementation) */
int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

/* Optimasation for error message */
int	msg_error(char *msg)
{
	printf("Error:\n%s\n", msg);
	return (1);
}
