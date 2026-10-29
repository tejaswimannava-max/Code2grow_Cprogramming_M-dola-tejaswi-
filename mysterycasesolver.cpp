
#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Global variable to store the player's score
double score = 0;

// Function to display the victory dance
void victoryDance() {
    cout << "\n*** VICTORY DANCE UNLOCKED! ***\n\n";
    cout << "  \\o/     YOU DID IT!\n";
    cout << "   |      AMAZING DETECTIVE!\n";
    cout << "  / \\     CASES SOLVED!\n";
    cout << "  \\o/     VICTORY!\n";
    cout << "\nCongratulations, Master Detective!\n";
}

// Function to get and validate the player's choice
int getChoice(string message, int min, int max) {
    int choice;

    while (true) {
        cout << message;

        if (cin >> choice && choice >= min && choice <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }

        cout << "Invalid input! Enter a number from "
             << min << " to " << max << ".\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Function to move to the next case
void continueGame() {
    string command;

    while (true) {
        cout << "\nType next to continue: ";
        cin >> command;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (command == "next" ||
            command == "NEXT" ||
            command == "Next") {
            return;
        }

        cout << "Please type next to continue.\n";
    }
}

// Function to display and play each mystery case
void playCase(
    string title,
    string story,
    string question,
    string options[],
    string hint,
    int answer,
    string explanation,
    int caseNumber
) {
    bool usedHint = false;

    cout << "\n====================================\n";
    cout << "CASE " << caseNumber << ": " << title << "\n";
    cout << "====================================\n";

    cout << story << "\n\n";
    cout << question << "\n";

    for (int i = 0; i < 3; i++) {
        cout << i + 1 << ". " << options[i] << "\n";
    }

    cout << "\nYou have two attempts.\n";
    cout << "Enter 0 if you need a hint.\n";

    for (int attempt = 1; attempt <= 2; attempt++) {
        int choice = getChoice(
            "\nEnter your answer (0 for hint): ", 0, 3
        );

        // Display a hint if the player enters 0
        if (choice == 0) {
            cout << "\nHINT: " << hint << "\n";
            usedHint = true;

            choice = getChoice(
                "Now enter your answer (1-3): ", 1, 3
            );
        }

        // Check whether the answer is correct
        if (choice == answer) {
            double points;

            cout << "\nCorrect! Great detective work!\n";

            if (attempt == 1) {
                points = usedHint ? 0.5 : 1.0;
            } else {
                points = usedHint ? 0.25 : 0.5;
            }

            score += points;

            cout << "Explanation: " << explanation << "\n";
            cout << "Points earned in this case: "
                 << points << "\n";

            return;
        }

        cout << "\nWrong answer! ";

        if (attempt == 1) {
            cout << "Try one more time.\n";
        } else {
            cout << "Both attempts used.\n";

            cout << "Correct answer: "
                 << options[answer - 1] << "\n";

            cout << "Explanation: "
                 << explanation << "\n";
        }
    }
}

int main() {
    // Welcome screen
    cout << "====================================\n";
    cout << "       MYSTERY CASE SOLVER\n";
    cout << "====================================\n";

    cout << "Welcome, Detective!\n";
    cout << "Solve five different mystery puzzles.\n";
    cout << "Earn points and unlock the victory dance!\n";

    // Game instructions
    cout << "\n========== GAME INSTRUCTIONS ==========\n";
    cout << "1. There are 5 mystery cases to solve.\n";
    cout << "2. Each case has 3 answer options.\n";
    cout << "3. Enter 1, 2, or 3 to select your answer.\n";
    cout << "4. Enter 0 if you want to see a hint.\n";
    cout << "5. You have 2 attempts for each case.\n";
    cout << "6. Correct answers earn points.\n";
    cout << "7. Using a hint reduces the points earned.\n";
    cout << "8. Type 'next' to move to the next case.\n";
    cout << "9. Your final score is out of 5.\n";
    cout << "10. Score 4 or more to unlock the victory dance!\n";
    cout << "=======================================\n";

    // Wait for the player to press Enter
    cout << "\nAre you ready, Detective? Press Enter to start...";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    cout << "\nLet's begin the investigation!\n";

    // Answer options for the five cases
    string options1[] = {"Rahul", "Priya", "Arjun"};
    string options2[] = {"Rahul", "Priya", "Arjun"};
    string options3[] = {"Sita", "Dev", "Maya"};
    string options4[] = {"24", "40", "42"};
    string options5[] = {"Key A", "Key B", "Key C"};

    // CASE 1: The Missing Phone
    playCase(
        "THE MISSING PHONE",

        "A phone disappeared from the classroom. "
        "Exactly one of these three statements is true.\n"
        "Rahul: Priya took the phone.\n"
        "Priya: Arjun took the phone.\n"
        "Arjun: Priya is lying.",

        "Who took the phone?",

        options1,

        "Check which suspect makes exactly one statement true.",

        1,

        "If Rahul took it, Rahul's statement is false, "
        "Priya's statement is false, and Arjun's statement "
        "is true. Therefore, exactly one statement is true.",

        1
    );

    continueGame();

    // CASE 2: The Muddy Footprints
    playCase(
        "THE MUDDY FOOTPRINTS",

        "A classroom window was broken after rain. "
        "Three students were nearby.\n"
        "Rahul has muddy shoes, and the matching footprints "
        "lead from the broken window to his desk.\n"
        "Priya's shoes are clean. Arjun's shoes have a "
        "different pattern.",

        "Who is the strongest suspect based on the evidence?",

        options2,

        "Look for the shoes matching the footprints.",

        1,

        "Rahul's muddy shoes match the footprints leading "
        "from the broken window. This makes him the strongest "
        "suspect based on the available evidence.",

        2
    );

    continueGame();

    // CASE 3: The Missing Exam Paper
    playCase(
        "THE MISSING EXAM PAPER",

        "The exam paper disappeared between 9:05 AM "
        "and 9:15 AM.\n"
        "Sita entered the room at 9:00 AM and left at 9:04 AM.\n"
        "Dev entered at 9:10 AM and stayed until 9:30 AM.\n"
        "Maya entered at 9:20 AM.",

        "Who was in the room when the paper disappeared?",

        options3,

        "Compare each person's time in the room with "
        "the 9:05 to 9:15 AM time window.",

        2,

        "Dev was in the room from 9:10 AM onward, "
        "so he was present during the time the paper disappeared. "
        "This identifies who was present, not necessarily who "
        "took the paper.",

        3
    );

    continueGame();

    // CASE 4: The Secret Code
    playCase(
        "THE SECRET CODE",

        "A detective finds a number sequence in a notebook:\n"
        "2, 6, 12, 20, 30, ?",

        "Which number should replace the question mark?",

        options4,

        "The differences are 4, 6, 8, and 10. "
        "What comes after adding 10?",

        3,

        "The differences increase by 2 each time. "
        "The next difference is 12, so 30 + 12 = 42.",

        4
    );

    continueGame();

    // CASE 5: The Locked Archive
    playCase(
        "THE LOCKED ARCHIVE",

        "Three keys might open a locked archive.\n"
        "A note says Key A does not open it.\n"
        "Another note says Key C does not open it.\n"
        "Exactly one key opens the archive.",

        "Which key opens the archive?",

        options5,

        "Eliminate the two keys that the notes rule out.",

        2,

        "Key A and Key C are ruled out. Therefore, "
        "Key B is the only remaining possible key.",

        5
    );

    // Display the final score and rank
    cout << "\n\n====================================\n";
    cout << "          GAME COMPLETED!\n";
    cout << "====================================\n";

    cout << "Your score: " << score << " / 5\n";

    if (score >= 4) {
        cout << "Rank: MASTER DETECTIVE!\n";
        victoryDance();
    } else if (score >= 3) {
        cout << "Rank: SKILLED DETECTIVE!\n";
    } else if (score >= 2) {
        cout << "Rank: JUNIOR DETECTIVE!\n";
    } else {
        cout << "Rank: DETECTIVE IN TRAINING!\n";
    }

    cout << "\nThanks for playing Mystery Case Solver!\n";
    cout << "====================================\n";

    return 0;
}