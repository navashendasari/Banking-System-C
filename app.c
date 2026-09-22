#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct Account{
    int account_id;
    float balance;
    char name[50];
    char password[50];
    struct Account *next;
};

struct Account *head = NULL;

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
        printf("[4] Fund Transfer (interal)\n");
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
                   printf("...Intiating New Session....\n");
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
                    printf(">> SECRUITY ALERT: Invalid password.\n");
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