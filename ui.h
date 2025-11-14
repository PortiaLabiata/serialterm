#pragma once
#include <curses.h>
#include "strbuf.h"

struct context_s {
	struct strpad_s pad;
	size_t scroll_position;
};

int ui_init(struct context_s *ctx);
int ui_refresh(struct context_s *ctx);
void ui_destroy(struct context_s *ctx);
