#include <stdio.h>
#include <stdlib.h>

enum LOG_LEVEL { INFO, WARNING, ERROR };

typedef struct {
  char *message;
  char *author;
  enum LOG_LEVEL log_level;
} Log;

char *parse_log_level(Log *);
void printl(Log *);

#define LOG_ASSERT(condition, message)                                         \
  do {                                                                         \
    if (!(condition)) {                                                        \
      fprintf(stderr, "Assertion failed in %s (line %d): %s\n", __func__,      \
              __LINE__, message);                                              \
      abort();                                                                 \
    }                                                                          \
  } while (0)

#define VALIDATE_LOG(log_ptr) \
	do { \
		Log *_l = (log_ptr); \
		LOG_ASSERT(_l != NULL, "Log pointer is NULL"); \
		LOG_ASSERT(_l->message != NULL, "Log message is NULL"); \
		LOG_ASSERT(_l->author != NULL, "Log author is NULL"); \
		LOG_ASSERT(_l->log_level >= INFO && _l->log_level <= ERROR, \
				"Log level out of valid range"); \
	} while (0)

int main(void) {
  FILE *fp;

  Log first_log = {
      .author = "Can",
      .message = "This is a test",
      .log_level = INFO,
  };
  Log second_log = {
      .author = "Can",
      .message = "This is another test",
      .log_level = WARNING,
  };
  Log third_log = {
      .author = "Can",
      .message = "This is yet another test",
      .log_level = ERROR,
  };
  Log fourth_log = {
      .author = "TEST",
      .message = "This is a test",
      .log_level = INFO,
  };
  Log logs[] = {first_log, second_log, third_log, fourth_log};

  for (size_t i = 0; i < 4; i++)
    VALIDATE_LOG(&logs[i]);

  if ((fp = fopen("test.log", "w")) != NULL)
    for (size_t i = 0; i < 4; i++)
      fprintf(fp, "Message: %s | Log level: %s | Author: %s\n", logs[i].message,
              parse_log_level(&logs[i]), logs[i].author);
  fclose(fp);

  return 0;
}

char *parse_log_level(Log *l) {
  switch (l->log_level) {
  case INFO:
    return "INFO";
    break;
  case WARNING:
    return "WARNING";
    break;
  case ERROR:
    return "ERROR";
    break;
  default:
    fprintf(stderr, "error: Unknown log level %d\n", l->log_level);
    return "UNKNOWN";
  }
}

void printl(Log *l) {
  printf("Message: %s | Log level: %s | Author: %s\n", l->message,
         parse_log_level(l), l->author);
}
