/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuzmin <zxcmasterass@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 01:46:54 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/08/09 18:28:07 by vkuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philos.h"

void	philo_takes_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->death_flag)
		printf("%lld\t%d\thas taken a fork\n",
			get_time() - philo->data->start_time, philo->id + 1);
	if (!philo->data->death_flag)
		printf("%lld\t%d\thas taken a fork\n",
			get_time() - philo->data->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->death_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	philo->start_eat_time = get_time();
	if (!philo->data->death_flag)
		printf("%lld\t%d\tis eating\n", philo->start_eat_time
			- philo->data->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->data->print_mutex);
	philo->num_of_eat += 1;
	if ((philo->num_of_eat == philo->data->must_eat)
		&& (!philo->data->death_flag))
		philo->data->count_eat += 1;
	philo_time_to(philo->data->t2e);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->death_mutex);
}

void	philo_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->death_flag)
		printf("%lld\t%d\tis sleeping\n",
			get_time() - philo->data->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->data->print_mutex);
	philo_time_to(philo->data->t2s);
}

void	philo_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->death_flag)
		printf("%lld\t%d\tis thinking\n",
			get_time() - philo->data->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
