#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 70
#define MAX_NAME_LENGTH 20
#define MAX_ROWS 10
#define MAX_COLS 7

void initializeSeats(char seats[MAX_ROWS][MAX_COLS][MAX_NAME_LENGTH]);
void displaySeats(char seats[MAX_ROWS][MAX_COLS][MAX_NAME_LENGTH]);
void assignSeat(char seats[MAX_ROWS][MAX_COLS][MAX_NAME_LENGTH], const char* student, int row, int col);
void reassignSeat(char seats[MAX_ROWS][MAX_COLS][MAX_NAME_LENGTH], const char* student, int newRow, int newCol);
void clearSeat(char seats[MAX_ROWS][MAX_COLS][MAX_NAME_LENGTH], int row, int col);
void automaticArrangement(char seats[MAX_ROWS][MAX_COLS][MAX_NAME_LENGTH], char students[MAX_STUDENTS][MAX_NAME_LENGTH], int numStudents);
void addStudents(char students[MAX_STUDENTS][MAX_NAME_LENGTH], int *numStudents);

int main() {
    char seats[MAX_ROWS][MAX_COLS][MAX_NAME_LENGTH];
    char students[MAX_STUDENTS][MAX_NAME_LENGTH];
    int numStudents = 0;

    initializeSeats(seats);

    printf("Enter the names of up to %d students (type 'done' to finish):\n", MAX_STUDENTS);
    while (numStudents < MAX_STUDENTS) {
        printf("Enter student name: ");
        scanf("%s", students[numStudents]);

        // Check for the 'done' command
        if (strcmp(students[numStudents], "done") == 0) {
            break;
        }
        numStudents++;
    }

    // Assign seats automatically
    automaticArrangement(seats, students, numStudents);

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Display Seating Arrangement\n");
        printf("2. Reassign a Seat by Student Name\n");
        printf("3. Clear a Seat\n");
        printf("4. Add More Students\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displaySeats(seats);
                break;
            case 2: {
                char student[MAX_NAME_LENGTH];
                int newRow, newCol;
                printf("Enter the name of the student to move: ");
                scanf("%s", student);
                printf("Enter new row (0 to %d) and column (0 to %d): ", MAX_ROWS - 1, MAX_COLS - 1);
                scanf("%d %d", &newRow, &newCol);
                reassignSeat(seats, student, newRow, newCol);
                break;
            }
            case 3: {
                int row, col;
                printf("Enter row and column to clear (0 to %d, 0 to %d): ", MAX_ROWS - 1, MAX_COLS - 1);
                scanf("%d %d", &row, &col);
                clearSeat(seats, row, col);
                break;
            }
            case 4:
                addStudents(students, &numStudents);
                automaticArrangement(seats, students, numStudents); // Reassign seats after adding
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void initializeSeats(char seats[MAX_ROWS][MAX_COLS][MAX_NAME_LENGTH]) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            strcpy(seats[i][j], "-"); // Initialize all seats as empty
        }
    }
}

void displaySeats(char seats[MAX_ROWS][MAX_COLS][MAX_NAME_LENGTH]) {
    printf("\nCurrent Seating Arrangement:\n");
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("%-10s ", seats[i][j]);
        }
        printf("\n");
    }
}

void assignSeat(char seats[MAX_ROWS][MAX_COLS][MAX_NAME_LENGTH], const char* student, int row, int col) {
    if (row >= 0 && row < MAX_ROWS && col >= 0 && col < MAX_COLS) {
        if (strcmp(seats[row][col], "-") == 0) {
            strcpy(seats[row][col], student); // Assign student to seat
        } else {
            printf("Seat (%d, %d) is already taken by %s.\n", row, col, seats[row][col]);
        }
    } else {
        printf("Invalid seat position (%d, %d).\n", row, col);
    }
}

void reassignSeat(char seats[MAX_ROWS][MAX_COLS][MAX_NAME_LENGTH], const char* student, int newRow, int newCol) {
    int found = 0;
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (strcmp(seats[i][j], student) == 0) {
                if (newRow >= 0 && newRow < MAX_ROWS && newCol >= 0 && newCol < MAX_COLS) {
                    if (strcmp(seats[newRow][newCol], "-") == 0) {
                        strcpy(seats[newRow][newCol], student); // Move student to new seat
                        strcpy(seats[i][j], "-"); // Clear old seat
                        printf("%s has been moved to seat (%d, %d).\n", student, newRow, newCol);
                    } else {
                        printf("New seat (%d, %d) is already taken by %s.\n", newRow, newCol, seats[newRow][newCol]);
                    }
                } else {
                    printf("Invalid seat position (%d, %d).\n", newRow, newCol);
                }
                found = 1;
                break;
            }
        }
        if (found) break;
    }
    if (!found) {
        printf("Student %s not found in the seating arrangement.\n", student);
    }
}

void clearSeat(char seats[MAX_ROWS][MAX_COLS][MAX_NAME_LENGTH], int row, int col) {
    if (row >= 0 && row < MAX_ROWS && col >= 0 && col < MAX_COLS) {
        if (strcmp(seats[row][col], "-") != 0) {
            printf("Clearing seat (%d, %d) occupied by %s.\n", row, col, seats[row][col]);
            strcpy(seats[row][col], "-"); // Clear the seat
        } else {
            printf("Seat (%d, %d) is already empty.\n", row, col);
        }
    } else {
        printf("Invalid seat position (%d, %d).\n", row, col);
    }
}

void automaticArrangement(char seats[MAX_ROWS][MAX_COLS][MAX_NAME_LENGTH], char students[MAX_STUDENTS][MAX_NAME_LENGTH], int numStudents) {
    for (int i = 0; i < numStudents; i++) {
        int row = i / MAX_COLS; // Calculate row index
        int col = i % MAX_COLS; // Calculate column index
        assignSeat(seats, students[i], row, col); // Automatically assign students to seats
    }
    printf("Automatic arrangement completed.\n");
}

void addStudents(char students[MAX_STUDENTS][MAX_NAME_LENGTH], int *numStudents) {
    if (*numStudents >= MAX_STUDENTS) {
        printf("Cannot add more students. Maximum limit of %d reached.\n", MAX_STUDENTS);
        return;
    }

    printf("Adding more students:\n");
    while (*numStudents < MAX_STUDENTS) {
        char student[MAX_NAME_LENGTH];
        printf("Enter student name (type 'done' to stop adding): ");
        scanf("%s", student);

        // Check for the 'done' command
        if (strcmp(student, "done") == 0) {
            break;
        }

        // Add the new student
        strcpy(students[*numStudents], student);
        (*numStudents)++;
    }
    printf("Students added. Total now: %d\n", *numStudents);
}
