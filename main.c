#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>


struct Boat{
    char boat_name[30];
    int boat_id;
    char category[10];
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
    char category[10];
    int duration;
    float price;
    char location[20];
    struct AddadditionalFacilities additional_facicilies;
    char customer_name[30];
    int phone_number;
    char email[40];
};


// function that add a new  inputCategory();
int addBoat();
int generate_unique_id();
struct BoatList ReadBoat();
struct BoatList searchBoat();
int searchBooking();

int main (){
    // int choice;

    // printf("Welcome to AquaRent Boat Managment and Renting System.\n\n");
    // printf("1. Do you want to access user Menu\n");
    // printf("2. Do you want to access admin Menu\n");
    // scanf("%d", &choice);
    // if(choice == 2){
    //     printf("\nUser Menu\n\n");
    //     printf("1. Book a Boat\n2. See all Boats\n3. Search Boats\n4. Search Your Booking");
    //     printf("Enter your choice 1 to 4: ");
    //     scanf("%d", &choice);
    //     do{
    //     if(choice == 1){
    //         bookBoat();
    //     }else if(choice == 2){
    //         ReadBoat();
    //     }else if(choice == 3){
    //         searchBoat();
    //     }else if(choice == 4){
    //         searchBooking();
    //     }else{
    //         printf("Invalid Input!");
    //         printf("Enter a correct vlaue 1 to 4: ");
    //     }
    //     }while (choice > 0 && choice < 5);
    // }
    // addBoat();
    // ReadBoat();          
    // searchBoat();
    // deleteBoat();
    // bookBoat();
    searchBooking();
    return 0;
}


// ---Main Functions--- 

// _Boats_

// Add Boat
int addBoat (){
    struct Boat b;
    int choice;
    static int current_id=0;
    char size, cate;
    FILE *ptr;


    printf("Add Boat Details\n");

    // name input
    printf("Enter Boat Name: ");
    scanf("%[^\n]%*c", b.boat_name);
    // id input
    b.boat_id = generate_unique_id();
    // category input
    inputCategory(b.category);
    // capacity input
    printf("Enter Maximum Capacity: ");
    scanf("%d", &b.max_capacity);
    // availablity input
    do{
        printf("Enter Availability: \n 1. Available \n 2. Not Available\n");
        printf("Enter your Choice: ");
        scanf("%d", &choice);
        if (choice == 1){
            b.isAvailable = true;
        }else if (choice == 2){
            b.isAvailable = false;
        }else{
            printf("Invalid Choice!\n");
            printf("Enter Valid Choice\n");
        }
    } while (choice < 1 || choice > 2);
    
    // price input
    printf("Enter Price per Hour: ");
    scanf("%f", &b.price_per_hour);

    // size input 
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


    ptr = fopen("Boats.rec", "a+");
    fprintf(ptr, "Boat Name: %s\n", b.boat_name);
    fprintf(ptr, "Boat Id: %d\n", b.boat_id);
    fprintf(ptr, "Category: %s\n", b.category); 
    fprintf(ptr, "Max Capacity: %d\n", b.max_capacity);
    fprintf(ptr, "Availability: %s\n", b.isAvailable ? "Available" : "Not Available");
    fprintf(ptr, "Price Per Hour: %.2f\n", b.price_per_hour);
    fprintf(ptr, "Size: %s\n", b.size); 
    fclose(ptr);
    printf("Saved Successfully.\n");
    return 0;
}

// Read Boat
struct BoatList ReadBoat() {
    struct BoatList list;
    FILE *file = fopen("Boats.rec", "r");
    if (file == NULL){
        printf("Could not open file!\n");
        return list;
    } 

    list.count = 0;
    char line[100];

