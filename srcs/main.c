/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:38:26 by wismith           #+#    #+#             */
/*   Updated: 2023/07/02 18:20:28 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PacketReader.h"
#include "../includes/utils.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data	data;
	char	errbuff[PCAP_ERRBUF_SIZE];

	if (argc != 3)
		err(ERRNUMARGS);
	if (cmpExt(argv[1], ".pcap"))
		err(ERRARGEXT);
	if (!ft_strlen(argv[2]))
		err(ERRFILELEN);

	char	*file = ft_strjoin(argv[2], ".output");
	data.WFILE = open(file, O_CREAT | O_RDWR, 0666);
	free(file);

	init_data(&data);
	data.pcap = pcap_open_offline(argv[1], errbuff);

	if (!data.pcap)
		err(ERRPCAP);

	start(&data);

	printValues(data.root);
	destroyTree(data.root);
	pcap_close(data.pcap);
	close (data.WFILE);

	return (0);
}
