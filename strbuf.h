#pragma once
#include <string.h>
#include <sys/types.h>

#define MAX_LINE_LEN 1024
#define MAX_LINE_NUM 1024

struct strbuf_s {
	char buffer[MAX_LINE_LEN];
	size_t size;
};

void strbuf_begin(struct strbuf_s *buf);
void strbuf_end(struct strbuf_s *buf);
int strbuf_push(struct strbuf_s *buf, char c); 
char strbuf_unpush(struct strbuf_s *buf);

struct strpad_s {
	struct strbuf_s buffers[MAX_LINE_NUM];
	size_t size;
};

void strpad_begin(struct strpad_s *pad);
int strpad_pushc(struct strpad_s *pad, char c);
ssize_t strpad_nextline(struct strpad_s *pad, char **line_ptr, size_t *cnt);
size_t strpad_cursx(struct strpad_s *pad);
struct strbuf_s *strpad_curbuf(struct strpad_s *pad);
