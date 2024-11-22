#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ResultGreen 1
#define ResultYellow 2
#define ResultRed 5

// struct s_word {
//     char word[8];
// }
typedef char Result;


struct s_words {
    char **arr;
    int ren;

}


typedef struct s_result Words;
struct s_result
{
    char color[5];
};



bool isin(char, char*);
void Example_printing_the_results(Result[]);
Result *checkword(char *, char *);
Result checkchar(char, int, char *);

int main(int, char**);


void Example_printing_the_results(Result res[]) {
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


bool isin(char c, char *str){
    int i,size;
    bool ret;
    ret = false;
    size = strlen(str);

    for(i=0;i<size;i=i+1)
    {
        if (str[i] == c){
            ret = true;
            break;
        }


    }
    return ret;
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

Words readfile(char *filename, int max) {

char buf[8];
int i,size;
FILE *fd;
char *ret[5];
Words words;
fd = fopen(filename, "r");
if (!fd) {
    perror("fopen");
    return (char **)0;
}


size = max*5;
ret = (char **)malloc(size);
if(!ret) {
    fclose(fd);
    perror("malloc");
    

    return (char **)0;

    i=0;

    memset(buf,0,8);
    while (fgets(buf, 7, fd)) {
        size = strlen(buf);
        if (size < 1) {
            memset(buf,0,8);
            continue;
        }



        size--;
        buf[size]=0;

        if (size != 0) {
            memset(buf, 0,8);
            continue;
        }
        ret[i][0]=buf[0];
        ret[i][1]=buf[1];
        ret[i][2]=buf[2];
        ret[i][3]=buf[3];
        ret[i][4]=buf[4];

        memset(buf,0,8);
        n++;



        if(max <= n){
            break;
        }
    }

    fclose(fd);
}

}
Result *checkword(char *guess, char *word){
    static Result res[5];
    int i;

    for (i=0; i<5;i++) {
        res[i]= checkchar(guess[i],i,word);
    }
    return res;
}

int main(int argc, char *argv[])
{
    char *correct, *guess;
    Result *res;
    if (argc < 3) {
        fprintf(stderr,
        "Usage: %s THE WORD IS CORRECT/WRONG \n",argv[0]
        );
        return -1;
    }


    correct = argv[1];
    guess = argv[2];

    res = checkword(guess, correct);
    Example_printing_the_results(res);
    return 0;
}