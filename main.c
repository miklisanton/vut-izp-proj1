#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE  100

bool containsLowerAndUpperCase(char *string);
bool matchesParameters(char *string, int x);
bool containsDigits(char *string);
bool containsSpecialSigns(char *string);
bool isAlphaNumeric(char ch);
bool hasSameSymbolsSequence(char *string, int x);
void formSubstring(char *string, char *substring, int start, int length);
bool isEqual(const char *string1, const char *string2);
bool hasTwoSameSubstrings(char *string, int x);
bool matchesSecurityLevel(char *string, int level, int x);
void differentElements(char *array, int *len, char ch);
int readArguments(int argc, char *argv[], int *level, int *x, bool *stats);
int checkParameters(int level, int x, int err);
void printStatistics(int NCHARS, int minLength, int passwordsLength, double passwordsAmount);


int main(int argc, char *argv[]) {
    int level = 0;
    int x = 0;
    bool stats = 0;

    //read and check given arguments
    int err = readArguments(argc, argv, &level, &x, &stats);
    int errorCode = checkParameters(level, x, err);
    if(errorCode){
        return errorCode;
    }

    //init variables for statistics
    double passwordsAmount = 0;
    int passwordsLength = 0;
    int minLength = MAX_LINE;
    int NCHARS = 0;
    char differentSymbolsArray[128];

    //init variables for getting passwords
    char buffer[MAX_LINE + 1];
    int ch = 0;
    int i = 0;

    while ((ch = getchar()) != EOF){
        buffer[i] = ch;
        if(i > MAX_LINE){
            fprintf(stderr, "Password too long!\n");
            return -1;
        }
        if (buffer[i] == '\n'){
            buffer[i] = '\0';
            if (matchesSecurityLevel(buffer, level, x)){
                printf("%s\n", buffer);
            }
            if (stats){
                passwordsLength += i;
                passwordsAmount++;
                if(i < minLength){
                    minLength = i;
                }
            }
            i = 0;
            continue;
        }else if(stats){
            //counts different symbols for statistics
            differentElements(differentSymbolsArray, &NCHARS, buffer[i]);
        }
        i++;
    }

    if (stats){
        printStatistics(NCHARS, minLength, passwordsLength, passwordsAmount);
    }
    return 0;
}

bool containsSpecialSigns(char *string){
    int i = 0;
    while (string[i]){
        if (string[i] >= 32 && string[i] <= 126 && !isAlphaNumeric(string[i])){
            return 1;
        }
        i++;
    }
    return 0;
}

bool containsDigits(char *string){
    int i = 0;
    bool containsDigits = 0;
    while (string[i]){
        if (string[i] >= '0' && string[i] <= '9'){
            containsDigits = 1;
            return 1;
        }
        i++;
    }
    return 0;
}

//checks if password matches 2nd security level
bool matchesParameters(char *string, int x){
    if(x < 3){
        return 1;
    }
    if (x == 3 && (containsDigits(string) || containsSpecialSigns(string))){
        return 1;
    }
    if (x >= 4 && containsDigits(string) && containsSpecialSigns(string)){
        return 1;
    }
    return 0;
}

bool containsLowerAndUpperCase(char *string){
    int i = 0;
    bool containsUpper = 0;
    bool containsLower = 0;
    while (string[i]){
        if (string[i] >= 'A' && string[i] <= 'Z'){
            containsUpper = 1;
        }
        if (string[i] >= 'a' && string[i] <= 'z'){
            containsLower = 1;
        }
        if (containsUpper && containsLower){
            return 1;
        }
        i++;
    }
    return 0;
}

bool isAlphaNumeric(char ch){
    if((ch >= 'a' && ch <= 'z') ||
       (ch >= 'A' && ch <= 'Z') ||
       (ch >= '0' && ch <= '9')){
        return 1;
    }
    return 0;
}

bool hasSameSymbolsSequence(char *string, int x){
    if (x == 1){
        return 1;
    }
    int i = 0;
    int count = 1;
    while (string[i + 1] != '\n'){
        if (string[i] == string[i + 1]){
            count++;
            if (count == x){
                return 1;
            }
        } else{
            count = 1;
        }
        i++;
    }
    return 0;
}

void formSubstring(char *string, char *substring, int start, int length){
    int i = 0;
    while (i < length && string[i]){
        substring[i] = string[start + i];
        i++;
    }
    substring[i] = '\0';
}

