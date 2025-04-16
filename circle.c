//YAĞIZ AKKAYA '%(+%)/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct InternshipRecords { // TABLE DATA STRUCTER
    char name[50];
    char surname[50];
    int depcode;
    int semester;
    float score;
    char grade;
} InternshipRecords;

InternshipRecords* Load_InternshipTable( char *filename, int* studentCount) { //LOAD RECORS BY USING DYNAMIC MEMORY ALLOCATION
    FILE *files;
    char buffer[1024];
    int student = 0;
    files = fopen(filename, "r");
    if (files == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    // Skip the header line-first line is empty, second line is not relevant-
    fgets(buffer, sizeof(buffer), files);
    fgets(buffer, sizeof(buffer), files);

    // First, count the number of students
    while (fgets(buffer, sizeof(buffer), files) != NULL) {
        student++;
    }

    // Allocate memory for the students
    InternshipRecords *InternshipDataTable = (InternshipRecords*)malloc(student * sizeof(InternshipRecords));
    if (InternshipDataTable == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    // Rewind the file to read again
    rewind(files);
    // Skip the header line again
    fgets(buffer, sizeof(buffer), files);
    fgets(buffer, sizeof(buffer), files);

    for (int i = 0; i < student; i++) {
        fgets(buffer, sizeof(buffer), files);
        sscanf(buffer, "%s %s %d %d %f", InternshipDataTable[i].name, InternshipDataTable[i].surname,
               &InternshipDataTable[i].depcode, &InternshipDataTable[i].semester, &InternshipDataTable[i].score);

        // Compute letter grade
        if (InternshipDataTable[i].score >= 70) {
            InternshipDataTable[i].grade = 'S'; // S for score >= 70
        } else {
            InternshipDataTable[i].grade = 'U'; // U for score < 70
        }
    }


    fclose(files);

    // Return the number of students read
    *studentCount = student;

    return InternshipDataTable;
}
void Display_InternshipDataTable(InternshipRecords* table, int student) { // DISPLAY
    printf("\n");
    // Print table header
    printf("%-10s %-10s %-15s %-10s %-10s %-10s\n", "name", "surname", "departmentCode", "semester", "score",
           "letterGrade");

    for (int i = 0; i < student; i++) {
        printf("%-10s %-10s %-15d %-10d %-10.1f %-10c\n",
               table[i].name, table[i].surname,
               table[i].depcode, table[i].semester,
               table[i].score, table[i].grade);

    }
}

void search(InternshipRecords* table, int size,  char* searchString){
    char name[50];
    char surname[50];
    int spaceIndex = -1;
    int destination=-1;

    // Find the space index
    for (int i = 0; searchString[i] != '\0'; i++) {
        if (searchString[i] == ' ') {
            spaceIndex = i;
            break;
        }
    }

    if (spaceIndex != -1) {
        // Split the search string into NAME and SURNAME
        strncpy(name, searchString, spaceIndex);
        name[spaceIndex] = '\0';
        strcpy(surname, &searchString[spaceIndex + 1]);

        // Search for the record
        for (int i = 0; i < size; i++) {
            if (strcmp(table[i].name, name) == 0 && strcmp(table[i].surname, surname) == 0) {
                destination= i;
            }
        }
    } else {
        // Search NAME
        strcpy(name, searchString);


        for (int i = 0; i < size; i++) {
            if (strcmp(table[i].name, name) == 0) {
                destination= i;
            }
        }
    }

    if (destination != -1) {
        printf(" \nname:%-10s\n surname:%-10s\n depertman code:%-15d\n semester: %-10d \n score: %-10.1f\n grade: %-10c\n",
               table[destination].name, table[destination].surname,
               table[destination].depcode, table[destination].semester,
               table[destination].score, table[destination].grade);
    } else {
        printf("\nThis student is not in our records!\n");
    }
}


void sort(InternshipRecords* table, int size){
    char option;
    printf("Which column (1: score, 2: letter grade)?: ");
    scanf("%s",&option);
    while (option<'1'&&option>'2'){
        printf("wrong input!");
        printf("Which column (1: score, 2: letter grade)?: ");
        scanf("%s",&option);
    }
    switch (option) { // BUBBLE SORT METHOD for score
        case '1':
            for (int i = 0; i < size-1; ++i) {
                for (int j = 0; j < size - i - 1; ++j) {
                    if(table[j].score > table[j+1].score){
                        InternshipRecords temp= table[j];
                        table[j] = table[j+1];
                        table[j+1] = temp;
                    }
                }
            }

            break;
        case '2': // BUBBLE SORT METHOD for letter grades
            for (int i = 0; i < size - 1; ++i) {
                for (int j = 0; j < size - i - 1; ++j) {
                    if (table[j].grade > table[j + 1].grade) {
                        // Swap the records
                        InternshipRecords temp = table[j];
                        table[j] = table[j + 1];
                        table[j + 1] = temp;
                    }
                }
            }
            break;
        default:
            printf("TEST");
    }
}




void Statistics(InternshipRecords* table, int size) { //PRINT STATISTICS

    int passed = 0, p355 = 0, p356 = 0, p365 = 0, p384 = 0;
    int failed = 0, f355 = 0, f356 = 0, f365 = 0, f384 = 0;

    for (int i = 0; i < size; ++i) {
        if (table[i].grade == 'S') {
            passed++;
        } else {
            failed++;
        }
    }
    printf("\n%d student(s) passed and %d student(s) failed!", passed, failed);
    for (int j = 0; j < size; ++j) {
        if (table[j].grade == 'S') {
            switch (table[j].depcode) {
                case 355:
                    p355++;
                    break;
                case 356:
                    p356++;
                    break;
                case 365:
                    p365++;
                    break;
                case 384:
                    p384++;
                    break;
            }
        } else {
            switch (table[j].depcode) {
                case 355:
                    f355++;
                    break;
                case 356:
                    f356++;
                    break;
                case 365:
                    f365++;
                    break;
                case 384:
                    f384++;
                    break;
            }
        }


    }
    printf("\nDepartment: 355, %d student(s) passed and %d student(s) failed!",p355,f355);
    printf("\nDepartment: 356, %d student(s) passed and %d student(s) failed!",p356,f356);
    printf("\nDepartment: 365, %d student(s) passed and %d student(s) failed!",p365,f365);
    printf("\nDepartment: 384, %d student(s) passed and %d student(s) failed!",p384,f384);

}



int main() { //I opened the existing text file on the computer and saved the data in it to the internship file I newly created.
    FILE *myfile, *data;
    char buffer[1024];
    char filename[] = "internshipData.txt";
    char entered[100];
    char option;
    data = fopen("data.txt", "r");
    if (data == NULL) {
        printf("ERROR! Could not open data.txt\n");
        exit(1);
    }
    myfile = fopen("internshipData.txt", "w");
    if (myfile == NULL) {
        printf("ERROR! Could not open internshipData.txt\n");
        fclose(data);
        exit(1);
    }
    while (fgets(buffer, sizeof(buffer), data) != NULL) {
        fputs(buffer, myfile);
    }

    fclose(data);
    fclose(myfile);

    printf(">");
    scanf("%s", entered);
    while (strcmp(filename, entered) != 0) { //comparing file names

        printf("This file does not exist. Please enter again: ");
        scanf("%s", entered);
    }
    printf("\nThe student records file (internshipData.txt) has been successfully loaded!\n");
    printf("The following records have been loaded:\n");

    int studentCount;
    InternshipRecords* InternshipData = Load_InternshipTable(filename, &studentCount);
    Display_InternshipDataTable(InternshipData, studentCount);
    int destination;

while(option!='4') {    //MENU
    printf("\nWhat would you like to do?\n"
           "1-search\n"
           "2-sort\n"
           "3-statistics\n"
           "4-exit\n"
           "Enter your choice: ");
    scanf("%s", &option);
    while (option > '4' && option < '1') { //MENU ERROR
        printf("Wrong input!\n"
               "What would you like to do?\n"
               "1-search\n"
               "2-sort\n"
               "3-statistics\n"
               "4-exit\n"
               "Enter your choice: ");
        scanf("%s", &option);
    }
    switch (option) {
        case '1':
            printf("\nPlease enter the name of the student:\n");
            scanf(" %[^\n]s", entered);
            search(InternshipData,studentCount,entered);
            break;
        case '2':
            sort(InternshipData,studentCount);
            Display_InternshipDataTable(InternshipData, studentCount);
            break;
        case '3':
            Statistics(InternshipData,studentCount);

            break;
        case '4':
            printf("BYEEE");
            return 0;
        default:
            printf("TEST");

    }
}
free(InternshipData);
    return 0;
}

//BUBBLE SORT EXPLAIN
//It uses two nested loops. The outer loop runs through the entire array, and the inner loop performs the comparison and swapping for each pass.
//In each pass, the largest unsorted element "bubbles" to its correct position.