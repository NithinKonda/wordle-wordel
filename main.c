#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ResultGreen 1
#define ResultYellow 2
#define ResultRed 5
#define max 5195

// struct s_word {
//     char word[8];
// }
typedef char Result;
bool continuation;

struct s_result
{
    char color[5];
};

void seed(void);
char *randomword(int);
int readfile(char*);
void gameloop(char*);
bool isin(char, char *);
void Example_printing_the_results(Result*, char*, char*);
Result *checkword(char *, char *);
Result checkchar(char, int, char *);

int main(int, char **);
static char words[max][5];
void Example_printing_the_results(Result *res, char *guess, char *correct)
{
    int i;
    for (i = 0; i < 5; i++)
        switch (res[i])
        {
        case ResultGreen:
            printf("%s%c%s", ClrGreen, guess[i], ClrStop);
            break;
        case ResultYellow:
            printf("%s%c%s", ClrYellow, guess[i], ClrStop);
            break;
            break;
        case ResultRed:
            printf("%s%c%s", ClrRed, guess[i], ClrStop);
            break;
            break;
        default:
            printf("Unknown %d\n", res[i]);
            break;
        }
        printf("\n");
}

char *randomword(int m)
{
    int x;
    static char ret[8];
    x = rand() % m;

    ret[0] = words[x][0];
    ret[1] = words[x][1];
    ret[2] = words[x][2];
    ret[3] = words[x][3];
    ret[4] = words[x][4];
    ret[5] = 0;

    return ret;
}

bool isin(char c, char *str)
{
    int i, size;
    bool ret;
    ret = false;
    size = strlen(str);

    for (i = 0; i < size; i = i + 1)
    {
        if (str[i] == c)
        {
            ret = true;
            break;
        }
    }
    return ret;
}
Result checkchar(char guess, int idx, char *word)
{
    char correct;
    correct = word[idx];
    if (guess == correct)
    {
        return ResultGreen;
    }
    else if (isin(guess, word))
        return ResultYellow;
    return ResultRed;
}

int readfile(char *filename)
{

    char buf[8];
    int i, size;
    FILE *fd;
    fd = fopen(filename, "r");
    if (!fd)
    {
        perror("fopen");
        return -1;
    }

    size = max * 5;

    i = 0;
    memset(buf, 0, 8);
    while (fgets(buf, 7, fd))
    {
        size = strlen(buf);
        if (size < 1)
        {
            memset(buf, 0, 8);
            continue;
        }

        size--;
        buf[size] = 0;

        if (size != 5)
        {
            memset(buf, 0, 8);
            continue;
        }
        words[i][0] = buf[0];
        words[i][1] = buf[1];
        words[i][2] = buf[2];
        words[i][3] = buf[3];
        words[i][4] = buf[4];

        memset(buf, 0, 8);
        i++;

        if (max <= i)
        {
            break;
        }
    }

    fclose(fd);
    return i;
}
Result *checkword(char *guess, char *word)
{
    static Result res[5];
    int i;

    for (i = 0; i < 5; i++)
    {
        res[i] = checkchar(guess[i], i, word);
    }
    return res;
}

void seed()
{
    int x;
    x = getpid();
    srand(x);

    return;
}

void gameloop(char *correct)
{




}

int main(int argc, char *argv[])
{
    int n;


    char *p;
    seed();
    n = readfile("wl5.txt");
    assert(!(n < 0));
    p=randomword(n);
    continuation = true;
    while(continuation)
    {
        gameloop(p);
    }

    return 0;
}