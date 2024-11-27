#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#define ResultGreen 1
#define ResultYellow 2
#define ResultRed 5
#define max 5195
#define ValOk 0
#define ValBadInput 1
#define ValNoSuchWord 2
#define ClrGreen "\x1b[32m"
#define ClrRed "\x1b[31m"
#define ClrYellow "\x1b[33m"
#define ClrStop "\x1b[0m"
// struct s_word {
//     char word[8];
// }

typedef char ValResult;
typedef char Result;
static char words[max][5];
bool continuation;
int rounds;
bool corrects[5];
bool win;

struct s_result
{
    char color[5];
};

ValResult validator(char *);
char *readline(void);
void prompt(char*);
void seed(void);
char *randomword(int);
int readfile(char *);
void gameloop(char *);
bool isin(char, char *);
void Example_printing_the_results(Result *, char *, char *);
Result *checkword(char *, char *);
Result checkchar(char, int, char *);

int main(int, char **);


ValResult validator(char *word) {
    int n = strlen(word);
    if (n != 5) {
        return ValBadInput;
    }
    for (int i = 0; i < max; i++) {
        if (strncmp(words[i], word, 5) == 0) {
            return ValOk;
        }
    }
    return ValNoSuchWord;
}

void prompt( char *correctword)
{

    int i;
    for (i = 0; i < 5; i++)
        switch (correctword[i])
        {
        case false:
            printf("-");
            break;
        case true:
           
            printf("%c", correctword[i]);
            break;
        }
    printf("\n\n%d>", rounds);
    fflush(stdout);
}

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
        corrects[idx] = true;
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

char *readline()
{
    static char buf[8];
    int size;
    memset(buf, 0, 8);
    fgets(buf, 7, stdin);
    size = strlen(buf);
    assert(size > 0);
    size--;
    buf[size] = 0;
    return buf;
}

void gameloop(char *correct)
{
    char *input;
    Result *res;
    ValResult valres;
    int i, c;
    // printf("FOR DEBUGGING THE CORRECT WORD IS: %s", correct);
    prompt(correct);
    input = readline();
    valres = validator(input);
    switch (valres)
    {
    case ValBadInput:
        printf("%s\n", " no such word");
        return;
    case ValNoSuchWord:
        printf("%s\n", " ValNoSuchWord");
        rounds++;
        return;

    default:
        break;
    }
    res = checkword(input, correct);
    for (i = c = 0; i < 5; i++)
    {
        if (corrects[i])
        {
            c++;
        }
    }
    Example_printing_the_results(res,input,correct);
    if (c == 5)
    {
        win = true;
        continuation = false;
        return;
    }
    rounds++;
    if(rounds > 4){
        win = false;
        continuation = false;
        return;
    }
    return;
}

int main(int argc, char *argv[])
{
    int n;
    char *p;
    corrects[0] = false;
    corrects[1] = false;
    corrects[2] = false;
    corrects[3] = false;
    corrects[4] = false;
    rounds = 0;
    win = false;

    seed();

    n = readfile("wl5.txt");
    assert(!(n < 0));
    p = randomword(n);
    printf("-----\n\n>");
    fflush(stdout);
    continuation = true;
    while (continuation)
    {
        gameloop(p);
    }
    printf("The correct word is %s",p);
    if(win){
        printf("\nYou win!\n");
    }
    else{
        printf("\nYou lose!\n");
    }
    return 0;
}