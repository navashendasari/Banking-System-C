#include <stdio.h>
#include <string.h>
#include "bank.h"

int auth_session(struct Account *current_user){
    int client_active = 1;
    int choice;

    while (client_active) {
        printf("\n=================================== \n");
        printf("            CLIENT PORTAL             \n");
        printf("=================================== \n");
        printf("Welcome, %s.\n", current_user->name);
        printf("Balance: $%.2f\n", current_user->balance);
        printf("-----------------------------------\n");
        printf("[1] Deposit\n");
        printf("[2] Withdraw\n");
        printf("[3] Delete Account\n");
        printf("[4] Fund Transfer (internal)\n");
        printf("[0] Logout\n");
        printf("Enter Command: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1; 
        }

        switch(choice) {
            case 1:{
                float deposit;
                printf("Enter deposit amount: ");

                if (scanf("%f", &deposit) != 1) {
                    printf("Invalid deposit amount.\n");
                    while (getchar() != '\n');
                    break;
                }
                if (deposit <= 0) {
                    printf("Deposit amount must be greater than zero.\n");
                    continue;
                }
                current_user->balance += deposit;

                printf("\nDeposit of %.2f was successful. Current Balance: %.2f", deposit, current_user->balance);

                break;
            }
            case 2:{
                float withdrawal;
                printf("Enter withdrawal amount: ");
                
                if (scanf("%f", &withdrawal) != 1) {
                    printf("Invalid withdrawal amount.\n");
                    while (getchar() != '\n');
                    break;
                }
                if (withdrawal <= 0) {
                    printf("Withdraw amount must be greater than zero.\n");
                    continue;
                }

                if(current_user->balance >= withdrawal){
                    current_user->balance -= withdrawal;
                    printf("\nWithdrawal of %.2f was successful. Current Balance: %.2f", withdrawal, current_user->balance);
                }else{
                    printf("Insufficient Funds, try again.\n");
                    continue;
                }
                break;
            }
            case 3:{
                int del = close_account(current_user->account_id);
                if(del == 1){
                   printf("...Initiating New Session....\n");
                   return 2;
                }
                break;
            }
            case 4: {
                float amount;
                int recipient_id;
                char transaction_auth_pwd[50];

                printf("\nEnter the recipient's Bank ID: ");

                if(scanf("%d", &recipient_id) != 1) {
                    while(getchar() != '\n');
                    printf("Invalid input. Please enter a number.\n");
                    continue;
                }
                
                if (recipient_id == current_user->account_id) {
                    printf("You cannot transfer funds to your own account.\n");
                    continue;
                }

                struct Account *recipient = find_account(recipient_id);

                if(recipient == NULL) {
                    printf("Bank ID not found, Try again with an existing Bank ID.\n");
                    continue;
                }

                printf("Enter transfer amount: ");
                if(scanf("%f", &amount) != 1) {
                    while(getchar() != '\n');
                    printf("Invalid input. Please enter a number.\n");
                    continue;
                }
                
                if (amount <= 0) {
                    printf("Invalid amount. Transfer amount cannot be zero or negative.\n");
                    continue;
                }

                if (current_user->balance < amount) {
                    printf("Insufficient Funds for this transfer.\n");
                    continue;
                }

                printf("Enter password to confirm transfer: ");
                scanf("%49s", transaction_auth_pwd);

                if(strcmp(transaction_auth_pwd, current_user->password) == 0) {
                    current_user->balance -= amount;
                    recipient->balance += amount;
                    printf("Transfer of $%.2f to %s was successful.\n", amount, recipient->name);
                } else {
                    printf("Wrong Password. Transfer cancelled.\n");
                }
                
                continue;
            }
            case 0:{
                printf("Logging out...\n");
                return 0;
            }
            default:{
                printf("Invalid command.\n");
            }
        }
    }
    return 1; 
}