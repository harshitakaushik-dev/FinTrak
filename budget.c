#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESC_LEN 50        //defining maximum length for descriptions
#define INITIAL_CAPACITY 10     //defeing Initial capacity for income & expense arrays

// Structure for income and expenses
typedef struct {
    char description[MAX_DESC_LEN];
    double amount;
} Entry;

typedef struct {
    Entry *income;
    Entry *expenses;
    int income_count;
    int expense_count;
    int income_capacity;
    int expense_capacity;
} Budget;

// Function prototypes
void initialize_budget(Budget *budget);
void resize_entries(Entry **entries, int *capacity);
void add_income(Budget *budget);
void add_expense(Budget *budget);
void display_summary(Budget *budget);
void display_by_category(Budget *budget);
void edit_income(Budget *budget);
void edit_expense(Budget *budget);
void delete_income(Budget *budget);
void delete_expense(Budget *budget);
void save_to_file(Budget *budget, const char *filename);
void load_from_file(Budget *budget, const char *filename);
void clear_input_buffer();
void free_budget(Budget *budget);

int main() {
    Budget budget;
    char choice;
    
    initialize_budget(&budget);     //Initializing our budget stucture
    
    load_from_file(&budget, "budget.txt");      //Loading existing data from file

    printf("Welcome to the Personal Budget Tracker!\n");
    
    do {
        printf("\nMenu:\n");
        printf("[1] Add Income\n");
        printf("[2] Add Expense\n");
        printf("[3] Edit Income\n");
        printf("[4] Edit Expense\n");
        printf("[5] Delete Income\n");
        printf("[6] Delete Expense\n");
        printf("[7] View Summary\n");
        printf("[8] View Expenses by Category\n");
        printf("[9] Save & Exit\n");
        printf("Choose an option: ");
        scanf(" %c", &choice);
        clear_input_buffer();   //clearing input buffer to avoid issues with subsequent inputs

        switch (choice) {
            case '1':
                add_income(&budget);
                break;
            case '2':
                add_expense(&budget);
                break;
            case '3':
                edit_income(&budget);
                break;
            case '4':
                edit_expense(&budget);
                break;
            case '5':
                delete_income(&budget);
                break;
            case '6':
                delete_expense(&budget);
                break;
            case '7':
                display_summary(&budget);
                break;
            case '8':
                display_by_category(&budget);
                break;
            case '9':
                save_to_file(&budget, "budget.txt");
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (choice != '9');
    
    free_budget(&budget);   //Freeing up allocated memory before exiting
    
    return 0;
}

// Initialize the budget structure with initial capacity 
void initialize_budget(Budget *budget) {
    budget->income = (Entry *)malloc(INITIAL_CAPACITY * sizeof(Entry));
    budget->expenses = (Entry *)malloc(INITIAL_CAPACITY * sizeof(Entry));
    budget->income_count = 0;
    budget->expense_count = 0;
    budget->income_capacity = INITIAL_CAPACITY;
    budget->expense_capacity = INITIAL_CAPACITY;
}

// Resize entry array when full (doubles the capacity)
void resize_entries(Entry **entries, int *capacity) {
    *capacity *= 2; //doubling the capacity
    *entries = (Entry *)realloc(*entries, (*capacity) * sizeof(Entry));
}

// Function to clear the input buffer (for scanf)
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to add income
void add_income(Budget *budget) {
    if (budget->income_count >= budget->income_capacity) {
        resize_entries(&budget->income, &budget->income_capacity);
    }
    
    Entry *income = &budget->income[budget->income_count++];
    
    printf("Enter income description: ");
    fgets(income->description, MAX_DESC_LEN, stdin);
    income->description[strcspn(income->description, "\n")] = 0; // Remove newline
    
    printf("Enter income amount: ");
    scanf("%lf", &income->amount);
    clear_input_buffer();
    
    printf("Income added successfully.\n");
}

// Function to add an expense
void add_expense(Budget *budget) {
    if (budget->expense_count >= budget->expense_capacity) {
        resize_entries(&budget->expenses, &budget->expense_capacity);
    }
    
    Entry *expense = &budget->expenses[budget->expense_count++];
    
    printf("Enter expense description: ");
    fgets(expense->description, MAX_DESC_LEN, stdin);
    expense->description[strcspn(expense->description, "\n")] = 0; // Remove newline
    
    printf("Enter expense amount: ");
    scanf("%lf", &expense->amount);
    clear_input_buffer();
    
    printf("Expense added successfully.\n");
}

// Function to edit income
void edit_income(Budget *budget) {
    if (budget->income_count == 0) {
        printf("No income to edit.\n");
        return;
    }
    
    int index;
    printf("Enter the index of income to edit (0 to %d): ", budget->income_count - 1);
    scanf("%d", &index);
    clear_input_buffer();

    if (index < 0 || index >= budget->income_count) {
        printf("Invalid index.\n");
        return;
    }

    printf("Editing income: %s, %.2f\n", budget->income[index].description, budget->income[index].amount);

    printf("Enter new description: ");
    fgets(budget->income[index].description, MAX_DESC_LEN, stdin);
    budget->income[index].description[strcspn(budget->income[index].description, "\n")] = 0; // Remove newline
    
    printf("Enter new amount: ");
    scanf("%lf", &budget->income[index].amount);
    clear_input_buffer();

    printf("Income updated successfully.\n");
}

// Function to edit expense
void edit_expense(Budget *budget) {
    if (budget->expense_count == 0) {
        printf("No expenses to edit.\n");
        return;
    }
    
    int index;
    printf("Enter the index of expense to edit (0 to %d): ", budget->expense_count - 1);
    scanf("%d", &index);
    clear_input_buffer();

    if (index < 0 || index >= budget->expense_count) {
        printf("Invalid index.\n");
        return;
    }

    printf("Editing expense: %s, %.2f\n", budget->expenses[index].description, budget->expenses[index].amount);

    printf("Enter new description: ");
    fgets(budget->expenses[index].description, MAX_DESC_LEN, stdin);
    budget->expenses[index].description[strcspn(budget->expenses[index].description, "\n")] = 0; // Remove newline
    
    printf("Enter new amount: ");
    scanf("%lf", &budget->expenses[index].amount);
    clear_input_buffer();

    printf("Expense updated successfully.\n");
}

// Function to delete income
void delete_income(Budget *budget) {
    if (budget->income_count == 0) {
        printf("No income to delete.\n");
        return;
    }
    
    int index;
    printf("Enter the index of income to delete (0 to %d): ", budget->income_count - 1);
    scanf("%d", &index);
    clear_input_buffer();

    if (index < 0 || index >= budget->income_count) {
        printf("Invalid index.\n");
        return;
    }

    for (int i = index; i < budget->income_count - 1; i++) {
        budget->income[i] = budget->income[i + 1];
    }
    budget->income_count--;
    printf("Income deleted successfully.\n");
}

// Function to delete expense
void delete_expense(Budget *budget) {
    if (budget->expense_count == 0) {
        printf("No expenses to delete.\n");
        return;
    }
    
    int index;
    printf("Enter the index of expense to delete (0 to %d): ", budget->expense_count - 1);
    scanf("%d", &index);
    clear_input_buffer();

    if (index < 0 || index >= budget->expense_count) {
        printf("Invalid index.\n");
        return;
    }

    for (int i = index; i < budget->expense_count - 1; i++) {
        budget->expenses[i] = budget->expenses[i + 1];
    }
    budget->expense_count--;
    printf("Expense deleted successfully.\n");
}

// Function to display a summary of income, expenses, and savings
void display_summary(Budget *budget) {
    double total_income = 0, total_expenses = 0, savings = 0;
    
    printf("\n--- Financial Summary ---\n");
    
    // Calculate total income
    for (int i = 0; i < budget->income_count; i++) {
        total_income += budget->income[i].amount;
    }
    
    // Calculate total expenses
    for (int i = 0; i < budget->expense_count; i++) {
        total_expenses += budget->expenses[i].amount;
    }
    
    // Calculate savings
    savings = total_income - total_expenses;
    
    // Display summary
    printf("Total Income: $%.2f\n", total_income);
    printf("Total Expenses: $%.2f\n", total_expenses);
    printf("Savings: $%.2f\n", savings);
}

// Function to display expenses grouped by category
void display_by_category(Budget *budget) {
    char category[MAX_DESC_LEN];
    
    printf("\nEnter category to view expenses: ");
    fgets(category, MAX_DESC_LEN, stdin);
    category[strcspn(category, "\n")] = 0; // Remove newline
    
    printf("\n--- Expenses in Category: %s ---\n", category);
    
    double total = 0;
    int found = 0;
    
    for (int i = 0; i < budget->expense_count; i++) {
        if (strstr(budget->expenses[i].description, category) != NULL) {
            printf("Description: %s, Amount: $%.2f\n", budget->expenses[i].description, budget->expenses[i].amount);
            total += budget->expenses[i].amount;
            found = 1;
        }
    }
    
    if (found) {
        printf("Total for category '%s': $%.2f\n", category, total);
    } else {
        printf("No expenses found in this category.\n");
    }
}

// Save data to a file
void save_to_file(Budget *budget, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error saving to file.\n");
        return;
    }

    fprintf(file, "%d %d\n", budget->income_count, budget->expense_count);

    for (int i = 0; i < budget->income_count; i++) {
        fprintf(file, "%s %.2f\n", budget->income[i].description, budget->income[i].amount);
    }

    for (int i = 0; i < budget->expense_count; i++) {
        fprintf(file, "%s %.2f\n", budget->expenses[i].description, budget->expenses[i].amount);
    }

    fclose(file);
    printf("Data saved successfully.\n");
}

// Load data from a file
void load_from_file(Budget *budget, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("No previous data found.\n");
        return;
    }

    fscanf(file, "%d %d\n", &budget->income_count, &budget->expense_count);

    for (int i = 0; i < budget->income_count; i++) {
        fscanf(file, "%s %lf\n", budget->income[i].description, &budget->income[i].amount);
    }

    for (int i = 0; i < budget->expense_count; i++) {
        fscanf(file, "%s %lf\n", budget->expenses[i].description, &budget->expenses[i].amount);
    }

    fclose(file);
    printf("Data loaded successfully.\n");
}

// Free dynamically allocated memory
void free_budget(Budget *budget) {
    free(budget->income);
    free(budget->expenses);
}
