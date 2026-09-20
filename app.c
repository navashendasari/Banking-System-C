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
    
    int session = 1;
    int choice;

    while(session){
        printf("=================================== \n");
        printf("🅣🅔🅡🅜🅘🅝🅐🅛 🅑🅐🅚🅘🅝🅖 🅢🅨🅢🅣🅔🅜🅢 \n");
        printf("=================================== \n");
        printf("[1] Open New Account\n");
        printf("[2] View All Active Accounts\n");
        printf("[0] Terminate Session\n");

        printf("Enter Command: ");

        scanf("%d", &choice);
        switch(choice){
            case 1:{
                int id;
                float balance;
                char name[50];

                printf("Enter your Full Name: ");
                scanf(" %[^\n]", name);

                printf("Create your Bank ID: ");
                scanf("%d", &id);

                printf("Enter the initial deposit amount: ");
                scanf("%f", &balance);
                
                struct Account *new_user = create_account(id, balance, name);
                
                if (new_user != NULL) {
                    add_Account(new_user);
                    printf(">> SYSTEM: Account successfully registered to %s.\n", name);
                
                }
                break;
            }
            case 2:{
                printf("System Database: \n");
                display_all_accounts();
                break;
            }

            case 0:{
                printf("\n>> SYSTEM: Saving states... Terminating process.\n");
                session = 0;
                printf("Session Terminated.");
                break;
            }
            
            default:{
                printf("Invalid Command Entered. \n");
                break;
            }
        }
    }
    
    return 0;
}