/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuzmin <zxcmasterass@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 20:15:25 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/08/09 18:40:35 by vkuzmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct	s_philo
{
	t_data			*data;
	int				id;
	int				num_of_eat;
	long long		start_eat_time;
	int				left_fork;
	int				right_fork;
	pthread_mutex_t	death_mutex;
};

struct	s_data
{
	pthread_t		*thread;
	pthread_t		*death;
	t_philo			*philo;
	int				num_of_philo;
	int				t2d;
	int				t2e;
	int				t2s;
	int				must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	int				death_flag;
	int				count_eat;
	long long		start_time;
};

//utils
int			ft_parse(char **argv);
int			ft_error(char *str);
int			ft_atoi(const char *str);
long long	get_time(void);
void		philo_time_to(int time);
int			free_data(t_data *data);

//init
int			init_philos(t_data *data);
int			init_data(t_data *data, int argc, char **argv);

//threads
int			start_threads(t_data *data, int argc);

//actions
void		philo_takes_forks(t_philo *philo);
void		philo_eating(t_philo *philo);
void		philo_sleeping(t_philo *philo);
void		philo_thinking(t_philo *philo);

#endif
