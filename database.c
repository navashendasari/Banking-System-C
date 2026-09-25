#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bank.h"

struct Account *create_account(int id, float balance, const char *name, const char *password){
    struct Account *newNode = malloc(sizeof(struct Account));
    if (newNode == NULL){
        printf("Server Memory Full.\n");
        return NULL;
    }

    newNode->account_id = id;
    newNode->balance = balance;
    strcpy(newNode->name, name);
    strcpy(newNode->password, password);
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

struct Account *find_account(int target_id){
    struct Account *current = head;
    while (current != NULL){
        if(current->account_id == target_id){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int close_account(int del_id){
    if(head == NULL){
        return -1;
    }
    int del_choice;
    printf("Are you sure you want to delete your Account? [ID: %d] \n[1] Yes.\n[2] No.", del_id);
    if (scanf("%d", &del_choice) != 1){
        while(getchar() != '\n');
        del_choice = -1;
    }

    switch(del_choice){
        case 1:{

            struct Account *del_user = find_account(del_id);
            if(head->account_id == del_id){
                head = head->next;
                free(del_user);
                return 1;
            }
            else {
                struct Account *current = head;

                while (current->next != NULL) {
                    if (current->next->account_id == del_id) {
                    current->next = del_user->next; 
                    break;
                }
                    current = current->next;
                }
    
                free(del_user);
                return 1;
            }
        }
        case 2:{
            printf("Account deletion cancelled.\n");
            return 0;
        }
        default:{
            printf("Invalid Selection, Please try again.\n");
            return 0;
        }
    }
}