bool isEqual(const char *string1,const  char *string2){
    int i = 0;
    while (string1[i] && string2[i]){
        if (string2[i] != string1[i]){
            return 0;
        }
        i++;
    }
    if (string1[i] || string2[i]){
        return 0;
    }
    return 1;
}

bool hasTwoSameSubstrings(char *string, int x){
    char sub1[MAX_LINE];
    char sub2[MAX_LINE];
    int i = 0;
    while (string[i]){
        int k = i;
        formSubstring(string, sub1, i, x);
        while (string[k + x - 1]){
            formSubstring(string, sub2, k + 1, x);
            if(isEqual(sub1, sub2)){
                return 1;
            }
            k++;
        }
        i++;
    }
        return 0;
}

bool matchesSecurityLevel(char *string, int level, int x){
    bool firstLevel = containsLowerAndUpperCase(string);
    bool secondLevel = firstLevel && matchesParameters(string, x);
    bool thirdLevel = secondLevel && !hasSameSymbolsSequence(string, x);
    bool fourthLevel = thirdLevel && !hasTwoSameSubstrings(string, x);
    if(level == 1 && firstLevel){
        return 1;
    }
    if(level == 2 && secondLevel){
        return 1;
    }
    if(level == 3 && thirdLevel){
        return 1;
    }
    if(level == 4 && fourthLevel){
        return 1;
    }
    return 0;
}

/*
 * checks if element is in array
 * if not, adds it to array and increases different elements counter
 */
void differentElements(char *array, int *len, char ch){
    int i = 0;
    for ( i = 0; i < *len; ++i) {
        if (ch == array[i]){
            break;
        }
    }
    if(*len == i){
        *len = *len + 1;
        array[i] = ch;
    }
}

/*
 * recognizes arguments type
 * writes arguments to variables
 * returns error code
 */
int readArguments(int argc, char *argv[], int *level, int *x, bool *stats){
    if (argc == 1){
        //if no args were given
        *level = 1;
        *x = 1;
        return 0;
    }
    long param;
    if(argv[1][0] == '-'){
        //read arguments with commutator
        if (argc != 6 && argc != 5 && argc != 3 && argc != 4 && argc != 2){
            return 7;
        }
        for (int i = 1; i < argc; ++i) {
            if (isEqual("--stats", argv[i])){
                *stats = 1;
            }else if(isEqual("-l", argv[i])){
                char *endptr;
                *level = strtoul(argv[i + 1], &endptr, 10);
                //checks if there is something except of number in level argument
                if (*endptr){
                    return 22;
                }
                i++;
            }else if(isEqual("-p", argv[i])){
                char *endptr;
                param = strtol(argv[i + 1], &endptr, 10);
                //checks if there is something except of number in x argument
                if (*endptr){
                    return 22;
                }
                i++;
            }else{
                return 22;
            }
        }
        //if x or level is not given
        *level = *level == 0 ? 1 : *level;
        *x = *x == 0 ? 1 : *x;
    }else{
        //read arguments in order
        if (argc != 3 && argc != 4){
            return 7;
        }
        char *endptr;
        *level = strtoul(argv[1], &endptr, 10);
        //checks if there is something except of number in level argument
        if (*endptr){
            return 22;
        }
        param = strtol(argv[2], &endptr, 10);
        //checks if there is something except of number in x argument
        if (*endptr){
            return 22;
        }
        if (argc == 4) {
            if (isEqual("--stats", argv[3])){
                *stats = 1;
            }else{
                return 22;
            }
        }
    }
    *x = param > 100 ? 100:param;
    return 0;
}

int checkParameters(int level, int x, int errorCode){
    switch (errorCode) {
        case 22:
            fprintf(stderr, "Wrong argument!\n");
            return EXIT_FAILURE;
        case 7:
            fprintf(stderr, "Wrong amount of arguments!\n");
            return EXIT_FAILURE;
        case 0:
            break;
        default:
            fprintf(stderr, "Some error occurred!\n");
    }

    if(level < 1 || level > 4){
        fprintf(stderr, "Wrong level!\n");
        return EXIT_FAILURE;
    }
    if (x < 1){
        fprintf(stderr, "Wrong parameter!\n");
        return EXIT_FAILURE;
    }
    return 0;
}

void printStatistics(int NCHARS, int minLength, int passwordsLength, double passwordsAmount){
    double averageLength = passwordsLength / passwordsAmount;
    printf("Statistika:\n");
    printf("Ruznych znaku: %d\n", NCHARS);
    printf("Minimalni delka: %d\n", minLength);
    printf("Prumerna delka: %.1f\n", averageLength);
}
