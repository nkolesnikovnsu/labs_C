#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <stdlib.h>

#include <memory.h>

#include <ctype.h>
#include <string.h>


void checkExceptions(const char* permutation, int size, int *flagOfWrongInput);

void* getArrayOfNumbers(const char* permutation, int size);

void getNextPermutation(unsigned char* currentPermutation, int countOfIterations, int quantity);

void swap(unsigned char *a, unsigned char *b);



void swap(unsigned char *a,unsigned char *b) {

   unsigned char temp = *a;

    *a = *b;

    *b = temp;

}

void checkExceptions(const char* permutation, int size, int *flagOfWrongInput) {

    int arrayForCheckRepetition[10];

    for (int i = 0; i < 10; i++) {

        arrayForCheckRepetition[i] = 0;

    }

    for (int i = 0; i < size; i++) {

        if (!isdigit(*(permutation + i)) || arrayForCheckRepetition[*(permutation + i) - '0'] != 0) {

            (*flagOfWrongInput)++;

            return;

        } else {

            arrayForCheckRepetition[*(permutation + i) - '0']++;

        }

    }

}



void* getArrayOfNumbers(const char* permutation, int size) {

    unsigned char* result = (unsigned char*)malloc(size * sizeof(unsigned char));

    for (int i = 0; i < size; i++) {

        *(result + i) = *(permutation + i);

    }

    return result;

}


void getNextPermutation(unsigned char* currentPermutation, int countOfIterations, int quantity) {

    if (countOfIterations == 0) {

        return;

    }

    int position = -1;



    // We should find the element which is breaking the increasing order



    for (int i = quantity - 2; i >= 0; i--) {

        if (currentPermutation[i] < currentPermutation[i + 1]) {

            position = i;

            break;

        }

    }



    // If element isn't found - it's the last permutation



    if (position == -1) {

        return;

    }



    // Find the min element in tail which is bigger than the founded element



    int currentIndex = position + 1;

    char current = currentPermutation[currentIndex];

    for (int i = position + 2; i < quantity; i++) {

        if (currentPermutation[i] < current && currentPermutation[i] > currentPermutation[position]) {

            currentIndex = i;

            current = currentPermutation[currentIndex];

        }

    }

    swap(&currentPermutation[position], &currentPermutation[currentIndex]);



    // We also have the decreasing order after the element with 'position' index

    // If we'll reverse the tail - we'll get the next permutation





    int leftBound = position + 1, rightBound = quantity - 1;

    while (leftBound < rightBound) {

        swap(&currentPermutation[leftBound], &currentPermutation[rightBound]);

        leftBound++;

        rightBound--;

    }

    for (int i = 0; i < quantity; i++) {

        printf("%c", currentPermutation[i]);

    }

    printf("\n");

    getNextPermutation(currentPermutation, countOfIterations - 1, quantity);

}



int main() {

    int flagOfWrongInput = 0;

    int n;

    const int ZERO = 0;

    char* permutation = (char*)malloc(11 * sizeof(char));

    if (scanf("%10s%d", permutation, &n) != 2) {

        printf("bad input");

        free(permutation);

        return 0;

    }

    checkExceptions(permutation, (int)strlen(permutation), &flagOfWrongInput);

    if (flagOfWrongInput == ZERO) {

        unsigned char* currentPermutation = getArrayOfNumbers(permutation, (int)strlen(permutation));

        getNextPermutation(currentPermutation, n, (int)strlen(permutation));

        free(currentPermutation);

    } else {

        printf("bad input");

    }

    free(permutation);

    return 0;
}
