/*
 * linkedlist.c
 *
 * Based on the implementation approach described in "The Practice 
 * of Programming" by Kernighan and Pike (Addison-Wesley, 1999).
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"


void *emalloc(size_t n) {
    void *p;

    p = malloc(n);
    if (p == NULL) {
        fprintf(stderr, "malloc of %zu bytes failed", n);
        exit(1);
    }

    return p;
}


wordnode_t *new_word(char *w, int val) {
    assert( w != NULL);

    wordnode_t *temp = (wordnode_t *)emalloc(sizeof(wordnode_t));

    temp->w = strdup(w);
    temp->val = val;
    temp->next = NULL;

    return temp;
}
int match(wordnode_t* list, char* line){
    wordnode_t *copy = list;
    int flag = 0;
    while(copy->next != NULL){
        if(strcasecmp(copy->w, line)==0) {
            flag = 1;
            break;
        }
        copy = copy->next;
    }
    return flag;
}

int match_word(wordnode_t* list, char* word){
    char * space = " ";
    wordnode_t* words = NULL;
    words = add_end(words, new_word(list->w, 0));
    int flag = 0;
    char *token = strtok(words->w, space);
    while(token != NULL){
        if(strcasecmp(token, word) == 0) flag =1;
        token = strtok(NULL, space);
    }
    return flag;

}
/* method to sort a linkedlist by finding the correct place each node should be added in at the time of insert
 * credit: https://www.geeksforgeeks.org/given-a-linked-list-which-is-sorted-how-will-you-insert-in-sorted-way/
 */
wordnode_t* sort (wordnode_t * head, wordnode_t* string){
    wordnode_t * current = NULL;

    //no element in list
    if(head == NULL|| strncmp(string->w, head->w, strlen(string->w))<0){
        add_front(head,string);
        return string;
    } else{
        current = head;
        while(current->next!=NULL && strcmp(string->w, current->next->w) >0) current = current->next;
        string->next = current->next;
        current->next = string;
    }
    return head;
}

wordnode_t *add_front(wordnode_t *list, wordnode_t *new) {
    new->next = list;
    return new;
}


wordnode_t *add_end(wordnode_t *list, wordnode_t *new) {
    wordnode_t *curr;

    if (list == NULL) {

        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return list;
}


wordnode_t *peek_front(wordnode_t *list) {
    return list;
}


wordnode_t *remove_front(wordnode_t *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->next;
}


void free_word(wordnode_t *word) {
    assert(word != NULL);

    if (word->w != NULL) {
        free(word->w);
    }
    free(word);
}


void apply(wordnode_t *list,
           void (*fn)(wordnode_t *list, void *),
           void *arg)
{
    for ( ; list != NULL; list = list->next) {
        (*fn)(list, arg);
    }
}