    while(fgets(line, sizeof(line), file) && list.count < 100){
        sscanf(line, "Boat Name: %[^\n]", list.boats[list.count].boat_name);

        fgets(line, sizeof(line), file);
        sscanf(line, "Boat Id: %d", &list.boats[list.count].boat_id);

        fgets(line, sizeof(line), file);
        sscanf(line, "Category: %[^\n]", list.boats[list.count].category);

        fgets(line, sizeof(line), file);
        sscanf(line, "Max Capacity: %d", &list.boats[list.count].max_capacity);

        fgets(line, sizeof(line), file);
        char avail[20];
        sscanf(line, "Availability: %[^\n]", avail);
        list.boats[list.count].isAvailable = (strcmp(avail, "Available") == 0);  // convert to bool

        fgets(line, sizeof(line), file);
        sscanf(line, "Price Per Hour: %f", &list.boats[list.count].price_per_hour);

        fgets(line, sizeof(line), file);
        sscanf(line, "Size: %[^\n]", list.boats[list.count].size);

        list.count++;
    }

    fclose(file);

    for (int i = 0; i < list.count; i++){
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
    return list;
}
   
// Search Boat
struct BoatList searchBoat(){
    struct BoatList list;
    FILE *file = fopen("Boats.rec", "r");
    if (file == NULL){
        printf("Could not open file!\n");
        return list;
    }  

    list.count = 0;
    char line[100];
    int found=0, choice2;


    while(fgets(line, sizeof(line), file) && list.count < 100){
        sscanf(line, "Boat Name: %[^\n]", list.boats[list.count].boat_name);

        fgets(line, sizeof(line), file);
        sscanf(line, "Boat Id: %d", &list.boats[list.count].boat_id);

        fgets(line, sizeof(line), file);
        sscanf(line, "Category: %[^\n]", list.boats[list.count].category);

        fgets(line, sizeof(line), file);
        sscanf(line, "Max Capacity: %d", &list.boats[list.count].max_capacity);

        fgets(line, sizeof(line), file);
        char avail[20];
        sscanf(line, "Availability: %[^\n]", avail);
        list.boats[list.count].isAvailable = (strcmp(avail, "Available") == 0);  // convert to bool

        fgets(line, sizeof(line), file);
        sscanf(line, "Price Per Hour: %f", &list.boats[list.count].price_per_hour);

        fgets(line, sizeof(line), file);
        sscanf(line, "Size: %[^\n]", list.boats[list.count].size);

        list.count++;
    }

    fclose(file);

    int choice;
    struct Boat input;
    printf("Search Boat By : \n1. Name\n2. Id\n3. Category\n4. Capacity\n5. Availability\n6. Price\n7. Size\n");
    printf("Enter Choice 1 to 10: ");
    scanf("%d", &choice);

    do{
    switch (choice)
    {
        case 1:
        getchar(); // clear leftover newline from previous scanf
        printf("Enter Boat Name: ");
        fgets(input.boat_name, sizeof(input.boat_name), stdin);
        input.boat_name[strcspn(input.boat_name, "\n")] = 0; // remove newline
        break;
        case 2:
        printf("Enter Boat Id: ");
        scanf("%d", &input.boat_id);
        break;
        case 3:
        printf("Enter Boat Category: ");
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
        } while (choice2 < 1 || choice2> 3);
        break;

    }
    } while (choice < 1 || choice > 10);

    for (int i = 0; i < list.count; i++){
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
        printf("No result Found!");
    }
    return list;
}

