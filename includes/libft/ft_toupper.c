/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:19:16 by jverdu-r          #+#    #+#             */
/*   Updated: 2022/01/24 19:52:25 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int a)
{
	if (a > 96 && a < 123)
		return (a - 32);
	else
		return (a);
}
