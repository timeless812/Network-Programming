#include <net/route.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	/* use to manage entries 
	in the routing table */
	struct rtentry rt = {0};
	/* use for set dest addr, 
	gateway and genmask */
	struct sockaddr_in *addr;
	int fd;

	fd = socket(AF_INET, SOCK_STREAM, 0);

	addr = (struct sockaddr_in *)&rt.rt_dst;
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = inet_addr("192.168.0.0");

	addr = (struct sockaddr_in *)&rt.rt_gateway;
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = inet_addr("192.168.0.1");

	addr = (struct sockaddr_in *)&rt.rt_genmask;
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = inet_addr("255.255.255.0");

	rt.rt_flags = RTF_UP | RTF_GATEWAY;
	rt.rt_metric = 200;
 
 	/* attempt add route */
	if (ioctl(fd, SIOCADDRT, &rt) == -1) {
	    perror("ioctl SIOCADDRT failed");
	}
	else {
	    printf("route added successfully.\n");
	}

	/* and delete this route */
	// if (ioctl(fd, SIOCDELRT, &rt) == -1) {
	//     perror("ioctl SIOCDELRT failed");
	// }
	// else {
	//     printf("route deleted successfully.\n");
	// }

	close(fd);

	return 0;
}