#include <netinet/ether.h>
#include <stdio.h>

/* print mac addr */
void printm(struct ether_addr *m)
{
	for (int i = 0; i < ETHER_ADDR_LEN; i++)
		printf("%02x%s", 
			m->ether_addr_octet[i],
			(i == 5)?"\n":":");
}

int main(int argc, char const *argv[])
{
	struct ether_addr *mac;
	char *str;

	/* ascii to mac */
	mac = ether_aton("20:7b:d5:1a:11:b8");
	printm(mac);

	/* mac to ascii */
	str = ether_ntoa(mac);
	printf("%s\n", str);

	/* get hostname from mac 
	(use /etc/ethers)

	char hostname[256];
	mac = ether_aton("xx:xx:xx:xx:xx:xx");

	if (!ether_ntohost(hostname, mac))
		printf("%s\n", hostname);

	*/

	return 0;
}