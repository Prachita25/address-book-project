#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    printf("\n-------------------------------------------------------------\n");
    printf("| %-3s | %-15s | %-15s | %-25s |\n", "No", "Name", "Phone", "Email");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
         printf("| %-3d | %-15s | %-15s | %-25s |\n",
               i + 1,
        addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int check_phone(char *phone, AddressBook *addressBook)
{
    for (int i = 0; i < addressBook -> contactCount; i++)
    {
        if(strcmp(phone, addressBook -> contacts[i].phone) == 0)
        {
            return 1;
        }
    }
    return 0;
}
int isValidPhone(char *phone)
{
    if (strlen(phone) != 10)
        return 0;

    for (int i = 0; i < 10; i++)
    {
        if (phone[i] < '0' || phone[i] > '9')
            return 0;
    }
    return 1;
}

int isValidEmail(char *email)
{
    int hasAt = 0, hasUpper = 0, hasLower = 0, hasDotCom = 0;
    int len = strlen(email);

    for (int i = 0; i < len; i++)
    {
        if (email[i] == '@') hasAt = 1;
        if (email[i] >= 'A' && email[i] <= 'Z') hasUpper = 1;
        if (email[i] >= 'a' && email[i] <= 'z') hasLower = 1;
    }

    if (len >= 4 && strcmp(email + (len - 4), ".com") == 0)
        hasDotCom = 1;

    if (hasAt && hasDotCom && hasUpper && hasLower)
        return 1;

    return 0;
}

void createContact(AddressBook *addressBook)
{
    char name[20], phone[20], email[20];

    printf("\n----------------------------------------\n");
    printf("           CREATE NEW CONTACT\n");
    printf("----------------------------------------\n");

    printf("Enter the Name : ");
    scanf(" %[^\n]", name);

    // ---------------- PHONE INPUT ----------------
    printf("Enter the Phone number : ");
    scanf(" %[^\n]", phone);

    // Validate phone number format
    if (!isValidPhone(phone))
    {
        printf("\n----------------------------------------\n");
        printf("  Invalid Phone Number!\n");
        printf("  -> Must be exactly 10 digits\n");
        printf("  -> No alphabets allowed\n");
        printf("  -> Contact NOT created.\n");
        printf("----------------------------------------\n\n");
        return;
    }

    // Check phone already exists
    if (check_phone(phone, addressBook) == 1)
    {
        printf("\n----------------------------------------\n");
        printf("  The phone number already exists!\n");
        printf("------------------------------------------\n");


        printf("\n-------------------------------------------\n");
        printf("  CONTACT NOT CREATED.\n");
        printf("----------------------------------------\n\n");
        return;
    }

    // ---------------- EMAIL INPUT ----------------
    printf("Enter the Email id : ");
    scanf(" %[^\n]", email);

    if (!isValidEmail(email))
    {
        printf("\n----------------------------------------\n");
        printf("  Invalid Email Format!\n");
        printf("  Requirements:\n");
        printf("    -> Must contain '@'\n");
        printf("    -> Must end with '.com'\n");
        printf("    -> Must contain UPPERCASE & lowercase letters\n");
        printf("-----------------------------------------\n");

        
        printf("\n---------------------------------------\n");
        printf("  CONTACT NOT CREATED.\n");
        printf("----------------------------------------\n\n");
        return;
    }

    // ---------------- SAVE CONTACT ----------------
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);
    addressBook->contactCount++;

    printf("\n----------------------------------------\n");
    printf("  Contact created successfully!\n");
    printf("----------------------------------------\n\n");
}

    


