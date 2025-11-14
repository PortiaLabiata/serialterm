#include "strbuf.h"

void strbuf_begin(struct strbuf_s *buf) {
	buf->size = 0;
}

void strbuf_end(struct strbuf_s *buf) {
	buf->buffer[buf->size] = '\0';
}

int strbuf_push(struct strbuf_s *buf, char c) {
	if (buf->size >= MAX_LINE_LEN-1) {
		return -1;
	}
	buf->buffer[buf->size++] = c;
	return 0;
}

char strbuf_unpush(struct strbuf_s *buf) {
	if (buf->size > 0) {
		char c = buf->buffer[buf->size];
		buf->buffer[buf->size--] = '\0';
		return c;
	}
	return '\0';
}

void strpad_begin(struct strpad_s *pad) {
	pad->size = 1;
	strbuf_begin(&pad->buffers[0]);
}

int strpad_pushc(struct strpad_s *pad, char c) {
	if (c == '\r') {
		if (pad->size >= MAX_LINE_NUM) {
			return -1;
		}
		strbuf_end(&pad->buffers[pad->size-1]);
		strbuf_begin(&pad->buffers[pad->size++]);
	} else {
		strbuf_push(&pad->buffers[pad->size-1], c);
	}
	return 0;
}

struct strbuf_s *strpad_curbuf(struct strpad_s *pad) {
	return &pad->buffers[pad->size-1];
}

ssize_t strpad_nextline(struct strpad_s *pad, char **line_ptr, size_t *cnt) {
	if (*cnt >= pad->size-1) {
		*line_ptr = NULL;
		return -1;
	}
	struct strbuf_s *buf = &pad->buffers[(*cnt)++];
	*line_ptr = buf->buffer;
	return buf->size;
}

size_t strpad_cursx(struct strpad_s *pad) {
	return pad->buffers[pad->size-1].size + 1;
}
