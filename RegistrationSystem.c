#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int num_student;
int num_courses;
int option;
int num = 0;

int* registered_studentid;
char(*registered_courseid)[8];
int* Student_ids;
char(*Courses_ids)[8];

void Welcome_prompt() {
    printf("Welcome to the Student Registration System.\n\n");
    printf("Enter the number of students to register: ");
    scanf_s("%d", &num_student);
}

void Studentid_prompt(int array[], int length) {
    for (int i = 0; i < length; i++) {
        int valid = 0;
        while (valid == 0) {
            printf("Enter the Student index[%d] student id [5-digits]: ", i);
            if (scanf_s("%d", &array[i]) == 1) {
                long content = array[i];
                int count = 0;
                while (content > 0) {
                    content /= 10;
                    count++;
                }

                if (count == 5) {
                    valid = 1;
                }
                else {
                    printf("Invalid input. Please enter 5 digits. Try again.\n");
                }
            }
            else {
                printf("Invalid input. Please enter 5 digits. Try again.\n");
                while (getchar() != '\n');
            }
        }
    }
}

void courses() {
    printf("Enter the number of courses available: ");
    scanf_s("%d", &num_courses);
}

int isAlpha(const char* str) {
    int count1 = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            count1++;
        }
    }
    return count1;
}

void courseid_prompt(char array[][8], int num_courses) {
    for (int i = 0; i < num_courses; i++) {
        int valid = 0;
        while (valid == 0) {
            printf("Enter the Student index[%d] course id [3-Alphas][4-digits]: ", i);
            if (scanf_s("%3s%4s", array[i], &array[i][3]) == 2) {
                if (isalpha(array[i][0]) && isalpha(array[i][1]) && isalpha(array[i][2]) &&
                    isdigit(array[i][3]) && isdigit(array[i][4]) && isdigit(array[i][5]) && isdigit(array[i][6])) {
                    valid = 1;
                }
                else {
                    printf("Incorrect Course Id input [3-Alphas][4-digits].\n");
                }
            }
            else {
                printf("Incorrect Course Id length [7-character Id].\n");
                while (getchar() != '\n');
            }
        }
    }
}

void Main_menu() {
    printf("\nMain Menu:\n");
    printf("[1] Register a student into a course.\n");
    printf("[2] Drop a student from a course.\n");
    printf("[3] Display Registration table.\n");
    printf("[4] Exit.\n");
    printf("Enter an option from the menu: ");
    scanf_s("%d", &option);
}

void List_Studentids() {
    printf("List of studentIds\n");
    for (int i = 0; i < num_student; i++) {
        printf("Index %d      %d\n", i, Student_ids[i]);
    }
}

void List_CourseIds() {
    printf("List of Available Course Id\n");
    for (int i = 0; i < num_courses; i++) {
        printf("Index %d      %s\n", i, Courses_ids[i]);
    }
}

void add_Student(int array1[], char array2[][8]) {
    if (num >= num_student) {
        printf("Registration is full. Cannot add more students.\n");
        return;
    }

    List_Studentids();
    Studentid_prompt(array1, 1);
    List_CourseIds();
    courseid_prompt(array2, 1);

    registered_studentid[num] = array1[0];
    strcpy_s(registered_courseid[num], 8, array2[0]);

    num++;

    printf("Registered successfully!\n");
}

void Drop(char D[], int num_student) {
    int index;
    printf("Please select Index number to drop student registration: ");
    scanf_s("%d", &index);
    if (index >= 0 && index < num_student) {
        D[index] = 'D';
        printf("Dropped successfully!\n");
    }
    else {
        printf("Invalid index. Please enter a valid index.\n");
    }
}

void Display_Registered(int array1[], char array2[][8], char D[]) {
    printf("                     Registration Table\n");
    printf("Registration Index        Student ID        Course ID        Registration Status\n");
    for (int f = 0; f < num; f++) {
        printf("       %d                  %d              %s                     %c\n", f, array1[f], array2[f], D[f]);
    }
}

int main() {
    Welcome_prompt();
    Student_ids = (int*)malloc(num_student * sizeof(int));
    Studentid_prompt(Student_ids, num_student);
    courses();
    Courses_ids = (char(*)[8])malloc(num_courses * sizeof(char[8]));
    courseid_prompt(Courses_ids, num_courses);
    registered_studentid = (int*)malloc(num_student * sizeof(int));
    registered_courseid = (char(*)[8])malloc(num_student * sizeof(char[8]));

    char* drop = (char*)malloc(num_student * sizeof(char)); // Allocate memory for 'drop'

    for (int i = 0; i < num_student; i++) {
        drop[i] = 'R';  // Initialize all registrations as 'R'
    }

    while (option != 4) {
        Main_menu();
        switch (option) {
        case 1:
            add_Student(registered_studentid, registered_courseid);
            break;
        case 2:
            Drop(drop, num_student); // Pass num_student to Drop function
            break;
        case 3:
            Display_Registered(registered_studentid, registered_courseid, drop);
            break;
        case 4:
            free(Student_ids);
            free(Courses_ids);
            free(registered_studentid);
            free(registered_courseid);
            free(drop); // Free the allocated memory for 'drop'
            break;
        default:
            break;
        }
    }

    return 0;
}
