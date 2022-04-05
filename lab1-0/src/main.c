#define _CRT_SECURE_NO_WARNINGS
 
#include <stdlib.h>
#include <stdio.h>
 
struct ListSymbol
{
    unsigned char symbol;
    unsigned long long position;
    struct ListSymbol* next;
    struct ListSymbol* previous;
};
  
int ReadTemplate(unsigned char* temp)
{
    int lengthTemplate = 0;
    int get;
    while ((get = getchar()) != '\n')
    {
        temp[lengthTemplate] = (unsigned char)get;
        lengthTemplate++;
    }
    return(lengthTemplate);
}
 
struct ListSymbol* FirstTextScannig(int lengthTemplate, struct ListSymbol* head)
{
    if (head == NULL) return(NULL);
    struct ListSymbol* pointer = head;
    pointer->position = 1;
    pointer->next = NULL;
    pointer->previous = NULL;
    int get = getchar();
    if (get == EOF) return NULL;
    pointer->symbol = (unsigned char)get;
    for (int i = 1; i < lengthTemplate; i++)
    {
        get = getchar();
        if ((EOF) == get) return(NULL);
        if (pointer == NULL) return(NULL);
        struct ListSymbol* prevPointer = pointer;
        pointer->next = pointer;
        pointer = (struct ListSymbol*)(malloc(sizeof(struct ListSymbol)));
        if (pointer == NULL) return(NULL);
        prevPointer->next = pointer;
        pointer->next = NULL;
        pointer->previous = prevPointer;
        pointer->symbol = (unsigned char)get;
        pointer->position = ((prevPointer->position) + 1);
 
    }
    return(pointer);
}
void Comparison(struct ListSymbol* tail, unsigned char* temp, int lengthTemplate)
{
    struct ListSymbol* pointer = tail;
    while (lengthTemplate > 0)
    {
        printf("%llu ", pointer->position);
        if (temp[lengthTemplate - 1] == (pointer->symbol))
        {
            lengthTemplate--;
            pointer = pointer->previous;
        }
        else
        {
            break;
        }
    }
}
 
short int TextScannig(struct ListSymbol* tail, struct ListSymbol* head, int move)
{
    if ((tail == NULL) || (head == NULL)) return 0;
    struct ListSymbol* pointer = tail;
    short int endOfTextFlag = 1;
    for (int i = 1; i < move; i++)
    {
        pointer = pointer->previous;
    }
    for (int i = 1; i <= move; i++)
    {
        int get = 0;
        if (EOF == (get = getchar()))
        {
            endOfTextFlag = 0;
            break;
        }
        else
        {
            long long int prevPosition = 0;
            pointer->symbol = (unsigned char)get;
            if ((pointer->previous) == NULL)
            {
                prevPosition = head->position;
            }
            else
            {
                pointer = pointer->previous;
                prevPosition = pointer->position;
                pointer = pointer->next;
            }
            pointer->position = prevPosition + 1;
            pointer = pointer->next;
        }
    }
    return(endOfTextFlag);
}
 
struct ListSymbol* structuralChainTransformations(struct ListSymbol* head, struct ListSymbol* tail, int move)
{
    if ((head == NULL) || (tail == NULL)) return(NULL);
    struct ListSymbol* pointer = head;
    for (int i = 1; i < move; i++)
    {
        pointer = pointer->next;
    }
    head->previous = tail;
    tail->next = head;
    head = (pointer->next);
    tail = pointer;
    head->previous = NULL;
    tail->next = NULL;
    return(head);
}
 
void cleanStruct(struct ListSymbol* head)
{
    while (head->next != NULL)
    {
        head = head->next;
        free(head->previous);
    }
    free(head);
}
 
int main()
{
    struct ListSymbol* tail, * head;
    unsigned char temp[17];
    int lengthTemplate = ReadTemplate(temp);
    int shiftTable[256];
    for (int i = 0; i < 256; i++) shiftTable[i] = lengthTemplate;
    for (int i = 0; i < lengthTemplate - 1; i++)
    {
        shiftTable[temp[i]] = lengthTemplate - i - 1;
    }
    head = (struct ListSymbol*)(malloc(sizeof(struct ListSymbol)));
    if (NULL == (tail = FirstTextScannig(lengthTemplate, head))) return(0);
    if (0 == lengthTemplate) return(0);
    short int endOfTextFlag = 1;
    /*
    if endOfTextFlag==0 then end
    if endOfTextFlag==1 then continue
    */
    if (head == NULL) return 0;
    while (endOfTextFlag == 1)
    {
        Comparison(tail, temp, lengthTemplate);
        int move = shiftTable[tail->symbol];
        if (move != lengthTemplate) {
            head = structuralChainTransformations(head, tail, move);
            for (int i = 1; i <= move; i++)
            {
                if (tail->next != NULL) tail = tail->next;
            }
        }
        else
        {
            head->position = tail->position;
        }
        endOfTextFlag = TextScannig(tail, head, move);
    }
    cleanStruct(head);
    return(0);
}
