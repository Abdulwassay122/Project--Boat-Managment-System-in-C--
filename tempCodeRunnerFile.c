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
   