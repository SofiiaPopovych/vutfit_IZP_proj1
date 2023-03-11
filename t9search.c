// Popovych Sofiia xpopov13

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE_OF_DATA 100


typedef struct personStruct {
    char name[MAX_SIZE_OF_DATA];
    char phone[MAX_SIZE_OF_DATA];
} personStruct;


void myTolower(char* str) {
    // make all letters lowercase 
    for(unsigned long i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }

}


bool isStrNum(char* str) {
    // search for numbers
    // str - what we want to check 
    // return false if it's number 
    // return true if it's char
    
    for(unsigned long i = 0; i < strlen(str); i++) {
        if ( ! (str[i] >= '0' && str[i] <= '9')) {
            return false; 
        }
    }

    return true;
}


bool isArgValid(int argc, char* argv[]) {
    // check valid arguments
    
    if (argc == 1) {
        return true; // no arguments
    }
    
    if (argc == 2) {
        if(isStrNum(argv[1])) {
            return true; // one valid argument
        }
    }

    return false;  // too many arguments
} 


void printErr(char* str) {
    fprintf(stderr, "%s", str); // print error message
}


void printPerson(personStruct person) {
    printf("%s, %s\n", person.name, person.phone); // print person and phone if finds a suitable argument
}


bool scanNum(char* num, char* str) {
    // check is number is valid
    unsigned long k = 0;
    bool isFound = false;
    
    for(unsigned long i = 0; i < strlen(num); i++) {
        // check every char in number 
        if(num[i] == str[k]) {
            k++;
            isFound = true;
        } else if (isFound) {
            k = 0;
            isFound = false;
            i--;
        }

        if(k == strlen(str)) {
            return true;
        } 
    }
    return false;
}


bool scanPerson(char* name, char* str) {
    // check if contacts is matching due to input parametr
    // return true if match was found
    // return false if match was not found
    const char letByNum[10][5] = {      // letter representation
        {'+'},
        {'\n'}, 
        {"abc"}, 
        {"def"}, 
        {"ghi"}, 
        {"jkl"}, 
        {"mno"}, 
        {"pqrs"}, 
        {"tuv"}, 
        {"wxyz"}
    };
    unsigned long i = 0;
    bool isFound = false;
    bool decrement = false;
    for(unsigned long j = 0; j < strlen(name); j++) {
        for(unsigned long k = 0; k < strlen(letByNum[str[i] - '0']) ; k++) {
            if(letByNum[str[i] - '0'][k] == name[j]) {
                // if represented letter is in string name
                i++;
                isFound = true;
                decrement = true;
                break; // if was new match found , break
            }
             
            isFound = false;
        }
      
       if (i == strlen(str)) { // if all matches was found return true 
            return true;
        }
        
        if ( ! isFound) {   // restart search from 1 char in str
            i = 0;
            if (decrement) {    // if at least 1 letter before succesefull match wasnt searched
                j--;
                decrement = false;
            }
        }
    } 
    
    return false;
}


bool checkValidPerson(personStruct person, char* str) {
    // check valid person
    // if was found return true
    // if was not found return false
    if(scanNum(person.phone, str)) {
    return true;
    }
    if(scanPerson(person.name, str)) {
        return true;
    }
    return false;
}



int main(int argc, char* argv[]) {
    if ( ! isArgValid(argc, argv)) {
        // if argument is invalid 
        printErr("Invalid arguments of program\n");         
        return 1;
    }

    char c;
    personStruct person;
    int i = 0;
    bool notFound = false;
    
    memset(person.name, 0, MAX_SIZE_OF_DATA); // use to clear memory
    memset(person.phone, 0, MAX_SIZE_OF_DATA); // use to clear memory

    while(true) {
        while ((c = getchar()) != '\n') { 
            // when find person without number
            if (c == EOF) {
                printErr("Person without number\n");
                return 1;
            }
            person.name[i] = c;
            i++;
        }

        i = 0;
        while ((c = getchar()) != '\n') {
            // search person number
            if (c == EOF) {
                break;
            }
            person.phone[i] = c;
            i++;
        }

        i = 0;
        myTolower(person.name); 
        if (argc == 1) {
            printPerson(person);
            notFound = true;
        } else if (checkValidPerson(person, argv[1])) {
            printPerson(person);
            notFound = true; 
        }

        memset(person.name, 0, MAX_SIZE_OF_DATA);
        memset(person.phone, 0, MAX_SIZE_OF_DATA);

        if (c == EOF) {
            break; 
        }
    }
    // dont't find contacts
    if ( ! notFound) {
        printf("Not Found\n");
    }

    return 0;
}
