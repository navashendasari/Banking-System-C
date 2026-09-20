#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct Account{
    int account_id;
    float balance;
    char name[50];
    struct Account *next;
};

struct Account *head = NULL;

struct Account *create_account(int id, float balance, const char *name){
    struct Account *newNode = malloc(sizeof(struct Account));
    if (newNode == NULL){
        printf("Server Memory Full.\n");
        return NULL;
    }

    newNode->account_id = id;
    newNode->balance = balance;
    strcpy(newNode->name, name);
    newNode->next = NULL;

    return newNode;
}

void add_Account(struct Account *new_account){
    if (head == NULL){
        head = new_account;
        return;
    }else{
        struct Account *current = head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = new_account;
    }
}

void display_all_accounts(){
    struct Account *current = head;
    while(current != NULL){
        printf("Name: %s, Account ID: %d, Balance: %.2f \n",current->name , current->account_id, current->balance);
        current = current->next;
    }
}

int main(){
    
    struct Account *user1 = create_account(5564075, 660000, "Winston");
    add_Account(user1);
    struct Account *user2 = create_account(5564175, 550000, "Franklin");
    add_Account(user2);
    struct Account *user3 = create_account(5564275, 710000, "Stanlin");
    add_Account(user3);

    display_all_accounts();
    
    return 0;
}