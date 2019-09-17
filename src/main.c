#include <syslog.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "config.h"
#include "network.h"

struct url_t url;

void options_parse(int argc, char ** argv)
{
	int ch = 0;
	const char *opt_short = "hv";
	struct option opt_long[] =
	{
		{"help",	no_argument,	NULL,	'h'},
		{"version",	no_argument,	NULL,	'v'},
		{NULL,		0,		NULL,	0}
	};

	while ((ch = getopt_long(argc, argv, opt_short, opt_long, NULL)) != -1)
	{
		switch (ch)
		{
		case 'h':
		case '?':
			printf("Usage: %s [OPTIONS] [URL]\n", argv[0]);
			printf("  -v, --version             print version info and exit\n");
			printf("  -h, --help                print this help and exit\n");
			exit(0);
			break;

		case 'v':
			printf("Media Stream Analizer version %s\n", VERSION);
			break;

		default:
			//syslog(LOG_ERR, "invalid option -- %c", ch);
			printf("Try `%s --help' for more information.", argv[0]);
			exit(0);
		}
	}

	if (argc < 3)
	{
		printf("Invalid number of arguments.");
		exit(1);
	}

	for (int index = optind; index < argc; index++)
	{
		printf("Check this [%d]  URL: %s\n", index, argv[index]);
		if (url_parse(argv[index], index, &url) == false)
		{
			printf("Invalid argument: %s", argv[index]);
			exit(1);
		}
	}
	
}

int main(int argc, char **argv)
{
	//openlog(strrchr(argv[0], '/') != NULL ? strrchr(argv[0], '/') + 1 : argv[0], LOG_CONS | LOG_PERROR, LOG_DAEMON);

	options_parse(argc, argv);
	
	// Start work
//	url_open(&url);

//	url_receive(&url);

	//closelog();

	return EXIT_SUCCESS;
}
