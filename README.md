# FinTrak: Personal Budget Management System

FinTrak is a terminal-based personal budget management system written in C. It helps users track their income, expenses, and savings with a simple, interactive interface. Users can add, edit, delete, and categorize their financial records, view summaries, and save/load data persistently. This project showcases advanced memory management, file I/O, and user interaction in a single C file.

## Features

- **Add Income and Expenses**: Easily add new income or expense entries with a description and amount.
- **Edit Records**: Modify any existing income or expense record.
- **Delete Records**: Remove specific income or expense entries.
- **Expense Categorization**: Group expenses by categories for more detailed tracking.
- **Summary View**: Displays total income, total expenses, and savings.
- **File Persistence**: Automatically saves data to a file and loads it upon startup.
- **Dynamic Memory Management**: Efficiently manages memory for income and expense lists as they grow in size.

## How to Use

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/FinTrak.git
    cd FinTrak
    ```

2. Compile the program using `gcc`:
    ```bash
    gcc fintrak.c -o fintrak
    ```

3. Run the program:
    ```bash
    ./fintrak
    ```

4. Follow the interactive prompts to manage your personal finances.

## Menu Options

- **[1] Add Income**: Add a new income entry by providing a description and amount.
- **[2] Add Expense**: Add a new expense with a description and amount.
- **[3] Edit Income**: Modify an existing income entry by selecting its index.
- **[4] Edit Expense**: Modify an existing expense entry by selecting its index.
- **[5] Delete Income**: Remove an income entry by specifying its index.
- **[6] Delete Expense**: Remove an expense entry by specifying its index.
- **[7] View Summary**: Displays the total income, total expenses, and calculated savings.
- **[8] View Expenses by Category**: Search and view expenses that match a specific category.
- **[9] Save & Exit**: Save all data to a file and exit the program.

## File Storage

All financial data is saved automatically in a local file (`budget.txt`). On the next run, the data is loaded and continues from where it was left off.

## Requirements

- A GCC compiler or any C compiler that supports the standard C library.
- Runs on Linux, macOS, and Windows (with GCC or a similar C compiler).

