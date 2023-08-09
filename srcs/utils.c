/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuzmin <zxcmasterass@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 20:18:43 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/08/09 19:05:53 by vkuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philos.h"

int	ft_parse(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			else
				j++;
		}
		i++;
	}
	return (1);
}

int	free_data(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->num_of_philo)
			pthread_mutex_destroy(&data->forks[i++]);
		free(data->forks);
	}
	if (data->philo)
	{
		i = 0;
		while (i < data->num_of_philo)
			pthread_mutex_destroy(&data->philo[i++].death_mutex);
		free(data->philo);
	}
	pthread_mutex_destroy(&data->print_mutex);
	free(data);
	return (0);
}

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	philo_time_to(int time)
{
	long long	x;
	long long	y;

	x = get_time() + time;
	while (get_time() < x)
	{
		y = x - get_time();
		if (y <= 50)
			usleep(10);
		else
			usleep(100);
	}
}
