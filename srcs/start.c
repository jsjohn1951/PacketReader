/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 20:16:37 by wismith           #+#    #+#             */
/*   Updated: 2023/06/12 21:53:26 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PacketReader.h"
#include "../includes/utils.h"

/** @brief main function for parser thread 
 * @note uses pcap_loop to call handlr parse_pcap on each packet.
 * @note at end of loop data structure's stop attribute is set to true
 * 			flagging the writer thread to end it's loop as well.
*/
void	*parser_(void *dat)
{
	t_data	*data = (t_data *) dat;
		if (pcap_loop(data->pcap, 0, parse_pcap, (u_char *)data) < 0)
			ft_putstr(2, "-> Error processing pcap\n\n");
	pthread_mutex_lock(&data->m_stop);
	data->stop = true;
	pthread_mutex_unlock(&data->m_stop);

	return (NULL);
}

/** @brief function to write data to 'file' from queue
 * @note uses mutex lock and unlock to protect against data races.
 * @note data->WFILE contains the file descriptor for file being written to.
 * @note ft_putstr function used to write to the fd.
 * @note after writing to 'file' function will pop_first node in the queue.
*/
void	write_data(t_data *data)
{
	pthread_mutex_lock(&data->m_queue);
	if (data->queue)
	{
		pthread_mutex_unlock(&data->m_queue);

		pthread_mutex_lock(&data->m_queue);
		ft_putstr(data->WFILE, data->queue->data);
		pthread_mutex_unlock(&data->m_queue);

		ft_putstr(data->WFILE, "\n");

		pthread_mutex_lock(&data->m_queue);
		data->queue = pop_first(data->queue);
		pthread_mutex_unlock(&data->m_queue);
	}
	else
		pthread_mutex_unlock(&data->m_queue);
}

/** @brief main function for writer thread
 * @note writer is delayed by 50ms to allow parser thread to
 * 			go ahead of writer.
 * @note if data->stop flag yields true runtime is set to false
 * 			thus ending the loop and the thread.
 * @note mutex lock and unlock is used to protect against data races.
*/
void	*writer_(void *dat)
{
	bool	runtime = true;	
	t_data	*data = (t_data *) dat;

	// usleep(50);
	while (runtime)
	{
		write_data(data);

		pthread_mutex_lock(&data->m_stop);
		if (data->stop)
		{
			pthread_mutex_unlock(&data->m_stop);
			pthread_mutex_lock(&data->m_queue);
			if (!data->queue)
			{
				pthread_mutex_unlock(&data->m_queue);
				runtime = false;
			}
			else
				pthread_mutex_unlock(&data->m_queue);
		}
		else
			pthread_mutex_unlock(&data->m_stop);
	}
	return (NULL);
}

/** @brief function to create the threads and join them */
void	start(t_data *data)
{
	pthread_t		parser_id;
	pthread_t		writer_id;

	init_mutex_(data);
	ft_putstr(1, "Starting ...\n");

	pthread_create(&parser_id,
			NULL, parser_, data);
	pthread_create(&writer_id,
			NULL, writer_, data);

	pthread_join(parser_id, NULL);
	pthread_join(writer_id, NULL);
	
	ft_putstr(1, "Done!\n");
	destroy_mutex_(data);
}
