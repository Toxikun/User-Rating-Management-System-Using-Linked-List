#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for linked list
typedef struct Node {
    int userID;
    int itemID;
    float rating;
    struct Node* next;
} Node;

// Head pointer for linked list
Node* head = NULL;

// Function to insert or update a rating
void insert(int userID, int itemID, float ratingValue) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->userID == userID && temp->itemID == itemID) {
            temp->rating = ratingValue;
            printf("Customer rating (%d, %d) is updated\n", userID, itemID);
            return;
        }
        temp = temp->next;
    }
    // If not found, create new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->userID = userID;
    newNode->itemID = itemID;
    newNode->rating = ratingValue;
    newNode->next = head;
    head = newNode;
    printf("Customer rating (%d, %d) is added successful\n", userID, itemID);
}

// Function to remove a rating
void removeRating(int userID, int itemID) {
    Node* temp = head;
    Node* prev = NULL;
    while (temp != NULL) {
        if (temp->userID == userID && temp->itemID == itemID) {
            if (prev == NULL) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Customer rating (%d, %d) is removed successful\n", userID, itemID);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Customer rating (%d, %d) does not exist\n", userID, itemID);
}

// Function to get a rating
void getRating(int userID, int itemID) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->userID == userID && temp->itemID == itemID) {
            printf("Customer rating (%d, %d) is: %.1f\n", userID, itemID, temp->rating);
            return;
        }
        temp = temp->next;
    }
    printf("Customer rating (%d, %d) is: 0.0\n", userID, itemID);
}

// Function to calculate average rating for an item
void average(int itemID) {
    Node* temp = head;
    float sum = 0.0;
    int count = 0;
    while (temp != NULL) {
        if (temp->itemID == itemID) {
            sum += temp->rating;
            count++;
        }
        temp = temp->next;
    }
    if (count == 0) {
        printf("Average rating (%d) is: 0.0\n", itemID);
    } else {
        printf("Average rating (%d) is: %.1f\n", itemID, sum / count);
    }
}

// Main function to handle input
int main() {
    char command[10];
    int userID, itemID;
    float ratingValue;
    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "INSERT") == 0) {
            scanf("%d %d %f", &userID, &itemID, &ratingValue);
            insert(userID, itemID, ratingValue);
        } else if (strcmp(command, "REMOVE") == 0) {
            scanf("%d %d", &userID, &itemID);
            removeRating(userID, itemID);
        } else if (strcmp(command, "RATING") == 0) {
            scanf("%d %d", &userID, &itemID);
            getRating(userID, itemID);
        } else if (strcmp(command, "AVERAGE") == 0) {
            scanf("%d", &itemID);
            average(itemID);
        }
    }
    return 0;
}
