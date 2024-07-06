
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PASSENGERS 50
#define MAX_BUSES 10

//structure of passenger//

struct Passenger {
    int p_no;
    char p_name[20];
    char p_mobile_no[15];
    char p_address[100];
    char p_gender[2];
    int p_age;
    int booked_tickets[MAX_BUSES];
};

//structure of Bus

struct Bus {
    int bus_no;
    char driver_name[20];
    char mobile_no[15];
    char time_start[20], time_stop[20];
    char des_start[20], des_stop[20];
    int fare, no_of_seat;
};


char users[2][15] = {"xyz", "1234"}; // Sample user credentials


//FUNCTIONS PROTOTYPE

//BUS FUNCTIONS

int authenticateUser();

int addBus(struct Bus buses[], int *buscount);
int busRemove(struct Bus buses[], int *buscount);
void displayBuses(struct Bus buses[], int buscount);

//PASSENGER FUNCTION

int addPassenger(struct Passenger passengers[], int *passcount);
int removePassenger(struct Passenger passengers[], int *passcount);
void displayPassengers(struct Passenger passengers[], int passcount);
void displayPassengers(struct Passenger passengers[], int passcount);

//TICKETS FUNCTION

void bookTickets(struct Passenger passengers[], int passcount, struct Bus buses[], int buscount);
int cancelTickets(struct Passenger passengers[], int *passcount, struct Bus buses[], int buscount);
int payment();

//MISCELLANEOUS FUNCTION

int feedbackForm(struct Passenger passengers[], int passcount, struct Bus buses[], int buscount);
int emergency(struct Passenger passengers[], int passcount);
void foodservices();
void complaint();

//MAIN MENU TYPE

