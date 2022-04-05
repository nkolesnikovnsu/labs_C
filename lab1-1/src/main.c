#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

const long long int LENGTH = 1024;
const int arrOfDegrees[17] = { 1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 59049*3, 59049*3*3, 59049*3*3*3,59049*3*3*3*3,59049*3*3*3*3*3, 59049*3*3*3*3*3*3};

void sample(char *HashTmpl, int *len) {
    int i = 0;
    unsigned char c = 0;
    while ((c = getchar()) != '\n') {
        HashTmpl[i] = c;
        *len = i;
        i++;
    } 
    *len = *len + 1;
}
 

int hash(char *buf, int pointer, int all_pointers ){
    int hash = 0, j = 0;
    for(int i = pointer; i < all_pointers; i++){
        hash += (((unsigned char)buf[i] % 3) * arrOfDegrees[j]);
        j++;
    }
    return hash;
}

int main() {
    unsigned int hashTmp, hashStr = 0;
    char  HashTmpl[17];
    int len = 0, i = 0, pointer = 0;
    char buf[LENGTH];
    sample(HashTmpl, &len);
    int allPointer = len;
    hashTmp = hash(HashTmpl,0, len);
    printf("%u ", hashTmp);
    int lenBuf = 0;
    while (1) {
        int c;
        while ((lenBuf < allPointer) && ((EOF != (c = getchar())))) {
            buf[i] = (unsigned char)c;
            i++;
            lenBuf++;
            if(i == LENGTH)
                i %=  LENGTH;
        }
        if(c == EOF)
            break;
        if(lenBuf == len)
            hashStr = hash(buf, pointer, allPointer);
        else {
            hashStr = ((hashStr - (unsigned char)buf[(pointer - 1) %  LENGTH] % 3)) / 3 + ((unsigned char)buf[(allPointer - 1) % LENGTH]) % 3 * arrOfDegrees[len - 1];
        }
        if(hashStr == hashTmp){
            int tmp = 0;
            while(pointer + tmp < allPointer){
                printf("%d ", pointer + 1 + tmp );
                if(buf[(pointer + tmp) % LENGTH] != HashTmpl[tmp])
                    break;
                tmp++;
            }
        }
        pointer++;
        allPointer++;
    }
    return 0;
}
