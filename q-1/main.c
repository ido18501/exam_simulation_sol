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
    //creating main histogram and one that will be used as a copy
    int hist1[ABC_SIZE] = {0};
    int hist2[ABC_SIZE] = {0};
    //initializing histograms according to s1 letters
    for (int i = 0; s1[i] != '\0'; i++) {
        hist1[s1[i] - ABC_DIFFERENCE]++;
        hist2[s1[i] - ABC_DIFFERENCE]++;
    }
    //iterating through s2 and looking for a matching subarray
    for (int i = 0; s2[i] != '\0'; i++) {
        check = 0;
        //if a letter that doesn't appear in s1 or was already seen the number
        // of appearances it has in s1, resetting histogram 2 and idx
        if (hist2[s2[i] - ABC_DIFFERENCE] == 0) {
            idx = i + 1;
            for (int j = 0; j < ABC_SIZE; j++) {
                hist2[j] = hist1[j];
            }
            //if a legal letter was found (histogram is not 0) -
            // adjusting histogram
        } else if (hist2[s2[i] - ABC_DIFFERENCE] > 0) {
            hist2[s2[i] - ABC_DIFFERENCE]--;
        }
        //checking histogram, whenever a letter was used
        // exactly the right number of time, counting it
        for (int j = 0; j < ABC_SIZE; j++) {
            if (hist2[j] == 0) {
                check++;
            }
        }
        //if all letters were used exactly the right amount of times - adding
        // an option to counter and adjusting histogram and idx
        if (check == ABC_SIZE) {
            counter++;
            hist2[s2[idx] - ABC_DIFFERENCE]++;
            idx++;
        }
    }
//returning result
    return counter;
}
