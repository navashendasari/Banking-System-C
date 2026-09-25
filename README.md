# **C Banking System**

A comprehensive terminal-based banking management application designed to demonstrate robust memory management, data structures, and secure data persistence in the C programming language.

# **Project Roadmap**

The development follows a modular approach, scaling from basic state management to a fully-featured secure application.

| Version | Phase | Primary Features | Ticket Range |
| :---- | :---- | :---- | :---- |
| v1.0 | State Management | Structs, Linked Lists, Menu Enums | BNK-100 to BNK-106 |
| v2.0 | Modular Logic | Makefiles, Header Refactoring, Error Codes | BNK-200 to BNK-210 |
| v3.0 | Hash Tables | O(1) Account Lookup, Collision Handling | BNK-300 to BNK-315 |
| v4.0 | Persistence | File I/O (Binary), Serialization | BNK-400 to BNK-408 |
| v5.0 | Cryptography | Bitwise XOR Encryption, SHA-256 Hashing | BNK-500 to BNK-512 |
| v6.0 | TUI | Ncurses integration, Viewport Scoping | BNK-600 to BNK-620 |

# **Development Phases**

## **v1.0: State Management**

Establish the core data architecture. Focuses on representing accounts as C structures and managing the runtime life cycle using a switch-case state machine.

* Implementation of **Linked Lists** for dynamic account storage.  
* Basic CRUD operations (Create, Read, Update, Delete) for client profiles.  
* Global state handler to manage transitions between user and admin modes.

## **v2.0: Modular Logic**

Refactoring the monolithic codebase into a scalable architecture.

* Separation of concerns using `.h` header files and `.c` implementation files.  
* Automated build pipeline using a **Makefile**.  
* Integration of a standard error-handling library for transaction validation.

## **v3.0: Hash Tables**

Optimizing data retrieval performance.

* Transitioning from O(n) linked list searches to O(1) **Hash Table** lookups.  
* Implementation of the Jenkins or DJB2 hashing algorithm for account IDs.  
* Chaining mechanism to resolve hash collisions.

## **v4.0: Persistence**

Transitioning from volatile memory to disk storage.

* Implementation of **File I/O** using binary modes (`rb`, `wb`).  
* Object serialization to ensure data integrity during save/load cycles.  
* Automatic database backups on application exit.

## **v5.0: Cryptography**

Securing sensitive user information.

* Application of **Bitwise Operations** for lightweight XOR encryption on stored data.  
* PIN hashing to prevent plain-text password exposure in the database.  
* Buffer overflow protection during sensitive data input.

## **v6.0: Terminal User Interface (TUI)**

Enhancing the user experience through a structured terminal interface.

* Integration of the **ncurses** library for window-based navigation.  
* Support for arrow-key navigation and color-coded status messages.  
* Real-time transaction history scrolling.

# **Compilation Instructions**

## **Prerequisites**

* GCC (GNU Compiler Collection) or Clang  
* Make (optional but recommended)  
* ncurses library (required for v6.0)

## **Manual Compilation**

To compile the system manually from the project root, execute the following command:

gcc \-Wall \-Iinclude src/\*.c \-o banking\_system \-lncurses

## **Using Makefile**

If you are using the provided build system, simply run:

`make all`

## **Running the Application**

Once compiled, start the system with:

FOR V2: Use : gcc app.c database.c auth.c -o bank

`./banking_system`  
