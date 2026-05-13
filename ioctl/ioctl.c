#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <net/if.h>

int main(int argc, char const *argv[])
{
	struct ifreq ifr = {0};
	char *name = "lo";
	int fd;

	unsigned char *mac;
	unsigned char *ip;
	int mtu;

	char *up;
	char *broadcast;
	char *loopback;
	
	snprintf(ifr.ifr_name, IFNAMSIZ, "%s", name);
	
	fd = socket(AF_INET, SOCK_STREAM, 0);

	/* get interface parameters */
	ioctl(fd, SIOCGIFHWADDR, &ifr);
	mac = (unsigned char *)ifr.ifr_hwaddr.sa_data;

	ioctl(fd, SIOCGIFADDR, &ifr);
	ip = (unsigned char*)ifr.ifr_addr.sa_data;

	ioctl(fd, SIOCGIFMTU, &ifr);
	mtu = ifr.ifr_mtu;

	ioctl(fd, SIOCGIFFLAGS, &ifr);
	up = (ifr.ifr_flags&IFF_UP)?"UP ":"";
	broadcast = (ifr.ifr_flags&IFF_BROADCAST)?"BROADCAST ":"";
	loopback = (ifr.ifr_flags&IFF_LOOPBACK)?"LOOPBACK":"";

	printf("name: %s\n", name);
	printf("mac: %02x:%02x:%02x:%02x:%02x:%02x\n", 
		mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	printf("ip: %hhu.%hhu.%hhu.%hhu\n",
		ip[0+2], ip[1+2], ip[2+2], ip[3+2]);
	printf("mtu: %d\n", mtu);
	printf("flags: <%s%s%s>\n", up, broadcast, loopback);

	return 0;
}