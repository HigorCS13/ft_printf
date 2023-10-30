/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hicunha- <hicunha-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:12:57 by hicunha-          #+#    #+#             */
/*   Updated: 2023/10/29 09:12:57 by hicunha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_char(int c, t_data *st)
{
	st->count += write(1, &c, 1);
}

static void	ft_put_str(char *str, t_data *st)
{
	if (!str)
		return (ft_put_str("(null)", st));
	while (*str)
		ft_put_char(*str++, st);
}

static void	ft_put_digt(unsigned long n, t_data *st, int spec)
{
	char	*hex;

	hex = "0123456789ABCDEF";
	if (spec == 'x')
		hex = "0123456789abcdef";
	if (spec == 'b')
		st->base_ref = 2;
	if (spec == 'o')
		st->base_ref = 8;
	if (spec == 'u')
		st->base_ref = 10;
	if (n >= st->base_ref)
		ft_put_digt(n / st->base_ref, st, spec);
	ft_put_char(hex[n % st->base_ref], st);
}

static void	ft_put_spec(char spec, va_list ap, t_data *st)
{
	if (spec == 'c')
		ft_put_char(va_arg(ap, int), st);
	else if (spec == 's')
		ft_put_str(va_arg(ap, char *), st);
	else if (spec == 'd' || spec == 'i')
	{
		st->temp = va_arg(ap, int);
		if (st->temp < 0)
		{
			ft_put_char('-', st);
			st->temp *= -1;
		}
		ft_put_digt(st->temp, st, 'u');
	}
	else if (spec == 'u' || spec == 'x' || spec == 'X' || spec == 'o' 
		|| spec == 'b')
		ft_put_digt((va_arg(ap, unsigned int)), st, spec);
	else if (spec == 'p')
	{
		st->temp = va_arg(ap, long);
		if (st->temp == 0)
			return (ft_put_str("(nil)", st));
		ft_put_str("0x", st);
		ft_put_digt(st->temp, st, 'x');
	}
}

int	ft_printf(const char *spec, ...)
{
	t_data	st;
	va_list	ap;

	st.count = 0;
	st.index = -1;
	va_start(ap, spec);
	while (spec[++st.index])
	{
		st.base_ref = 16;
		if (spec[st.index] == '%')
		{
			if (spec[++st.index] == '%')
				ft_put_char('%', &st);
			else
				ft_put_spec(spec[st.index], ap, &st);
		}
		else
			ft_put_char(spec[st.index], &st);
	}
	va_end(ap);
	return (st.count);
}

/*#include <stdio.h>

int	main()
{

	ft_printf(" NULL %s NULL ", NULL);
	// printf(" NULL %s NULL ", NULL);

	return (0);
}
*/