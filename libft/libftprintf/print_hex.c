/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 22:30:40 by hna               #+#    #+#             */
/*   Updated: 2020/04/09 18:56:06 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	check_prec(t_option *opt, char *pr, char *s_pad, char *temp)
{
	if (!(pr = make_padstr(opt->prec, '0')))
		return (-1);
	ft_strncpy(&pr[opt->prec - ft_strlen(temp)], temp, ft_strlen(temp));
	if (opt->width > opt->prec)
	{
		if (!(s_pad = make_padstr(opt->width, opt->pad)))
			return (-1);
		if (opt->minus == 1)
		{
			ft_strncpy(s_pad, pr, ft_strlen(pr));
			ft_memset(&s_pad[ft_strlen(pr)], ' ', opt->width - ft_strlen(pr));
		}
		else
		{
			ft_strncpy(&s_pad[opt->width - opt->prec], pr, ft_strlen(pr));
			ft_memset(s_pad, ' ', opt->width - ft_strlen(pr));
		}
		ft_putnstr(s_pad, ft_strlen(s_pad), opt);
		free(s_pad);
	}
	else
		ft_putnstr(pr, ft_strlen(pr), opt);
	free(pr);
	return (0);
}

static int	check_width(t_option *opt, char *s_pad, char *temp)
{
	if (opt->prec < ft_strlen(temp) && opt->prec != -1)
		opt->pad = ' ';
	if (!(s_pad = make_padstr(opt->width, opt->pad)))
		return (-1);
	if (opt->minus == 1)
		ft_strncpy(s_pad, temp, ft_strlen(temp));
	else
		ft_strcpy(&s_pad[opt->width - ft_strlen(temp)], temp);
	ft_putnstr(s_pad, ft_strlen(s_pad), opt);
	free(s_pad);
	return (0);
}

int			print_hex(t_option *opt, va_list ap, char m)
{
	char	*temp;
	char	*s_pad;
	char	*s_prec;

	s_pad = 0;
	s_prec = 0;
	temp = (m == 'x') ? ft_itoa_base(va_arg(ap, int), "0123456789abcdef") :
		ft_itoa_base(va_arg(ap, int), "0123456789ABCDEF");
	if (opt->prec == 0)
		temp[0] = '\0';
	if (opt->prec > ft_strlen(temp))
	{
		if (check_prec(opt, s_prec, s_pad, temp) == -1)
			return (-1);
	}
	else if (opt->width > ft_strlen(temp))
	{
		if (check_width(opt, s_pad, temp) == -1)
			return (-1);
	}
	else
		ft_putnstr(temp, ft_strlen(temp), opt);
	free(temp);
	return (0);
}