// Delete Boat
int deleteBoat(){
    FILE *file = fopen("Boats.rec", "r");
    if (file == NULL){
        printf("Could not open file!\n");
        return 1;
    } 

    struct Boat boats[100];
    int count = 0;
    char line[100];
    int found=0, choice2;


    while(fgets(line, sizeof(line), file) && count < 100){
        sscanf(line, "Boat Name: %[^\n]", boats[count].boat_name);

        fgets(line, sizeof(line), file);
        sscanf(line, "Boat Id: %d", &boats[count].boat_id);

        fgets(line, sizeof(line), file);
        sscanf(line, "Category: %[^\n]", boats[count].category);

        fgets(line, sizeof(line), file);
        sscanf(line, "Max Capacity: %d", &boats[count].max_capacity);

        fgets(line, sizeof(line), file);
        char avail[20];
        sscanf(line, "Availability: %[^\n]", avail);
        boats[count].isAvailable = (strcmp(avail, "Available") == 0);  // convert to bool

        fgets(line, sizeof(line), file);
        sscanf(line, "Price Per Hour: %f", &boats[count].price_per_hour);

        fgets(line, sizeof(line), file);
        sscanf(line, "Size: %[^\n]", boats[count].size);

        count++;
    }

    fclose(file);

    int boat_id;
    printf("Enter Id of Boat you want to Delete: ");
    scanf("%d", &boat_id);
    char confirm;
    printf("Are you sure you want to delete this boat? (y/n): ");
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') return 0;

    FILE *ptr = fopen("Boats.rec", "w");
    if (ptr == NULL){
        printf("Could not open file!\n");
        return 1;
    } 
    
    for (int i = 0; i < count; i++){
        if(boat_id != boats[i].boat_id){
        fprintf(ptr, "Boat Name: %s\n", boats[i].boat_name);
        fprintf(ptr, "Boat Id: %d\n", boats[i].boat_id);
        fprintf(ptr, "Category: %s\n", boats[i].category); 
        fprintf(ptr, "Max Capacity: %d\n", boats[i].max_capacity);
        fprintf(ptr, "Availability: %s\n", boats[i].isAvailable ? "Available" : "Not Available");
        fprintf(ptr, "Price Per Hour: %.2f\n", boats[i].price_per_hour);
        fprintf(ptr, "Size: %s\n", boats[i].size); 
        }else{
            found = 1;
        }
    }
    fclose(ptr);
    if(!found){
        printf("Boat id not Found!");
    }else{
        printf("Boat Deleted Successfully!");   
    }

    return 0;
}

// _Booking_

// Add Booking
int bookBoat(){ 
    int choice, BoatId;
    struct BoatList list; 
    struct Booking booking;
    struct Boat selected_boat;
    int found = 0, no_meals;
    FILE *ptr;
    printf("Boat Booking\n1. See all Boats\n2. Search Boats\n");
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
    printf("Enter Boat id to select Boat: ");
    scanf("%d", &BoatId);

    for(int i = 0; i < 100 && list.boats[i].boat_id != -1; i++){
        if(list.boats[i].boat_id == BoatId){
            selected_boat = list.boats[i];
            found = 1;
            break;
        }
    }

    if(!found){
        printf("Boat not fount with id %d\n", BoatId);
        return 1;
    }

    //  add booking deatils

    booking.booking_id = generate_unique_id();

    booking.boat_id = selected_boat.boat_id;
    strcpy(booking.boat_name, selected_boat.boat_name);
    strcpy(booking.category, selected_boat.category);

    printf("Enter Booking Duration in hours: ");
    scanf("%d", &booking.duration);
    booking.price = booking.duration * selected_boat.price_per_hour;
    
    printf("Select Locaton: \n1.Palm Jumeirah\n2.Burj al Arab\n3.Charna Island\n4.Manora Island\n5.Zanzibar Island\n6.Norman Island\n7.Curieuse Island\n8.Kapas Island\n9.Great Barrier Island");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:strcpy(booking.location, "Palm Jumeirah");break;
    case 2:strcpy(booking.location, "Burj al Arab");break;
    case 3:strcpy(booking.location, "Charna Island");break;
    case 4:strcpy(booking.location, "Manora Island");break;
    case 5:strcpy(booking.location, "Zanzibar Island");break;
    case 6:strcpy(booking.location, "Norman Island");break;
    case 7:strcpy(booking.location, "Curieuse Island");break;
    case 8:strcpy(booking.location, "Kapas Island");break;
    case 9:strcpy(booking.location, "Great Barrier Island");break;
    default:printf("Invalid choice!");break;
    }

    printf("\n\nMeal per person cost: 400");
    printf("Do you Want to add meal (1 = yes, 0 = no): ");
    scanf("%d", &booking.additional_facicilies.meal);
    if(booking.additional_facicilies.meal){
        printf("Number of meals:");
        scanf("%d", &no_meals);
        booking.additional_facicilies.mealcost = 400 * no_meals;
        booking.price += booking.additional_facicilies.mealcost;
    }

    printf("\n\nCost of Life guard: 2000");
    printf("Do you Want to hire a lifeguard (1 = yes, 0 = no): ");
    scanf("%d", &booking.additional_facicilies.lifeguard);
    if(booking.additional_facicilies.lifeguard){
        booking.additional_facicilies.lifeguardcost = 2000;
        booking.price += booking.additional_facicilies.lifeguardcost;
    }

    getchar();
    printf("Enter customer name: ");
    scanf("%[^\n]%*c", booking.customer_name);

    printf("Enter phone number: ");
    scanf("%d", &booking.phone_number);

    printf("Enter email: ");
    scanf("%s", &booking.email);


    ptr = fopen("Booking.rec", "a+");
    fprintf(ptr, "Booking ID: %d\n", booking.booking_id  );
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
    fprintf(ptr, "Customer Phone: %d\n", booking.phone_number);
    fprintf(ptr, "Customer Email: %s\n", booking.email);
    fclose(ptr);
    printf("Saved Successfully.\n");
    return 0;
    
}

