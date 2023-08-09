/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuzmin <zxcmasterass@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 20:25:48 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/08/09 01:20:51 by vkuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philos.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->count_eat = 0;
	data->death_flag = 0;
	data->start_time = 0;
	data->forks = (pthread_mutex_t *)malloc(sizeof(*(data->forks))
			* data->num_of_philo);
	if (!(data->forks))
		return (0);
	while (i < data->num_of_philo)
		if (pthread_mutex_init(&data->forks[i++], NULL))
			return (0);
	return (1);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philo = (t_philo *)malloc(sizeof(*(data->philo))
			* data->num_of_philo);
	if (!(data->philo))
		return (0);
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (0);
	while (i < data->num_of_philo)
	{
		data->philo[i].id = i;
		data->philo[i].data = data;
		data->philo[i].num_of_eat = 0;
		data->philo[i].start_eat_time = 0;
		data->philo[i].left_fork = i;
		if (i == 0)
			data->philo[i].right_fork = data->num_of_philo - 1;
		else
			data->philo[i].right_fork = i - 1;
		if (pthread_mutex_init(&data->philo[i].death_mutex, NULL))
			return (0);
		i++;
	}
	return (init_mutex(data));
}

int init_data(t_data *data, int argc, char **argv)
{
	data->num_of_philo = ft_atoi(argv[1]);
	data->t2d = ft_atoi(argv[2]);
	data->t2e = ft_atoi(argv[3]);
	data->t2s = ft_atoi(argv[4]);
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	return (1);
}