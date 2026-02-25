#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum LOG_LEVEL { INFO, WARNING, ERROR };

typedef struct {
  char *message;
  char *author;
  enum LOG_LEVEL log_level;
} Log;

void destroy_log(Log *);
Log *create_log(char *, char *, enum LOG_LEVEL);
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

#define VALIDATE_LOG(log_ptr)                                                  \
  do {                                                                         \
    Log *_l = (log_ptr);                                                       \
    LOG_ASSERT(_l != NULL, "Log pointer is NULL");                             \
    LOG_ASSERT(_l->message != NULL, "Log message is NULL");                    \
    LOG_ASSERT(_l->author != NULL, "Log author is NULL");                      \
    LOG_ASSERT(_l->log_level >= INFO && _l->log_level <= ERROR,                \
               "Log level out of valid range");                                \
  } while (0)

int main(void) {
  FILE *fp;

  Log *first_log = create_log("This is a test", "Can", INFO);
  
  if (first_log == NULL) {
	  fprintf(stderr, "Log creation failed!\n");
	  return 1;
  }

  Log *second_log = create_log("This is yet another test", "Can", ERROR);

  if (second_log == NULL) {
	  fprintf(stderr, "Log creation failed!\n");
	  return 1;
  }

  Log *third_log = create_log("Kept you waiting, huh?", "Solid Snake", INFO);

  if (third_log == NULL) {
	  fprintf(stderr, "Log creation failed!\n");
	  return 1;
  }
  Log *fourth_log = create_log("You're pretty good.", "Revolver Ocelot", INFO);

  if (fourth_log == NULL) {
	  fprintf(stderr, "Log creation failed!\n");
	  return 1;
  }

  Log *fifth_log = create_log("This log is on the heap", "Can", INFO);

  if (fifth_log == NULL) {
	  fprintf(stderr, "Failed to create log!\n");
	  return 1;
  }
  Log *logs[] = {first_log, second_log, third_log, fourth_log, fifth_log};

  for (size_t i = 0; i < 5; i++)
    VALIDATE_LOG(logs[i]);

  if ((fp = fopen("test.log", "w")) != NULL) {
    for (size_t i = 0; i < 5; i++)
      fprintf(fp, "Message: %s | Log level: %s | Author: %s\n", logs[i]->message,
              parse_log_level(logs[i]), logs[i]->author);
	  fclose(fp);
  }
  for (size_t i = 0; i < 5; i++)
	  destroy_log(logs[i]);

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

Log *create_log(char *message, char *author, enum LOG_LEVEL log_level) {
  Log *new_log = malloc(sizeof(*new_log));

  if (new_log == NULL) {
    fprintf(stderr, "Memory allocation failed!\n");
    return NULL;
  }

  new_log->message = strdup(message);
  if (new_log->message == NULL) {
    free(new_log);
    fprintf(stderr, "Memory allocation failed for message!\n");
    return NULL;
  }

  new_log->author = strdup(author);
  if (new_log->author == NULL) {
    free(new_log->message);
    free(new_log);
    fprintf(stderr, "Memory allocation failed for author!\n");
    return NULL;
  }
  new_log->log_level = log_level;
  return new_log;
}

void destroy_log(Log *l) {
  if (l == NULL)
    return;
  free(l->message);
  free(l->author);
  free(l);
}
