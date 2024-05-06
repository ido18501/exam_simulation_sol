#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ABC_DIFFERENCE 'a'
#define ABC_SIZE 26

int es_q2(char *s1, char *s2);

char *readStr();


int main() {
    char *s1 = readStr();
    if (!s1) {
        return 1;
    }
    char *s2 = readStr();
    if (!s2) {
        free(s1);
        return 1;
    }
    printf("%d", es_q2(s1, s2));
    free(s1);
    free(s2);
    return 0;
}

char *readStr() {
    int n;
    if (scanf("%d", &n) != 1) {
        return NULL;
    }
    char *s = malloc(n + 1);
    if (!s) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        if (scanf("%c", s + i) != 1) {
            free(s);
            return NULL;
        }
        if (s[i] == '\n') {
            i--;
        }
    }
    s[n] = '\0';
    return s;
}


int es_q2(char *s1, char *s2) {
    //initializing variables
    int counter = 0;
    int check;
    int idx = 0;
    int s1_size = 0;
    //creating main histogram and one that will be used as a copy
    int hist[ABC_SIZE] = {0};
    //initializing histograms according to s1 letters
    for (int i = 0; s1[i] != '\0'; i++) {
        s1_size++;
        hist[s1[i] - ABC_DIFFERENCE]++;
    }
    int size = 0;
    //iterating through s2 and looking for a matching subarray
    for (int i = 0; s2[i] != '\0'; i++) {
        //adjusting size of subarray
        size += size < s1_size ? 1 : 0;
        //marking letter as read
        hist[s2[i] - ABC_DIFFERENCE]--;
        //if subarray the size of s1, checking for a match
        if (size == s1_size) {
            check = 0;
            //counting amount of letters in subarray that appear
            // exactly the same amount of times in s1
            for (int j = 0; j < ABC_SIZE; j++) {
                if (hist[j] == 0) {
                    check++;
                }
            }
            //if all letters appeared the right amount of
            // times, adding a match to counter
            counter += check == ABC_SIZE ? 1 : 0;
            //restoring value of first letter of subarray
            // in histogram and adjusting index
            hist[s2[idx] - ABC_DIFFERENCE]++;
            idx++;
        }
    }
//returning result
    return counter;
}
