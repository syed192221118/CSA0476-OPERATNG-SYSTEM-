#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent an employee
struct Employee {
    int emp_id;
    char name[50];
    float salary;
};

int main() {
    FILE* file;
    struct Employee employee;
    int choice, emp_id;

    while (1) {
        printf("\nEmployee Record System\n");
        printf("1. Add Employee\n");
        printf("2. Read Employee\n");
        printf("3. Update Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Add an employee
                file = fopen("employees.dat", "ab");
                if (file == NULL) {
                    perror("File open error");
                    exit(1);
                }

                printf("Enter Employee ID: ");
                scanf("%d", &employee.emp_id);
                printf("Enter Name: ");
                scanf("%s", employee.name);
                printf("Enter Salary: ");
                scanf("%f", &employee.salary);

                fwrite(&employee, sizeof(struct Employee), 1, file);
                fclose(file);
                break;

            case 2:
                // Read an employee
                file = fopen("employees.dat", "rb");
                if (file == NULL) {
                    perror("File open error");
                    exit(1);
                }

                printf("Enter Employee ID to read: ");
                scanf("%d", &emp_id);

                while (fread(&employee, sizeof(struct Employee), 1, file)) {
                    if (employee.emp_id == emp_id) {
                        printf("Employee ID: %d\nName: %s\nSalary: %.2f\n", employee.emp_id, employee.name, employee.salary);
                        break;
                    }
                }

                fclose(file);
                break;

            case 3:
                // Update an employee
                file = fopen("employees.dat", "r+b");
                if (file == NULL) {
                    perror("File open error");
                    exit(1);
                }

                printf("Enter Employee ID to update: ");
                scanf("%d", &emp_id);

                while (fread(&employee, sizeof(struct Employee), 1, file)) {
                    if (employee.emp_id == emp_id) {
                        printf("Enter New Name: ");
                        scanf("%s", employee.name);
                        printf("Enter New Salary: ");
                        scanf("%f", &employee.salary);
                        fseek(file, -sizeof(struct Employee), SEEK_CUR);
                        fwrite(&employee, sizeof(struct Employee), 1, file);
                        break;
                    }
                }

                fclose(file);
                break;

            case 4:
                // Delete an employee
                file = fopen("employees.dat", "r+b");
                if (file == NULL) {
                    perror("File open error");
                    exit(1);
                }

                printf("Enter Employee ID to delete: ");
                scanf("%d", &emp_id);

                FILE* temp_file = fopen("temp.dat", "wb");

                while (fread(&employee, sizeof(struct Employee), 1, file)) {
                    if (employee.emp_id != emp_id) {
                        fwrite(&employee, sizeof(struct Employee), 1, temp_file);
                    }
                }

                fclose(file);
                fclose(temp_file);

                remove("employees.dat");
                rename("temp.dat", "employees.dat");
                break;

            case 5:
                // Exit the program
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
