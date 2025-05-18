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
    float price_per_day;
    char size[10];
};


// function that add a new  inputCategory();
int addBoat();
int generate_unique_id();

int main (){

    // addBoat();
    // ReadBoat();          1
    searchBoat();
    return 0;
}


// Main Functions 
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
    printf("Enter Price per Day: ");
    scanf("%f", &b.price_per_day);
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
    fprintf(ptr, "Price Per Day: %.2f\n", b.price_per_day);
    fprintf(ptr, "Size: %s\n", b.size); 
    fclose(ptr);
    printf("Saved Successfully.\n");
    return 0;
}

// Read Boat
int ReadBoat() {
    FILE *file = fopen("Boats.rec", "r");
    if (file == NULL){
        printf("Could not open file!\n");
        return 1;
    } 

    struct Boat boats[100];
    int count = 0;
    char line[100];

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
        sscanf(line, "Price Per Day: %f", &boats[count].price_per_day);

        fgets(line, sizeof(line), file);
        sscanf(line, "Size: %[^\n]", boats[count].size);

        count++;
    }

    fclose(file);

    for (int i = 0; i < count; i++){
        printf("Boat #%d\n", i + 1);
        printf("  Name: %s\n", boats[i].boat_name);
        printf("  ID: %d\n", boats[i].boat_id);
        printf("  Category: %s\n", boats[i].category);
        printf("  Capacity: %d\n", boats[i].max_capacity);
        printf("  Availability: %s\n", boats[i].isAvailable ? "Available" : "Not Available");
        printf("  Price/Hour: %.2f\n", boats[i].price_per_hour);
        printf("  Price/Day: %.2f\n", boats[i].price_per_day);
        printf("  Size: %s\n", boats[i].size);
        printf("------------------------\n");
    }
    return 0;
}
   
// Search Boat
int searchBoat(){
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
        sscanf(line, "Price Per Day: %f", &boats[count].price_per_day);

        fgets(line, sizeof(line), file);
        sscanf(line, "Size: %[^\n]", boats[count].size);

        count++;
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

    for (int i = 0; i < count; i++){
        bool match = false;
        switch (choice) {
            case 1: match = (strcmp(input.boat_name, boats[i].boat_name) == 0); break;
            case 2: match = (input.boat_id == boats[i].boat_id); break;
            case 3: match = (strcmp(input.category, boats[i].category) == 0); break;
            case 4: match = (boats[i].max_capacity >= input.max_capacity); break;
            case 5: match = (boats[i].isAvailable == input.isAvailable); break;
            case 6: match = (boats[i].price_per_hour <= input.price_per_hour); break;
            case 7: match = (strcmp(input.size, boats[i].size) == 0); break;
        }
        if(match){
        found = 1;
        printf("Boat #%d\n", i + 1);
        printf("  Name: %s\n", boats[i].boat_name);
        printf("  ID: %d\n", boats[i].boat_id);
        printf("  Category: %s\n", boats[i].category);
        printf("  Capacity: %d\n", boats[i].max_capacity);
        printf("  Availability: %s\n", boats[i].isAvailable ? "Available" : "Not Available");
        printf("  Price/Hour: %.2f\n", boats[i].price_per_hour);
        printf("  Price/Day: %.2f\n", boats[i].price_per_day);
        printf("  Size: %s\n", boats[i].size);
        printf("------------------------\n");
        }
    }
    if(!found){
        printf("No result Found!");
    }
    return 0;
}





// Supporter Functions 

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
