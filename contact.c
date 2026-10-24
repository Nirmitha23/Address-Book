#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

int unique_phone(char temp[],AddressBook *addressBook){//check whether entered phone is unique or not
   int i;
   for (i = 0; i < addressBook->contactCount; i++){
      if(strcmp(addressBook->contacts[i].phone,temp)==0){
        printf("Enter a unique phone number,as number already exists \n ");
        return 1;
      }
   }
   return 0;
}

int unique_email(char temp[],AddressBook *addressBook){//check whether entered phone is unique or not
   int i;
   for (i = 0; i < addressBook->contactCount; i++){
      if(strcmp(addressBook->contacts[i].email,temp)==0){
        printf("Enter a unique email,as email already exists \n ");
        return 1;
      }
   }
   return 0;
}

int validate_name(char temp[]){//validate whether user is entering name or not
    int i=0;
    while (temp[i]!='\0')
    {
        if (temp[i]>='a' && temp[i]<='z' || temp[i]>='A' && temp[i]<='Z' || temp[i] == ' '){
          i++;   
        }else{
            printf("Invalid name entered\n");
            return 1;
        }
    }
    return 0;
}

int validate_mobile(char temp[]){//validate whether user is entering name or not
    int i=0;
    while (temp[i]!='\0')
    {
        if (temp[i]>='0' && temp[i]<='9'){
          i++;   
        }else{
            printf("Entered phone number is invalid\n");
            return 1;
        }
    }
    if(i>10 || i<10){
        printf("Entered phone number is invalid\n");
        return 1;
    }else{
        return 0;
    }
}

int validate_email(char temp[]){//validate whether user is entering name or not
    int i=0;
    char com[]=".com";
    char target[]="@";

    if(strstr(temp,com)==NULL){
        printf("Entered email is invalid, \".com\" is missing\n");
        return 1;
    }
    if(strstr(temp,target)==NULL){
        printf("Entered email is invalid, \"@\" is missing\n");
        return 1;
    }
    return 0;
}   

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    Contact dummy;
    int i,j;
    // Sort contacts based on the chosen criteria
    switch(sortCriteria){
        case 1 :
        printf("Sorted based on name\n");
        for(i=0;i< addressBook->contactCount;i++){
            for(j=0;j< addressBook->contactCount-1;j++){
                if((strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name))>0){
                    //strcmp compare two string
                    dummy = addressBook -> contacts[j];
                    addressBook -> contacts[j] = addressBook -> contacts[j+1];
                    addressBook -> contacts[j+1] = dummy;
                }
            }
        }
        break;
        //logic to sort and display based on name
        case 2 :
        printf("Sorted based on phone\n");
        for(i=0;i< addressBook->contactCount;i++){
            for(j=0;j< addressBook->contactCount-1;j++){
                if((strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone))>0){
                    //strcmp compare two string
                    dummy = addressBook -> contacts[j];
                    addressBook -> contacts[j] = addressBook -> contacts[j+1];
                    addressBook -> contacts[j+1] = dummy;
                }
            }
        }
        break;
        //logic to sort and display based on phone
        case 3 :
        printf("Sorted based on email\n");
        for(i=0;i< addressBook->contactCount;i++){
            for(j=0;j< addressBook->contactCount-1;j++){
                if((strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email))>0){
                    //strcmp compare two string
                    dummy = addressBook -> contacts[j];
                    addressBook -> contacts[j] = addressBook -> contacts[j+1];
                    addressBook -> contacts[j+1] = dummy;
                }
            }
        }
        break;
        //logic to sort and display based on email
        default:
        printf("Selection Criteria is invalid\n");

    }
    printf("_____________________>\n");
    printf("INDEX\tNAME\tMOBILE\tEMAIL\n");
    printf("_____________________>\n");
    for(i=0;i<addressBook->contactCount;i++){
        printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
   // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    char temp[50];
	printf("Menu ->Create Contact\n");
    printf("------------------------------------------------------------->\n");
    do{
        printf("Enter the name\n");
        scanf("%[^\n]",temp);
        getchar();
    }while(validate_name(temp));
    strcpy(addressBook->contacts[addressBook->contactCount].name,temp);

    do{
        printf("Enter the phone\n");
        scanf("%s",temp);
        getchar();
    }while(validate_mobile(temp)|unique_phone(temp,addressBook));//to avoid sort circuiting using bitwise or operator
    strcpy(addressBook->contacts[addressBook->contactCount].phone,temp);
    
    do{
        printf("Enter the email\n");
        scanf("%s",temp);
        getchar();
    }while(validate_email(temp)|unique_email(temp,addressBook));
    strcpy(addressBook->contacts[addressBook->contactCount].email,temp);

    printf("Creating contact Successfully\n");
    addressBook->contactCount++;
}

