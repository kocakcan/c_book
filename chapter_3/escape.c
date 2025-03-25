#include <stdio.h>

void escape(char s[], char t[]);
void rescape(char s[], char t[]);

int main() {
  char s[100] = "";
  char t[] = "This\tis\ta\ttest\n";

  escape(s, t);
  printf("%s\n", s);

  rescape(t, s);
  printf("%s\n", t);
  return 0;
}

void escape(char s[], char t[]) {
  int i = 0, j = 0;

  while (t[i] != '\0') {
    switch (t[i]) {
    case '\n':
      s[j++] = '\\';
      s[j++] = 'n';
      break;
    case '\t':
      s[j++] = '\\';
      s[j++] = 't';
      break;
    default:
      s[j++] = t[i];
      break;
    }
    i++;
  }

  s[j] = '\0';
}

void rescape(char s[], char t[]) {
  int i = 0, j = 0;

  while (t[i] != '\0') {
    if (t[i] == '\\') {
      i++;
      switch (t[i]) {
      case 't':
        s[j++] = '\t';
        break;
      case 'n':
        s[j++] = '\n';
        break;
      default:
        s[j++] = '\\';
        s[j++] = t[i];
        break;
      }
    } else {
      s[j++] = t[i];
    }
    i++;
  }

  s[j] = '\0';
}
