#include <cstring>
#include <iostream>
#include <omp.h>
#include <string>
// #define FN "words.txt"

#define COUNT 8
char search_words[COUNT + 1][32] = { "The", "lorem", "ipsum", "present", "dolor", "sit", "in","quid", "" };
long counts[COUNT]={0};
int line_c = 0;

int is_equal(char* a, const char* key, bool ignore_case)
{
    return ignore_case ? strcasecmp(a, key) : strcmp(a, key);
}

/** read into temp from fp*/
void read_word(char* temp, FILE* fp)
{
    int i = 0;
    char ch;

    while ((ch = fgetc(fp)) != EOF && !isalpha(ch))
        ;

    while (ch != EOF && isalpha(ch)) {
        temp[i++] = ch;
        ch = fgetc(fp);
    }

    temp[i] = '\0';
}

long determine_count(char* file_name, const char* key, int ignore_case)
{
    int key_index = 0, key_len = strlen(key);
    long word_count = 0;
    char ch;
    FILE* fp = fopen(file_name, "r");
    if (fp==nullptr){std::cout<<"No file\n"; return 0;}
    char temp[40]={0};
    int i = 0;
    while (feof(fp) == 0) {
        read_word(temp, fp);
        if (is_equal(temp, key, ignore_case) == 0)
            word_count++;
    }
    return word_count;
}

int main(int argc, char** argv)
{
    int i, nt = 0, ignore_case = 1;
    char choice, buf;
    if(argc<2){printf("No args\n");return 1;}char* FN = argv[1];
    for (nt = 1; nt <= 16; nt *= 2) {
        omp_set_num_threads(nt);
        for (i = 0; i < COUNT; i++) {
            counts[i] = 0;
        }

        double t = omp_get_wtime();
    // #pragma omp parallel for shared(counts, search_words) private(i)
        for (i = 0; i < COUNT; i++) {
            counts[i] = determine_count(FN, search_words[i], ignore_case);
        }

        t = omp_get_wtime() - t;

        for (i = 0; i < COUNT; i++) {
            printf("\n%s: %ld", search_words[i], counts[i]);
        }
        printf("\n%d Threads, time = %lf\n", nt, t);
    }
}