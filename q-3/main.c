#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int es_q4(char *s1, char *s2);

bool is_letter(char *s);

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
    //note - a replica of pointers to s1 and s2 was created in order
    // to make sure the main function frees memory appropriately
    char *s11 = s1;
    char *s22 = s2;
    printf("%d", es_q4(s1, s2));
    free(s11);
    free(s22);
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

int es_q4(char *s1, char *s2) {
    //note - a replica of pointers to s1 and s2 was created in main function
    // in order to make sure the main function frees memory appropriately

    //stop condition- a match found and both strings ended
    if (s1[0] == '\0' && s2[0] == '\0') {
        return 1;
    }
    //if mismatch found, checking situation
    if (s1[0] != s2[0]) {
        //case1- both letters, returning 0
        if (is_letter(s1) && is_letter(s2)) {
            return 0;
        }
        //case2- only one is letter and mismatch
        // occurred in the middle of a word
        if (is_letter(s1) && is_letter(s1 - 1)) {
            return 0;
        }
        //case2 but with opposite strings
        if (is_letter(s2) && is_letter(s2 - 1)) {
            return 0;
        }
        //if mismatch was "legal", meaning it did not contradict a possible
        // correlation between strings, adjusting pointers
        s1 += is_letter(s1) ? 0 : 1;
        s2 += is_letter(s2) ? 0 : 1;
        return es_q4(s1, s2);
    }
    //if both characters match, proceeding no next character
    return es_q4(s1 + 1, s2 + 1);
}

bool is_letter(char *s) {
    //checking whether current pointer to start of string is a
    // letter or not, and returning true or false accordingly
    int control = 0;
    if (s[0] > 'z' || s[0] < 'A') {
        control++;
    } else if (s[0] > 'Z' && s[0] < 'a') {
        control++;
    }
    return control == 0 ? true : false;
}
