#include "dmstring.h"
#include <string.h>
#include <stdlib.h>

//#define CATCH_CONFIG_MAIN

int indexOf(const char *str, const char *search, int start = 0)
{
    const char *haystack = str + start;

    const char *found = strstr(haystack, search);
    if (found == NULL)
        return -1;

    int diff = (found - str);

    return diff;
}

char *clone(const char *str)
{
    return strdup(str);
}

bool equals(const char *s1, const char *s2)
{
    if (s1 == NULL && s2 == NULL)
        return true;

    if (s1 == NULL || s2 == NULL)
        return false;

    return strcmp(s1, s2) == 0;
}

void substring(const char *str, int start, int length, char *output)
{
    if (start + length > strlen(str))
        length = strlen(str) - start;
        

    for (int i = 0; i < length; i++)
    {
        output[i] = str[i + start];
    }
    output[length] = 0;
}

void section(char *str, const char *separator, int index, char *output)
{
    //separator not found? easy!
    if (indexOf(str, separator) == -1)
    {
        strcpy(output, str);
        return;
    }

    if (index == 0)
    {
        int nextIndex = indexOf(str, separator, 0);
        int tokenLength = nextIndex;
        substring(str, 0, nextIndex, output);
        return;
    }

    int lastIndex = indexOf(str, separator, 0);
    for (int i = 1; i <= index; i++)
    {
        
        if (i == index)
        {
            int nextIndex = indexOf(str, separator, lastIndex + 1);
            int tokenLength = nextIndex - (lastIndex+1);
            substring(str, lastIndex + 1, tokenLength, output);
            return;
        }
        lastIndex = indexOf(str, separator, lastIndex+1);
        if(lastIndex == -1)
        {
            strcpy(output, "");
            return;
        }
    }
}

#ifdef CATCH_CONFIG_MAIN

#include "catch.hpp"

TEST_CASE("string equality", "[equals]")
{
    REQUIRE(equals("bla", "bla") == true);
    REQUIRE(equals("bla", "bla1") == false);
    REQUIRE(equals(NULL, "bla1") == false);
    REQUIRE(equals(NULL, NULL) == true);
}

TEST_CASE("string cloning", "[clone]")
{
    const char *original = "paf";
    char *myClone = clone(original);

    REQUIRE(equals(myClone, original) == true);
    free(myClone);
    myClone = NULL;
}

TEST_CASE("string substring", "[subString]")
{
    const char *original = "pifpafpouf";
    char buff[50];

    substring(original, 0, 3, buff);
    REQUIRE(equals("pif", buff) == true);

    substring(original, 3, 4, buff);
    REQUIRE(equals("pafp", buff) == true);

    substring(original, 1, 15, buff);
    REQUIRE(equals("ifpafpouf", buff) == true);
}

TEST_CASE("string indexOf", "[indexOf]")
{
    const char *original = "blabliblo";
    const char *search = "bli";

    int idx = indexOf(original, search);
    REQUIRE(idx == 3);

    search = "bla";
    idx = indexOf(original, search);
    REQUIRE(idx == 0);

    search = "blo";
    idx = indexOf(original, search);
    REQUIRE(idx == 6);

    search = "paf";
    idx = indexOf(original, search);
    REQUIRE(idx == -1);

    search = "bl";
    idx = indexOf(original, search, 1);
    REQUIRE(idx == 3);

    search = "bl";
    idx = indexOf(original, search, 3);
    REQUIRE(idx == 3);

    search = "bl";
    idx = indexOf(original, search, 4);
    REQUIRE(idx == 6);

    search = "bla";
    idx = indexOf(original, search, 2);
    REQUIRE(idx == -1);
}

TEST_CASE("string sections", "[section]")
{
    char str[] = "un,deux,trois,quatre";
    char buff[50];

    section(str, ",", 0, buff);
    REQUIRE(equals("un", buff) == true);
    REQUIRE(equals("un,deux,trois,quatre", str) == true);

    section(str, ",", 1, buff);
    REQUIRE(equals("deux", buff) == true);

    section(str, ",", 2, buff);
    REQUIRE(equals("trois", buff) == true);

    section(str, ",", 3, buff);
    REQUIRE(equals("quatre", buff) == true);

    //hors limites -> ""
    section(str, ",", 4, buff);
    REQUIRE(equals("", buff) == true);

    //delimiteur non trouvé
    char str2[] = "abcd";
    section(str2, ";", 2, buff);
    REQUIRE(equals("abcd", buff));

    section(str2, "a", 0, buff);
    REQUIRE(equals("", buff));

    section(str2, "a", 1, buff);
    REQUIRE(equals("bcd", buff));

    REQUIRE(equals("un,deux,trois,quatre", str) == true);
}

#else
int main(int argc, char **args)
{
    char str[] = "un,deux,trois,quatre";
    char buff[50];

    section(str, ",", 0, buff);
    return 0;
}

#endif