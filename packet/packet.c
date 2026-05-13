#include <netpacket/packet.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    /* 
    the raw ARP packet.

                Header
    destination MAC = broadcast addr,
    source MAC,
    type = 0x0806 - ARP.

            ARP request or reply
    HTYPE (hardware type) = 1 - Ethernet,
    PTYPE (protocol type) = 0x0800 - IPv4,
    HLEN (hardware addr len) = 6 - MAC len,
    PLEN (protocol addr len) = 4 - IPv4 len,
    OPER (opcode) = 1 - "who have this addr?",
    OPER = 2 - "it's me.",

    SHA (source hardware addr) = source MAC,
    SPA (source protocol addr) = source IP,
    THA (target hardware addr) = unknown,
    TPA (target protocol addr) = target IP.
    */

	unsigned char arp[42] = 
	{
        /*       ARP packet header       */
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0x20, 0x7b, 0xd5, 0x1a, 0x11, 0xb8,
		0x08, 0x06,

	/*    HTYPE,      PTYPE,    HLEN, PLEN,    OPER      */
		0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01, 

    /*   22    23    24    25    26    27   */
		0x20, 0x7b, 0xd5, 0x1a, 0x11, 0xb8, /* SHA */
		0xc0, 0xa8, 0x00, 0x0b, /* SPA */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* THA */
		0xc0, 0xa8, 0x00, 0x01 /* TPA */
	};
    unsigned char buf[1024];

	/* used in working with AF_PACKET for 
    addressing at the data link layer */
    struct sockaddr_ll sll = {0};
	int fd;

	sll.sll_ifindex = 2; /* interface index */

    fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    sendto(fd, arp, sizeof(arp), 0, (struct sockaddr*)&sll, sizeof(sll));

    recv(fd, buf, sizeof(buf), 0);
    printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
        buf[22], buf[23], buf[24], buf[25], buf[26], buf[27]);

	close(fd);

	return 0;
}