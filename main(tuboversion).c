#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

/* Define bool type for Turbo C */
#define bool int
#define true 1
#define false 0

struct Boat{
    char boat_name[30];
    int boat_id;
    char category[15];
    int max_capacity;
    bool isAvailable;
    float price_per_hour;
    char size[10];
};

struct BoatList{
    struct Boat boats[100];
    int count;
};

struct AddadditionalFacilities {
    bool meal;
    float mealcost;
    bool lifeguard;
    int lifeguardcost;
};

struct Booking{
    int booking_id;
    char boat_name[30];
    int boat_id;
    char category[15];
    int duration;
    float price;
    char location[25];
    struct AddadditionalFacilities additional_facicilies;
    char customer_name[30];
    long phone_number;
    char email[40];
};

/* Function prototypes */
int addBoat(void);
int generate_unique_id(void);
void inputCategory(char *category);
struct BoatList ReadBoat(void);
struct BoatList searchBoat(void);
int searchBooking(void);
int deleteBoat(void);
int bookBoat(void);
int seeAllBooking(void);

int main(){
    int choice1, choice2, choice3, password;
    
    step1:
    clrscr();
    printf("Welcome to AquaRent Boat Management and Renting System.\n\n");
    printf("1. Do you want to access user Menu\n");
    printf("2. Do you want to access admin Menu\n");
    printf("3. Exit\n");
    printf("Enter Your Choice: ");
    scanf("%d", &choice1);
    
    if(choice1 == 1){
        do{
            clrscr();
            printf("\n---User Menu---\n\n");
            printf("1. Book a Boat\n2. See all Boats\n3. Search Boats\n4. Search Your Booking\n5. Exit\n");
            printf("Enter your choice 1 to 5: ");
            scanf("%d", &choice2);
            
            if(choice2 == 1){
                bookBoat();
                getch();
            }else if(choice2 == 2){
                ReadBoat();
                getch();
            }else if(choice2 == 3){
                searchBoat();
                getch();
            }else if(choice2 == 4){
                searchBooking();
                getch();
            }else if(choice2 == 5){
                goto step1;
            }else{
                printf("Invalid Input! Press any key to continue...");
                getch();
            }
        }while(choice2 != 5);
    }
    else if(choice1 == 2){
        printf("\nEnter Password: ");
        scanf("%d", &password);
        if(password == 123){
            do{
                clrscr();
                printf("\n---Admin Menu---\n\n");
                printf("1. ADD a Boat\n2. Delete a Boat\n3. See All Bookings\n4. See all Boats\n5. Search Boats\n6. Search Your Booking\n7. Exit\n");
                printf("Enter Choice 1 to 7: ");
                scanf("%d", &choice3);
                
                if(choice3 == 1){
                    addBoat();
                    getch();
                }
                else if(choice3 == 2){
                    deleteBoat();
                    getch();
                }
                else if(choice3 == 3){
                    seeAllBooking();
                    getch();
                }
                else if(choice3 == 4){
                    ReadBoat();
                    getch();
                }
                else if(choice3 == 5){
                    searchBoat();
                    getch();
                }
                else if(choice3 == 6){
                    searchBooking();
                    getch();
                }
                else if(choice3 == 7){
                    goto step1;
                }
                else{
                    printf("Invalid Input! Press any key to continue...");
                    getch();
                }
            }while(choice3 != 7);
        }else{
            printf("Incorrect Password!\n");
            getch();
            goto step1;
        }
    }
    else if(choice1 == 3){
        printf("Thank you for using AquaRent!\n");
        getch();
        return 0;
    }
    else{
        printf("Invalid choice! Press any key to continue...");
        getch();
        goto step1;
    }
    
    return 0;
}

