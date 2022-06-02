/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:22:22 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/02 20:04:52 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Check if are take the limit of eat philosophers
*/
void	ft_check_eat(t_philosophers *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->mutex_eating);
	while (i < philo->istance->number_of_philosophers)
	{
		if (philo->istance->philosophers[i]->count >= \
				philo->istance->number_philosopher_must_eat)
		{
			if (i == philo->istance->number_of_philosophers - 1)
			{
				pthread_mutex_lock(&philo->istance->mutex_write);
				philo->istance->stop = false;
			}
			i++;
		}
		else
			break ;
	}
	pthread_mutex_unlock(&philo->mutex_eating);
}

/*
Check that all philosophers aren't death.
Lock the eating beacuse if one philosophers is death block all process
The istance is false beaccuse in "main" exit of while
*/
void	*ft_check_death(void *arg)
{
	t_philosophers	*philo;

	philo = ((t_philosophers *)arg);
	while (philo->istance->stop)
	{
		if (!(philo->is_eating)
			&& ft_get_time() - philo->last_eat >= philo->istance->time_to_die)
		{
			pthread_mutex_lock(&philo->mutex_eating);
			ft_message_shell(philo->istance, philo->philosophers_number, \
							"died");
			philo->istance->stop = false;
			pthread_mutex_unlock(&philo->mutex_eating);
		}
		if (philo->istance->number_philosopher_must_eat
			&& philo->count >= philo->istance->number_philosopher_must_eat)
			ft_check_eat(philo);
		ft_usleep(100);
	}
	return (NULL);
}

/*
If all philosophers dont'death the routine continue
The philosophers take the fork, unlok the fork right and left, 
that have lok in ft_take_ fork.
ft_message_shell print the message in shell; last argument is message the write,,
second argument is the number of philosophers.
*/
void	*ft_routine(void *arg)
{
	t_philosophers	*philo;

	philo = ((t_philosophers *)arg);
	while (philo->istance->stop)
	{
		ft_take_fork(philo);
		pthread_mutex_unlock(&philo->istance->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->istance->forks[philo->right_fork]);
		ft_message_shell(philo->istance, philo->philosophers_number, \
						"is sleeping");
		ft_usleep(philo->istance->time_to_sleep);
		ft_message_shell(philo->istance, philo->philosophers_number, \
						"is thinking");
	}
	return (NULL);
}

/*
Repeat the routine and check that all philosophers don't are death
and that have eat
*/
void	ft_start_routin(t_main *istance)
{
	int	i;

	i = 0;
	while (i < istance->number_of_philosophers)
	{
		istance->philosophers[i]->last_eat = ft_get_time();
		pthread_create(&istance->philosophers[i]->philosophers_thread, NULL, \
			ft_routine, (void *)istance->philosophers[i]);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < istance->number_of_philosophers)
	{
		pthread_create(&istance->philosophers[i]->check_death_philosophers, \
			NULL, ft_check_death, (void *)istance->philosophers[i]);
		i++;
		usleep(100);
	}
}

/*
Strat the programm, check the arguments is correct. (135)
Create the mutex wirte, the fork, the philosophers, (140 - 1143)
Check the correcte creation of fork and philosophers (144)
Start with the routine the philosophers (147)
If the philosophers don't death the proces continue (148)
*/
int	main(int argc, char **argv)
{
	t_main	istance;

	if (ft_check_arguments(argc, argv, &istance) != 0)
	{
		ft_error(&istance);
		return (0);
	}
	pthread_mutex_init(&istance.mutex_write, NULL);
	istance.forks = ft_start_fork(&istance);
	istance.time = ft_get_time();
	istance.philosophers = ft_philosophers_start(&istance);
	if (!istance.philosophers || !istance.forks)
		return (0);
	istance.stop = true;
	ft_start_routin(&istance);
	while (istance.stop)
		continue ;
}