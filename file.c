/*#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
 {
    FILE *fptr = fopen("contact.txt", "w");
    if (fptr == NULL)
    {
        printf("Error: Cannot open file to save contacts!\n");
        return;
    }

    // Store the contact count
    fprintf(fptr, "%d\n", addressBook->contactCount);

    // Store each contact
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s %s %s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fptr);
    printf(" Contacts saved successfully!\n");
  
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    void loadContacts(AddressBook *addressBook)
{
    FILE *fptr = fopen("contact.txt", "r");
    if (fptr == NULL)
    {
        printf("No saved contacts.\n");
        return;
    }

    // Read contact count
    fscanf(fptr, "%d\n", &addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    fclose(fptr);
}

    
}
*/
#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contact.txt", "w");
    if (fptr == NULL)
    {
        printf("Error: Cannot open file to save contacts!\n");
        return;
    }

    // Save contact count
    fprintf(fptr, "%d\n", addressBook->contactCount);

    // Save each contact using comma-separated format
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fptr);
    printf("Contacts saved successfully!\n");
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contact.txt", "r");

    if (fptr == NULL)
    {
        printf("No saved contacts found. Starting fresh.\n");
        return;
    }

    fscanf(fptr, "%d\n", &addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    fclose(fptr);
    printf(" Contacts loaded successfully!\n");
}
void saveToCSV(AddressBook *addressBook) {
    FILE *fp = fopen("contacts.csv", "w");
    if (fp == NULL) {
        printf("Error: Cannot create CSV file!\n");
        return;
    }

    fprintf(fp, "Name,Phone,Email\n");

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fp, "%s,%s,%s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email
        );
    }

    fclose(fp);
    printf("CSV file saved as contacts.csv\n");
}


