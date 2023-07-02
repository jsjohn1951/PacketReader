/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:05:00 by wismith           #+#    #+#             */
/*   Updated: 2023/07/02 18:59:56 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PacketReader.h"
#include "../includes/utils.h"

/** @brief adds string to the queue to be written to file
 * @note data structure's queue attributes may be accessed by writer thread
 * @note uses mutex_locks and unlocks to protect again data races.
*/
void	add_queue(t_data *data, char *s)
{
	pthread_mutex_lock(&data->m_queue);
	if (!data->queue)
	{
		pthread_mutex_unlock(&data->m_queue);

		pthread_mutex_lock(&data->m_queue);
		data->queue = new_entry(s);
		pthread_mutex_unlock(&data->m_queue);
	}
	else
	{
		pthread_mutex_unlock(&data->m_queue);
		pthread_mutex_lock(&data->m_queue);
		push_back(data->queue, s);
		pthread_mutex_unlock(&data->m_queue);
	}
}

/** @brief parses the connection protocol 
 * @note ternary operator used in place of if/else statements.
 * @note returns an allocated string to be written to 'file.'
*/
char	*protocol(struct ip *ip_header)
{
	return ( ft_strdup(
					ip_header->ip_p == IPPROTO_TCP ? "TCP" :
					ip_header->ip_p == IPPROTO_UDP ? "UDP" :
					ip_header->ip_p == IPPROTO_ICMP ? "ICMP" :
					"UNKNOWN" ) );
}

/** @brief parses source and destination ips 
 * @note t_string structure is used for string manipulation
 * 			purposes.
 * @note returns and allocated string to be written to 'file'
*/
char	*ip_src_dst(struct ip *ip_header, t_hash *hashAttr)
{
	char src_ip[INET_ADDRSTRLEN];
    char dst_ip[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &(ip_header->ip_src), src_ip, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &(ip_header->ip_dst), dst_ip, INET_ADDRSTRLEN);

	hashAttr->src_ip = ft_strdup(src_ip);
	hashAttr->dst_ip = ft_strdup(dst_ip);

	t_strings	sets = {
			ft_strjoin("ip ", src_ip),
			ft_strjoin(sets.set, " -> "),
			ft_strjoin(sets.set2, dst_ip)};

	free_all(2, sets.set, sets.set2);
	return (sets.res);
}

/** @brief parses ports for tcp and udp packets. 
 * @note the src and dst arrays are modified by dereferencing
 * @note tcp connection macro : IPPROTO_TCP
 * @note udp connection macro : IPPROTO_UDP
*/
void	ports(struct ip *head, const u_char *pack, u_int16_t *src, u_int16_t *dst)
{
	if (head->ip_p == IPPROTO_TCP) {
        struct tcphdr *tcp_header
			= (struct tcphdr *)(pack + 14 + head->ip_hl * 4);
        *src = ntohs(tcp_header->th_sport);
        *dst = ntohs(tcp_header->th_dport);

    } else if (head->ip_p == IPPROTO_UDP) {
        struct udphdr *udp_header
			= (struct udphdr *)(pack + 14 + head->ip_hl * 4);
        *src = ntohs(udp_header->uh_sport);
        *dst = ntohs(udp_header->uh_dport);
    }
}

/** @brief parses ports for tcp and udp packets.
 * @note the action parsing is done by `ports function.
 * @note t_string structure is used for string manipulation
 * 			purposes.
 * @note returns an allocated string to be written to 'file.'
*/
char	*tcp_udp_ports(struct ip *ip_header, const u_char *packet_data, t_hash *hashAttr)
{
	u_int16_t src_port = 0;
	u_int16_t dst_port = 0;

	ports(ip_header, packet_data, &src_port, &dst_port);
	char	*src = num_str_gen(src_port);
	char	*dst = num_str_gen(dst_port);

	hashAttr->src_p = src_port;
	hashAttr->dst_p = dst_port;

	t_strings	sets = {
			ft_strjoin("Ports ", src),
			ft_strjoin(sets.set, " -> "),
			ft_strjoin(sets.set2, dst)};

	free_all(4, src,
		dst, sets.set, sets.set2);
	return (sets.res);
}

/** @brief parses the mac source and destination addresses
 * @note returns an allocated string to be written to file.
 * @note t_string is used for string manipulation purposes.
*/
char	*mac_srcs_dst(struct ether_header *eth_header)
{
	struct ether_addr *src_mac = (struct ether_addr *)(eth_header->ether_shost);
    struct ether_addr *dst_mac = (struct ether_addr *)(eth_header->ether_dhost);
	
	if (ntohs(eth_header->ether_type) != ETHERTYPE_IP)
		return (NULL);

	t_strings	sets = {
			ft_strjoin("mac ", ether_ntoa(src_mac)),
			ft_strjoin(sets.set, " -> "),
			ft_strjoin(sets.set2, ether_ntoa(dst_mac))};

	free_all(2, sets.set, sets.set2);
	return (sets.res);
}

/** @brief generates and inserts a new tree node into the binary tree
 * 			if the hash_value is unique in both forward and reverse order.
 * @brief If reverse hash value exists in tree ( hash_value2 ),
 * 			it means that the packet is incoming, not outgoing.
*/
void	genTreeNode(t_hash *hashAttr, t_data *data)
{
	t_node	*node = NULL;				
	unsigned long hash_value1 = hash( hashAttr->src_ip,
								hashAttr->dst_ip,
								hashAttr->src_p,
								hashAttr->dst_p,
								37,
								9 );

	unsigned long hash_value2 = hash( hashAttr->dst_ip,
								hashAttr->src_ip,
								hashAttr->dst_p,
								hashAttr->src_p,
								37,
								9 );

	if (data->root && (node = search(hash_value1, data->root)))
	{
		node->nConOut++;
		return ;
	}
	else if (data->root && (node = search(hash_value2, data->root)))
	{
		node->nConIn++;
		return ;
	}

	node = newNode(hash_value1);
	node->nConOut++;
	data->root = insert(data->root, node);
}

/** @brief Main function used to parse the connection.
 * 			Used as handlr function for pcap_loop.
 * @note data is first argument for function.
 * @note data to be written to 'file' is added to the queue
 * 			using the add_queue function.
*/
void	parse_pcap ( u_char *user_data,
						const struct pcap_pkthdr *pkthdr,
								const u_char *packet_data )
{
	t_hash	hashAttr = {NULL,
					NULL,
					0,
					0 };

	(void)	pkthdr;
	t_data	*data = (t_data *) user_data;

	char	*mac_ = mac_srcs_dst( (struct ether_header *)packet_data );
	if (!mac_)
		return ;

	char	*proto = protocol( (struct ip *)(packet_data + 14) );
	char	*ip_ = ip_src_dst( (struct ip *)(packet_data + 14) , &hashAttr);

	add_queue(data, proto);
	add_queue(data, ip_);
	add_queue(data, mac_);

	//* Ports
	if (!ft_strcmp(proto, "TCP") || !ft_strcmp(proto, "UDP"))
	{
		char	*ports_ = tcp_udp_ports( (struct ip *)(packet_data + 14), 
											packet_data , &hashAttr);
		add_queue(data, ports_);
		free (ports_);
	}
	
	add_queue(data, "-------------------------------");

	genTreeNode(&hashAttr, data);

	free_all(5, proto, mac_, ip_, hashAttr.src_ip, hashAttr.dst_ip);
	data->npcap++;
}