void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int option, flag=0;
    char name[100];
    printf("1.search by mame \n2.Search by  ph no \n3.Search by email id\n");
    printf("Enter the option : ");
    scanf("%d",&option);
    while (getchar() != '\n');
    

    switch(option)
    {
    
    case 1 : 
    
    printf("Enter the name : ");
    getchar();
    scanf("%[^\n]", name);

    for(int i=0; i < addressBook -> contactCount; i++)
    {
        if (strcmp(name, addressBook -> contacts[i].name) == 0)
        {
            flag=1;
            printf("%s %s %s\n",addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
        }
       
    }
    if (flag == 0)
        printf("name is not present\n");
    break;

    case 2 : 
    
    printf("Enter the Phone number : ");
    
    scanf(" %[^\n]", name);
    name[strcspn(name, "\r\n")] = 0;
    
    for(int i=0; i<addressBook -> contactCount; i++)
    {
        if (strcmp(name, addressBook -> contacts[i].phone) == 0)
        {
            flag=1;
            printf("%s %s %s\n",addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
        }
    }
    if (flag == 0)
            printf("phone number not present\n");
        break;

        case 3 :
        
        printf("Enter the Email : ");
        
        scanf(" %[^\n]",name);
        
        for(int i=0; i<addressBook -> contactCount; i++)
        {
            addressBook->contacts[i].email[strcspn(addressBook->contacts[i].email, "\r\n")] = 0;
            name[strcspn(name, "\r\n ")] = 0;
            if (strcmp(name,addressBook -> contacts[i].email)==0)
            {
                flag = 1;
                printf("%s %s %s\n",addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
            }
        }
        if (flag == 0)
        printf("Email ID is not present");
    break;
}
}


void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int option, flag=0,index = -1,choice;
    char name[100], phone[100], email[100];
    printf("\n-----------------------------------------\n");
    printf("    You Entered Into Edit Contact\n");
    printf("--------------------------------------------\n");

    printf("1.search by :\n");

    printf("1.Name\n");

    printf("2.Phone number\n");

    printf("3.Email\n");

    printf("Enter the option : ");
    scanf("%d",&option);

    int matches[100];
    int count = 0;

    switch (option)
    {
        case 1:
        printf("Enter the name :");
        scanf(" %[^\n]",name);
        for (int i = 0; i<addressBook -> contactCount; i++)
        {
            if (strcmp( addressBook -> contacts[i].name,name)==0)
            {
                matches[count++] = i;
                printf("%d %s %s %s\n",count,addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
       
            }
        }

        break;

        case 2:
        printf("Enter the Phone No.");
        scanf(" %[^\n]",phone);
        for (int i=0; i<addressBook->contactCount; i++)
        {
            if (strcmp(addressBook -> contacts[i].phone,phone)==0)
            {
                matches[count++] = i;
                printf("%d %s %s %s\n",count,addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
       
            }
        }
        
        break;
        
        
       
        case 3:
        
        printf("Enter the Email ID: ");
        scanf(" %[^\n]",email);

        for (int i=0; i<addressBook->contactCount; i++)

        {
            if (strcmp( addressBook -> contacts[i].email,email)==0)

            {
                matches[count++] = i;
                printf(" %d %s %s %s\n",count,addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
       
            }
        }
        
        break;

    }
    if (count == 0)
    {
        printf("No matching contacts found.\n");
        return;
    }
    if (count == 1)
    {
        index = matches[0];
    }
    else
    {

    printf("\nMultiple contacts Found. Enter the number to edit: ");
    scanf("%d",&choice);

    if (choice < 1 || choice > count)
    {
        printf("Invalid selection!\n");
        return;
    }
    index = matches[choice - 1];
    }
    printf("\nYou want to edit:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("4.Edit all\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:
        printf("Enter the new name: ");
        scanf(" %[^\n]",name);
        strcpy(addressBook->contacts[index].name,name);
        break;

        case 2:
        printf("Enter new phone number: ");
        scanf(" %[^\n]",phone);
        strcpy(addressBook->contacts[index].phone,phone);
        break;

        case 3:
        printf("Enter new email: ");
        scanf(" %[^\n]",email);
        strcpy(addressBook->contacts[index].email,email);
        break;

        case 4: 
            printf("Enter new name: ");
            scanf(" %[^\n]", name);
            strcpy(addressBook->contacts[index].name, name);

            printf("Enter new phone number: ");
            scanf(" %[^\n]", phone);
            strcpy(addressBook->contacts[index].phone, phone);

            printf("Enter new email: ");
            scanf(" %[^\n]", email);
            strcpy(addressBook->contacts[index].email, email);
            break;

        default:
        printf("Invalid option.\n");
        return;

    }
    printf("\n---------------------------------------------\n");
    printf("       Contact updated successfully!\n");
    printf("-----------------------------------------------\n");
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
     while (getchar() != '\n');
    int option, count = 0, choice, index = -1;
    char name[100], phone[100], email[100];

    printf("\n-----------------------------------------\n");
    printf("         Delete Contact Section\n");
    printf("-------------------------------------------\n");

    printf("Search contact to delete by:\n");
    printf("1. Name\n");
    printf("2. Phone number\n");
    printf("3. Email\n");

    printf("Enter option: ");
    scanf("%d", &option);

    int matches[100];

    switch(option)
    {
        case 1:
            printf("Enter the name: ");
            scanf(" %[^\n]", name);

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].name, name) == 0)
                {
                    matches[count++] = i;
                    printf("%d. %s %s %s\n", count,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);
                }
            }
            break;

        case 2:
            printf("Enter the phone number: ");
            scanf(" %[^\n]", phone);

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    matches[count++] = i;
                    printf("%d. %s %s %s\n", count,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);
                }
            }
            break;

        case 3:
            printf("Enter the email: ");
            scanf(" %[^\n]", email);

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].email, email) == 0)
                {
                    matches[count++] = i;
                    printf("%d. %s %s %s\n", count,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);
                }
            }
            break;

        default:
            printf("Invalid option.\n");
            return;
    }

    if (count == 0)
    {
        printf("No contact found.\n");
        return;
    }

    if (count == 1)
    {
        index = matches[0];
    }
    else
    {
        printf("\nMultiple contacts found.\n");
        printf("Enter the number of the contact to delete: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > count)
        {
            printf("Invalid selection.\n");
            return;
        }

        index = matches[choice - 1];
    }

    // Shift contacts to delete the entry
    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("\n---------------------------------------------\n");
    printf("         Contact deleted successfully!\n");
    printf("-----------------------------------------------\n");
}


