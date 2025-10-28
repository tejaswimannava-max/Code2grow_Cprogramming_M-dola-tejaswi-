#include <stdio.h>

int main() {
    int age, health;
    char gender;
    float premium = 0.0;

    // Input Section
    printf("Enter age: ");
    scanf("%d", &age);
    printf("Enter gender (M/F): ");
    scanf(" %c", &gender);
    printf("Health condition (1-Healthy / 0-Unhealthy): ");
    scanf("%d", &health);

    printf("\nCustomer Details:\n");
    printf("Age: %d\n", age);
    printf("Gender: %c\n", gender);

    // Health condition output
    if (health == 1)
        printf("Health: Healthy\n");
    else
        printf("Health: Unhealthy\n");

    // Decision Section
    if (health == 0 && age > 60) {
        printf("Status: Not Eligible for Insurance\n");
    }
    else {
        if (age < 25) {
            if (health == 1)
                premium = 5000;
        }
        else if (age >= 25 && age <= 40) {
            if (health == 1)
                premium = 7000;
            else
                premium = 9500;
        }
        else if (age >= 41 && age <= 60) {
            if (health == 1)
                premium = 10000;
            else
                premium = 13000;
        }
        else if (age > 60) {
            if (health == 1)
                premium = 15000;
        }

        // Apply discount for female customers
        if (gender == 'F' || gender == 'f') {
            premium = premium - (premium * 0.10);
        }

        // Output final premium
        if (premium > 0)
            printf("Final Premium: ₹%.2f\n", premium);
        else
            printf("Status: Not Eligible for Insurance\n");
    }

    return 0;
}