#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 10

struct Vehicle {
    char number[20];
    char type[10];   // car, bike, cycle
    time_t entryTime;
};

struct Queue {
    struct Vehicle vehicles[MAX];
    int front;
    int rear;
};

void initQueue(struct Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isFull(struct Queue *q) {
    return q->rear == MAX - 1;
}

int isEmpty(struct Queue *q) {
    return q->front == -1 || q->front > q->rear;
}

// Validate vehicle type
int isValidType(char type[]) {
    return strcmp(type, "car") == 0 || strcmp(type, "bike") == 0 || strcmp(type, "cycle") == 0;
}

int getFeePerHour(char type[]) {
    if (strcmp(type, "car") == 0) return 40;
    else if (strcmp(type, "bike") == 0) return 20;
    else if (strcmp(type, "cycle") == 0) return 5;
    else return 0;
}

// Add vehicle to queue
void parkVehicle(struct Queue *q, char number[], char type[]) {
    if (!isValidType(type)) {
        printf("Invalid vehicle type! Only 'car', 'bike', or 'cycle' allowed.\n");
        return;
    }

    if (isFull(q)) {
        printf("Parking Lot is FULL!\n");
        return;
    }

    if (q->front == -1) q->front = 0;
    q->rear++;
    strcpy(q->vehicles[q->rear].number, number);
    strcpy(q->vehicles[q->rear].type, type);
    q->vehicles[q->rear].entryTime = time(NULL);

    printf("%s (%s) parked successfully at %s", number, type, ctime(&q->vehicles[q->rear].entryTime));
}

// Remove specific vehicle from queue
void removeVehicle(struct Queue *q, char number[], char type[]) {
    if (!isValidType(type)) {
        printf("Invalid vehicle type! Only 'car', 'bike', or 'cycle' allowed.\n");
        return;
    }

    if (isEmpty(q)) {
        printf("Parking Lot is EMPTY!\n");
        return;
    }

    int found = 0;
    for (int i = q->front; i <= q->rear; i++) {
        if (strcmp(q->vehicles[i].number, number) == 0 && strcmp(q->vehicles[i].type, type) == 0) {
            found = 1;
            time_t exitTime = time(NULL);
            double duration = difftime(exitTime, q->vehicles[i].entryTime) / 3600.0;
            if(duration < 1) duration = 1; // Minimum 1 hour
            int fee = (int)duration * getFeePerHour(type);

            printf("%s (%s) left at %s", number, type, ctime(&exitTime));
            printf("Parking Duration: %.2f hours\n", duration);
            printf("Parking Fee: ₹%d\n", fee);

            // Shift remaining vehicles
            for (int j = i; j < q->rear; j++) {
                q->vehicles[j] = q->vehicles[j + 1];
            }
            q->rear--;
            if (q->rear < q->front) q->front = -1; // Queue empty
            break;
        }
    }

    if (!found) printf("Vehicle %s (%s) not found in parking.\n", number, type);
}

// Display all vehicles in queue
void display(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Parking Lot is EMPTY!\n");
        return;
    }

    printf("Vehicles in Parking Lot:\n");
    for (int i = q->front; i <= q->rear; i++) {
        struct Vehicle v = q->vehicles[i];
        time_t now = time(NULL);
        double duration = difftime(now, v.entryTime) / 3600.0;
        if(duration < 1) duration = 1;
        int fee = (int)duration * getFeePerHour(v.type);

        printf("%s (%s) | Entry: %s | Duration: %.2f hours | Potential Fee: ₹%d\n",
               v.number, v.type, ctime(&v.entryTime), duration, fee);
    }
}

int main() {
    struct Queue q;
    initQueue(&q);
    int choice;
    char number[20], type[10];

    while (1) {
        printf("\n--- Parking Lot Menu ---\n");
        printf("1. Park Vehicle\n");
        printf("2. Remove Specific Vehicle & Show Fee\n");
        printf("3. Display Vehicles & Potential Fee\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter vehicle type (car/bike/cycle): ");
                scanf("%s", type);
                printf("Enter vehicle number: ");
                scanf("%s", number);
                parkVehicle(&q, number, type);
                break;
            case 2:
                printf("Enter vehicle type to remove: ");
                scanf("%s", type);
                printf("Enter vehicle number to remove: ");
                scanf("%s", number);
                removeVehicle(&q, number, type);
                break;
            case 3:
                display(&q);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
