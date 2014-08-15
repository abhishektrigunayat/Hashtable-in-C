//
//  main.c
//  HashTable
//
//  Created by Abhishek Trigunayat on 7/24/14.
//  Copyright (c) 2014 Abhishek Trigunayat. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LENG 12

struct hashEntry{
    char * string;
    struct hashEntry * next;
};

void initialize();
int addEntry(char *);
int removeEntry(char *);
int containsEntry(char *);
long getHashCode(char *);
int getTableIndex(long);
void printHashTable();

struct hashEntry hashTable[LENG];

int main(int argc, const char * argv[])
{
    initialize();
    char string1[] = "Los Angeles";
    char string2[] = "New York";
    char string3[] = "Seattle";
    char string4[] = "San Diego";
    char string5[] = "Chicago";
    char string6[] = "Las Vegas";
    char string7[] = "Phoenix";
    char string8[] = "San Jose";
    char string9[] = "Santa Clara";
    char string10[] = "Pittsburgh";
    char string11[] = "San Francisco";
    char string12[] = "Houston";
    char string13[] = "Dallas";
    addEntry(string1);
    addEntry(string2);
    addEntry(string3);
    addEntry(string4);
    addEntry(string5);
    addEntry(string6);
    addEntry(string7);
    addEntry(string8);
    addEntry(string9);
    addEntry(string10);
    addEntry(string11);
    addEntry(string12);
    addEntry(string13);
    printHashTable();
    removeEntry(string2);
    removeEntry(string1);
    removeEntry(string9);
    removeEntry(string10);
    removeEntry(string5);
    removeEntry(string13);
    removeEntry(string4);
    removeEntry(string8);
    removeEntry(string7);
    removeEntry(string12);
    removeEntry(string6);
    removeEntry(string3);
    removeEntry(string11);
    printHashTable();
    return 0;
}

void initialize()
{
    for(int i=0;i<LENG;i++)
    {
        hashTable[i].next = NULL;
        hashTable[i].string = NULL;
    }
}

int addEntry(char *string)
{
    long hashCode = getHashCode(string);
    int table_index = getTableIndex(hashCode);
    if(hashTable[table_index].string == NULL && hashTable[table_index].next == NULL)
    {
        hashTable[table_index].string = (char *) malloc(sizeof(char) * (strlen(string) + 1));
        strcpy(hashTable[table_index].string,string);
        return 1;
    }
    
    if(hashTable[table_index].string != NULL)
    {
        if(strcmp(hashTable[table_index].string,string) == 0)
        {
            return 0;
        }
        struct hashEntry *n = &hashTable[table_index];
        while(n->next != NULL){
            if(strcmp(n->string,string) == 0){
                return 0;
            }
            n = n->next;
        }
        struct hashEntry *temp = (struct hashEntry *)malloc(sizeof(struct hashEntry));
        temp->string = (char *) malloc(sizeof(char) * (strlen(string) + 1));
        strcpy(temp->string,string);
        n->next = temp;
        return 1;
    }
    assert(0);
}

int removeEntry(char *string)
{
    long hashCode = getHashCode(string);
    int table_index = getTableIndex(hashCode);
    printf("Removing entry %s from : %d\n",string,table_index);
    if(hashTable[table_index].string == NULL && hashTable[table_index].next == NULL)
    {
        return 0;
    }
    
    if(hashTable[table_index].string != NULL)
    {
        if(strcmp(hashTable[table_index].string,string) == 0)
        {
            hashTable[table_index].string = NULL;
            if(hashTable[table_index].next != NULL)
            {
                hashTable[table_index].string = (char *) malloc(sizeof(char) * (strlen(hashTable[table_index].next->string) + 1));
                strcpy(hashTable[table_index].string,hashTable[table_index].next->string);
                struct hashEntry *temp = hashTable[table_index].next;
                hashTable[table_index].next = hashTable[table_index].next->next;
                free(temp);
            }
            return 1;
        }
        struct hashEntry *n = hashTable[table_index].next;
        struct hashEntry *p = &hashTable[table_index];
        while(n != NULL)
        {
            if(strcmp(n->string,string) == 0)
            {
                if(n->next !=NULL){
                    strcpy(n->string,n->next->string);
                    n->next = n->next->next;
                    free(n);
                    return 1;
                }
                else{
                    p->next = NULL;
                    free(n);
                    return 1;
                }
            }
            p=n;
            n = (n->next);
        }
        return 0;
    }
    assert(0);
}

int containsEntry(char *string)
{
    long hashCode = getHashCode(string);
    int table_index = getTableIndex(hashCode);
    if(hashTable[table_index].string == NULL && hashTable[table_index].next == NULL)
    {
        return 0;
    }
    
    if(hashTable[table_index].string != NULL)
    {
        if(strcmp(hashTable[table_index].string,string) == 0)
        {
            return 1;
        }
        struct hashEntry *n = hashTable[table_index].next;
        struct hashEntry *p = &hashTable[table_index];
        while(n != NULL)
        {
            if(strcmp(n->string,string) == 0)
            {
                return 1;
            }
            p=n;
            n = (n->next);
        }
        return 0;
    }
    assert(0);
}

long getHashCode(char *string)
{
    long hash = 0;
    for(int i=0;i<strlen(string);i++)
    {
        hash = hash * 13 + string[i];
    }
    return hash;
}

int getTableIndex(long hashCode)
{
    return (hashCode % LENG);
}

void printHashTable()
{
    for(int i=0;i<LENG;i++)
    {
        printf("%d ",i);
        if(hashTable[i].string != NULL)
        {
            printf("%s ",hashTable[i].string);
        }
        else
        {
            printf("NULL ");
        }
        if(hashTable[i].next != NULL)
        {
            printf("List : ");
            struct hashEntry *n = hashTable[i].next;
            while(n!= NULL)
            {
                printf("%s, ",n->string);
                n = n->next;
            }
        }
        printf("\n");
    }
}