/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:12:25 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/28 18:33:27 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_power(int n, int p)
{
	int	r;

	r = n;
	if (p == 0)
		return (1);
	while (--p)
		r *= n;
	return (r);
}
