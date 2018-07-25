#include "network.h"

#define BUFLEN 2048

bool url_parse(const char *addr, struct url_t *url)
{
	//url = malloc(sizeof(struct url_t));
	//url->network = PF_INET;
	//url->protocol = SOCK_DGRAM;
	//url->address = atoi("224.1.0.1");
	//url->port = 11111;

	return true;
}

bool url_open(struct url_t *url)
{
	if ((url->s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		perror("socket");
		exit(1);
	}

	memset(&url->a, 0, sizeof(url->a));
	url->a.sin_family = AF_INET;
	url->a.sin_port = htons(11111);
	url->a.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((bind(url->s, &url->a, sizeof(url->a))) < 0)
	{
		perror("bind");
		exit(1);
	}

	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr = inet_addr("225.0.0.1");
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);//inet_addr("10.118.1.99");

	if (setsockopt(url->s, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
	{
		perror("setsockopt");
		exit(1);
	}

	return true;
}

bool url_receive(struct url_t *url)
{
	struct sockaddr_in ra;
	char rb[BUFLEN];
	int rl = sizeof(ra);
	ssize_t rs;
	unsigned int pn = 0;
	
	while (true)
	{
		if ((rs = recvfrom(url->s, rb, BUFLEN, 0, &ra, &rl)) < 0)
		{
			perror("recvfrom");
			exit(1);
		}

		printf("Received packet %i from %s:%d\nSize: %i\n\n", ++pn, inet_ntoa(ra.sin_addr), ntohs(ra.sin_port), rs);
	}

	return true;
}

bool url_close(struct url_t *url)
{
	close(url->s);

	return true;
}
