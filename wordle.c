#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define ResultGreen 1
#define ResultYellow 2
#define ResultRed 5

// struct s_word {
//     char word[8];
// }

struct s_result
{
    char color[5];
}

typedef char Result;
typedef Result[5] Results;

Results checkword(char *guess, char *word){
    Results res;
    int i;

    for (i=0; i<5;i++) {
        res[i]= checkchar(guess[i],i,word);
    }
    return res;
}
Result checkchar(char, int, char *);

int main();

Result checkchar(char guess,  int idx, char *word)
{
    char correct;
    correct = word[idx];
    switch (guess) {
        case correct:
            return ResultGreen;
        default:
            if (isin(guess, word))
                return ResultYellow;
    }
    return ResultRed;
    
}

int main()
{
    printf("abc\n");
    return 0;
}