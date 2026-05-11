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
	
	snprintf(ifr.ifr_name, IFNAMSIZ, "%s", name);
	fd = socket(AF_INET, SOCK_STREAM, 0);

	printf("name: %s\n", name);

	ioctl(fd, SIOCGIFHWADDR, &ifr);

	unsigned char *mac = (unsigned char *)ifr.ifr_hwaddr.sa_data;
	printf("mac: %02x:%02x:%02x:%02x:%02x:%02x\n", 
		mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

	ioctl(fd, SIOCGIFADDR, &ifr);

	unsigned char *ip = (unsigned char*)ifr.ifr_addr.sa_data;
	printf("ip: %hhu.%hhu.%hhu.%hhu\n",
		ip[0+2], ip[1+2], ip[2+2], ip[3+2]);

	ioctl(fd, SIOCGIFMTU, &ifr);
	
	int mtu = ifr.ifr_mtu;
	printf("mtu: %d\n", mtu);

	ioctl(fd, SIOCGIFFLAGS, &ifr);

	char *up = (ifr.ifr_flags&IFF_UP)?"UP ":"";
	char *broadcast = (ifr.ifr_flags&IFF_BROADCAST)?"BROADCAST ":"";
	char *loopback = (ifr.ifr_flags&IFF_LOOPBACK)?"LOOPBACK":"";

	printf("flags: <%s%s%s>", up, broadcast, loopback);

	return 0;
}