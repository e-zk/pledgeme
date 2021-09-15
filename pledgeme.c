#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
	if(pledge("stdio proc exec", argv[1]) == -1) {
		errx(1, "pledge");
	}

	argc -= 2;
	argv += 2;

	errno = 0;
	execvp(argv[0], &argv[0]);
	err((errno == ENOENT) ? 127 : 126, "%s", argv[0]);
}

static void __dead
usage(void) {
	fprintf(stderr, "usage: pledge <promises> program [argument ...]\n");
	exit(1);
}
