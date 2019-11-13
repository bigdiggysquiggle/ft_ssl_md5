/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 23:53:09 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/13 07:28:02 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

unsigned char	*post_checks(unsigned char *s, t_ssl_input *input)
{
	if (input->salt)
		s = append_salt(s, input);
	if (input->flags & a)
	{
		s = (unsigned char *)swap_n_free((char *)ft_base64_e((char *)s,
				input->len), (char **)&s);
		s = (unsigned char *)swap_n_free(ft_strjoin((char *)s, "\n"),
				(char **)&s);
		input->len = ft_strlen((char *)s);
	}
	return (s);
}

unsigned char	*ft_des_cbc_e(t_ssl_input *input)
{
	unsigned long	chunk;
	unsigned long	vector;
	unsigned long	*subkeys;
	size_t			i;
	unsigned char	*s;

	i = 0;
	subkeys = gen_key(input->key);
	vector = input->iv;
	s = (unsigned char *)ft_strnew(0);
	while (i < input->len)
	{
		chunk = 0;
		ft_memcpy(&chunk, input->input + i, 8);
		chunk = flip_end_512(chunk);
		chunk ^= vector;
		chunk = init_perm(chunk);
		chunk = flip_end_512(split_perm_e(chunk, subkeys));
		s = (unsigned char *)ft_hardjoin((char *)s, i, (char *)&chunk, 8);
		vector = flip_end_512(chunk);
		i += 8;
	}
	s = post_checks(s, input);
	free(subkeys);
	return (s);
}

unsigned char	*ft_des_cbc_d(t_ssl_input *input)
{
	unsigned long	chunk;
	unsigned long	vector;
	unsigned long	*subkeys;
	size_t			i;
	unsigned char	*s;

	i = 0;
	subkeys = gen_key(input->key);
	s = (unsigned char *)ft_strnew(0);
	while (i < input->len)
	{
		vector = input->iv;
		ft_memcpy(&chunk, input->input + i, 8);
		chunk = flip_end_512(chunk);
		input->iv = chunk;
		chunk = init_perm(chunk);
		chunk = split_perm_d(chunk, subkeys);
		chunk = flip_end_512(chunk ^ vector);
		s = (unsigned char *)ft_hardjoin((char *)s, i, (char *)&chunk, 8);
		i += 8;
	}
	free(subkeys);
	return (s);
}
