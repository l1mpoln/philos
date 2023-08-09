/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuzmin <zxcmasterass@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 20:15:49 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/08/09 18:28:39 by vkuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philos.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6 || !ft_parse(argv))
		return (ft_error("Error with params"));
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_error("Failed to allocate memory"));
	if (!init_data(data, argc, argv))
		return (0);
	if (!init_philos(data))
	{
		free_data(data);
		return (0);
	}
	if (!start_threads(data, argc))
	{
		free_data(data);
		return (0);
	}
}
