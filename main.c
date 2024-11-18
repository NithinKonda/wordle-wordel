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

void Example_printing_the_results(Result*);

Result *checkword(char *, char *);
Result checkchar(char, int, char *);

int main(int, char**);


void Example_printing_the_results[](Result[] res) {
    int i;
    for (i=0; i<5; i++) 
        switch(res[i]) {
            case ResultGreen:
                printf("%s\n","Green");
                break;
            case ResultYellow:
                printf("%s\n","Yellow");
                break;
            case ResultRed:
                printf("%s\n","Red");
                break;
            default:
                printf("Unknown %d\n",res[i]);
                break;

    }
}


bool isin(char guess, char *word){
    int i;
    for (i=0; i<5; i++){
        if (guess == word[i])
            return true;
    }
    return false;
}
Result checkchar(char guess,  int idx, char *word)
{
    char correct;
    correct = word[idx];
    if (guess == correct){
        return ResultGreen;
    }
        else if (isin(guess, word))
                return ResultYellow;
    return ResultRed;
    
}
Result *checkword(char *guess, char *word){
    Result res[5];
    int i;

    for (i=0; i<5;i++) {
        res[i]= checkchar(guess[i],i,word);
    }
    return res;
}

int main(int argc, char *argv[])
{
    char *correct, *guess;
    Result res[5];
    if (argc < 3) {
        fprintf(stderr,
        "Usage: %s THE WORD IS CORRECT",argv[0]
        );
        return -1;
    }


    correct = argv[1];
    guess = argv[2];

    res = checkword(correct, guess);
    Example_printing_the_results(res);
    return 0;
}