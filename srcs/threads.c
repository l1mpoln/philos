/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuzmin <zxcmasterass@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 01:35:01 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/08/09 01:21:03 by vkuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philos.h"

void	*eat_monitoring(void *thread)
{
	t_data	*data;

	data = thread;
	while (!data->death_flag)
	{
		pthread_mutex_lock(&data->print_mutex);
		if (data->count_eat == data->num_of_philo)
			data->death_flag = 1;
		pthread_mutex_unlock(&data->print_mutex);
	}
	return (NULL);
}

void	*monitoring(void *thread)
{
	t_philo	*philo;

	philo = thread;
	while (!philo->data->death_flag)
	{
		pthread_mutex_lock(&philo->death_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		if (get_time() - philo->start_eat_time >= philo->data->t2d
			&& !philo->data->death_flag)
		{
			printf("%lld\t%d\tdied\n", get_time() - philo->data->start_time,
				   philo->id + 1);
			philo->data->death_flag = 1;
		}
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_unlock(&philo->death_mutex);
	}
	return (NULL);
}

void	*start_routine(void *thread)
{
	t_philo	*philo;

	philo = thread;
	philo->start_eat_time = get_time();
	if (((philo->id) % 2) != 0)
		usleep(philo->data->t2e * 500);
	if (philo->data->num_of_philo != 1)
	{
		while (!philo->data->death_flag)
		{
			philo_takes_forks(philo);
			philo_eating(philo);
			philo_sleeping(philo);
			philo_thinking(philo);
		}
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		if (!philo->data->death_flag)
			printf("%lld\t%d\thas taken a fork\n",
				   get_time() - philo->data->start_time, philo->id + 1);
		usleep(philo->data->t2d * 1000);
	}
	return (NULL);
}

void	waiting(t_data *data, pthread_t *thread, pthread_t *death,
						int argc)
{
	int			i;
	pthread_t	eat;

	if (argc == 6)
	{
		pthread_create(&eat, NULL, eat_monitoring, data);
		pthread_detach(eat);
	}
	i = -1;
	while (++i < data->num_of_philo)
	{
		pthread_join(thread[i], NULL);
		pthread_join(death[i], NULL);
	}
}

int	start_threads(t_data *data, int argc)
{
	int			i;
	pthread_t	*thread;
	pthread_t	*death;

	i = -1;
	thread = (pthread_t *)malloc(sizeof(pthread_t) * data->num_of_philo);
	death = (pthread_t *)malloc(sizeof(pthread_t) * data->num_of_philo);
	if (!thread || !death)
		return (0);
	data->start_time = get_time();
	while (++i < data->num_of_philo)
		pthread_create(&thread[i], NULL, start_routine, &data->philo[i]);
	usleep(1000);
	i = -1;
	while (++i < data->num_of_philo)
		pthread_create(&death[i], NULL, monitoring, &data->philo[i]);
	waiting(data, thread, death, argc);
	free(thread);
	free(death);
	return (1);
}