// Search booking
int searchBooking(){
    FILE *file = fopen("Booking.rec", "r");
    if (file == NULL){
        printf("Could not open file!\n");
        return 1;
    } 

    struct Booking booking[100];
    int count = 0;
    char line[100];
    int found=0, choice2;


    while(fgets(line, sizeof(line), file) && count < 100){
        sscanf(line, "Booking ID: %d", &booking[count].booking_id);
        
        fgets(line, sizeof(line), file);
        sscanf(line, "Boat Name: %[^\n]", &booking[count].boat_name);
        
        fgets(line, sizeof(line), file);
        sscanf(line, "Boat Id: %d", &booking[count].boat_id);

        fgets(line, sizeof(line), file);
        sscanf(line, "Category: %s", &booking[count].category);

        fgets(line, sizeof(line), file);
        sscanf(line, "Duration: %d", &booking[count].duration);

        fgets(line, sizeof(line), file);
        sscanf(line, "Total Price: %f", &booking[count].price);

        fgets(line, sizeof(line), file);
        sscanf(line, "Location: %s", &booking[count].location);

        fgets(line, sizeof(line), file);
        sscanf(line, "Meal: %d", &booking[count].additional_facicilies.meal);
        fgets(line, sizeof(line), file);
        sscanf(line, "Meal Cost: %f", &booking[count].additional_facicilies.mealcost);
        fgets(line, sizeof(line), file);
        sscanf(line, "Lifeguard: %d", &booking[count].additional_facicilies.lifeguard);
        fgets(line, sizeof(line), file);
        sscanf(line, "Lifeguard Cost: %d", &booking[count].additional_facicilies.lifeguardcost);

        fgets(line, sizeof(line), file);
        sscanf(line, "Customer Name: %[^\n]", &booking[count].customer_name);
        fgets(line, sizeof(line), file);
        sscanf(line, "Customer Phone: %s", &booking[count].phone_number);
        fgets(line, sizeof(line), file);
        sscanf(line, "Customer Email: %s", &booking[count].email);
        
        count++;
    }

    fclose(file);

    int choice;
    struct Booking input;
    printf("Search Booking\n");
    printf("Enter Booking Id: ");
    scanf("%d", &input.booking_id);
    getchar();
    printf("Enter Customer Name: ");
    scanf("%[^\n]%*c", input.customer_name);


    for (int i = 0; i < count; i++){
        if(input.booking_id == booking[i].booking_id && strcmp(input.customer_name, booking[i].customer_name) == 0){

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
        printf("  Customer Phone: %d\n", booking[i].phone_number);
        printf("  Customer Email: %s\n", booking[i].email);
        printf("------------------------\n");
        }
    }
    if(!found){
        printf("No result Found!");
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
    FILE *file = fopen("id_store.txt", "r+");
    int id = 0;

    if (file == NULL) { 
        file = fopen("id_store.txt", "w+");
        if (file == NULL) {
            perror("File error");
            return -1;
        }
    } else {
        fscanf(file, "%d", &id);
    }

    id++;  // Increment ID

    rewind(file);        // Move back to start of file
    fprintf(file, "%d", id);  // Write new ID
    fclose(file);

    return id;
}
