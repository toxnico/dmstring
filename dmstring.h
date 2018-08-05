#ifndef _DMSTRING_H
#define _DMSTRING_H

int indexOf(const char *str, const char *search, int start = 0);
char *clone(const char *str);
bool equals(const char *s1, const char *s2);
void substring(const char *str, int start, int length, char *output);
int substringInt(const char *str, int start, int length);
float substringFloat(const char *str, int start, int length);
void section(char *str, const char *separator, int index, char *output);
bool startsWith(const char *str, const char *stringToSearch);
#endif //_DMSTRING_H