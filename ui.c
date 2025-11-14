#include <curses.h>
#include <locale.h>
#include <string.h>
#include <stdio.h>
#include "ui.h"

static WINDOW *history_w = NULL;
static WINDOW *prompt_w = NULL;

int ui_init(struct context_s *ctx) {
	(void)ctx;
	(void)initscr();
	(void)cbreak();
	(void)noecho();
	(void)nonl();
	(void)nodelay;

	history_w = newwin(LINES-3, 0, 0, 0);
	prompt_w = newwin(3, 0, LINES-3, 0);

	(void)keypad(history_w, TRUE);
	(void)keypad(prompt_w, TRUE);
	strpad_begin(&ctx->pad);
	wmove(prompt_w, 1, 1);
	ctx->scroll_position = 0;
	return 0;
}

static void update_history(struct context_s *ctx) {
	char *line_ptr = NULL;
	size_t line_idx = ctx->scroll_position;
	while (strpad_nextline(&ctx->pad, &line_ptr, &line_idx) > 0) {
		if (line_idx > (size_t)getmaxy(history_w)) break;
		wmove(history_w, line_idx - ctx->scroll_position, 1);
		waddnstr(history_w, line_ptr, MAX_LINE_LEN);		
	}
}

static void draw_symbol(struct context_s *ctx, char c) {
	if (getcurx(prompt_w) >= 1) waddch(prompt_w, c);
	if (c == '\r') {
		werase(prompt_w);
		wmove(prompt_w, 1, 1);
	}
	if (c == '\b') {
		strbuf_unpush(strpad_curbuf(&ctx->pad));
		wclrtoeol(prompt_w);
	}
}

int ui_refresh(struct context_s *ctx) {
	box(history_w, 0, 0);
	box(prompt_w, 0, 0);
	wrefresh(history_w);

	int c = '\0';
	if ((c = wgetch(prompt_w)) != ERR) {
		switch (c) {
			case KEY_PPAGE:
				if (ctx->scroll_position > 0) {
					ctx->scroll_position--;
					werase(history_w);
				}
				goto update;
			case KEY_NPAGE:
				if (ctx->scroll_position < (size_t)getmaxy(history_w)-2) {
					ctx->scroll_position++;
					werase(history_w);
				}
				goto update;
			default:
				break;
		}
		draw_symbol(ctx, c);
		strpad_pushc(&ctx->pad, c);
	}
update:
	update_history(ctx);
	return 0;
}

void ui_destroy(struct context_s *ctx) {
	(void)ctx;
	delwin(history_w);
	delwin(prompt_w);

	(void)endwin();
}
