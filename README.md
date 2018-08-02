#DMLibCpp

I essentially wrote this library to parse raw char* strings in an embedded, non-Arduino, environment (typically ESP-IDF).

Some fundamental (but not trivial with char* strings) functions are available:

* int indexOf(const char *str, const char *search, int start);
* char *clone(const char *str);
* bool equals(const char *s1, const char *s2);
* void substring(const char *str, int start, int length, char *output);
* void section(char *str, const char *separator, int index, char *output);