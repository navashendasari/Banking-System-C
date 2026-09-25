#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "bank.h"

struct Account *head = NULL;

void display_all_accounts(){
    struct Account *current = head;
     if(current == NULL){
        printf("Currently no active accounts.\n");
        return;
    }
    while(current != NULL){
        printf("Name: %s, Account ID: %d \n",current->name , current->account_id);
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
        printf("[3] Account Login\n");
        printf("[0] Terminate Session\n");

        printf("Enter Command: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1; 
        }

        switch(choice){
            case 1:{

                int id;
                float balance;
                char password[50];
                char name[50];

                printf("Enter your Full Name: ");
                scanf(" %49[^\n]", name);

                printf("Create your Bank ID: ");
                
                if (scanf("%d", &id) != 1) {
                    while (getchar() != '\n');
                    printf("Invalid Bank ID, Enter a numeric value. \n");
                    continue;
                }


                if (find_account(id) != NULL){
                    printf("Bank ID Already exists!, Please try a new one. \n");
                    continue;
                }

                printf("Enter a strong password: ");
                scanf("%49s", password);


                printf("Enter the initial deposit amount: ");
                
                if (scanf("%f", &balance) != 1) {
                    while (getchar() != '\n');
                    printf("Invalid input. Please enter a number.\n");
                    continue;
                }
                if (balance < 100.00) {
                    printf("Initial deposit must be at least $100.00.\n");
                    continue;
                }

                struct Account *new_user = create_account(id, balance, name, password);
                
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

            case 3:{
                int auth_id;
                char auth_pwd[50];

                printf("===================================\n");
                printf("Welcome to Login Portal\n");
                printf("Enter your Bank ID: ");
                if (scanf("%d", &auth_id) != 1) {
                    while (getchar() != '\n');
                    printf("Invalid Bank ID, Enter a numeric value. \n");
                    continue;
                }

                struct Account *user = find_account(auth_id);
                    
                if (user == NULL) {
                    printf(">> ERROR: Account not found.\n");
                    break; 
                }
                printf("Enter Password: ");
                scanf("%49s", auth_pwd);
                if (strcmp(user->password, auth_pwd) != 0) {
                    printf(">> SECURITY ALERT: Invalid password.\n");
                    break;
                }

                printf(">> SUCCESS: Welcome back, %s.\n", user->name);

                int auth_status = 1;
                auth_status = auth_session(user);
                if (auth_status == 0) {
                    // logout
                    continue; 
                } else if (auth_status == 2) {
                    // account deleted
                    continue; 
                }
                break;

            }

            case 0:{
                printf("\n>> SYSTEM: Saving states... Terminating process.\n");
                session = 0;
                printf("Program Terminated.");
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
