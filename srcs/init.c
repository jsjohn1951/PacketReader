/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:55:32 by wismith           #+#    #+#             */
/*   Updated: 2023/06/27 16:39:41 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/data.h"

/** @brief initializes data attributes */
void	init_data(t_data *data)
{
	data->pcap = NULL;
	data->queue = NULL;
	data->root = NULL;
	data->stop = false;
}

/** @brief initializes mutexes */
void	init_mutex_(t_data *data)
{
	pthread_mutex_init(&data->m_queue, NULL);
	pthread_mutex_init(&data->m_stop, NULL);
}

/** @brief destroys mutexes */
void	destroy_mutex_(t_data *data)
{
	pthread_mutex_destroy(&data->m_queue);
	pthread_mutex_destroy(&data->m_stop);
}
