#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "linkedlist.h"

wordnode_t *exclude_l = NULL;
wordnode_t *lines_l= NULL;
wordnode_t *sorted_l = NULL;

void printword(wordnode_t *n, void *arg) {
    char *format = (char *)arg;

    printf(format, n->w);
}

int parse_string(char *buf) {
    char *ptr = strchr(buf, '\n');
    return ptr - buf;
}

void read_input(){
    char* exclude= malloc(sizeof(char)*20);
    char *line = malloc(sizeof(char)*100);
    fgets(exclude,20,stdin);
    fgets(exclude,20,stdin);
    int location;
    while(fgets(exclude,20,stdin)){
        if(strcmp(exclude,"::\n") == 0) break;
        location = parse_string(exclude); //find index of new line character, set as location
        exclude[location]='\0'; //remove newline character
        exclude_l = add_end(exclude_l, new_word(exclude, 0));
    }
    while(fgets(line ,100 ,stdin)){
        location = parse_string(line);
        line[location]='\0'; //remove newline character
        lines_l = add_end(lines_l, new_word(line, 0));
    }
    free(exclude);
    free(line);
}
//change entire string to Uppercase
char *to_upper(char *string){
    int c = 0;
    while (string[c] != '\0'){
        if(string[c] >= 'a' && string[c] <= 'z') string[c]= string[c]-32;
        c++;
    }
    return string;
}

//find words needed to be uppsercased, and then sort then put into a list
void find_word(){
    char *temp = malloc(sizeof(char)*100); //take each node for modifying
    const char *space = " ";
    char* token;
    wordnode_t *exptr;
    wordnode_t *ptr = lines_l;
    while(ptr != NULL){
        memset(&temp[0], 0, sizeof(char)*100);
        strncpy(temp, ptr->w, strlen(ptr->w));
        token = strtok(temp, space);
        int boolean = 0;
        while(token != NULL){

            boolean = 0;
            for(exptr = exclude_l;exptr != NULL;exptr = exptr->next) {
                if ((match(exptr, token))==1) boolean = 1;
            }
            to_upper(token);
            if(boolean == 0) sorted_l= sort(sorted_l,new_word(token,0));
            token = strtok(NULL, space);
        }
        ptr = ptr->next;
    }
    free(temp);
}
/* In this method
 * 1. remove duplicate
 * 2. resize and formatting to print pretty (incomplete)
 */
void pretty_print(wordnode_t * ans){
    wordnode_t * ptr = ans;
    int length_f = -1; //first half length
    int length_s = 0; //second half
    while(ptr->val != 1){
        length_f += 1+strlen(ptr->w);
        ptr = ptr->next;
    }
    while(length_f >20){ //first part deletion
        length_f -= 1+strlen(ans->w);
        wordnode_t *temp;
        temp = peek_front(ans);
        ans = remove_front(ans);
        free_word(temp);
    }
    length_s += strlen(ptr->w);
    //wordnode_t * remove_back;
    //wordnode_t * back_ref;
    while(ptr->next != NULL){
        length_s += 1+strlen(ptr->next->w);
        if(length_s < 30) ptr= ptr->next;
        else{
            length_s -= 1+strlen(ptr->next->w);
            //remove_back = ptr->next;
            ptr->next = NULL;
            /*while(remove_back != NULL){
                if(remove_back->next != NULL){
                    back_ref = remove_back;
                    remove_back = remove_back->next;
                    back_ref = remove_front(back_ref);
                    free(back_ref);
                }
            } */
        }
    }
    int space = 0;
    for(; space< 28 - length_f; space++) printf(" ");
    apply(ans, printword, "%s ");
    printf("\n");

}
/* replace each letter needed to be uppercased by its uppercase
 * call pretty print to print out resulting format
*/
void replace_lower() {
    wordnode_t *ptr;
    wordnode_t *word;
    for (word  = sorted_l; word != NULL; word = word->next) {
        for (ptr = lines_l; ptr != NULL; ptr = ptr->next) {
            if (match_word(ptr, word->w) == 1) {

                char arr[strlen(ptr->w + 1)];
                arr[strlen(ptr->w)] = '\0';//set last character to \0
                strncpy(arr, ptr->w, strlen(ptr->w));
                char *token = strtok(arr, " ");
                wordnode_t *output = NULL;
                while (token != NULL) {
                    if (strncasecmp(word->w, token, strlen(word->w)) == 0) { //matched
                        output = add_end(output, new_word(word->w, 1));
                    } else { //not matched
                        output = add_end(output, new_word(token, 0));
                    }
                    token = strtok(NULL, " ");
                }
                pretty_print(output);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    read_input();
    find_word();
    replace_lower();
    return 0;
}

/*wordnode_t *list1 = NULL;
wordnode_t *list2 = NULL;

list1 = add_front(list1, new_word("the", 0));
list1 = add_front(list1, new_word("fields", 0));
list1 = add_front(list1, new_word("are", 0));
list1 = add_front(list1, new_word("alive", 0));

apply(list1, printword, "%s\n");

printf("------------\n");

list2 = add_end(list2, new_word("the", 0));
list2 = add_end(list2, new_word("fields", 0));
list2 = add_end(list2, new_word("are", 0));
list2 = add_end(list2, new_word("alive", 0));

apply(list2, printword, "%s\n");

wordnode_t *temp;
temp = peek_front(list2);
list2 = remove_front(list2);
free_word(temp);

printf("------------\n");
apply(list2, printword, "%s\n");

#ifdef DEBUG
while (list2) {
    temp = peek_front(list2);
    list2 = remove_front(list2);
    free_word(temp);
}

while (list1) {
    temp = peek_front(list1);
    list1 = remove_front(list1);
    free_word(temp);
}
#endif
exit(0);
}*/