int main() {
    int choice;

    struct Passenger passengers[MAX_PASSENGERS];
    int passcount = 0;

    struct Bus buses[MAX_BUSES];
    int buscount = 0;

    printf("****************************\n");
    printf("*  Bus Reservation System  *\n");
    printf("****************************\n\n");

    do {
        printf("***************\n");
        printf("*  Main Menu  *\n");
        printf("***************\n");

        printf("\n\n1. Add Bus\n");
        printf("2. Remove Bus\n");
        printf("3. Display Bus\n");
        printf("4. Add Passenger\n");
        printf("5. Remove Passenger\n");
        printf("6. Display Passengers\n");
        printf("7. Book Tickets\n");
        printf("8. Cancel Tickets\n");
        printf("9. Emergency\n");
        printf("10. Feedback Form\n");
        printf("11. Order Food\n");
        printf("12. File a Complaint\n");
        printf("13. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        // Initialize main function
        switch (choice) {
            case 1:
                addBus(buses, &buscount);
                break;

            case 2:
                busRemove(buses, &buscount);
                break;

            case 3:
                displayBuses(buses, buscount);
                break;

            case 4:
                addPassenger(passengers, &passcount);
                break;

            case 5:
                removePassenger(passengers, &passcount);
                break;

            case 6:
                displayPassengers(passengers, passcount);
                break;

            case 7:
                bookTickets(passengers, passcount, buses, buscount);
                break;

            case 8:
                cancelTickets(passengers, &passcount, buses, buscount);
                break;

            case 9:
                emergency(passengers, passcount);
                break;

            case 10:
                feedbackForm(passengers, passcount, buses, buscount);
                break;

            case 11:
                foodservices();
                break;

            case 12:
                complaint();
                break;

            case 13:
                printf("Exiting the program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 13);

    return 0;
}

//BUS REMOVING FUNCTION

int busRemove(struct Bus buses[], int *buscount) {

    int busNoToRemove;
    char driverNameToRemove[20];

    printf("Enter Bus Number to Remove: ");
    scanf("%d", &busNoToRemove);

    printf("Enter Driver Name to Remove: ");
    scanf("%19s", driverNameToRemove);

    int foundIndex = -1;
    for (int i = 0; i < *buscount; ++i) {
        if (buses[i].bus_no == busNoToRemove && strcmp(buses[i].driver_name, driverNameToRemove) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        // Confirmation
        printf("Do you want to remove Bus %d with Driver %s? (y/n): ", busNoToRemove, driverNameToRemove);
        char confirmation;
        scanf(" %c", &confirmation);

        if (confirmation == 'y' || confirmation == 'Y') {
            // Shift the elements to remove the bus
            for (int i = foundIndex; i < *buscount - 1; ++i) {
                buses[i] = buses[i + 1];
            }

            (*buscount)--;
            printf("Bus %d with Driver %s has been removed. Total buses: %d\n", busNoToRemove, driverNameToRemove, *buscount);
        } else {
            printf("Removal canceled.\n");
        }
    } else {
        printf("Bus %d with Driver %s not found. Removal failed.", busNoToRemove, driverNameToRemove);
    }
    printf("\n\n");

    return 0;
}

//REMOVE PASSENGER FUNCTION

int removePassenger(struct Passenger passengers[], int *passcount) {

    char passengerMobileToRemove[15];
    char passengerNameToRemove[20];

    printf("Enter Passenger Mobile Number to Remove: ");
    scanf("%s", passengerMobileToRemove);

    printf("Enter Passenger Name to Remove: ");
    scanf("%19s", passengerNameToRemove);

//CHECKING THAT IT EXIST OR NOT

    int foundIndex = -1;
    for (int i = 0; i < *passcount; ++i) {
        if (strcmp(passengers[i].p_mobile_no, passengerMobileToRemove) == 0 && strcmp(passengers[i].p_name, passengerNameToRemove) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        // Confirmation
        printf("Do you want to remove Passenger %s with Mobile Number %s? (y/n): ", passengerNameToRemove, passengerMobileToRemove);
        char confirmation;
        scanf(" %c", &confirmation);

        if (confirmation == 'y' || confirmation == 'Y') {
            // Shift the elements to remove the passenger
            for (int i = foundIndex; i < *passcount - 1; ++i) {
                passengers[i] = passengers[i + 1];
            }

            (*passcount)--;
            printf("Passenger %s with Mobile Number %s has been removed. Total passengers: %d\n", passengerNameToRemove, passengerMobileToRemove, *passcount);
            printf("Passenger %s with Mobile Number %s has been removed. Total passengers: %d\n", passengerNameToRemove, passengerMobileToRemove, *passcount);
        } else {
            printf("Removal canceled.\n");
        }
    } else {
        printf("Passenger %s with Mobile Number %s not found. Removal failed.\n", passengerNameToRemove, passengerMobileToRemove);
    }
    printf("\n\n");

    return 0;
}


//AUTHENTICATION USER FUNCTION

int authenticateUser() {
    char username[15];
    char password[15];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    return (strcmp(username, users[0]) == 0 && strcmp(password, users[1]) == 0);
}

// ADD PASSENGER FUNCTION

int addPassenger(struct Passenger passengers[], int *passcount) {
    //STRUCTURE FOR PASSENGER

    struct Passenger newPassenger;

    printf("\nEnter your name: ");
    scanf(" %[^\n]s", newPassenger.p_name);

    printf("Enter your Mobile Number: ");
    scanf("%11s", newPassenger.p_mobile_no);

    printf("Enter your address: ");
    scanf(" %[^\n]s",newPassenger.p_address);

    printf("Enter your age: ");
    scanf("%d",&newPassenger.p_age);

    printf("Enter your Gender(M/F/O): ");
    scanf(" %1s", newPassenger.p_gender);

    if (*passcount < MAX_PASSENGERS) {
        newPassenger.p_no = *passcount + 1;
        passengers[(*passcount)++] = newPassenger;
        printf("Passenger %s has been added. Total passengers: %d\n", newPassenger.p_name, *passcount);
    } else {
        printf("Maximum passenger capacity reached. Cannot add more passengers.\n");
    }
        printf("\nPassenger %s has been added.\n\n", newPassenger.p_name);
        printf("Details:\n\n");
        printf("**PLEASE REMEMBER PASSENGER NUMBER, NAME AND MOBILE NUMBER FOR FUTURE REFRENCES**");
        printf("\nYOUR DETAILS HAS BEEN SENT TO YOUR MOBILE NUMBER\n");
        printf("Passenger Number: %d\n", newPassenger.p_no);
        printf("Name: %s\n", newPassenger.p_name);
        printf("Mobile Number: %s\n", newPassenger.p_mobile_no);
        printf("Age: %d\n", newPassenger.p_age);
        printf("Address: %s\n", newPassenger.p_address);
        printf("Gender: %s\n", newPassenger.p_gender);
        sleep(3);
        printf("\n\n");

    return 0;
}

//STRUCTURE FOR NEW BUS

int addBus(struct Bus buses[], int *buscount) {
    if (authenticateUser()) {

        struct Bus newBus;

        printf("\nEnter Bus Number: ");
        scanf("%d", &newBus.bus_no);

        printf("Enter Driver Name: ");
        scanf(" %[^\n]s", newBus.driver_name);

        printf("Enter Driver Mobile Number: ");
        scanf("%14s", newBus.mobile_no);

        printf("Enter Departure Time: ");
        scanf(" %19s", newBus.time_start);

        printf("Enter Arrival Time: ");
        scanf(" %19s", newBus.time_stop);

        printf("Enter Departure Destination: ");
        scanf(" %[^\n]s", newBus.des_start);

        printf("Enter Arrival Destination: ");
        scanf(" %[^\n]s", newBus.des_stop);

        printf("Enter Fare: ");
        scanf("%d", &newBus.fare);

        printf("Enter Number of Seats: ");
        scanf("%d", &newBus.no_of_seat);

        if (*buscount < MAX_BUSES) {
            buses[(*buscount)++] = newBus;
            printf("Bus %d has been added. Total buses: %d\n", newBus.bus_no, *buscount);
        } else {
            printf("Maximum bus capacity reached. Cannot add more buses.\n");
        }
    } else {
        printf("User authentication failed. Cannot add bus.\n");
    }
    printf("\n\n");

    return 0;
}

//FUNCTIONS FOR  DISPLAYING PASSENGERS

void displayPassengers(struct Passenger passengers[], int passcount) {
 if (authenticateUser()){
    if (passcount == 0) {
        printf("No passengers to display.\n");
        return;
    }


    printf("\nPassenger List:\n");
    for (int i = 0; i < passcount; ++i) {
        printf("Passenger %d\n", i + 1);
        printf("Name: %s\n", passengers[i].p_name);
        printf("Mobile Number: %s\n", passengers[i].p_mobile_no);
        printf("Age: %d\n", passengers[i].p_age);
        printf("Address: %s\n", passengers[i].p_address);
        printf("Gender: %s\n", passengers[i].p_gender);
        sleep(2);
        printf("\n\n");

    }
}
else {
        printf("User authentication failed.\n\n\n");
    }
    sleep(2);
    }

//FUNCTIONS FOR DISPLAY BUSES

void displayBuses(struct Bus buses[], int buscount) {
    if (buscount == 0) {
        printf("No buses to display.\n");
        return;
    }

    printf("\nBus List:\n");
    for (int i = 0; i < buscount; ++i) {
        printf("Bus %d\n", buses[i].bus_no);
        printf("Departure Time: %s\n", buses[i].time_start);
        printf("Arrival Time: %s\n", buses[i].time_stop);
        printf("Departure Destination: %s\n", buses[i].des_start);
        printf("Arrival Destination: %s\n", buses[i].des_stop);
        printf("Fare: %d\n", buses[i].fare);
        printf("Number of Seats: %d\n", buses[i].no_of_seat);
        sleep(2);
        printf("\n\n");

    }
}

//FUNCTIONS FOR BOOK TICKETS

void bookTickets(struct Passenger passengers[], int passcount, struct Bus buses[], int buscount) {
    printf("\n\n");
    if (passcount == 0) {
        printf("No passengers available. Please add passengers first.\n");
        return;
    }

    if (buscount == 0) {
        printf("No buses available. Please add buses first.\n");
        return;
    }

    // Get passenger details

    int passengerIndex;
    printf("PLEASE ENTER YOUR PASSENGER NUMBER CAREFULLY");
    printf("\nEnter your Passenger Number: ");
    scanf("%d", &passengerIndex);

    if (passengerIndex < 1 || passengerIndex > passcount) {
        printf("Invalid Passenger Number.\n");
        return;
    }

    // Display list of buses

    printf("\nAvailable Buses:\n");
    displayBuses(buses, buscount);

    // Get bus selection

    int busIndex;
    printf("\nEnter the Bus Number you want to book tickets for: ");
    scanf("%d", &busIndex);

    if (busIndex < 1 || busIndex > buscount) {
        printf("Invalid Bus Number.\n");
        return;
    }

    // Get number of tickets to book

    int numTickets;
    printf("Enter the number of tickets you want to book: ");
    scanf("%d", &numTickets);


    if (numTickets <= 0 || numTickets > buses[busIndex - 1].no_of_seat) {
        printf("Invalid number of tickets. Please choose a valid number.\n");
        return;
    }

    // Update booked seats and passenger details

    buses[busIndex - 1].no_of_seat -= numTickets;
    printf("Total Fare: %d\n", numTickets * buses[busIndex - 1].fare);
    payment();
    printf("Booking successful!\n");
    passengers[passengerIndex - 1].booked_tickets[passengerIndex-1]=numTickets;

    // Display booking details

    printf("Passenger: %s\n", passengers[passengerIndex - 1].p_name);
    printf("Bus Number: %d\n", buses[busIndex - 1].bus_no);
    printf("Number of Tickets Booked: %d\n", numTickets);
    printf("Total Fare: %d\n", numTickets * buses[busIndex - 1].fare);
    printf("\n\n");

    }

//FUNCTIONS FOR PAYMENTS

int payment() {

    int a;
    char upi_id[11], account_no[20], password[20];


    printf("Which payment option do you want to opt\n");
    printf("1. UPI\n");
    printf("2. CASH\n");
    printf("3. NET BANKING\n");
    scanf("%d", &a);

    if (a == 1) {
        printf("Enter UPI ID\n");
        scanf("%s", upi_id);
        sleep(1);
        printf("Your UPI ID has been verified\n");
        printf("GO TO YOUR UPI PAYMENT APPLICATION AND COMPLETE THE TRANSACTION\n\n");
        sleep(5);
        printf("YOUR TRANSACTION HAS BEEN COMPLETED\n\n");
        printf("YOUR TICKET IS BOOKED\n\n");
    }
    else if (a == 2) {
        printf("PLEASE! PAY the required amount to book the tickets\n\n");
        printf("PAYMENT RECEIVED\n\n");
        printf("PROCESSING ----\n\n");
        sleep(10);
        printf("YOUR TRANSACTION HAS BEEN COMPLETED\n\n");
        printf("YOUR TICKET IS BOOKED\n\n");
    }
    else if (a == 3) {
        printf("ENTER YOUR ACCOUNT NUMBER\n\n");
        scanf("%s", account_no);
        printf("Enter your password\n\n");
        scanf("%s", password);
        printf("PROCESSING ----\n\n");
        sleep(5);
        printf("YOU ARE GOING TO BE DIRECTED TO YOUR SPECIFIC BANKS NET BANKING PORTAL\n");
        sleep(5);
        printf("YOUR TRANSACTION HAS BEEN COMPLETED\n\n");
        printf("YOUR TICKET IS BOOKED\n");
    }
    else {
        printf("YOU HAVE CHOSEN THE WRONG NUMBER\n\n");
    }
    printf("\n\n");

    return 0;
}

//FUNCTIONS FOR EMERGENCY

int emergency(struct Passenger passengers[], int passcount) {

    char a;
    char name[20];
    char location[20];

    printf("YOU HAVE ENTERED THE EMERGENCY PORTAL\n");
    printf("DO YOU WANT TO CONTINUE Y/N: ");
    scanf(" %c", &a);

    if (a == 'Y' || a == 'y') {
        printf("Enter your name: ");
        scanf(" %[^\n]s", name);

        int foundIndex = -1;
        for (int i = 0; i < passcount; ++i) {
            if (strcmp(passengers[i].p_name, name) == 0) {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex != -1) {
            printf("Enter your current location: ");
            scanf(" %[^\n]s", location);

            printf("Our Agent Will Be Coming There Soon. Sorry For Inconvenience.\n");
            printf("FOR INSTANT ASSISTANCE CALL AT 7868789798\n");
        }
        else {
            printf("Passenger with name %s not found.\n", name);
        }
    }
    else {
        printf("WE ARE TAKING YOU BACK TO THE MAIN MENU\n");
        sleep(1);
    }
    printf("\n\n");

    return 0;
}

//FUNCTIONS FOR FEEDBACK FORM

int feedbackForm(struct Passenger passengers[], int passcount, struct Bus buses[], int buscount) {

    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;

    char exp[100];
    char passengerName[20];
    int busNumber;

    printf("\n");
    printf("******************\n");
    printf("* Feedback Form  *\n");
    printf("******************\n");

    // Get passenger name

    printf("\nEnter your name: ");
    scanf(" %[^\n]s", passengerName);

    // Get bus number

    printf("Enter the Bus Number you traveled on: ");
    scanf("%d", &busNumber);

    // Check if the passenger and bus exist

    int passengerIndex = -1;
    for (int i = 0; i < passcount; ++i) {
        if (strcmp(passengers[i].p_name, passengerName) == 0) {
            passengerIndex = i;
            break;
        }
    }

    int busIndex = -1;
    for (int i = 0; i < buscount; ++i) {
        if (buses[i].bus_no == busNumber) {
            busIndex = i;
            break;
        }
    }

    if (passengerIndex == -1 || busIndex == -1) {
        printf("Passenger or Bus not found. Exiting feedback form.\n");
        return 0;
    }

    printf("HOW WAS THE EXPERIENCE:\n");
    getchar();  // Consume the newline character left in the input buffer
    scanf(" %[^\n]s",&exp);

    printf("\n(I)HOW WAS STAFF MEMBERS BEHAVIOR TOWARDS PASSENGERS:\n");
    printf("1.EXCELLENT\n");
    printf("2.OUTSTANDING\n");
    printf("3.VERY GOOD\n");
    printf("4.GOOD\n");
    printf("5.NOT GOOD\n");
    printf("6.VERY BAD EXPERIENCE\n");
    scanf("%d", &a);

    printf("\n(II)HOW WAS THE COVID 19 PROTOCOLS FOLLOWED:\n");
    printf("1.EXCELLENT\n");
    printf("2.OUTSTANDING\n");
    printf("3.VERY GOOD\n");
    printf("4.GOOD\n");
    printf("5.NOT GOOD\n");
    printf("6.VERY BAD EXPERIENCE\n");
    scanf("%d", &b);

    printf("\n(III)HOW WAS THE CLEANLINESS IN BUS:\n");
    printf("1.EXCELLENT\n");
    printf("2.OUTSTANDING\n");
    printf("3.VERY GOOD\n");
    printf("4.GOOD\n");
    printf("5.NOT GOOD\n");
    printf("6.VERY BAD EXPERIENCE\n");
    scanf("%d", &c);

    printf("\n(IV)HOW WAS THE WI-FI CONNECTION:\n");
    printf("1.EXCELLENT\n");
    printf("2.OUTSTANDING\n");
    printf("3.VERY GOOD\n");
    printf("4.GOOD\n");
    printf("5.NOT GOOD\n");
    printf("6.VERY BAD EXPERIENCE\n");
    scanf("%d", &d);

    printf("\n(V)HOW WAS THE FOOD SERVICES AND QUALITY:\n");
    printf("1.EXCELLENT\n");
    printf("2.OUTSTANDING\n");
    printf("3.VERY GOOD\n");
    printf("4.GOOD\n");
    printf("5.NOT GOOD\n");
    printf("6.VERY BAD EXPERIENCE\n");
    scanf("%d", &e);

    printf("\n(VI)HOW WAS THE FIRST AID FACILITY:\n");
    printf("1.EXCELLENT\n");
    printf("2.OUTSTANDING\n");
    printf("3.VERY GOOD\n");
    printf("4.GOOD\n");
    printf("5.NOT GOOD\n");
    printf("6.VERY BAD EXPERIENCE\n");
    scanf("%d", &f);

    printf("\n(VII)HOW WAS THE EMERGENCY RESPONSE ( IF NEEDED):\n");
    printf("1.EXCELLENT\n");
    printf("2.OUTSTANDING\n");
    printf("3.VERY GOOD\n");
    printf("4.GOOD\n");
    printf("5.NOT GOOD\n");
    printf("6.VERY BAD EXPERIENCE\n");
    scanf("%d", &g);

    printf("\n(VIII)HOW WAS YOUR OVERALL EXPERIENCE:\n");
    printf("1.EXCELLENT\n");
    printf("2.OUTSTANDING\n");
    printf("3.VERY GOOD\n");
    printf("4.GOOD\n");
    printf("5.NOT GOOD\n");
    printf("6.VERY BAD EXPERIENCE\n");
    scanf("%d", &h);
    printf("\n");

    sleep(2);

    printf("THANK YOU FOR YOUR FEEDBACK.\n");
    printf("WE HOPE TO SERVE YOU BETTER NEXT TIME.\n");
    printf("\n\n");

    return 0;
}

//CANCEL TICKETS

int cancelTickets(struct Passenger passengers[], int *passcount, struct Bus buses[], int buscount) {

    if (*passcount == 0) {
        printf("No passengers available. Please add passengers first.\n");
        return 0;
    }

    // Get passenger details

    int passengerIndex;
    printf("Enter your Passenger Number: ");
    scanf("%d", &passengerIndex);

    if (passengerIndex < 1 || passengerIndex > *passcount) {
        printf("Invalid Passenger Number.\n");
        return 0;
    }

    // Display passenger's booked tickets

    printf("\nTicket Details:\n");
    printf("Passenger: %s\n", passengers[passengerIndex - 1].p_name);

    // Display the details of booked tickets

    // (Assuming that each passenger can book tickets for multiple buses)
    for (int i = 0; i < buscount; ++i) {
        printf("Bus Number: %d\n", buses[i].bus_no);
        printf("Number of Tickets Booked: %d\n", passengers[passengerIndex - 1].booked_tickets[i]);
        printf("Fare per Ticket: %d\n", buses[i].fare);
        printf("Total Fare: %d\n", passengers[passengerIndex - 1].booked_tickets[i] * buses[i].fare);
        printf("\n");
    }

    // Get the number of tickets to cancel

    int numTicketsToCancel;
    printf("Enter the number of tickets you want to cancel: ");
    scanf("%d", &numTicketsToCancel);

    // Validate the number of tickets to cancel
    if (numTicketsToCancel <=0 || numTicketsToCancel > passengers[passengerIndex - 1].booked_tickets[passengerIndex-1]) {
        printf("Invalid number of tickets. Please enter a non-negative number and not more than the booked tickets.\n");
        return 0;
    }

    // Confirm cancellation
    char confirmation;
    printf("Do you want to cancel %d tickets? (y/n): ", numTicketsToCancel);
    scanf(" %c", &confirmation);

    if (confirmation == 'y' || confirmation == 'Y') {
        // Update the number of seats and passenger details
        for (int i = 0; i < buscount; ++i) {
            buses[i].no_of_seat += numTicketsToCancel;
            passengers[passengerIndex - 1].booked_tickets[i] -= numTicketsToCancel;
        }

        printf("Tickets canceled successfully!\n");
        printf("New Ticket Details:\n");
        // Display the updated ticket details
        for (int i = 0; i < buscount; ++i) {
            printf("Bus Number: %d\n", buses[i].bus_no);
            printf("Number of Tickets left booked: %d\n", passengers[passengerIndex - 1].booked_tickets[i]);
            printf("Fare per Ticket: %d\n", buses[i].fare);

            printf("\n");

            printf("YOUR REFUND REQUEST HAS BEEN PLACED\n");
            printf("THE AMOUNT WILL BE REFUNDED INTO YOUR BANK ACCOUNT ,UPI ID OR IN CASH AS YOU HAVE PAID RESPECTIVELY ");
        }
    } else {
        printf("Cancellation canceled.\n");
    }
    printf("\n\n");

    return 0;
}

void foodservices() {

    char a;
    char b;
    char c;
    char d;
    char name[20];
    char no[13];

    printf("DO YOU WANT TO ENJOY OUR FOOD SERVICES (Y/N):\n");
    scanf(" %c", &a);

    if (a == 'y' || a == 'Y') {

        printf("ENTER PASSENGER NAME:\n");
        scanf("%s",&name);
        printf("ENTER YOUR PHONE NUMBER:\n");
        scanf("%d",&no);

        printf("DO YOU WANT TO ENJOY VEG or NON-VEG (V/N):\n");
        scanf(" %c", &b);

        if (b == 'v' || b == 'V') {

            // DESIGN
            printf("*******************\n");
            printf("*****VEG MENU******\n");
            printf("*******************\n");

            printf("1. PANEER MASALA \t 300\n");
            printf("2. SHAHI PANEER \t 100\n");
            printf("3. DAL MAKHANI \t\t 200\n");
            printf("4. RAJMA RICE \t\t 70\n");
            printf("5. CHOLE BHATURE \t 150\n");
            printf("6. VEG BIRYANI \t\t 100\n");
            printf("7. PLAIN DOSA \t\t 70\n");
            printf("8. MASALA DOSA \t\t 80\n");
            printf("9. PANEER TIKKA \t 50\n");
            printf("10. PANEER ROLL \t 60\n");
            printf("11. NAAN \t\t 10\n");
            printf("12. PLAIN ROTI \t\t 15\n");
            printf("13. PLAIN RICE \t\t 80\n");
            printf("14. LEMON RICE \t\t 80\n");
            printf("15. VEG FRIED RICE \t 100\n\n");

            printf("ARE YOU READY TO PLACE YOUR ORDER (Y/N): ");
            scanf(" %c", &c);

            if (c == 'y' || c == 'Y') {

                printf("WE HAVE INFORMED OUR HELPER\n");
                printf("OUR HELPER WILL COME TO YOUR SEAT AND TAKE YOUR ORDER\n");
                printf("THE BUS WILL STOP AT THE NEXT SERVICE STATION TO FETCH YOUR ORDERS AND THEN YOU CAN PAY\n");
            }
            else if (c == 'n' || c == 'N') {

                sleep(10); // Wait for 10 seconds
                printf("ARE YOU READY TO PLACE YOUR ORDER (Y/N): ");
                scanf(" %c", &d);
                if (d == 'y' || d == 'Y') {

                    printf("WE HAVE INFORMED OUR HELPER\n");
                    printf("OUR HELPER WILL COME TO YOUR SEAT AND TAKE YOUR ORDER\n");
                    printf("THE BUS WILL STOP AT THE NEXT SERVICE STATION TO FETCH YOUR ORDERS AND THEN YOU CAN PAY\n");
                }
            else {
                    printf("Invalid choice. Taking you back to the main menu\n");
                }
            }
            else {
                printf("Invalid choice. Taking you back to the main menu\n");
            }
        }
        else if (b == 'n' || b == 'N') {

            // DESIGN

            printf("***********************\n");
            printf("*****NON-VEG MENU******\n");
            printf("***********************\n");

            printf("1. BUTTER CHICKEN \t 200\n");
            printf("2. KADAI CHICKEN \t 100\n");
            printf("3. CHICKEN MASALA \t 300\n");
            printf("4. CHICKEN RARA \t 200\n");
            printf("5. CHICKEN BIRYANI \t 400\n");
            printf("6. CHICKEN ROLL \t 100\n");
            printf("7. EGG CURRY \t\t 150\n");
            printf("8. CHICKEN TIKKA \t 300\n");
            printf("9. CHICKEN MASALA \t 500\n");
            printf("10. CHICKEN HANDI \t 200\n");
            printf("11. MUTTON CURRY \t 200\n");
            printf("12. RUMALI ROTI \t 12\n\n");

            printf("ARE YOU READY TO PLACE YOUR ORDER (Y/N): ");
            scanf(" %c", &c);

            if (c == 'y' || c == 'Y') {

                printf("WE HAVE INFORMED OUR HELPER\n");
                printf("OUR HELPER WILL COME TO YOUR SEAT AND TAKE YOUR ORDER\n");
                printf("THE BUS WILL STOP AT THE NEXT SERVICE STATION TO FETCH YOUR ORDERS AND THEN YOU CAN PAY\n");
            }
            else if (c == 'n' || c == 'N') {

                sleep(10); // Wait for 10 seconds
                printf("ARE YOU READY TO PLACE YOUR ORDER (Y/N): ");
                scanf(" %c", &d);

                if (d == 'y' || d == 'Y') {

                    printf("WE HAVE INFORMED OUR HELPER\n");
                    printf("OUR HELPER WILL COME TO YOUR SEAT AND TAKE YOUR ORDER\n");
                    printf("THE BUS WILL STOP AT THE NEXT SERVICE STATION TO FETCH YOUR ORDERS AND THEN YOU CAN PAY\n");
                }
                else {
                    printf("Invalid choice. Taking you back to the main menu\n");
                }
            }
            else {
                printf("Invalid choice. Taking you back to the main menu\n");
            }
        }
        else {
            printf("Invalid choice. Taking you back to the main menu\n");
        }
    }
    else {
        printf("Taking you back to the main menu\n");
    }
    printf("\n\n");

}


void complaint() {
    char b;
    char a[100];

    printf("DO YOU WANT TO FILE A COMPLAINT (Y/N):");
    scanf(" %c", &b);

    // Clear input buffer

    while (getchar() != '\n');

    if (b == 'y' || b == 'Y') {
        printf("PLEASE WRITE YOUR COMPLAINT HERE:\n ");

        fgets(a, sizeof(a), stdin);
        printf("Please press Enter to continue");

        // Clear input buffer after fgets

        while (getchar() != '\n');

        printf("COMPLAINT SUBMITTED:\n%s\n", a);
        printf("FOR INSTANT ASSISTANCE CALL AT 7868789798\n");
        printf("SORRY FOR ANY INCONVENIENCE CAUSED\n");
    } else {
        printf("Thank you for your feedback. Taking you back to the main menu...\n");
    }
}
