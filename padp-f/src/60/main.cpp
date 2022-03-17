#include <omp.h>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define FN "words.txt"
vector<string> words = {"Hello", "no", "cry"};
vector<int> counts;
int compare(string a, string b, bool ignorecase) {
    const char *ac = a.c_str(), *bc = b.c_str();
    return ignorecase ? strcasecmp(ac, bc) : strcmp(ac, bc);
}

int get_count(string word, bool ignorecase) {
    FILE* fp = fopen(FN, "r");
    if (fp == nullptr)
        return 0;
    char c;
    int count=0;

    while (!feof(fp)) {
        string gotword = "";
        // skip garbage
        while ((c = fgetc(fp)) != EOF and !isalpha(c))
            ;

        while (c != EOF and isalpha(c)) {
            gotword += c;
            c = fgetc(fp);
        }
        //we have a gotword
        if(compare(gotword,word,true)==0) count++;
    }

    fclose(fp);
    return count;
}

int main() {
    for (auto v : words) {
        counts.push_back(0);
    }

    int n = words.size();
    double t = omp_get_wtime();
    #pragma omp parallel for num_threads(8)
    for (int i = 0; i < n; i++) {
        int x = get_count(words[i], true);
        counts[i] += x;
    }
    t=omp_get_wtime()-t;
    for (int i = 0; i < n; i++) {
        cout<<"WORD "<<words[i]<<' '<<counts[i]<<endl;
    }
    cout<<"t="<<t<<endl;
    
}