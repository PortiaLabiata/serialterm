#include <signal.h>
#include <stdlib.h>
#include "ui.h"

static void finish(int sig);
struct context_s ctx = {0};

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;

	signal(SIGINT, finish);
	ui_init(&ctx);

	for (;;) {
		ui_refresh(&ctx);
	}
	finish(0);

	return 0;
}

void finish(int sig) {
	(void)sig;
	ui_destroy(&ctx);
	exit(0);
}
