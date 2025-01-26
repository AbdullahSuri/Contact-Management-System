# Contact Management System

## Table of Contents

- [Introduction](#introduction)
- [Directory Structure](#directory-structure)
- [Dependencies](#dependencies)
- [Compilation and Execution](#compilation-and-execution)
- [Usage](#usage)
- [Commands](#commands)
- [Contact Format](#contact-format)
- [Code Details](#code-details)

---

## Introduction

The Contact Management System is a C++ program that allows users to manage contact information using a binary search tree (BST). Contacts can be imported/exported from/to CSV files, added, updated, marked as favorites, and displayed in various orders.

---

## Directory Structure

```
├── cms.out
├── contact.cpp
├── contact.h
├── contact.o
├── contactbst.cpp
├── contactbst.h
├── contactbst.o
├── contacts.csv
├── main.cpp
├── main.o
├── Makefile
├── myvector.cpp
├── myvector.h
├── myvector.o
└── README.md
```

---

## Dependencies

This program requires the following:

- A C++ compiler (e.g., g++) supporting C++11 or later

---

## Compilation and Execution

### Compilation

To compile the program, use the provided `Makefile` by running the following command in the terminal:

```bash
make
```

This will generate the executable file `cms.out`.

### Running the Program

To execute the program, run:

```bash
./cms.out
```

---

## Usage

The program provides an interactive command-line interface where users can execute various commands to manage contacts. Use the `help` command to display all available commands.

---

## Commands

Below is a list of available commands:

| Command           | Description                                                        |
| ----------------- | ------------------------------------------------------------------ |
| `import <path>`   | Import contacts from a CSV file.                                   |
| `export <path>`   | Export contacts to a CSV file.                                     |
| `add`             | Add a new contact by providing the required details interactively. |
| `update <key>`    | Update a contact's details.                                        |
| `remove <key>`    | Delete a contact.                                                  |
| `searchFor <key>` | Search for a contact by their name.                                |
| `markFav <key>`   | Mark a contact as favorite.                                        |
| `unmarkFav <key>` | Unmark a contact as favorite.                                      |
| `printASC`        | Print all contacts in ascending order.                             |
| `printDES`        | Print all contacts in descending order.                            |
| `printFav`        | Print all favorite contacts.                                       |
| `help`            | Display the list of available commands.                            |
| `exit`            | Exit the program.                                                  |

---

## Contact Format

Each contact consists of the following details:

| Field        | Description                                              |
| ------------ | -------------------------------------------------------- |
| `First Name` | Contact's first name.                                    |
| `Last Name`  | Contact's last name.                                     |
| `Email`      | Contact's email address.                                 |
| `Phone`      | Contact's phone number.                                  |
| `City`       | City where the contact resides.                          |
| `Country`    | Country where the contact resides.                       |
| `Favorite`   | Whether the contact is a favorite (1 for yes, 0 for no). |

---

## Code Details

### `main.cpp`

- Handles user interaction and command processing.
- Calls appropriate functions from the `ContactBST` class.

### `contact.cpp` and `contact.h`

- Defines the `Contact` class to store individual contact details.

### `contactbst.cpp` and `contactbst.h`

- Implements the `ContactBST` class, which manages contacts using a binary search tree.
- Key functions:
  - `add`: Adds a new contact to the BST.
  - `remove`: Removes a contact from the BST.
  - `update`: Updates contact details.
  - `markFav`/`unmarkFav`: Marks/unmarks a contact as favorite.
  - `printASC`/`printDES`: Prints contacts in ascending/descending order.
  - `importCSV`/`exportCSV`: Handles CSV file import/export.

### `myvector.cpp` and `myvector.h`

- Defines a custom vector implementation `MyVector`.
- Used to store multiple contacts within a single BST node.
- Key functions:
  - `push_back`: Adds an element to the vector.
  - `erase`: Removes an element from the vector.
  - `at`: Accesses an element by index.
  - `shrink_to_fit`: Adjusts capacity to match size.

### `contacts.csv`

- Example CSV file to store and retrieve contact data.
- Each line represents a contact in the format:
  ```csv
  FirstName,LastName,Email,Phone,City,Country,Favorite
  ```

---

## Example

### Importing Contacts

To import contacts from a CSV file:

```bash
> import contacts.csv
```

### Adding a New Contact

To add a new contact:

```bash
> add
```

Follow the prompts to enter the contact details.

### Exporting Contacts

To export all contacts to a CSV file:

```bash
> export output.csv
```

### Marking a Contact as Favorite

To mark a contact as a favorite:

```bash
> markFav John Doe
```

### Printing All Contacts

To display all contacts in ascending order:

```bash
> printASC
```

---

## Notes

- Ensure that the CSV file paths are correct when importing/exporting contacts.
- Use unique names for contacts to avoid conflicts.
- The program handles invalid inputs gracefully and prompts users to retry.
