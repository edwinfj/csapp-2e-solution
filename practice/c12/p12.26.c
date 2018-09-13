#include "csapp.h"
#include <netdb.h>
#include <string.h>

static sem_t mutex = 1;

struct hostent* gethostbyname_ts(const char *name)
{
	struct hostent *ent, *pent;
	int i, j;

	ent = (struct hostent*)malloc(sizeof(struct hostent));
	P(&mutex);
	pent = gethostbyname(name);
	ent->h_addrtype = pent->h_addrtype;
	ent->h_length = pent->h_length;

	for (i = 0; pent->h_name[i]; ++i);
	ent->h_name = (char*)malloc(sizeof(char) * (i+1));
	memcpy(ent->h_name, pent->h_name, sizeof(char)*(i+1));

	for (i = 0; pent->h_aliases[i]; ++i);
	ent->h_aliases = (char**)malloc(sizeof(char*) * (i+1));
	for (i = 0; pent->h_aliases[i]; ++i) {
		for (j = 0; pent->h_aliases[i][j]; ++j);
		ent->h_aliases[i] = (char*)malloc(sizeof(char) * (j+1));
		memcpy(ent->h_aliases[i], pent->h_aliases[i], sizeof(char)*(j+1));
	}

	for (i = 0; pent->h_addr_list[i]; ++i);
	ent->h_addr_list = (char**)malloc(sizeof(char*) * (i+1));
	for (i = 0; pent->h_addr_list[i]; ++i) {
		for (j = 0; pent->h_addr_list[i][j]; ++j);
		ent->h_addr_list[i] = (char*)malloc(sizeof(char) * (j+1));
		memcpy(ent->h_addr_list[i], pent->h_addr_list[i], sizeof(char)*(j+1));
	}

	V(&mutex);
	return ent;
}
