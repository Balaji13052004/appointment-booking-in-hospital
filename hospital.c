#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_APPOINTMENTS 100

// Structure to store appointment details
typedef struct {
    char patientName[50];
    char doctorName[50];
    char date[15];
    char time[10];
} Appointment;

Appointment appointments[MAX_APPOINTMENTS];
int appointmentCount = 0;

// Function prototypes
void bookAppointment();
void viewAppointments();
void cancelAppointment();
int isValidDate(const char *date);
int isValidTime(const char *time);

int main() {
    int choice;

    while (1) {
        printf("\n--- Hospital Appointment Booking System ---\n");
        printf("1. Book Appointment\n");
        printf("2. View Appointments\n");
        printf("3. Cancel Appointment\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear the buffer

        switch (choice) {
            case 1:
                bookAppointment();
                break;
            case 2:
                viewAppointments();
                break;
            case 3:
                cancelAppointment();
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

// Function to book an appointment
void bookAppointment() {
    if (appointmentCount >= MAX_APPOINTMENTS) {
        printf("Maximum appointment limit reached!\n");
        return;
    }

    Appointment newAppointment;

    printf("Enter patient name: ");
    fgets(newAppointment.patientName, sizeof(newAppointment.patientName), stdin);
    newAppointment.patientName[strcspn(newAppointment.patientName, "\n")] = '\0'; // Remove newline

    if (strlen(newAppointment.patientName) == 0) {
        printf("Patient name cannot be empty.\n");
        return;
    }

    printf("Enter doctor name: ");
    fgets(newAppointment.doctorName, sizeof(newAppointment.doctorName), stdin);
    newAppointment.doctorName[strcspn(newAppointment.doctorName, "\n")] = '\0'; // Remove newline

    if (strlen(newAppointment.doctorName) == 0) {
        printf("Doctor name cannot be empty.\n");
        return;
    }

    printf("Enter appointment date (DD/MM/YYYY): ");
    fgets(newAppointment.date, sizeof(newAppointment.date), stdin);
    newAppointment.date[strcspn(newAppointment.date, "\n")] = '\0'; // Remove newline

    if (!isValidDate(newAppointment.date)) {
        printf("Invalid date format! Please use DD/MM/YYYY.\n");
        return;
    }

    printf("Enter appointment time (HH:MM): ");
    fgets(newAppointment.time, sizeof(newAppointment.time), stdin);
    newAppointment.time[strcspn(newAppointment.time, "\n")] = '\0'; // Remove newline

    if (!isValidTime(newAppointment.time)) {
        printf("Invalid time format! Please use HH:MM.\n");
        return;
    }

    // Check for duplicate appointment
    for (int i = 0; i < appointmentCount; i++) {
        if (strcmp(appointments[i].patientName, newAppointment.patientName) == 0 &&
            strcmp(appointments[i].doctorName, newAppointment.doctorName) == 0 &&
            strcmp(appointments[i].date, newAppointment.date) == 0 &&
            strcmp(appointments[i].time, newAppointment.time) == 0) {
            printf("Duplicate appointment found! Booking not allowed.\n");
            return;
        }
    }

    appointments[appointmentCount++] = newAppointment;
    printf("Appointment booked successfully!\n");
}

// Function to view all appointments
void viewAppointments() {
    if (appointmentCount == 0) {
        printf("No appointments found.\n");
        return;
    }

    printf("\n--- List of Appointments ---\n");
    for (int i = 0; i < appointmentCount; i++) {
        printf("Appointment %d:\n", i + 1);
        printf("  Patient Name: %s\n", appointments[i].patientName);
        printf("  Doctor Name: %s\n", appointments[i].doctorName);
        printf("  Date: %s\n", appointments[i].date);
        printf("  Time: %s\n", appointments[i].time);
    }
}

// Function to cancel an appointment
void cancelAppointment() {
    if (appointmentCount == 0) {
        printf("No appointments to cancel.\n");
        return;
    }

    int cancelIndex;
    printf("Enter the appointment number to cancel (1 to %d): ", appointmentCount);
    scanf("%d", &cancelIndex);
    getchar(); // Clear the buffer

    if (cancelIndex < 1 || cancelIndex > appointmentCount) {
        printf("Invalid appointment number!\n");
        return;
    }

    // Shift appointments to remove the selected one
    for (int i = cancelIndex - 1; i < appointmentCount - 1; i++) {
        appointments[i] = appointments[i + 1];
    }

    appointmentCount--;
    printf("Appointment canceled successfully!\n");
}

// Function to validate date format
int isValidDate(const char *date) {
    if (strlen(date) != 10 || date[2] != '/' || date[5] != '/')
        return 0;

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5)
            continue;
        if (!isdigit(date[i]))
            return 0;
    }

    return 1;
}

// Function to validate time format
int isValidTime(const char *time) {
    if (strlen(time) != 5 || time[2] != ':')
        return 0;

    for (int i = 0; i < 5; i++) {
        if (i == 2)
            continue;
        if (!isdigit(time[i]))
            return 0;
    }

    return 1;
}