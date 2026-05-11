#include <net/if.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	char buffer[IF_NAMESIZE];
	char *name = "lo";
	unsigned int index;

	/* get index */
	index = if_nametoindex(name);
	printf("index: %d\n", index);

	/* get name */
	if_indextoname(index, buffer);
	printf("name: %s\n", buffer);

	printf("\n");
	
	/* name_index = 
	[ [if_nameindex], [if_nameindex], ... ] */
	struct if_nameindex *name_index;
	index = 0;

	name_index = if_nameindex();	
	for (;name_index->if_name;name_index++, index++) {
		printf("index: %d, name: %s\n", 
			name_index->if_index, name_index->if_name);
	}
	name_index -= index;
	if_freenameindex(name_index);

	return 0;
}