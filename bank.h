#ifndef BANK_H
#define BANK_H

struct Account {
    int account_id;
    float balance;
    char name[50];
    char password[50];
    struct Account *next;
};
// "extern" needed bcz main requires, just creating inter-file struct
extern struct Account *head;

struct Account *create_account(int id, float balance, const char *name, const char *password);
void add_Account(struct Account *new_account);
void display_all_accounts();
struct Account *find_account(int target_id);
int close_account(int del_id);
int auth_session(struct Account *current_user);

#endif