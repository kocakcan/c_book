#include <stdio.h>
#include <ctype.h>

enum State { OUT, IN };

void lower(char *s) {
	while (*s)
		*s = tolower((unsigned char)*s), s++;
}

void upper(char *s) {
	while (*s)
		*s = toupper((unsigned char)*s), s++;
}

void capitalize(char *s) {
	if (!s) return;
	*s = toupper((unsigned char)*s);
	for (++s; *s; s++)
		*s = tolower((unsigned char)*s);
}

/* title: capitalize each word in given string */
void title(char *s) {
	enum State STATE = OUT;
	for (; *s; s++) {
		if (*s == ' ' || *s == '\t' || *s == '\n')
			STATE = OUT;
		else if (STATE == OUT) {
			*s = toupper((unsigned char)*s);
			STATE = IN;
		} else {
			*s = tolower((unsigned char)*s);
		}
	}
}
	
int main(void) {
	char s[] = "THE LORD OF THE RINGS";

	title(s);
	printf("%s\n", s);
	return 0;
}
