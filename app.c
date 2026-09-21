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
        printf("Name: %s, Account ID: %d, Balance: %.2f, password: %s \n",current->name , current->account_id, current->balance, current->password);
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
        printf("[0] Logout\n");
        printf("Enter Command: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1; 
        }

        switch(choice) {
            case 1:
                // TODO: Ask for amount, add to current_user->balance
                break;
            case 2:
                // TODO: Ask for amount, subtract from current_user->balance
                break;
            case 3:
                // TODO: Call close_account(), then return 2;
                break;
            case 0:
                printf("Logging out...\n");
                return 0; // This cleanly exits the function and passes 0 back to main()
            default:
                printf("Invalid command.\n");
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
                scanf(" %[^\n]", name);

                printf("Create your Bank ID: ");
                
                if (scanf("%d", &id) != 1) {
                    while (getchar() != '\n');
                    printf("Invalid Bank ID, Enter a numeric value. \n");
                    continue;
                }


                if (find_account(id) != NULL){
                    printf("Bank ID Already exisits!, Please try a new one. \n");
                    continue;
                }

                printf("Enter a strong password: ");
                scanf(" %[^\n]", password);


                printf("Enter the initial deposit amount: ");
                
                if (scanf("%f", &balance) != 1) {
                    while (getchar() != '\n');
                    printf("Invalid Deposit, Enter a numeric value. \n");
                    continue;
                }
// Automate this user input checking thingy to a seperate function();

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
                    printf("Invalid Bank ID, Enter a numeric value.");
                    continue;
                }

                struct Account *user = find_account(auth_id);
                    
                if (user == NULL) {
                    printf(">> ERROR: Account not found.\n");
                    break; 
                }
                printf("Enter Password: ");
                scanf("%s", auth_pwd);
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