int searchContact(AddressBook *addressBook) 
{
    int opt,count=0;
    char temp[20];
    printf("Menu - search contact\n");
    printf("Press 1 for Search by name \nPress 2 for Search by Phone \nPress 3 for Search by email\n");
    scanf("%d",&opt);
    getchar();
    switch(opt){
          case 1:do{
                   printf("Enter the name\n");
                   scanf("%[^\n]",temp);
                   getchar();
                } while (validate_name(temp));
				
                for(int i=0;i<addressBook->contactCount;i++){
			        if(strcasestr(addressBook->contacts[i].name,temp)!=NULL){
                      count++;
                      printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);    
                    }
                } 
				if(count == 0){
                     printf("Contact not found\n");
                     return 0;
                    }
                break;
        case 2:
		        printf("Enter the phone number\n");
                scanf("%[^\n]",temp);
                getchar();
				
                for(int i=0;i<addressBook->contactCount;i++){
			        if(strcasestr(addressBook->contacts[i].phone,temp)!=NULL){
                      count++;
                      printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);    
                    }
                }
				if(count == 0){
                     printf("Contact not found\n");
                     return 0;
                    }
                break;
        case 3:
		        printf("Enter the email\n");
                scanf("%[^\n]",temp);
                getchar();
				
                for(int i=0;i<addressBook->contactCount;i++){
			        if(strcasestr(addressBook->contacts[i].email,temp)!=NULL){
                      count++;
                      printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);    
                    }
                } 
				if(count == 0){
                     printf("Contact not found\n");
                     return 0;
                    }
                break;              
        default:
                printf("Entered option is invalid\n");
    }
    return 1;
}

void editContact(AddressBook *addressBook)
{
    char var[50];
    int index,opt;
    printf("Menu --- Edit Contact\n");
    // searchContact(addressBook);
    if(!searchContact(addressBook))
       return;
    printf("Enter the index to edit ----> ");
    scanf("%d",&index);
    getchar();

    if(index<0 || index>addressBook->contactCount){
        printf("You have entered a invalid index\n");
        return;
    }

    edit:
    printf("1.Edit name \t2.Edit Phone Number \t3.Edit Email\n"); 
    scanf("%d",&opt);
    getchar();

    switch(opt){
        case 1:
        do{
            printf("Enter the name to edit\n");
            scanf("%[^\n]",var);
	        getchar();
	    }while(validate_name(var));
        strcpy(addressBook->contacts[index-1].name,var);
        printf("Name edited successfully\n");
        break;

	    case 2:
        do{
            printf("Enter the phone number to edit\n");
	        scanf("%s",var);
	        getchar();
        }while((validate_mobile(var))|unique_phone(var,addressBook));
        strcpy(addressBook->contacts[index-1].phone,var);
	    printf("Phone Number edited successfully\n");
        break;

	   case 3:
       do{
           printf("Enter the email to edit\n");
	       scanf("%s",var);
	       getchar();
	   }while((validate_email(var))|unique_email(var,addressBook));
       strcpy(addressBook->contacts[index-1].email,var);
	   printf("Email Edited Successfully\n");
       break;

	   default:
	    {
           printf("Entered option is invalid\n");
	       goto edit;
	    }
	}
}

void deleteContact(AddressBook *addressBook)
{
    int index,i;
	printf("Menu -- Delete Contact\n ");
    if(!searchContact(addressBook))
       return;
    printf("Enter the index to edit ----> ");
    scanf("%d",&index);
    getchar();
    
    if(index<0 || index>addressBook->contactCount){
       printf("You have entered a invalid index\n");
       return;
    }

    for(i=index-1;i<addressBook->contactCount-1;i++ ){
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf("Contact Deleted Successfully\n");   
}