/* Add Boat Function */
int addBoat(){
    struct Boat b;
    int choice;
    FILE *ptr;
    
    clrscr();
    printf("Add Boat Details\n\n");
    
    /* name input */
    printf("Enter Boat Name: ");
    fflush(stdin);
    gets(b.boat_name);
    
    /* id input */
    b.boat_id = generate_unique_id();
    printf("Generated Boat ID: %d\n", b.boat_id);
    
    /* category input */
    inputCategory(b.category);
    
    /* capacity input */
    printf("Enter Maximum Capacity: ");
    scanf("%d", &b.max_capacity);
    
    /* availability input */
    do{
        printf("Enter Availability: \n 1. Available \n 2. Not Available\n");
        printf("Enter your Choice: ");
        scanf("%d", &choice);
        if (choice == 1){
            b.isAvailable = true;
        }else if (choice == 2){
            b.isAvailable = false;
        }else{
            printf("Invalid Choice! Enter Valid Choice\n");
        }
    } while (choice < 1 || choice > 2);
    
    /* price input */
    printf("Enter Price per Hour: ");
    scanf("%f", &b.price_per_hour);
    
    /* size input */
    do {
        printf("Enter Size:\n 1. Small\n 2. Medium\n 3. Large\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1)
            strcpy(b.size, "Small");
        else if (choice == 2)
            strcpy(b.size, "Medium");
        else if (choice == 3)
            strcpy(b.size, "Large");
        else
            printf("Invalid choice. Try again.\n");
    } while (choice < 1 || choice > 3);
    
    ptr = fopen("Boats.rec", "a");
    if(ptr == NULL){
        printf("Error opening file!\n");
        return 1;
    }
    
    fprintf(ptr, "Boat Name: %s\n", b.boat_name);
    fprintf(ptr, "Boat Id: %d\n", b.boat_id);
    fprintf(ptr, "Category: %s\n", b.category);
    fprintf(ptr, "Max Capacity: %d\n", b.max_capacity);
    fprintf(ptr, "Availability: %s\n", b.isAvailable ? "Available" : "Not Available");
    fprintf(ptr, "Price Per Hour: %.2f\n", b.price_per_hour);
    fprintf(ptr, "Size: %s\n", b.size);
    fclose(ptr);
    
    printf("Boat Added Successfully.\n");
    return 0;
}

/* Read Boat Function */
struct BoatList ReadBoat(){
    struct BoatList list;
    int i;
    FILE *file;
    char line[100];
    
    list.count = 0;
    
    file = fopen("Boats.rec", "r");
    if (file == NULL){
        printf("Could not open file or no boats available!\n");
        return list;
    }
    
    while(fgets(line, sizeof(line), file) && list.count < 100){
        if(strstr(line, "Boat Name:") != NULL){
            sscanf(line, "Boat Name: %[^\n]", list.boats[list.count].boat_name);
            
            fgets(line, sizeof(line), file);
            sscanf(line, "Boat Id: %d", &list.boats[list.count].boat_id);
            
            fgets(line, sizeof(line), file);
            sscanf(line, "Category: %[^\n]", list.boats[list.count].category);
            
            fgets(line, sizeof(line), file);
            sscanf(line, "Max Capacity: %d", &list.boats[list.count].max_capacity);
            
            fgets(line, sizeof(line), file);
            if(strstr(line, "Available") != NULL)
                list.boats[list.count].isAvailable = true;
            else
                list.boats[list.count].isAvailable = false;
            
            fgets(line, sizeof(line), file);
            sscanf(line, "Price Per Hour: %f", &list.boats[list.count].price_per_hour);
            
            fgets(line, sizeof(line), file);
            sscanf(line, "Size: %[^\n]", list.boats[list.count].size);
            
            list.count++;
        }
    }
    
    fclose(file);
    
    printf("\n=== ALL BOATS ===\n");
    for (i = 0; i < list.count; i++){
        printf("Boat #%d\n", i + 1);
        printf("  Name: %s\n", list.boats[i].boat_name);
        printf("  ID: %d\n", list.boats[i].boat_id);
        printf("  Category: %s\n", list.boats[i].category);
        printf("  Capacity: %d\n", list.boats[i].max_capacity);
        printf("  Availability: %s\n", list.boats[i].isAvailable ? "Available" : "Not Available");
        printf("  Price/Hour: %.2f\n", list.boats[i].price_per_hour);
        printf("  Size: %s\n", list.boats[i].size);
        printf("------------------------\n");
    }
    
    if(list.count == 0){
        printf("No boats found!\n");
    }
    
    return list;
}

/* Search Boat Function */
struct BoatList searchBoat(){
    struct BoatList list;
    FILE *file;
    char line[100];
    int found = 0, choice, choice2, i;
    struct Boat input;
    
    list.count = 0;
    
    file = fopen("Boats.rec", "r");
    if (file == NULL){
        printf("Could not open file!\n");
        return list;
    }
    
    /* Read all boats first */
    while(fgets(line, sizeof(line), file) && list.count < 100){
        if(strstr(line, "Boat Name:") != NULL){
            sscanf(line, "Boat Name: %[^\n]", list.boats[list.count].boat_name);
            
            fgets(line, sizeof(line), file);
            sscanf(line, "Boat Id: %d", &list.boats[list.count].boat_id);
            
            fgets(line, sizeof(line), file);
            sscanf(line, "Category: %[^\n]", list.boats[list.count].category);
            
            fgets(line, sizeof(line), file);
            sscanf(line, "Max Capacity: %d", &list.boats[list.count].max_capacity);
            
            fgets(line, sizeof(line), file);
            if(strstr(line, "Available") != NULL)
                list.boats[list.count].isAvailable = true;
            else
                list.boats[list.count].isAvailable = false;
            
            fgets(line, sizeof(line), file);
            sscanf(line, "Price Per Hour: %f", &list.boats[list.count].price_per_hour);
            
            fgets(line, sizeof(line), file);
            sscanf(line, "Size: %[^\n]", list.boats[list.count].size);
            
            list.count++;
        }
    }
    fclose(file);
    
    printf("Search Boat By:\n1. Name\n2. Id\n3. Category\n4. Capacity\n5. Availability\n6. Price\n7. Size\n");
    printf("Enter Choice 1 to 7: ");
    scanf("%d", &choice);
    
    switch (choice){
        case 1:
            printf("Enter Boat Name: ");
            fflush(stdin);
            gets(input.boat_name);
            break;
        case 2:
            printf("Enter Boat Id: ");
            scanf("%d", &input.boat_id);
            break;
        case 3:
            inputCategory(input.category);
            break;
        case 4:
            printf("Enter Minimum Capacity: ");
            scanf("%d", &input.max_capacity);
            break;
        case 5:
            do {
                printf("Enter Availability:\n 1. Available \n 2. Not Available\n");
                printf("Enter your Choice: ");
                scanf("%d", &choice2);
                if (choice2 == 1)
                    input.isAvailable = true;
                else if (choice2 == 2)
                    input.isAvailable = false;
                else
                    printf("Invalid Choice! Try again.\n");
            } while (choice2 < 1 || choice2 > 2);
            break;
        case 6:
            printf("Enter Maximum Price Per Hour: ");
            scanf("%f", &input.price_per_hour);
            break;
        case 7:
            do {
                printf("Enter Size:\n 1. Small\n 2. Medium\n 3. Large\n");
                printf("Enter your choice: ");
                scanf("%d", &choice2);
                if (choice2 == 1)
                    strcpy(input.size, "Small");
                else if (choice2 == 2)
                    strcpy(input.size, "Medium");
                else if (choice2 == 3)
                    strcpy(input.size, "Large");
                else
                    printf("Invalid choice. Try again.\n");
            } while (choice2 < 1 || choice2 > 3);
            break;
        default:
            printf("Invalid choice!\n");
            return list;
    }
    
    printf("\n=== SEARCH RESULTS ===\n");
    for (i = 0; i < list.count; i++){
        bool match = false;
        switch (choice) {
            case 1: match = (strcmp(input.boat_name, list.boats[i].boat_name) == 0); break;
            case 2: match = (input.boat_id == list.boats[i].boat_id); break;
            case 3: match = (strcmp(input.category, list.boats[i].category) == 0); break;
            case 4: match = (list.boats[i].max_capacity >= input.max_capacity); break;
            case 5: match = (list.boats[i].isAvailable == input.isAvailable); break;
            case 6: match = (list.boats[i].price_per_hour <= input.price_per_hour); break;
            case 7: match = (strcmp(input.size, list.boats[i].size) == 0); break;
        }
        
        if(match){
            found = 1;
            printf("Boat #%d\n", i + 1);
            printf("  Name: %s\n", list.boats[i].boat_name);
            printf("  ID: %d\n", list.boats[i].boat_id);
            printf("  Category: %s\n", list.boats[i].category);
            printf("  Capacity: %d\n", list.boats[i].max_capacity);
            printf("  Availability: %s\n", list.boats[i].isAvailable ? "Available" : "Not Available");
            printf("  Price/Hour: %.2f\n", list.boats[i].price_per_hour);
            printf("  Size: %s\n", list.boats[i].size);
            printf("------------------------\n");
        }
    }
    
    if(!found){
        printf("No matching boats found!\n");
    }
    
    return list;
}

/* Delete Boat Function */
int deleteBoat(){
    FILE *file, *temp;
    char line[100];
    int boat_id, found = 0;
    char confirm;
    
    printf("Enter ID of Boat you want to Delete: ");
    scanf("%d", &boat_id);
    
    printf("Are you sure you want to delete this boat? (y/n): ");
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') return 0;
    
    file = fopen("Boats.rec", "r");
    if (file == NULL){
        printf("Could not open file!\n");
        return 1;
    }
    
    temp = fopen("temp.rec", "w");
    if (temp == NULL){
        printf("Could not create temporary file!\n");
        fclose(file);
        return 1;
    }
    
    while(fgets(line, sizeof(line), file)){
        if(strstr(line, "Boat Id:") != NULL){
            int current_id;
            sscanf(line, "Boat Id: %d", &current_id);
            if(current_id == boat_id){
                found = 1;
                /* Skip this boat's data (7 lines) */
                fgets(line, sizeof(line), file); /* Name */
                fgets(line, sizeof(line), file); /* Category */
                fgets(line, sizeof(line), file); /* Capacity */
                fgets(line, sizeof(line), file); /* Availability */
                fgets(line, sizeof(line), file); /* Price */
                fgets(line, sizeof(line), file); /* Size */
                continue;
            }
        }
        fprintf(temp, "%s", line);
    }
    
    fclose(file);
    fclose(temp);
    
    remove("Boats.rec");
    rename("temp.rec", "Boats.rec");
    
    if(found){
        printf("Boat Deleted Successfully!\n");
    }else{
        printf("Boat ID not found!\n");
    }
    
    return 0;
}

/* Book Boat Function */
int bookBoat(){
    int choice, BoatId;
    struct BoatList list;
    struct Booking booking;
    struct Boat selected_boat;
    int found = 0, no_meals;
    FILE *ptr;
    int i;
    
    printf("Boat Booking\n1. See all Boats\n2. Search Boats\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    switch (choice){
        case 1:
            list = ReadBoat();
            break;
        case 2:
            list = searchBoat();
            break;
        default:
            printf("Invalid choice.\n");
            return 1;
    }
    
    if(list.count == 0){
        printf("No boats available for booking!\n");
        return 1;
    }
    
    printf("Enter Boat ID to select Boat: ");
    scanf("%d", &BoatId);
    
    for(i = 0; i < list.count; i++){
        if(list.boats[i].boat_id == BoatId){
            selected_boat = list.boats[i];
            found = 1;
            break;
        }
    }
    
    if(!found){
        printf("Boat not found with ID %d\n", BoatId);
        return 1;
    }
    
    if(!selected_boat.isAvailable){
        printf("Sorry, this boat is not available!\n");
        return 1;
    }
    
    /* Generate booking details */
    booking.booking_id = generate_unique_id();
    booking.boat_id = selected_boat.boat_id;
    strcpy(booking.boat_name, selected_boat.boat_name);
    strcpy(booking.category, selected_boat.category);
    
    printf("Enter Booking Duration in hours: ");
    scanf("%d", &booking.duration);
    booking.price = booking.duration * selected_boat.price_per_hour;
    
    printf("Select Location:\n");
    printf("1.Palm Jumeirah\n2.Burj al Arab\n3.Charna Island\n4.Manora Island\n");
    printf("5.Zanzibar Island\n6.Norman Island\n7.Curieuse Island\n8.Kapas Island\n9.Great Barrier Island\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    switch (choice){
        case 1: strcpy(booking.location, "Palm Jumeirah"); break;
        case 2: strcpy(booking.location, "Burj al Arab"); break;
        case 3: strcpy(booking.location, "Charna Island"); break;
        case 4: strcpy(booking.location, "Manora Island"); break;
        case 5: strcpy(booking.location, "Zanzibar Island"); break;
        case 6: strcpy(booking.location, "Norman Island"); break;
        case 7: strcpy(booking.location, "Curieuse Island"); break;
        case 8: strcpy(booking.location, "Kapas Island"); break;
        case 9: strcpy(booking.location, "Great Barrier Island"); break;
        default: strcpy(booking.location, "Unknown"); break;
    }
    
    printf("\nMeal per person cost: 400\n");
    printf("Do you want to add meal (1 = yes, 0 = no): ");
    scanf("%d", &booking.additional_facicilies.meal);
    booking.additional_facicilies.mealcost = 0;
    if(booking.additional_facicilies.meal){
        printf("Number of meals: ");
        scanf("%d", &no_meals);
        booking.additional_facicilies.mealcost = 400 * no_meals;
        booking.price += booking.additional_facicilies.mealcost;
    }
    
    printf("\nCost of Life guard: 2000\n");
    printf("Do you want to hire a lifeguard (1 = yes, 0 = no): ");
    scanf("%d", &booking.additional_facicilies.lifeguard);
    booking.additional_facicilies.lifeguardcost = 0;
    if(booking.additional_facicilies.lifeguard){
        booking.additional_facicilies.lifeguardcost = 2000;
        booking.price += booking.additional_facicilies.lifeguardcost;
    }
    
    printf("Enter customer name: ");
    fflush(stdin);
    gets(booking.customer_name);
    
    printf("Enter phone number: ");
    scanf("%ld", &booking.phone_number);
    
    printf("Enter email: ");
    scanf("%s", booking.email);
    
    ptr = fopen("Booking.rec", "a");
    if(ptr == NULL){
        printf("Error opening booking file!\n");
        return 1;
    }
    
    fprintf(ptr, "Booking ID: %d\n", booking.booking_id);
    fprintf(ptr, "Boat Name: %s\n", booking.boat_name);
    fprintf(ptr, "Boat Id: %d\n", booking.boat_id);
    fprintf(ptr, "Category: %s\n", booking.category);
    fprintf(ptr, "Duration: %d\n", booking.duration);
    fprintf(ptr, "Total Price: %.2f\n", booking.price);
    fprintf(ptr, "Location: %s\n", booking.location);
    fprintf(ptr, "Meal: %d\n", booking.additional_facicilies.meal);
    fprintf(ptr, "Meal Cost: %.2f\n", booking.additional_facicilies.mealcost);
    fprintf(ptr, "Lifeguard: %d\n", booking.additional_facicilies.lifeguard);
    fprintf(ptr, "Lifeguard Cost: %d\n", booking.additional_facicilies.lifeguardcost);
    fprintf(ptr, "Customer Name: %s\n", booking.customer_name);
    fprintf(ptr, "Customer Phone: %ld\n", booking.phone_number);
    fprintf(ptr, "Customer Email: %s\n", booking.email);
    fclose(ptr);
    
    printf("\nBooking Successful!\n");
    printf("Your Booking ID is: %d\n", booking.booking_id);
    printf("Total Cost: %.2f\n", booking.price);
    
    return 0;
}

/* Search Booking Function */
int searchBooking(){
    FILE *file;
    char line[100];
    struct Booking booking;
    int search_id, found = 0;
    char search_name[30];
    file = fopen("Booking.rec", "r");
    if (file == NULL){
        printf("Could not open booking file or no bookings available!\n");
        return 1;
    }
    
    printf("Enter Booking ID: ");
    scanf("%d", &search_id);
    
    printf("Enter Customer Name: ");
    fflush(stdin);
    gets(search_name);
    
    while(fgets(line, sizeof(line), file)){
        if(strstr(line, "Booking ID:") != NULL){
            sscanf(line, "Booking ID: %d", &booking.booking_id);
            
            if(booking.booking_id == search_id){
                /* Read remaining booking details */
                fgets(line, sizeof(line), file);
                sscanf(line, "Boat Name: %[^\n]", booking.boat_name);
                fgets(line, sizeof(line), file);
                sscanf(line, "Boat Id: %d", &booking.boat_id);
                fgets(line, sizeof(line), file);
                sscanf(line, "Category: %s", booking.category);
                fgets(line, sizeof(line), file);
                sscanf(line, "Duration: %d", &booking.duration);
                fgets(line, sizeof(line), file);
                sscanf(line, "Total Price: %f", &booking.price);
                fgets(line, sizeof(line), file);
                sscanf(line, "Location: %s", booking.location);
                fgets(line, sizeof(line), file);
                sscanf(line, "Meal: %d", &booking.additional_facicilies.meal);
                fgets(line, sizeof(line), file);
                sscanf(line, "Meal Cost: %f", &booking.additional_facicilies.mealcost);
                fgets(line, sizeof(line), file);
                sscanf(line, "Lifeguard: %d", &booking.additional_facicilies.lifeguard);
                fgets(line, sizeof(line), file);
                sscanf(line, "Lifeguard Cost: %d", &booking.additional_facicilies.lifeguardcost);
                fgets(line, sizeof(line), file);
                sscanf(line, "Customer Name: %[^\n]", booking.customer_name);
                fgets(line, sizeof(line), file);
                sscanf(line, "Customer Phone: %ld", &booking.phone_number);
                fgets(line, sizeof(line), file);
                sscanf(line, "Customer Email: %s", booking.email);
                
                if(strcmp(search_name, booking.customer_name) == 0){
                    found = 1;
                    printf("\n=== BOOKING FOUND ===\n");
                    printf("Booking ID: %d\n", booking.booking_id);
                    printf("Boat Name: %s\n", booking.boat_name);
                    printf("Boat ID: %d\n", booking.boat_id);
                    printf("Category: %s\n", booking.category);
                    printf("Duration: %d hours\n", booking.duration);
                    printf("Total Price: %.2f\n", booking.price);
                    printf("Location: %s\n", booking.location);
                    printf("Meal: %s\n", booking.additional_facicilies.meal ? "Yes" : "No");
                    printf("Meal Cost: %.2f\n", booking.additional_facicilies.mealcost);
                    printf("Lifeguard: %s\n", booking.additional_facicilies.lifeguard ? "Yes" : "No");
                    printf("Lifeguard Cost: %d\n", booking.additional_facicilies.lifeguardcost);
                    printf("Customer Name: %s\n", booking.customer_name);
                    printf("Customer Phone: %ld\n", booking.phone_number);
                    printf("Customer Email: %s\n", booking.email);
                    printf("------------------------\n");
                    break;
                }
            }
        }
    }
    
    fclose(file);
    
    if(!found){
        printf("No booking found with the given ID and name!\n");
    }
    
    return 0;
}

// see all bookings 
int seeAllBooking(){
    struct Booking booking[100];
    int count = 0;
    char line[100];
    int found = 0;
    int i;
    FILE *file = fopen("Booking.rec", "r");
    if (file == NULL){
        printf("Could not open file!\n");
        return 1;
    } 


    while (!feof(file) && count < 100){
        fgets(line, sizeof(line), file);
        sscanf(line, "Booking ID: %d", &booking[count].booking_id);
        
        fgets(line, sizeof(line), file);
        sscanf(line, "Boat Name: %[^\n]", booking[count].boat_name);
        
        fgets(line, sizeof(line), file);
        sscanf(line, "Boat Id: %d", &booking[count].boat_id);

        fgets(line, sizeof(line), file);
        sscanf(line, "Category: %s", booking[count].category);

        fgets(line, sizeof(line), file);
        sscanf(line, "Duration: %d", &booking[count].duration);

        fgets(line, sizeof(line), file);
        sscanf(line, "Total Price: %f", &booking[count].price);

        fgets(line, sizeof(line), file);
        sscanf(line, "Location: %s", booking[count].location);

        fgets(line, sizeof(line), file);
        sscanf(line, "Meal: %d", &booking[count].additional_facicilies.meal);
        fgets(line, sizeof(line), file);
        sscanf(line, "Meal Cost: %f", &booking[count].additional_facicilies.mealcost);
        fgets(line, sizeof(line), file);
        sscanf(line, "Lifeguard: %d", &booking[count].additional_facicilies.lifeguard);
        fgets(line, sizeof(line), file);
        sscanf(line, "Lifeguard Cost: %d", &booking[count].additional_facicilies.lifeguardcost);

        fgets(line, sizeof(line), file);
        sscanf(line, "Customer Name: %[^\n]", booking[count].customer_name);
        fgets(line, sizeof(line), file);
        sscanf(line, "Customer Phone: %s", booking[count].phone_number);
        fgets(line, sizeof(line), file);
        sscanf(line, "Customer Email: %s", booking[count].email);

        count++;
    }

    fclose(file);

    for (i = 0; i < count; i++){
        found = 1;
        printf("Booking #%d\n", i + 1);
        printf("  Booking ID: %d\n", booking[i].booking_id);
        printf("  Boat Name: %s\n", booking[i].boat_name);
        printf("  Boat Id: %d\n", booking[i].boat_id);
        printf("  Category: %s\n", booking[i].category);
        printf("  Duration: %d\n", booking[i].duration);
        printf("  Total Price: %.2f\n", booking[i].price);
        printf("  Location: %s\n", booking[i].location);
        printf("  Meal: %d\n", booking[i].additional_facicilies.meal);
        printf("  Meal Cost: %.2f\n", booking[i].additional_facicilies.mealcost);
        printf("  Lifeguard: %d\n", booking[i].additional_facicilies.lifeguard);
        printf("  Lifeguard Cost: %d\n", booking[i].additional_facicilies.lifeguardcost);
        printf("  Customer Name: %s\n", booking[i].customer_name);
        printf("  Customer Phone: %s\n", booking[i].phone_number);
        printf("  Customer Email: %s\n", booking[i].email);
        printf("------------------------\n");
    }

    if (!found){
        printf("No Booking Found!\n");
    }
    return 0;
}

// ---Supporter Functions--- 


// function for input boat category
void inputCategory(char *category){
    int choice;
    const char *categories[] = {
        "Yacht", "Sailboat", "CenterConsole", "CruiseShip", "EventBoat",
        "CabinCruise", "DeckBoat", "SpeedBoat", "Catamaran", "Bowrider"
    };
    do {
        printf("Select Boat Category:\n");
        for (int i = 0; i < 10; i++) {
            printf("%d. %s\n", i + 1, categories[i]);
        }
        printf("Enter your choice (1-10): ");
        scanf("%d", &choice);
        if (choice >= 1 && choice <= 10)
            strcpy(category, categories[choice - 1]);
        else
            printf("Invalid choice. Try again.\n");
    } while (choice < 1 || choice > 10);
}
// unique id generator
int generate_unique_id() {
    FILE *file;
    int id = 0;

    file = fopen("id_store.txt", "r+");
    if (file == NULL) {
        file = fopen("id_store.txt", "w+");
        if (file == NULL) {
            printf("File error!\n");
            return -1;
        }
    } else {
        fscanf(file, "%d", &id);
    }

    id++;

    rewind(file);
    fprintf(file, "%d", id);
    fclose(file);

    return id;
}
