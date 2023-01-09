#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <errno.h>

// user types: admin, staff, user
typedef struct{
	char fname[25];
	char lname[25];
	char email[25];
	char pass[25];
	char user_type[10];
}Account;

void firstScreen();
void login();
void registration();
void adminMain(int fixed_id);
void manageAccount(int fixed_id);
void manageStaff(int fixed_id);
void staffList(int fixed_id);
void addStaff(int fixed_id);
void editStaff(int fixed_id);
void manageOU(int fixed_id);
void listOU(int fixed_id);
void editOU(int fixed_id);
void manageEquip(int fixed_id);
void equipList(int fixed_id);
void addEquip(int fixed_id);
void editEquip(int fixed_id);
void deleteEquip(int fixed_id);
void changePersonalPass(int fixed_id);
void staffMain(int fixed_id);
void reqBorrowEquip(int fixed_id);
void reqReturnEquip(int fixed_id);
void staffChangePPass(int fixed_id);
void userMain(int fixed_id);
void borrowEquip(int fixed_id);
void returnEquip(int fixed_id);
void ouChangePPass(int fixed_id);

int main(){
	firstScreen();
	return 0;	
}

void firstScreen(){
	char x;
	
	printf("========================================\n");
	printf(">Do you already have an account? (Y/N)\n");
	printf("========================================\n>");
	scanf("%c", &x);
	fflush(stdin);
	system("cls");
	if(x == 'Y'){
		login();
	} else if(x == 'N'){
		registration();
	} else {
		printf("Invalid input");
		exit(0);
	}
}

void login(){
	int i, num, row = 0, column = 0, confirmation = 0, id, is_deleted;
	char buffer[1025];
	char *token;
	Account info;
	FILE *fp;
	
	fp = fopen("accountDB.txt", "r");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("===================================\n");
	printf(">Please enter your username(email)\n>");
	gets(info.email);
	fflush(stdin);
	printf("===================================\n");
	printf(">Please enter your password\n>");
	gets(info.pass);
	fflush(stdin);
	
	while(fgets(buffer, 1025, fp)){
		confirmation = 0;
		column = 0;
		row++;
		token = strtok(buffer, ", ");
		while(token != NULL){
			if(column == 0){
				id = atoi(token);
				confirmation++;
			}
			if(id == row && strcmp(token, info.email) == 0){
				confirmation++;
			}
			if(id == row && strcmp(token, info.pass) == 0){
				confirmation++;
			}
			if(column == 5){
				strcpy(info.user_type, token);
				confirmation++;
			}
			if(column == 6){
				is_deleted = atoi(token);
				confirmation++;
			}
			if(confirmation == 5 && is_deleted == 0){
				break;
			}
			token = strtok(NULL, ", ");
			column++;
		}
		if(confirmation == 5 && is_deleted == 0){
			break;
		}
	}
	fclose(fp);
//	printf("%d %s %s %s\n", id, info.email, info.pass, info.user_type);
//	printf("%d", confirmation);

	if(confirmation == 5 && is_deleted == 0){
		system("cls");
		if(strcmp(info.user_type, "Admin") == 0){
			adminMain(id);
		} else if(strcmp(info.user_type, "Staff") == 0){
			staffMain(id);
		} else if(strcmp(info.user_type, "OU") == 0){
			userMain(id);
		}
	} else {
		system("cls");
		printf("Wrong credentials!\n");
		printf("[1]Re-enter credentials\n");
		printf("[2]Go back to first screen\n");
		scanf("%d", &num);
		fflush(stdin);
		system("cls");
		if(num == 1){
			login();
		} else if(num == 2){
			firstScreen();
		}
	}
}

void registration(){
	Account info;
	char cpass[25], role[3] = "OU", buffer[25], c;
	int i, confirmation = 0, row = 0, column = 0, id = 1, is_deleted = 0;
	char *token;
	FILE *fp;
	fp = fopen("accountDB.txt", "a+");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("=================================\n");
	printf("======= REGISTRATION PAGE =======\n");
	printf("=================================\n");
	printf("\n>Enter your first name:\n>");
	gets(info.fname);
	printf("\n>Enter your last name:\n>");
	gets(info.lname);
	printf("\n>Enter your email:\n>");
	gets(info.email);
	printf("\n>Enter your password:\n>");
	gets(info.pass);
	printf("\n>Re-Enter your password:\n>");
	gets(cpass);
	fflush(stdin);
	system("cls");
	
	//generating id 
	for (c = getc(fp); c != EOF; c = getc(fp)){
		if(c == '\n'){
			id++;
		}
	}
	
//	if(confirmation == 1){
//		printf("Email has already been used!\n");sleep(1);
//		for(i = 0; i < 1; i++){
//			printf("Redirecting you to first screen");
//			printf(".");sleep(1);
//			printf(".");sleep(1);
//			printf(".\n");sleep(1);
//			system("cls");
//		}
//		firstScreen();
//	}
	
	//printf("Pass: %s CPass: %s\n", info.pass, cpass);
	if(strcmp(info.pass, cpass) == 0){
		fprintf(fp, "%d, %s, %s, %s, %s, %s, %d\n", id, info.fname, info.lname, info.email, info.pass, role, is_deleted);
		fclose(fp);
		printf("Registered successfully!\n");sleep(1);
		for(i = 0; i < 1; i++){
			printf("Redirecting you to login screen");
			printf(".");sleep(1);
			printf(".");sleep(1);
			printf(".\n");sleep(1);
			system("cls");
		}
		login();
	} else {
		fclose(fp);
		printf("Passwords do not match!\n");sleep(1);
		for(i = 0; i < 1; i++){
			printf("Redirecting you to first screen");
			printf(".");sleep(1);
			printf(".");sleep(1);
			printf(".\n");sleep(1);
			system("cls");
		}
		firstScreen();	
	}
}

void adminMain(int fixed_id){
	int num;
	
	printf("===================================\n");
	printf(">Admin Main Menu\n");
	printf("===================================\n");
	printf(">1 Manage Accounts\n");
	printf(">2 Manage Equipment\n");
	printf(">3 Change Personal Password\n");
	printf(">4 Exit\n");
	printf("===================================\n");
	printf("\nChoose what to do next\n>");
	scanf("%d", &num);
	system("cls");
	switch(num){
		case 1:
			manageAccount(fixed_id);
			break;
		case 2:
			manageEquip(fixed_id);
			break;
		case 3:
			changePersonalPass(fixed_id);
			break;
		case 4:
			exit(0);
			break;
		default:
			printf("Invalid input");
			adminMain(fixed_id);
	}
}

void manageAccount(int fixed_id){
	int num;
	
	printf("===================================\n");
	printf(">Account Management\n");
	printf("===================================\n");
	printf(">1 Manage Staff\n");
	printf(">2 Manage Ordinary User\n");
	printf(">3 Return to Admin Main Menu\n");
	printf("===================================\n");
	printf("\nChoose what to do next\n>");
	scanf("%d", &num);
	system("cls");
	switch(num){
		case 1:
			manageStaff(fixed_id);
			break;
		case 2:
			manageOU(fixed_id);
			break;
		case 3:
			adminMain(fixed_id);
			break;
		default:
			printf("Invalid input");
			manageAccount(fixed_id);
	}
}

void manageStaff(int fixed_id){
	int num;
	
	printf("===================================\n");
	printf(">Manage Staff\n");
	printf("===================================\n");
	printf(">1 List All Staff\n");
	printf(">2 Add New Staff\n");
	printf(">3 Edit Staff Details\n");
	printf(">4 Return to Account Management\n");
	printf("===================================\n");
	printf("\nChoose what to do next\n>");
	scanf("%d", &num);
	system("cls");
	switch(num){
		case 1:
			staffList(fixed_id);
			break;
		case 2:
			addStaff(fixed_id);
			break;
		case 3:
			editStaff(fixed_id);
			break;
		case 4:
			manageAccount(fixed_id);
			break;
		default:
			printf("Invalid input");
			manageStaff(fixed_id);
	}
}

void staffList(int fixed_id){
	char fname[25], lname[25], email[25], pass[25], role[25];
	int staff_id, is_deleted = 0, confirm = 0, num;
	char buffer[1025];
	FILE *fp;
	fp = fopen("accountDB.txt", "r");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("====================\n");
	printf(">List of all Staff\n");
	printf("====================\n\n");
	int row = 0;
	int column = 0;
	printf(">ID\tFirstName\tFamilyName\tEmail\t\t\t    Password\t\tRole\t\t\n");
		
	while (fgets(buffer,1025, fp)) {
		column = 0;
		row++;
		confirm = 0;
		char* token = strtok(buffer, ", ");
			
		while (token) {
			// ID
			if (column == 0) {
				staff_id = atoi(token);
				confirm++;
			}

			// firstname
			if (column == 1) {
				strcpy(fname, token);
				confirm++;
			}

			// lastname
			if (column == 2) {
				strcpy(lname, token);
				confirm++;
			}
			// email
			if (column == 3) {
				strcpy(email, token);
				confirm++;
			}

			// password
			if (column == 4) {
				strcpy(pass, token);
				confirm++;
			}
			// role
			if (column == 5) {
				strcpy(role, token);
				confirm++;
			}
			//is_deleted
			if (column == 6) {
				is_deleted = atoi(token);
				confirm++;
			}
				
			if(confirm == 7){
				if(strcmp(role, "Staff") == 0 && is_deleted == 0){
					printf(">%-6d %-15s %-15s %-27s %-15s \t%-15s\n", staff_id, fname, lname, email, pass, role);
				}	
			}
			token = strtok(NULL, ", ");
			column++;
		}
	}
	fclose(fp);
	
	printf("\n\n===========================\n");
	printf(">1 Go back to Manage Staff\n");
	printf(">2 Exit\n");
	printf("===========================\n");
	printf(">Choose what to do next\n>");
	scanf("%d", &num);
	system("cls");
	if(num == 1){
		manageStaff(fixed_id);
	} else if(num == 2){
		exit(0);
	} else {
		printf("Invalid input!");
		exit(0);
	}
}

void addStaff(fixed_id){
	Account info;
	int i, id = 1, is_deleted = 0;
	char cpass[25], role[6] = "Staff", c;
	FILE *fp;
	fp = fopen("accountDB.txt", "a+");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fflush(stdin);
	printf("================\n");
	printf(">Add New Staff\n");
	printf("================\n");
	printf("\n>Enter First Name:\n>");
	gets(info.fname);
	printf("\n>Enter Last name:\n>");
	gets(info.lname);
	printf("\n>Enter Email:\n>");
	gets(info.email);
	printf("\n>Enter Password:\n>");
	gets(info.pass);
	printf("\n>Re-Enter Password:\n>");
	gets(cpass);
	fflush(stdin);
	system("cls");
	
	//generating id 
	for (c = getc(fp); c != EOF; c = getc(fp)){
		if(c == '\n'){
			id++;
		}
	}
	
	if(strcmp(info.pass, cpass) == 0){
		fprintf(fp, "%d, %s, %s, %s, %s, %s, %d\n", id, info.fname, info.lname, info.email, info.pass, role, is_deleted);
		fclose(fp);
		printf("Added successfully!\n");sleep(1);
		for(i = 0; i < 1; i++){
			printf("Redirecting you back to Manage Staff screen");
			printf(".");sleep(1);
			printf(".");sleep(1);
			printf(".\n");sleep(1);
			system("cls");
		}
		manageStaff(id);
	} else {
		fclose(fp);
		printf("Passwords do not match!\n");sleep(1);
		for(i = 0; i < 1; i++){
			printf("Redirecting you back to Manage Staff screen");
			printf(".");sleep(1);
			printf(".");sleep(1);
			printf(".\n");sleep(1);
			system("cls");
		}
		manageStaff(id);	
	}
}

void editStaff(fixed_id){
	int i, num, staff_id, row = 0, column = 0, confirm = 0, confirmation = 0, id, count, line, is_deleted;
	FILE *fp, *fptr, *fptr1, *fptr2, *fptr3;
	char newPass1[25], newPass2[25], buffer[1025], temp[1025], *token, pass[25];
	char str[255] = "", fname[25], lname[25], email[25], role[25], str_id[255], str_isDeleted[255];
	char new_fname[25], new_lname[25], new_email[25];
	
	fp = fopen("accountDB.txt", "r");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fptr1 = fopen("accountDB.txt", "r");
	if(fptr1 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fptr2 = fopen("tempEditStaff.txt", "w");
	if(fptr2 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("=====================\n");
	printf(">Edit Staff Details\n");
	printf("=====================\n\n");
	printf(">List of All Staff\n");
	printf("=====================\n\n");
	row = 0;
	column = 0;
	printf(">ID\tFirstName\tFamilyName\tEmail\t\t\t    Password\t\tRole\n");
	
	row = 0;	
	while (fgets(buffer,1025, fp)) {
		column = 0;
		row++;
		confirm = 0;
		char* token = strtok(buffer, ", ");
			
		while (token) {
			// ID
			if (column == 0) {
				staff_id = atoi(token);
				confirm++;
			}
			// firstname
			if (column == 1) {
				strcpy(fname, token);
				confirm++;
			}
			// lastname
			if (column == 2) {
				strcpy(lname, token);
				confirm++;
			}
			// email
			if (column == 3) {
				strcpy(email, token);
				confirm++;
			}
			// password
			if (column == 4) {
				strcpy(pass, token);
				confirm++;
			}
			// role
			if (column == 5) {
				strcpy(role, token);
				confirm++;
			}
			//is_deleted
			if (column == 6) {
				is_deleted = atoi(token);
				confirm++;
			}
				
			if(confirm == 7){
				if(strcmp(role, "Staff") == 0 && is_deleted == 0){
					printf(">%-6d %-15s %-15s %-27s %-15s \t%-15s\n", staff_id, fname, lname, email, pass, role);
				}	
			}
			token = strtok(NULL, ", ");
			column++;
		}
	}
	fclose(fp);
	
	fptr = fopen("accountDB.txt", "r");
	if(fptr == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("\n\n===================================\n");
	printf(">Choose Staff to Edit(Enter the ID)\n");
	printf(">");
	scanf("%d", &staff_id);
	fflush(stdin);
	
	row = 0;
	while(fgets(temp, 1025, fptr)){
		column = 0;
		row++;
		confirm = 0;
		
		char *value = strtok(temp, ", ");
		while(value){
			// ID
			if(column == 0){
				id = atoi(value);
				if(staff_id == id){
					confirm++;
				} else {
					break;
				}
				
			}
			// firstname
			if (column == 1) {
				strcpy(fname, value);
				confirm++;
			}
			// lastname
			if (column == 2) {
				strcpy(lname, value);
				confirm++;
			}
			// email
			if (column == 3) {
				strcpy(email, value);
				confirm++;
			}
			// pass
			if (column == 4) {
				strcpy(pass, value);
				confirm++;
			}
			// role
			if (column == 5) {
				strcpy(role, value);
				confirm++;
			}
			// is_deleted
			if (column == 6) {
				is_deleted = atoi(value);
				confirm++;
			}
			if(confirm == 7){
				break;
			}
			value = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 7){
			break;
		}
	}
	fclose(fptr);
	
	printf("\n\n===================================\n");
	printf(">New First Name: %s", fname);
	printf("\n>");
	gets(new_fname);
	printf(">New Last Name: %s", lname);
	printf("\n>");
	gets(new_lname);
	printf(">New Email: %s", email);
	printf("\n>");
	gets(new_email);
	
	
	
	fptr3 = fopen("accountDB.txt", "r");
	if(fptr3 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	row = 0;
	while(fgets(buffer, 1025, fptr3)){
		confirmation = 0;
		column = 0;
		row++;
		token = strtok(buffer, ", ");
		while(token != NULL){
			if(column == 0){
				id = atoi(token);
				if(id == staff_id){
					line = row;
					confirmation++;
				} else {
					break;
				}
			}
			if(column == 1){
				strcpy(fname, new_fname);
				confirmation++;
			}
			if(column == 2){
				strcpy(lname, new_lname);
				confirmation++;
			}
			if(column == 3){
				strcpy(email, new_email);
				confirmation++;
			}
			if(column == 4){
				strcpy(pass, token);
				confirmation++;
			}
			if(column == 5){
				strcpy(role, token);
				confirmation++;
			}
			if(column == 6){
				is_deleted = atoi(token);
				confirmation++;
			}
			if(confirmation == 7 && is_deleted == 0){
				break;
			}
			token = strtok(NULL, ", ");
			column++;
		}
		if(confirmation == 7 && is_deleted == 0){
			break;
		}
	}
	if(confirmation == 7 && is_deleted == 0){
		itoa(id, str_id, 10);
		itoa(is_deleted, str_isDeleted, 10);
		strcat(str, str_id);
		strcat(str, ", ");
		strcat(str, fname);
		strcat(str, ", ");
		strcat(str, lname);
		strcat(str, ", ");
		strcat(str, email);
		strcat(str, ", ");
		strcat(str, pass);
		strcat(str, ", ");
		strcat(str, role);
		strcat(str, ", ");
		strcat(str, str_isDeleted);
		strcat(str, "\n");
	}
	fclose(fptr3);
	
	count = 0;
	while((fgets(temp, 1025, fptr1)) != NULL){
	    count++;
	
		if (count == line){
			fputs(str, fptr2);
		} else {
			fputs(temp, fptr2);
		}
	}
		
	fclose(fptr1);
	fclose(fptr2);
		
	remove("accountDB.txt");
	int check = rename("tempEditStaff.txt", "accountDB.txt");
	
	system("cls");
	if(!check){
		printf("Successfully edited the staff!\n");sleep(1);
		for(i = 0; i < 1; i++){
			printf("Redirecting you to Manage Staff screen!");
			printf(".");sleep(1);
			printf(".");sleep(1);
			printf(".\n");sleep(1);
			system("cls");
		}
		manageStaff(fixed_id);
	} else {
		printf("Failed to edit the staff!\n");sleep(1);
		for(i = 0; i < 1; i++){
			printf("Redirecting you to Manage Staff screen!");
			printf(".");sleep(1);
			printf(".");sleep(1);
			printf(".\n");sleep(1);
			system("cls");
		}
		manageStaff(fixed_id);
	}
}

void manageOU(int fixed_id){
	int num;
	
	printf("===================================\n");
	printf(">Manage Ordinary User\n");
	printf("===================================\n");
	printf(">1 List all Ordinary User\n");
	printf(">2 Edit Ordinary User Details\n");
	printf(">3 Return to Account Management\n");
	printf("===================================\n");
	printf("\nChoose what to do next\n>");
	scanf("%d", &num);
	system("cls");
	switch(num){
		case 1:
			listOU(fixed_id);
			break;
		case 2:
			editOU(fixed_id);
			break;
		case 3:
			manageAccount(fixed_id);
			break;
		default:
			printf("Invalid input");
			manageOU(fixed_id);
	}
}

void listOU(int fixed_id){
	char fname[25], lname[25], email[25], pass[25], role[25], status[25];
	int ou_id, is_deleted = 0, confirm = 0, num;
	char buffer[1025];
	FILE *fp;
	fp = fopen("accountDB.txt", "r");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("============================\n");
	printf(">List of all Ordinary User\n");
	printf("============================\n\n");
	int row = 0;
	int column = 0;
	printf(">ID\tFirstName\tFamilyName\tEmail\t\t\t    Password\t\tRole\t\tStatus\n");
		
	while (fgets(buffer,1025, fp)) {
		column = 0;
		row++;
		confirm = 0;
		char* token = strtok(buffer, ", ");
			
		while (token) {
			// ID
			if (column == 0) {
				ou_id = atoi(token);
				confirm++;
			}

			// firstname
			if (column == 1) {
				strcpy(fname, token);
				confirm++;
			}

			// lastname
			if (column == 2) {
				strcpy(lname, token);
				confirm++;
			}
			// email
			if (column == 3) {
				strcpy(email, token);
				confirm++;
			}

			// password
			if (column == 4) {
				strcpy(pass, token);
				confirm++;
			}
			// role
			if (column == 5) {
				strcpy(role, token);
				confirm++;
			}
			//is_deleted
			if (column == 6) {
				is_deleted = atoi(token);
				if(is_deleted == 0){
					strcpy(status, "Enabled");
				} else if(is_deleted == 1){
					strcpy(status, "Disabled");
				}
				confirm++;
			}
				
			if(confirm == 7){
				if(strcmp(role, "OU") == 0){
					printf(">%-6d %-15s %-15s %-27s %-15s \t%-15s %s\n", ou_id, fname, lname, email, pass, role, status);
				}	
			}
			token = strtok(NULL, ", ");
			column++;
		}
	}
	fclose(fp);
	
	printf("\n\n===================================\n");
	printf(">1 Go back to Manage Ordinary User\n");
	printf(">2 Exit\n");
	printf("===================================\n");
	printf(">Choose what to do next\n>");
	scanf("%d", &num);
	system("cls");
	if(num == 1){
		manageOU(fixed_id);
	} else if(num == 2){
		exit(0);
	} else {
		printf("Invalid input!");
		exit(0);
	}
}

void editOU(int fixed_id){
	int i, num, ou_id, row = 0, column = 0, confirm = 0, confirmation = 0, id, count, line, is_deleted;
	FILE *fp, *fptr, *fptr1, *fptr2, *fptr3;
	char fname[25], lname[25], email[25], pass[25], role[25], status[25];
	char new_fname[25], new_lname[25], new_email[25], new_status[25];
	char buffer[1025], temp[1025];
	char str[255] = "", str_id[255], str_isDeleted[255], *token;
	fp = fopen("accountDB.txt", "r");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fptr1 = fopen("accountDB.txt", "r");
	if(fptr1 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fptr2 = fopen("tempEditOU.txt", "w");
	if(fptr2 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("=====================\n");
	printf(">Edit OU Details\n");
	printf("=====================\n\n");
	printf(">List of All OU\n");
	printf("=====================\n\n");
	row = 0;
	column = 0;
	printf(">ID\tFirstName\tFamilyName\tEmail\t\t\t    Password\t\tRole\t\tStatus\n");
		
	while (fgets(buffer,1025, fp)) {
		column = 0;
		row++;
		confirm = 0;
		char* token = strtok(buffer, ", ");
			
		while (token) {
			// ID
			if (column == 0) {
				ou_id = atoi(token);
				confirm++;
			}
			// firstname
			if (column == 1) {
				strcpy(fname, token);
				confirm++;
			}
			// lastname
			if (column == 2) {
				strcpy(lname, token);
				confirm++;
			}
			// email
			if (column == 3) {
				strcpy(email, token);
				confirm++;
			}
			// password
			if (column == 4) {
				strcpy(pass, token);
				confirm++;
			}
			// role
			if (column == 5) {
				strcpy(role, token);
				confirm++;
			}
			//is_deleted
			if (column == 6) {
				is_deleted = atoi(token);
				if(is_deleted == 0){
					strcpy(status, "Enabled");
				} else if(is_deleted == 1){
					strcpy(status, "Disabled");
				}
				confirm++;
			}
				
			if(confirm == 7){
				if(strcmp(role, "OU") == 0){
					printf(">%-6d %-15s %-15s %-27s %-15s \t%-15s %s\n", ou_id, fname, lname, email, pass, role, status);
				}	
			}
			token = strtok(NULL, ", ");
			column++;
		}
	}
	fclose(fp);
	
	fptr = fopen("accountDB.txt", "r");
	if(fptr == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("\n\n===================================\n");
	printf(">Choose OU to Edit(Enter the ID)\n");
	printf(">");
	scanf("%d", &ou_id);
	fflush(stdin);
	
	row = 0;
	while(fgets(temp, 1025, fptr)){
		column = 0;
		row++;
		confirm = 0;
		
		char *value = strtok(temp, ", ");
		while(value){
			// ID
			if(column == 0){
				id = atoi(value);
				if(ou_id == id){
					confirm++;
				} else {
					break;
				}
				
			}
			// firstname
			if (column == 1) {
				strcpy(fname, value);
				confirm++;
			}
			// lastname
			if (column == 2) {
				strcpy(lname, value);
				confirm++;
			}
			// email
			if (column == 3) {
				strcpy(email, value);
				confirm++;
			}
			// pass
			if (column == 4) {
				strcpy(pass, value);
				confirm++;
			}
			// role
			if (column == 5) {
				strcpy(role, value);
				confirm++;
			}
			// is_deleted
			if (column == 6) {
				is_deleted = atoi(value);
				confirm++;
			}
			if(confirm == 7){
				break;
			}
			value = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 7){
			break;
		}
	}
	fclose(fptr);
	
	printf("\n\n===================================\n");
	printf(">New First Name: %s\n>", fname);
	gets(new_fname);
	printf(">New Last Name: %s\n>", lname);
	gets(new_lname);
	printf(">New Email: %s\n>", email);
	gets(new_email);
	printf(">New Status: Enabled/Disabled\n>");
	gets(new_status);
	
//	printf("%s %s %s %s", new_fname, new_lname, new_email, new_status);
	
	
	fptr3 = fopen("accountDB.txt", "r");
	if(fptr3 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	row = 0;
	while(fgets(buffer, 1025, fptr3)){
		confirmation = 0;
		column = 0;
		row++;
		token = strtok(buffer, ", ");
		while(token != NULL){
			if(column == 0){
				id = atoi(token);
				if(id == ou_id){
					line = row;
					confirmation++;
				} else {
					break;
				}
			}
			if(column == 1){
				strcpy(fname, new_fname);
				confirmation++;
			}
			if(column == 2){
				strcpy(lname, new_lname);
				confirmation++;
			}
			if(column == 3){
				strcpy(email, new_email);
				confirmation++;
			}
			if(column == 4){
				strcpy(pass, token);
				confirmation++;
			}
			if(column == 5){
				strcpy(role, token);
				confirmation++;
			}
			if(column == 6){
				//is_deleted = atoi(token);
				strcpy(status, new_status);
				if(strcmp(status, "Enabled") == 0){
					is_deleted = 0;
				} else if(strcmp(status, "Disabled") == 0){
					is_deleted = 1;
				}
				confirmation++;
			}
			if(confirmation == 7){
				break;
			}
			token = strtok(NULL, ", ");
			column++;
		}
		if(confirmation == 7){
			break;
		}
	}
	if(confirmation == 7){
		itoa(id, str_id, 10);
		itoa(is_deleted, str_isDeleted, 10);
		strcat(str, str_id);
		strcat(str, ", ");
		strcat(str, fname);
		strcat(str, ", ");
		strcat(str, lname);
		strcat(str, ", ");
		strcat(str, email);
		strcat(str, ", ");
		strcat(str, pass);
		strcat(str, ", ");
		strcat(str, role);
		strcat(str, ", ");
		strcat(str, str_isDeleted);
		strcat(str, "\n");
	}
	fclose(fptr3);
	
	count = 0;
	while((fgets(temp, 1025, fptr1)) != NULL){
	    count++;
	
		if (count == line){
			fputs(str, fptr2);
		} else {
			fputs(temp, fptr2);
		}
	}
		
	fclose(fptr1);
	fclose(fptr2);
		
	remove("accountDB.txt");
	int check = rename("tempEditOU.txt", "accountDB.txt");
	
	system("cls");
	if(!check){
		printf("Successfully edited the user!\n");sleep(1);
		for(i = 0; i < 1; i++){
			printf("Redirecting you to Manage User screen!");
			printf(".");sleep(1);
			printf(".");sleep(1);
			printf(".\n");sleep(1);
			system("cls");
		}
		manageOU(fixed_id);
	} else {
		printf("Failed to edit the user!\n");sleep(1);
		for(i = 0; i < 1; i++){
			printf("Redirecting you to Manage User screen!");
			printf(".");sleep(1);
			printf(".");sleep(1);
			printf(".\n");sleep(1);
			system("cls");
		}
		manageOU(fixed_id);
	}
}

void manageEquip(int fixed_id){
	int num;
	
	printf("===================================\n");
	printf(">Management Equipment \n");
	printf("===================================\n");
	printf(">1 List of all Equipment\n");
	printf(">2 Add New Equipment\n");
	printf(">3 Edit Equipment\n");
	printf(">4 Delete Equipment\n");
	printf(">5 Return to Admin Main Menu\n");
	printf("===================================\n");
	printf("\nChoose what to do next\n>");
	scanf("%d", &num);
	system("cls");
	switch(num){
		case 1:
			equipList(fixed_id);
			break;
		case 2:
			addEquip(fixed_id);
			break;
		case 3:
			editEquip(fixed_id);
			break;
		case 4:
			deleteEquip(fixed_id);
			break;
		case 5:
			adminMain(fixed_id);
			break;
		default:
			printf("Invalid input");
			adminMain(fixed_id);
	}
}

void equipList(int fixed_id){
	char equip_name[25], equip_status[25], equip_availability[25];
	int equip_id, quantity, confirm = 0, num, is_deleted;
	char buffer[1025];
	FILE *fp;
	fp = fopen("equipmentDB.txt", "r");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("========================\n");
	printf(">List of all Equipment\n");
	printf("========================\n\n");
	int row = 0;
	int column = 0;
	printf(">ID\tEquipment Name\t\tEquipment Status\tQuantity\t\tAvailability\n");
	printf("=============================================================================================\n");
	
	while (fgets(buffer,1025, fp)) {
		column = 0;
		row++;
		confirm = 0;
		char* token = strtok(buffer, ", ");
			
		while (token) {
			// ID
			if (column == 0) {
				equip_id = atoi(token);
				confirm++;
			}

			// equipment name
			if (column == 1) {
				strcpy(equip_name, token);
				confirm++;
			}

			// equipment status
			if (column == 2) {
				strcpy(equip_status, token);
				confirm++;
			}
			// quantity
			if (column == 3) {
				quantity = atoi(token);
				confirm++;
			}
			//availability
			if (column == 4) {
				strcpy(equip_availability, token);
				confirm++;
			}
			// is_deleted
			if (column == 5) {
				is_deleted = atoi(token);
				confirm++;
			}
	
			token = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 6 && is_deleted == 0){
			printf(">%-6d %-23s %-23s %-23d %-15s\n", equip_id, equip_name, equip_status, quantity, equip_availability);	
		}
	}
	fclose(fp);
	
	printf("\n\n===================================\n");
	printf(">1 Go back to Manage Equipment\n");
	printf(">2 Exit\n");
	printf("===================================\n");
	printf(">Choose what to do next\n>");
	scanf("%d", &num);
	system("cls");
	if(num == 1){
		manageEquip(fixed_id);
	} else if(num == 2){
		exit(0);
	} else {
		printf("Invalid input!");
		exit(0);
	}
}

void addEquip(int fixed_id){
	int i, id = 1, is_deleted = 0, equip_quantity, wordExist = 0;
	char equip_name[25], equip_status[25], equip_availability[25], c;
	char buffer[1025];
	FILE *fp;
	FILE *fptr;
	fp = fopen("equipmentDB.txt", "a+");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	fptr = fopen("equipmentDB.txt", "r");
	if(fptr == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fflush(stdin);
	printf("====================\n");
	printf(">Add New Equipment\n");
	printf("====================\n");
	printf("\n>Enter Equipment Name:\n>");
	gets(equip_name);
	printf("\n>Enter Equipment Status:(Good, Broken)\n>");
	gets(equip_status);
	printf("\n>Enter Quantity:\n>");
	scanf("%d", &equip_quantity);
	fflush(stdin);
	printf("\n>Enter Availability:(Available, Borrowed)\n>");
	gets(equip_availability);
	fflush(stdin);
	system("cls");
	
	//generating id 
	for (c = getc(fp); c != EOF; c = getc(fp)){
		if(c == '\n'){
			id++;
		}
	}
	
	//checks if equipment already exist
	while(fgets(buffer, 1025, fptr)){
		char *ptr = strstr(buffer, equip_name);
		if(ptr != NULL){
			wordExist = 1;
			break;
		}
	}
	fclose(fptr);
	
	if(wordExist == 0){
		fprintf(fp, "%d, %s, %s, %d, %s, %d\n", id, equip_name, equip_status, equip_quantity, equip_availability, is_deleted);
		fclose(fp);
		printf("Added successfully!\n");sleep(1);
		for(i = 0; i < 1; i++){
			printf("Redirecting you back to Manage Equipment screen");
			printf(".");sleep(1);
			printf(".");sleep(1);
			printf(".\n");sleep(1);
			system("cls");
		}
		manageEquip(fixed_id);
	} else {
		printf("Equipment already exists!\n");sleep(1);
		for(i = 0; i < 1; i++){
			printf("Redirecting you back to Manage Equipment screen");
			printf(".");sleep(1);
			printf(".");sleep(1);
			printf(".\n");sleep(1);
			system("cls");
		}
		manageEquip(fixed_id);
	}
}

void editEquip(int fixed_id){
	int i, num, equip_id, row = 0, column = 0, confirm = 0, confirmation = 0, id, count, line, is_deleted;
	int quantity, new_quantity;
	FILE *fp, *fptr, *fptr1, *fptr2, *fptr3;
	char equip_name[25], equip_status[25], equip_availability[25];
	char new_name[25], new_status[25], new_availability[25];
	char buffer[1025], temp[1025];
	char str[255] = "", str_id[255], str_isDeleted[255], *token, str_quantity[255];
	fp = fopen("equipmentDB.txt", "r");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fptr1 = fopen("equipmentDB.txt", "r");
	if(fptr1 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fptr2 = fopen("tempEditEquip.txt", "w");
	if(fptr2 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("=====================\n");
	printf(">Edit Equipment\n");
	printf("=====================\n\n");
	row = 0;
	column = 0;
	printf(">ID\tEquipment Name\t\tEquipment Status\tQuantity\t\tAvailability\n");
	printf("=============================================================================================\n");
		
	while (fgets(buffer,1025, fp)) {
		column = 0;
		row++;
		confirm = 0;
		char* token = strtok(buffer, ", ");
			
		while (token) {
			// ID
			if (column == 0) {
				equip_id = atoi(token);
				confirm++;
			}

			// equipment name
			if (column == 1) {
				strcpy(equip_name, token);
				confirm++;
			}

			// equipment status
			if (column == 2) {
				strcpy(equip_status, token);
				confirm++;
			}
			// quantity
			if (column == 3) {
				quantity = atoi(token);
				confirm++;
			}

			//availability
			if (column == 4) {
				strcpy(equip_availability, token);
				confirm++;
			}
	
			token = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 5){
			printf(">%-6d %-23s %-23s %-23d %-15s\n", equip_id, equip_name, equip_status, quantity, equip_availability);	
		}
	}
	fclose(fp);
	
	fptr = fopen("equipmentDB.txt", "r");
	if(fptr == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("\n\n===================================\n");
	printf(">Choose Equipment to Edit(Enter the ID)\n");
	printf(">");
	scanf("%d", &equip_id);
	fflush(stdin);
	
	while(fgets(temp, 1025, fptr)){
		column = 0;
		row++;
		confirm = 0;
		
		char *value = strtok(temp, ", ");
		while(value){
			// ID
			if(column == 0){
				id = atoi(value);
				if(equip_id == id){
					confirm++;
				} else {
					break;
				}
				
			}
			// equip name
			if (column == 1) {
				strcpy(equip_name, value);
				confirm++;
			}
			// equip status
			if (column == 2) {
				strcpy(equip_status, value);
				confirm++;
			}
			// quantity
			if (column == 3) {
				quantity = atoi(value);
				confirm++;
			}
			// equip availability
			if (column == 4) {
				strcpy(equip_availability, value);
				confirm++;
			}
			// is_deleted
			if (column == 5) {
				is_deleted = atoi(value);
				confirm++;
			}
			if(confirm == 6){
				break;
			}
			value = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 6){
			break;
		}
	}
	
	printf("\n\n===================================\n");
	printf(">Enter Equipment Name:\n>");
	gets(new_name);
	printf(">Enter Equipment Status:\n>");
	gets(new_status);
	printf(">Enter Quantity:\n>");
	scanf("%d", &new_quantity);
	fflush(stdin);
	printf(">Enter Availability:\n>");
	gets(new_availability);
	
//	printf("%s %s %d %s", new_name, new_status, new_quantity, new_availability);
	fclose(fptr);
	
	fptr3 = fopen("equipmentDB.txt", "r");
	if(fptr3 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	row = 0;
	while(fgets(temp, 1025, fptr3)){
		column = 0;
		row++;
		confirm = 0;
		
		char *value = strtok(temp, ", ");
		while(value){
			// ID
			if(column == 0){
				id = atoi(value);
				if(equip_id == id){
					line = row;
					confirm++;
				} else {
					break;
				}
				
			}
			// equip name
			if (column == 1) {
				strcpy(equip_name, new_name);
				confirm++;
			}
			// equip status
			if (column == 2) {
				strcpy(equip_status, new_status);
				confirm++;
			}
			// quantity
			if (column == 3) {
				quantity = new_quantity;
				confirm++;
			}
			// equip availability
			if (column == 4) {
				strcpy(equip_availability, new_availability);
				confirm++;
			}
			// is_deleted
			if (column == 5) {
				is_deleted = atoi(value);
				confirm++;
			}
			if(confirm == 6){
				break;
			}
			value = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 6){
			break;
		}
	}
	if(confirm == 6){
		itoa(id, str_id, 10);
		itoa(is_deleted, str_isDeleted, 10);
		itoa(quantity, str_quantity, 10);
		strcat(str, str_id);
		strcat(str, ", ");
		strcat(str, equip_name);
		strcat(str, ", ");
		strcat(str, equip_status);
		strcat(str, ", ");
		strcat(str, str_quantity);
		strcat(str, ", ");
		strcat(str, equip_availability);
		strcat(str, ", ");
		strcat(str, str_isDeleted);
		strcat(str, "\n");
	}
	fclose(fptr3);
	
	count = 0;
//	puts(str);
//	printf("Line: %d", line);
//	exit(0);
	while((fgets(temp, 1025, fptr1)) != NULL){
	    count++;
	
		if (count == line){
			fputs(str, fptr2);
		} else {
			fputs(temp, fptr2);
		}
	}
		
	fclose(fptr1);
	fclose(fptr2);
		
	remove("equipmentDB.txt");
	int check = rename("tempEditEquip.txt", "equipmentDB.txt");
	
	system("cls");
	if(!check){
		printf("Successfully edited the equipment!\n");sleep(1);
		for(i = 0; i < 1; i++){
			printf("Redirecting you to Manage Equipment screen!");
			printf(".");sleep(1);
			printf(".");sleep(1);
			printf(".\n");sleep(1);
			system("cls");
		}
		manageEquip(fixed_id);
	} else {
		printf("Failed to edit the equipment!\n");sleep(1);
		for(i = 0; i < 1; i++){
			printf("Redirecting you to Manage Equipment screen!");
			printf(".");sleep(1);
			printf(".");sleep(1);
			printf(".\n");sleep(1);
			system("cls");
		}
		manageEquip(fixed_id);
	}
}

void deleteEquip(int fixed_id){
	int i, num, equip_id, row = 0, column = 0, confirm = 0, confirmation = 0, id, count, line, is_deleted;
	int quantity, new_quantity;
	FILE *fp, *fptr, *fptr1, *fptr2, *fptr3;
	char equip_name[25], equip_status[25], equip_availability[25];
	char new_name[25], new_status[25], new_availability[25];
	char buffer[1025], temp[1025];
	char str[255] = "", str_id[255], str_isDeleted[255], *token, str_quantity[255];
	fp = fopen("equipmentDB.txt", "r");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fptr1 = fopen("equipmentDB.txt", "r");
	if(fptr1 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fptr2 = fopen("tempDeleteEquip.txt", "w");
	if(fptr2 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("=====================\n");
	printf(">Delete Equipment\n");
	printf("=====================\n\n");
	row = 0;
	column = 0;
	printf(">ID\tEquipment Name\t\tEquipment Status\tQuantity\t\tAvailability\n");
	printf("=============================================================================================\n");
		
	while (fgets(buffer,1025, fp)) {
		column = 0;
		row++;
		confirm = 0;
		token = strtok(buffer, ", ");
			
		while (token) {
			// ID
			if (column == 0) {
				equip_id = atoi(token);
				confirm++;
			}

			// equipment name
			if (column == 1) {
				strcpy(equip_name, token);
				confirm++;
			}

			// equipment status
			if (column == 2) {
				strcpy(equip_status, token);
				confirm++;
			}
			// quantity
			if (column == 3) {
				quantity = atoi(token);
				confirm++;
			}
			//availability
			if (column == 4) {
				strcpy(equip_availability, token);
				confirm++;
			}
			// is_deleted
			if (column == 5) {
				is_deleted = atoi(token);
				confirm++;
			}
	
			token = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 6 && is_deleted == 0){
			printf(">%-6d %-23s %-23s %-23d %-15s\n", equip_id, equip_name, equip_status, quantity, equip_availability);	
		}
	}
	fclose(fp);
	
	printf("\n\n===================================\n");
	printf(">Choose Equipment to Delete(Enter the ID)\n");
	printf(">");
	scanf("%d", &num);
	fflush(stdin);
	
	fptr = fopen("equipmentDB.txt", "r");
	if(fptr == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	row = 0;
	while(fgets(temp, 1025, fptr)){
		column = 0;
		row++;
		confirm = 0;
		
		char *value = strtok(temp, ", ");
		while(value){
			// ID
			if(column == 0){
				id = atoi(value);
				if(num == id){
					line = row;
					confirm++;
				} else {
					break;
				}
				
			}
			// equip name
			if (column == 1) {
				strcpy(equip_name, value);
				confirm++;
			}
			// equip status
			if (column == 2) {
				strcpy(equip_status, value);
				confirm++;
			}
			// quantity
			if (column == 3) {
				quantity = atoi(value);
				confirm++;
			}
			// equip availability
			if (column == 4) {
				strcpy(equip_availability, value);
				confirm++;
			}
			// is_deleted
			if (column == 5) {
				is_deleted = 1;
				confirm++;
			}
			if(confirm == 6){
				break;
			}
			value = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 6){
			break;
		}
	}
	fclose(fptr);
	
	
	fptr3 = fopen("equipmentDB.txt", "r");
	if(fptr3 == NULL){
		printf("Failed to open file.");
		exit(0);
	}

	if(confirm == 6){
		itoa(id, str_id, 10);
		itoa(is_deleted, str_isDeleted, 10);
		itoa(quantity, str_quantity, 10);
		strcat(str, str_id);
		strcat(str, ", ");
		strcat(str, equip_name);
		strcat(str, ", ");
		strcat(str, equip_status);
		strcat(str, ", ");
		strcat(str, str_quantity);
		strcat(str, ", ");
		strcat(str, equip_availability);
		strcat(str, ", ");
		strcat(str, str_isDeleted);
		strcat(str, "\n");
	}
	fclose(fptr3);
	
	count = 0;
//	puts(str);
//	printf("Line: %d", line);
//	exit(0);
	while((fgets(temp, 1025, fptr1)) != NULL){
	    count++;
	
		if (count == line){
			fputs(str, fptr2);
		} else {
			fputs(temp, fptr2);
		}
	}
		
	fclose(fptr1);
	fclose(fptr2);
		
	remove("equipmentDB.txt");
	int check = rename("tempDeleteEquip.txt", "equipmentDB.txt");
	
	system("cls");
	if(!check){
		printf("Successfully deleted the equipment!\n");sleep(1);
		for(i = 0; i < 1; i++){
			printf("Redirecting you to Manage Equipment screen!");
			printf(".");sleep(1);
			printf(".");sleep(1);
			printf(".\n");sleep(1);
			system("cls");
		}
		manageEquip(fixed_id);
	} else {
		printf("Failed to delete the equipment!\n");sleep(1);
		for(i = 0; i < 1; i++){
			printf("Redirecting you to Manage Equipment screen!");
			printf(".");sleep(1);
			printf(".");sleep(1);
			printf(".\n");sleep(1);
			system("cls");
		}
		manageEquip(fixed_id);
	}
}

void changePersonalPass(int fixed_id){
	int i, num, row = 0, column = 0, confirm = 0, confirmation = 0, id, count = 0, line, is_deleted;
	FILE *fp, *fptr, *fp1, *fp2;
	char newPass1[25], newPass2[25], buffer[1025], temp[1025], *token, pass[25];
	char str[255] = "", fname[25], lname[25], email[25], role[25], str_id[255], str_isDeleted[255];
	char temp1[] = "tempChangePersonalPass.txt";	

	fp = fopen("accountDB.txt", "r");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fp1 = fopen("accountDB.txt", "r");
	if(fp1 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fp2 = fopen(temp1, "w");
	if(fp2 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf(">1 Change Personal Password\n");
	printf(">2 Return to Admin Main Menu\n");
	printf("\nChoose what to do next\n>");
	scanf("%d", &num);
	system("cls");
	fflush(stdin);
	if(num == 1){
		printf(">New Password:\n>");
		gets(newPass1);
		printf("\n>Repeat Password:\n>");
		gets(newPass2);
		fflush(stdin);
		
		if(strcmp(newPass1, newPass2) == 0){
			while(fgets(buffer, 1025, fp)){
				confirmation = 0;
				column = 0;
				row++;
				token = strtok(buffer, ", ");
				while(token != NULL){
					if(column == 0){
						id = atoi(token);
						if(id == fixed_id){
							line = row;
							confirmation++;
						} else {
							break;
						}
					}
					if(column == 1){
						strcpy(fname, token);
						confirmation++;
					}
					if(column == 2){
						strcpy(lname, token);
						confirmation++;
					}
					if(column == 3){
						strcpy(email, token);
						confirmation++;
					}
					if(column == 4){
						strcpy(pass, newPass1);
						confirmation++;
					}
					if(column == 5){
						strcpy(role, token);
						confirmation++;
					}
					if(column == 6){
						is_deleted = atoi(token);
						confirmation++;
					}
					if(confirmation == 7 && is_deleted == 0){
						break;
					}
					token = strtok(NULL, ", ");
					column++;
				}
				if(confirmation == 7 && is_deleted == 0){
					break;
				}
			}
			if(confirmation == 7 && is_deleted == 0){
				itoa(id, str_id, 10);
				itoa(is_deleted, str_isDeleted, 10);
				strcat(str, str_id);
				strcat(str, ", ");
				strcat(str, fname);
				strcat(str, ", ");
				strcat(str, lname);
				strcat(str, ", ");
				strcat(str, email);
				strcat(str, ", ");
				strcat(str, newPass1);
				strcat(str, ", ");
				strcat(str, role);
				strcat(str, ", ");
				strcat(str, str_isDeleted);
				strcat(str, "\n");
			}
			fclose(fp);
			
			 while ((fgets(temp, 1025, fp1)) != NULL){
		        count++;
		
		        if (count == line){
		        	fputs(str, fp2);
				} else {
					fputs(temp, fp2);
				}  
		    }
		    fclose(fp1);
		    fclose(fp2);
		
		    remove("accountDB.txt");
		 	rename(temp1, "accountDB.txt");
		    printf("\nSuccessfully changed password!\n");sleep(1);
			for(i = 0; i < 1; i++){
				printf("Redirecting you to Admin Main screen!");
				printf(".");sleep(1);
				printf(".");sleep(1);
				printf(".\n");sleep(1);
				system("cls");
			}
			adminMain(fixed_id);
		} else {
			printf("Passwords do not match!\n");sleep(1);
			for(i = 0; i < 1; i++){
				printf("Please try again!");
				printf(".");sleep(1);
				printf(".");sleep(1);
				printf(".\n");sleep(1);
				system("cls");
			}
			changePersonalPass(fixed_id);
		}
	}  else if(num == 2){
		adminMain(fixed_id);
	} else {
		printf("Invalid input!\n");
		changePersonalPass(fixed_id);
	}
}

void staffMain(int fixed_id){
	int num;
	
	printf("===================================\n");
	printf(">Staff Main Menu\n");
	printf("===================================\n");
	printf(">1 Request for Borrowing Equipment\n");
	printf(">2 Request for Returning Equipment\n");
	printf(">3 Change Personal Password\n");
	printf(">4 Exit\n");
	printf("===================================\n");
	printf("\nChoose what to do next\n>");
	scanf("%d", &num);
	system("cls");
	switch(num){
		case 1:
			reqBorrowEquip(fixed_id);
			break;
		case 2:
			reqReturnEquip(fixed_id);
			break;
		case 3:
			staffChangePPass(fixed_id);
			break;
		case 4:
			exit(0);
			break;
		default:
			printf("Invalid input");
			adminMain(fixed_id);
	}
}

void reqBorrowEquip(int fixed_id){
	char equip_name[25], equip_status[25], equip_availability[25], fname[25], lname[25], status[25];
	int equip_id, quantity, confirm, num, id, is_deleted = 0, status_num, confirm2, row = 0, column = 0;
	char buffer[1025], temp[1025], x, y, ch, str[255], buffer1[1025], str1[255], temp1[1025];
	char str_id[255], str_isDeleted[255], str_quantity[255];
	char new_name[25], new_status[25], new_availability[25];
	int temp_id, ctr = 0, count, line;
	FILE *fp;
	FILE *fptr, *fptr1, *fptr2, *fptr3;
	fp = fopen("request_borrow.txt", "r");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fptr1 = fopen("request_borrow.txt", "r");
	if(fptr1 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fptr2 = fopen("tempReqBorrowEquip.txt", "w");
	if(fptr2 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("====================================\n");
	printf(">List of all Application to Borrow\n");
	printf("====================================\n\n");
	printf(">ID\tEquipment Name\t Equipment Status\tQuantity\tAvailability\t     Borrower\t\tStatus\n");
	printf("=======================================================================================================================\n");
	
	while (fgets(buffer,1025, fp)) {
		column = 0;
		row++;
		confirm = 0;
		char* token = strtok(buffer, ", ");
			
		while (token) {
			// ID
			if (column == 0) {
				equip_id = atoi(token);
				confirm++;
			}

			// equipment name
			if (column == 1) {
				strcpy(equip_name, token);
				confirm++;
			}

			// equipment status
			if (column == 2) {
				strcpy(equip_status, token);
				confirm++;
			}
			// quantity
			if (column == 3) {
				quantity = atoi(token);
				confirm++;
			}
			// availability
			if (column == 4) {
				strcpy(equip_availability, token);
				confirm++;
			}
			// fname borrower
			if (column == 6) {
				strcpy(fname, token);
				confirm++;
			}
			// lname borrower
			if (column == 7) {
				strcpy(lname, token);
				confirm++;
			}
			// status
			if (column == 8) {
				strcpy(status, token);
				confirm++;
			}
	
			token = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 8){
			printf(">%-8d %-18s %-21s %-13d %-18s %s %-10s\t  %s\n", equip_id, equip_name, equip_status, quantity, equip_availability, fname, lname, status);	
		}
	}
	fclose(fp);
	
	fptr = fopen("request_borrow.txt", "r");
	if(fptr == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("\n>Choose what to approve or disapprove by typing the number\n>");
	scanf("%d", &num);
	fflush(stdin);
	
	row = 0;
	while(fgets(temp, 1025, fptr)){
		column = 0;
		row++;
		confirm = 0;
		
		char *value = strtok(temp, ", ");
		while(value){
			// ID
			if(column == 0){
				id = atoi(value);
				if(num == id){
					confirm++;
				} else {
					break;
				}
				
			}
			// equip name
			if (column == 1) {
				strcpy(equip_name, value);
				confirm++;
			}
			// equip status
			if (column == 2) {
				strcpy(equip_status, value);
				confirm++;
			}
			// quantity
			if (column == 3) {
				quantity = atoi(value);
				confirm++;
			}
			// equip availability
			if (column == 4) {
				strcpy(equip_availability, value);
				confirm++;
			}
			// id of the borrower
			if (column == 5) {
				temp_id = atoi(value);
				confirm++;
			}
			// fname
			if (column == 6) {
				strcpy(fname, value);
				confirm++;
			}
			// lname
			if (column == 7) {
				strcpy(lname, value);
				confirm++;
			}
			if(confirm == 8){
				break;
			}
			value = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 8){
			break;
		}
	}
	fclose(fptr);
		
	printf("\n>Approve(Y/N)\n>");
	scanf("%c", &x);
	fflush(stdin);
	
	FILE *fileptr;
	fileptr = fopen("borrowed_equip.txt", "a+");
	if(fileptr == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	FILE *fileptr1;
	fileptr1 = fopen("equipmentDB.txt", "r");
	if(fileptr1 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	
	if(confirm == 8 && x == 'Y'){
		fprintf(fileptr,"%d, %s, %s, %d, %s, %d, %s, %s, 2\n", id, equip_name, equip_status, quantity, equip_availability, temp_id, fname, lname);
		fclose(fileptr);
		// copy all contents to the temporary file except the specific line	
        while (!feof(fptr1)) 
        {
            strcpy(str, "\0");
            fgets(str, 255, fptr1);
            if (!feof(fptr1)) 
            {
                ctr++;
                /* skip the line at given line number */
                if (ctr != row) 
                {
                    fprintf(fptr2, "%s", str);
                }
            }
        }
        fclose(fptr1);
        fclose(fptr2);
        remove("request_borrow.txt");  		// remove the original file 
        rename("tempReqBorrowEquip.txt", "request_borrow.txt"); 	// rename the temporary file to original name
       
	} else if(confirm == 8 && x == 'N'){
		fprintf(fileptr,"%d, %s, %s, %d, %s, %d, %s, %s, 5\n", id, equip_name, equip_status, quantity, equip_availability, temp_id, fname, lname);
		fclose(fileptr);
		// copy all contents to the temporary file except the specific line	
        while (!feof(fptr1)) 
        {
            strcpy(str, "\0");
            fgets(str, 255, fptr1);
            if (!feof(fptr1)) 
            {
                ctr++;
                /* skip the line at given line number */
                if (ctr != row) 
                {
                    fprintf(fptr2, "%s", str);
                }
            }
        }
        fclose(fptr1);
        fclose(fptr2);
        remove("request_borrow.txt");  		// remove the original file 
        rename("tempReqBorrowEquip.txt", "request_borrow.txt"); 	// rename the temporary file to original name
			        
        row = 0;
        while (fgets(buffer1,1025, fileptr1)) {
			column = 0;
			row++;
			confirm = 0;
			char* token = strtok(buffer1, ", ");
				
			while (token) {
				// ID
				if (column == 0) {
					id = atoi(token);
					if(id == num){
						line = row;
						confirm++;
					} else {
						break;
					}
				}
				// equipment name
				if (column == 1) {
					strcpy(equip_name, token);
					confirm++;
				}
				// equipment status
				if (column == 2) {
					strcpy(equip_status, token);
					confirm++;
				}
				// quantity
				if (column == 3) {
					quantity = atoi(token);
					quantity++;
					confirm++;
				}
				//availability
				if (column == 4) {
					strcpy(equip_availability, token);
					confirm++;
				}
				// is_deleted
				if (column == 5) {
					is_deleted = atoi(token);
					confirm++;
				}
				if(confirm == 6){
					break;
				}
				token = strtok(NULL, ", ");
				column++;
			}
			if(confirm == 6){
				break;
			}
		}
		if(confirm == 6){
		itoa(id, str_id, 10);
		itoa(is_deleted, str_isDeleted, 10);
		itoa(quantity, str_quantity, 10);
		strcat(str1, str_id);
		strcat(str1, ", ");
		strcat(str1, equip_name);
		strcat(str1, ", ");
		strcat(str1, equip_status);
		strcat(str1, ", ");
		strcat(str1, str_quantity);
		strcat(str1, ", ");
		strcat(str1, equip_availability);
		strcat(str1, ", ");
		strcat(str1, str_isDeleted);
		strcat(str1, "\n");
	}
		fclose(fileptr1);
		
		FILE *fileptr2;
		fileptr2 = fopen("equipmentDB.txt", "r");
		if(fileptr2 == NULL){
			printf("Failed to open file.");
			exit(0);
		}
		
		fptr3 = fopen("tempEquipDB.txt", "w");
		if(fptr3 == NULL){
			printf("Failed to open file.");
			exit(0);
		}
		
		count = 0;
		while((fgets(temp1, 1025, fileptr2)) != NULL){
		    count++;
		
			if (count == line){
				fputs(str1, fptr3);
			} else {
				fputs(temp1, fptr3);
			}
		}
        fclose(fileptr2);
        fclose(fptr3);
        remove("equipmentDB.txt");  
        rename("tempEquipDB.txt", "equipmentDB.txt");
	} else {
		printf("Invalid input");
		exit(0);
	}
	
	printf("\n>Do you want to approve or disapprove another one?(Y/N)\n>");
	scanf("%c", &y);
	fflush(stdin);
	system("cls");
	if(y == 'Y'){
		reqBorrowEquip(fixed_id);
	} else if(y == 'N'){
		staffMain(fixed_id);
	} else {
		printf("Invalid input");
		exit(0);
	}
}

void reqReturnEquip(int fixed_id){
	char equip_name[25], equip_status[25], equip_availability[25], fname[25], lname[25], status[25];
	int equip_id, quantity, confirm, num, id, is_deleted = 0, status_num, confirm2, row = 0, column = 0;
	char buffer[1025], temp[1025], x, y, ch, str[255];
	char str_id[255], str_isDeleted[255], str_quantity[255], buffer1[1025], str1[255], temp1[1025];
	char new_name[25], new_status[25], new_availability[25];
	int temp_id, ctr = 0, count, line;
	FILE *fp;
	FILE *fptr, *fptr1, *fptr2;;
	fp = fopen("request_return.txt", "r");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fptr1 = fopen("request_return.txt", "r");
	if(fptr1 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fptr2 = fopen("tempReqReturnEquip.txt", "w");
	if(fptr2 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("====================================\n");
	printf(">List of all Application to Return\n");
	printf("====================================\n\n");
	printf(">ID\tEquipment Name\t Equipment Status\tQuantity\tAvailability\t     Borrower\t\tStatus\n");
	printf("=======================================================================================================================\n");
	
	while (fgets(buffer,1025, fp)) {
		column = 0;
		row++;
		confirm = 0;
		char* token = strtok(buffer, ", ");
			
		while (token) {
			// ID
			if (column == 0) {
				equip_id = atoi(token);
				confirm++;
			}

			// equipment name
			if (column == 1) {
				strcpy(equip_name, token);
				confirm++;
			}

			// equipment status
			if (column == 2) {
				strcpy(equip_status, token);
				confirm++;
			}
			// quantity
			if (column == 3) {
				quantity = atoi(token);
				confirm++;
			}
			// availability
			if (column == 4) {
				strcpy(equip_availability, token);
				confirm++;
			}
			// fname borrower
			if (column == 6) {
				strcpy(fname, token);
				confirm++;
			}
			// lname borrower
			if (column == 7) {
				strcpy(lname, token);
				confirm++;
			}
			// status
			if (column == 8) {
				strcpy(status, token);
				confirm++;
			}
	
			token = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 8){
			printf(">%-8d %-18s %-21s %-13d %-18s %s %-10s\t  %s\n", equip_id, equip_name, equip_status, quantity, equip_availability, fname, lname, status);	
		}
	}
	fclose(fp);
	
	fptr = fopen("request_return.txt", "r");
	if(fptr == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("\n>Choose what to approve or disapprove by typing the number\n>");
	scanf("%d", &num);
	fflush(stdin);
	
	row = 0;
	while(fgets(temp, 1025, fptr)){
		column = 0;
		row++;
		confirm = 0;
		
		char *value = strtok(temp, ", ");
		while(value){
			// ID
			if(column == 0){
				id = atoi(value);
				if(num == id){
					confirm++;
				} else {
					break;
				}
				
			}
			// equip name
			if (column == 1) {
				strcpy(equip_name, value);
				confirm++;
			}
			// equip status
			if (column == 2) {
				strcpy(equip_status, value);
				confirm++;
			}
			// quantity
			if (column == 3) {
				quantity = atoi(value);
				confirm++;
			}
			// equip availability
			if (column == 4) {
				strcpy(equip_availability, value);
				confirm++;
			}
			// id of the borrower
			if (column == 5) {
				temp_id = atoi(value);
				confirm++;
			}
			// fname
			if (column == 6) {
				strcpy(fname, value);
				confirm++;
			}
			// lname
			if (column == 7) {
				strcpy(lname, value);
				confirm++;
			}
			if(confirm == 8){
				break;
			}
			value = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 8){
			break;
		}
	}
	fclose(fptr);
		
	printf("\n>Approve(Y/N)\n>");
	scanf("%c", &x);
	fflush(stdin);
	
	FILE *fileptr;
	fileptr = fopen("returned_equip.txt", "a+");
	if(fileptr == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	FILE *fileptr1;
	fileptr1 = fopen("equipmentDB.txt", "r");
	if(fileptr1 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	if(confirm == 8 && x == 'Y'){
		fprintf(fileptr,"%d, %s, %s, %d, %s, %d, %s, %s, 4\n", id, equip_name, equip_status, quantity, equip_availability, temp_id, fname, lname);
		fclose(fileptr);
		// copy all contents to the temporary file except the specific line	
        while (!feof(fptr1)) 
        {
            strcpy(str, "\0");
            fgets(str, 255, fptr1);
            if (!feof(fptr1)) 
            {
                ctr++;
                /* skip the line at given line number */
                if (ctr != row) 
                {
                    fprintf(fptr2, "%s", str);
                }
            }
        }
        fclose(fptr1);
        fclose(fptr2);
        remove("request_return.txt");  		// remove the original file 
        rename("tempReqReturnEquip.txt", "request_return.txt"); 	// rename the temporary file to original name
	
		row = 0;
        while (fgets(buffer1,1025, fileptr1)) {
			column = 0;
			row++;
			confirm = 0;
			char* token = strtok(buffer1, ", ");
				
			while (token) {
				// ID
				if (column == 0) {
					id = atoi(token);
					if(id == num){
						line = row;
						confirm++;
					} else {
						break;
					}
				}
				// equipment name
				if (column == 1) {
					strcpy(equip_name, token);
					confirm++;
				}
				// equipment status
				if (column == 2) {
					strcpy(equip_status, token);
					confirm++;
				}
				// quantity
				if (column == 3) {
					quantity = atoi(token);
					quantity++;
					confirm++;
				}
				//availability
				if (column == 4) {
					strcpy(equip_availability, token);
					confirm++;
				}
				// is_deleted
				if (column == 5) {
					is_deleted = atoi(token);
					confirm++;
				}
				if(confirm == 6){
					break;
				}
				token = strtok(NULL, ", ");
				column++;
			}
			if(confirm == 6){
				break;
			}
		}
		if(confirm == 6){
		itoa(id, str_id, 10);
		itoa(is_deleted, str_isDeleted, 10);
		itoa(quantity, str_quantity, 10);
		strcat(str1, str_id);
		strcat(str1, ", ");
		strcat(str1, equip_name);
		strcat(str1, ", ");
		strcat(str1, equip_status);
		strcat(str1, ", ");
		strcat(str1, str_quantity);
		strcat(str1, ", ");
		strcat(str1, equip_availability);
		strcat(str1, ", ");
		strcat(str1, str_isDeleted);
		strcat(str1, "\n");
	}
		fclose(fileptr1);
		
		FILE *fileptr2;
		fileptr2 = fopen("equipmentDB.txt", "r");
		if(fileptr2 == NULL){
			printf("Failed to open file.");
			exit(0);
		}
		
		FILE *fptr3;
		fptr3 = fopen("tempReqRetDB.txt", "w");
		if(fptr3 == NULL){
			printf("Failed to open file.");
			exit(0);
		}
		
		count = 0;
		while((fgets(temp1, 1025, fileptr2)) != NULL){
		    count++;
		
			if (count == line){
				fputs(str1, fptr3);
			} else {
				fputs(temp1, fptr3);
			}
		}
        fclose(fileptr2);
        fclose(fptr3);
        remove("equipmentDB.txt");  
        rename("tempReqRetDB.txt", "equipmentDB.txt");
	} else if(confirm == 8 && x == 'N'){
		fprintf(fileptr,"%d, %s, %s, %d, %s, %d, %s, %s, 6\n", id, equip_name, equip_status, quantity, equip_availability, temp_id, fname, lname);
		fclose(fileptr);
		// copy all contents to the temporary file except the specific line	
        while (!feof(fptr1)) 
        {
            strcpy(str, "\0");
            fgets(str, 255, fptr1);
            if (!feof(fptr1)) 
            {
                ctr++;
                /* skip the line at given line number */
                if (ctr != row) 
                {
                    fprintf(fptr2, "%s", str);
                }
            }
        }
        fclose(fptr1);
        fclose(fptr2);
        remove("request_return.txt");  		// remove the original file 
        rename("tempReqReturnEquip.txt", "request_return.txt"); 	// rename the temporary file to original name
	} else {
		printf("Invalid input");
		exit(0);
	}
	
	printf("\n>Do you want to approve or disapprove another one?(Y/N)\n>");
	scanf("%c", &y);
	fflush(stdin);
	system("cls");
	if(y == 'Y'){
		reqBorrowEquip(fixed_id);
	} else if(y == 'N'){
		staffMain(fixed_id);
	} else {
		printf("Invalid input");
		exit(0);
	}
}

void staffChangePPass(int fixed_id){
	int i, num, row = 0, column = 0, confirm = 0, confirmation = 0, id, count = 0, line, is_deleted;
	FILE *fp, *fptr, *fp1, *fp2;
	char newPass1[25], newPass2[25], buffer[1025], temp[1025], *token, pass[25];
	char str[255] = "", fname[25], lname[25], email[25], role[25], str_id[255], str_isDeleted[255];
	char temp1[] = "tempStaffChangePPass.txt";	

	fp = fopen("accountDB.txt", "r");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fp1 = fopen("accountDB.txt", "r");
	if(fp1 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fp2 = fopen(temp1, "w");
	if(fp2 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf(">1 Change Personal Password\n");
	printf(">2 Return to Staff Main Menu\n");
	printf("\nChoose what to do next\n>");
	scanf("%d", &num);
	system("cls");
	fflush(stdin);
	if(num == 1){
		printf(">New Password:\n>");
		gets(newPass1);
		printf("\n>Repeat Password:\n>");
		gets(newPass2);
		fflush(stdin);
		
		if(strcmp(newPass1, newPass2) == 0){
			while(fgets(buffer, 1025, fp)){
				confirmation = 0;
				column = 0;
				row++;
				token = strtok(buffer, ", ");
				while(token != NULL){
					if(column == 0){
						id = atoi(token);
						if(id == fixed_id){
							line = row;
							confirmation++;
						} else {
							break;
						}
					}
					if(column == 1){
						strcpy(fname, token);
						confirmation++;
					}
					if(column == 2){
						strcpy(lname, token);
						confirmation++;
					}
					if(column == 3){
						strcpy(email, token);
						confirmation++;
					}
					if(column == 4){
						strcpy(pass, newPass1);
						confirmation++;
					}
					if(column == 5){
						strcpy(role, token);
						confirmation++;
					}
					if(column == 6){
						is_deleted = atoi(token);
						confirmation++;
					}
					if(confirmation == 7 && is_deleted == 0){
						break;
					}
					token = strtok(NULL, ", ");
					column++;
				}
				if(confirmation == 7 && is_deleted == 0){
					break;
				}
			}
			if(confirmation == 7 && is_deleted == 0){
				itoa(id, str_id, 10);
				itoa(is_deleted, str_isDeleted, 10);
				strcat(str, str_id);
				strcat(str, ", ");
				strcat(str, fname);
				strcat(str, ", ");
				strcat(str, lname);
				strcat(str, ", ");
				strcat(str, email);
				strcat(str, ", ");
				strcat(str, newPass1);
				strcat(str, ", ");
				strcat(str, role);
				strcat(str, ", ");
				strcat(str, str_isDeleted);
				strcat(str, "\n");
			}
			fclose(fp);
			
			 while ((fgets(temp, 1025, fp1)) != NULL){
		        count++;
		
		        if (count == line)
		            fputs(str, fp2);
		        else
		            fputs(temp, fp2);
		    }
		    fclose(fp1);
		    fclose(fp2);
		
		    remove("accountDB.txt");
		 	rename(temp1, "accountDB.txt");
		    printf("\nSuccessfully changed password!\n");sleep(1);
			for(i = 0; i < 1; i++){
				printf("Redirecting you to Staff Main screen!");
				printf(".");sleep(1);
				printf(".");sleep(1);
				printf(".\n");sleep(1);
				system("cls");
			}
			staffMain(fixed_id);
		} else {
			printf("Passwords do not match!\n");sleep(1);
			for(i = 0; i < 1; i++){
				printf("Please try again!");
				printf(".");sleep(1);
				printf(".");sleep(1);
				printf(".\n");sleep(1);
				system("cls");
			}
			staffChangePPass(fixed_id);
		}
	}  else if(num == 2){
		staffMain(fixed_id);
	} else {
		printf("Invalid input!\n");
		staffChangePPass(fixed_id);
	}
}

void userMain(int fixed_id){
	int num;
	
	printf("===================================\n");
	printf(">Ordinary User Main Menu\n");
	printf("===================================\n");
	printf(">1 Borrow Equipment\n");
	printf(">2 Return Equipment\n");
	printf(">3 Change Personal Password\n");
	printf(">4 Exit\n");
	printf("===================================\n");
	printf("\nChoose what to do next\n>");
	scanf("%d", &num);
	system("cls");
	switch(num){
		case 1:
			borrowEquip(fixed_id);
			break;
		case 2:
			returnEquip(fixed_id);
			break;
		case 3:
			ouChangePPass(fixed_id);
			break;
		case 4:
			exit(0);
			break;
		default:
			printf("Invalid input");
			adminMain(fixed_id);
	}
}

void borrowEquip(int fixed_id){
	char equip_name[25], equip_status[25], equip_availability[25], status[25];
	int equip_id, quantity, confirm = 0, num, id, is_deleted, statusNum = 1;
	char buffer[1025], buffer1[1025], temp[1025], temp1[1025], temp2[1025], temp3[1025];
	char str_id[255], str_isDeleted[255], str_quantity[255];
	char new_name[25], new_status[25], new_availability[25], str1[255];
	int ctr = 0, count, line;
	FILE *fp;
	FILE *fptr, *fptr3;
	fp = fopen("equipmentDB.txt", "r");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}

	printf("========================\n");
	printf(">List of all Equipment\n");
	printf("========================\n\n");
	int row = 0;
	int column = 0;
	printf(">ID\tEquipment Name\t\tEquipment Status\tQuantity\t\tAvailability\n");
	printf("=============================================================================================\n");
	
	while (fgets(buffer,1025, fp)) {
		column = 0;
		row++;
		confirm = 0;
		char* token = strtok(buffer, ", ");
			
		while (token) {
			// ID
			if (column == 0) {
				equip_id = atoi(token);
				confirm++;
			}

			// equipment name
			if (column == 1) {
				strcpy(equip_name, token);
				confirm++;
			}

			// equipment status
			if (column == 2) {
				strcpy(equip_status, token);
				confirm++;
			}
			// quantity
			if (column == 3) {
				quantity = atoi(token);
				if(quantity == 0){
					break;
				}
				confirm++;
			}
			//availability
			if (column == 4) {
				strcpy(equip_availability, token);
				confirm++;
			}
			// is_deleted
			if (column == 5) {
				is_deleted = atoi(token);
				confirm++;
			}
	
			token = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 6 && is_deleted == 0){
			printf(">%-6d %-23s %-23s %-23d %-15s\n", equip_id, equip_name, equip_status, quantity, equip_availability);	
		}
	}
	fclose(fp);
	
	fptr = fopen("equipmentDB.txt", "a+");
	if(fptr == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("\n\n===================================\n");
	printf(">Choose what to borrow by typing the number\n>");
	scanf("%d", &num);
	fflush(stdin);
	
	while(fgets(temp, 1025, fptr)){
		column = 0;
		row++;
		confirm = 0;
		
		char *value = strtok(temp, ", ");
		while(value){
			// ID
			if(column == 0){
				id = atoi(value);
				if(num == id){
					confirm++;
				} else {
					break;
				}
				
			}
			// equip name
			if (column == 1) {
				strcpy(equip_name, value);
				confirm++;
			}
			// equip status
			if (column == 2) {
				strcpy(equip_status, value);
				confirm++;
			}
			// quantity
			if (column == 3) {
				quantity = atoi(value);
				confirm++;
			}
			// equip availability
			if (column == 4) {
				strcpy(equip_availability, value);
				confirm++;
			}
			// is_deleted
			if (column == 5) {
				is_deleted = atoi(value);
				confirm++;
			}
			if(confirm == 6){
				break;
			}
			value = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 6){
			break;
		}
	}
	fclose(fptr);
	
	printf("\n>You would like to borrow a %s\n", equip_name);
	printf(">Please wait for the staff to approve your application to borrow.\n");
	printf(">You can pick it up when approved.\n");
	
	FILE *fileptr;
	fileptr = fopen("equipmentDB.txt", "r");
	if(fileptr == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	while(fgets(temp1, 1025, fileptr)){
		column = 0;
		row++;
		confirm = 0;
		
		char *value = strtok(temp1, ", ");
		while(value){
			// ID
			if(column == 0){
				id = atoi(value);
				if(num == id){
					confirm++;
				} else {
					break;
				}
				
			}
			// equip name
			if (column == 1) {
				strcpy(equip_name, value);
				confirm++;
			}
			// equip status
			if (column == 2) {
				strcpy(equip_status, value);
				confirm++;
			}
			// quantity
			if (column == 3) {
				quantity = atoi(value);
				confirm++;
			}
			// equip availability
			if (column == 4) {
				strcpy(equip_availability, value);
				confirm++;
			}
			// is_deleted
			if (column == 5) {
				is_deleted = atoi(value);
				if(is_deleted == 0){
					strcpy(status, "Enabled");
				} else if(is_deleted == 1){
					strcpy(status, "Disabled");
				}
				confirm++;
			}
			if(confirm == 6){
				break;
			}
			value = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 6){
			break;
		}
	}
	fclose(fileptr);
	
	FILE *fptrborrow;
	fptrborrow = fopen("request_borrow.txt", "a+");
	if(fptrborrow == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	FILE *fileptr1;
	fileptr1 = fopen("accountDB.txt", "r");
	if(fileptr1 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	char fname[25], lname[25];
	int confirm2, temp_id;
	while(fgets(temp2, 1025, fileptr1)){
		column = 0;
		row++;
		confirm2 = 0;
		
		char *value = strtok(temp2, ", ");
		while(value){
			// ID
			if(column == 0){
				temp_id = atoi(value);
				if(fixed_id == temp_id){
					confirm2++;
				} else {
					break;
				}
				
			}
			// first name
			if (column == 1) {
				strcpy(fname, value);
				confirm2++;
			}
			// last name
			if (column == 2) {
				strcpy(lname, value);
				confirm2++;
			}
			// is_deleted
			if (column == 6) {
				is_deleted = atoi(value);
//				if(is_deleted == 0){
//					strcpy(status, "Enabled");
//				} else if(is_deleted == 1){
//					strcpy(status, "Disabled");
//				}
				confirm2++;
			}
			if(confirm2 == 4){
				break;
			}
			value = strtok(NULL, ", ");
			column++;
		}
		if(confirm2 == 4){
			break;
		}
	}
	
	FILE *fileptr3;
	fileptr3 = fopen("equipmentDB.txt", "r");
	if(fileptr3 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	if(confirm == 6 && confirm2 == 4){
		fprintf(fptrborrow,"%d, %s, %s, 1, %s, %d, %s, %s, %d\n", id, equip_name, equip_status, equip_availability, temp_id, fname, lname, statusNum);
		fclose(fileptr1);
		fclose(fptrborrow);
		
		fptr3 = fopen("tempEquipDB.txt", "w");
		if(fptr3 == NULL){
			printf("Failed to open file.");
			exit(0);
		}
		
		FILE *fileptr2;
		fileptr2 = fopen("equipmentDB.txt", "r");
		if(fileptr2 == NULL){
			printf("Failed to open file.");
			exit(0);
		}
		
		row = 0;
        while (fgets(buffer1,1025, fileptr3)) {
			column = 0;
			row++;
			confirm = 0;
			char* token = strtok(buffer1, ", ");
				
			while (token) {
				// ID
				if (column == 0) {
					id = atoi(token);
					if(id == num){
						line = row;
						confirm++;
					} else {
						break;
					}
				}
				// equipment name
				if (column == 1) {
					strcpy(equip_name, token);
					confirm++;
				}
				// equipment status
				if (column == 2) {
					strcpy(equip_status, token);
					confirm++;
				}
				// quantity
				if (column == 3) {
					quantity = atoi(token);
					quantity--;
					confirm++;
				}
				//availability
				if (column == 4) {
					strcpy(equip_availability, token);
					confirm++;
				}
				// is_deleted
				if (column == 5) {
					is_deleted = atoi(token);
					confirm++;
				}
				if(confirm == 6){
					break;
				}
				token = strtok(NULL, ", ");
				column++;
			}
			if(confirm == 6){
				break;
			}
		}
		if(confirm == 6){
		itoa(id, str_id, 10);
		itoa(is_deleted, str_isDeleted, 10);
		itoa(quantity, str_quantity, 10);
		strcat(str1, str_id);
		strcat(str1, ", ");
		strcat(str1, equip_name);
		strcat(str1, ", ");
		strcat(str1, equip_status);
		strcat(str1, ", ");
		strcat(str1, str_quantity);
		strcat(str1, ", ");
		strcat(str1, equip_availability);
		strcat(str1, ", ");
		strcat(str1, str_isDeleted);
		strcat(str1, "\n");
	}
		fclose(fileptr3);
		
		count = 0;
		while((fgets(temp3, 1025, fileptr2)) != NULL){
		    count++;
		
			if (count == line){
				fputs(str1, fptr3);
			} else {
				fputs(temp3, fptr3);
			}
		}
        fclose(fileptr2);
        fclose(fptr3);
        remove("equipmentDB.txt");  
        rename("tempEquipDB.txt", "equipmentDB.txt");
	}
	
	char x;
	printf("\n>Do you want to borrow another one?(Y/N)\n");
	scanf("%c", &x);
	fflush(stdin);
	system("cls");
	if(x == 'Y'){
		borrowEquip(fixed_id);
	} else if(x == 'N'){
		userMain(fixed_id);
	} else {
		printf("Invalid input");
		exit(0);
	}
}

void returnEquip(int fixed_id){
	char equip_name[25], equip_status[25], equip_availability[25], status[25];
	int equip_id, quantity, confirm = 0, num, row, column, id, is_deleted = 0, statusNum = 3, temp_id1, is_approved;
	char buffer[1025], temp[1025], temp1[1025], temp2[1025];;
	FILE *fp;
	FILE *fptr;
	fp = fopen("borrowed_equip.txt", "r");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("===========================================\n");
	printf(">List of all approved Borrowed Equipments\n");
	printf("===========================================\n\n");
	printf(">ID\tEquipment Name\t\tEquipment Status\tQuantity\t\tAvailability\n");
	printf("=============================================================================================\n");
	
	while (fgets(buffer,1025, fp)) {
		column = 0;
		row++;
		confirm = 0;
		char* token = strtok(buffer, ", ");
			
		while (token) {
			// ID
			if (column == 0) {
				equip_id = atoi(token);
				confirm++;
			}
			// equipment name
			if (column == 1) {
				strcpy(equip_name, token);
				confirm++;
			}

			// equipment status
			if (column == 2) {
				strcpy(equip_status, token);
				confirm++;
			}
			// quantity
			if (column == 3) {
				quantity = atoi(token);
				confirm++;
			}
			//availability
			if (column == 4) {
				strcpy(equip_availability, token);
				confirm++;
			}
			// id of borrower
			if (column == 5) {
				temp_id1 = atoi(token);
				confirm++;
			}
			// approved or not
			if (column == 8) {
				is_approved = atoi(token);
				confirm++;
			}
	
			token = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 7 && fixed_id == temp_id1){
			if(is_approved == 2){
				printf(">%-6d %-23s %-26s %-23d %-15s\n", equip_id, equip_name, equip_status, quantity, equip_availability);	
			}
		}
	}
	fclose(fp);
	
	fptr = fopen("equipmentDB.txt", "a+");
	if(fptr == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf("\n\n===================================\n");
	printf(">Choose what to return by typing the number\n>");
	scanf("%d", &num);
	fflush(stdin);
	
		while(fgets(temp, 1025, fptr)){
		column = 0;
		row++;
		confirm = 0;
		
		char *value = strtok(temp, ", ");
		while(value){
			// ID
			if(column == 0){
				id = atoi(value);
				if(num == id){
					confirm++;
				} else {
					break;
				}
				
			}
			// equip name
			if (column == 1) {
				strcpy(equip_name, value);
				confirm++;
			}
			// equip status
			if (column == 2) {
				strcpy(equip_status, value);
				confirm++;
			}
			// quantity
			if (column == 3) {
				quantity = atoi(value);
				confirm++;
			}
			// equip availability
			if (column == 4) {
				strcpy(equip_availability, value);
				confirm++;
			}
			// is_deleted
			if (column == 5) {
				is_deleted = atoi(value);
				confirm++;
			}
			if(confirm == 6){
				break;
			}
			value = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 6){
			break;
		}
	}
	fclose(fptr);
	
	printf("\n>You would like to return a %s\n", equip_name);
	printf(">Please wait for the staff to approve your application to return the borrowed equipment.\n");
	printf(">You can bring it back to the laboratory when you application to return will be approved.\n");
	
	FILE *fileptr;
	fileptr = fopen("borrowed_equip.txt", "r");
	if(fileptr == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	while(fgets(temp1, 1025, fileptr)){
		column = 0;
		row++;
		confirm = 0;
		
		char *value = strtok(temp1, ", ");
		while(value){
			// ID
			if(column == 0){
				id = atoi(value);
				if(num == id){
					confirm++;
				} else {
					break;
				}
				
			}
			// equip name
			if (column == 1) {
				strcpy(equip_name, value);
				confirm++;
			}
			// equip status
			if (column == 2) {
				strcpy(equip_status, value);
				confirm++;
			}
			// quantity
			if (column == 3) {
				quantity = atoi(value);
				confirm++;
			}
			// equip availability
			if (column == 4) {
				strcpy(equip_availability, value);
				confirm++;
			}
			// is_deleted
			if (column == 5) {
				is_deleted = atoi(value);
				if(is_deleted == 0){
					strcpy(status, "Enabled");
				} else if(is_deleted == 1){
					strcpy(status, "Disabled");
				}
				confirm++;
			}
			if(confirm == 6){
				break;
			}
			value = strtok(NULL, ", ");
			column++;
		}
		if(confirm == 6){
			break;
		}
	}
	FILE *fptrborrow;
	fptrborrow = fopen("request_return.txt", "a+");
	if(fptrborrow == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	FILE *fileptr1;
	fileptr1 = fopen("accountDB.txt", "r");
	if(fileptr1 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	char fname[25], lname[25];
	int confirm2, temp_id;
	while(fgets(temp2, 1025, fileptr1)){
		column = 0;
		row++;
		confirm2 = 0;
		
		char *value = strtok(temp2, ", ");
		while(value){
			// ID
			if(column == 0){
				temp_id = atoi(value);
				if(fixed_id == temp_id){
					confirm2++;
				} else {
					break;
				}
				
			}
			// first name
			if (column == 1) {
				strcpy(fname, value);
				confirm2++;
			}
			// last name
			if (column == 2) {
				strcpy(lname, value);
				confirm2++;
			}
			// is_deleted
			if (column == 6) {
				is_deleted = atoi(value);
//				if(is_deleted == 0){
//					strcpy(status, "Enabled");
//				} else if(is_deleted == 1){
//					strcpy(status, "Disabled");
//				}
				confirm2++;
			}
			if(confirm2 == 4){
				break;
			}
			value = strtok(NULL, ", ");
			column++;
		}
		if(confirm2 == 4){
			break;
		}
	}
	
	if(confirm == 6 && confirm2 == 4){
		fprintf(fptrborrow,"%d, %s, %s, %d, %s, %d, %s, %s, %d\n", id, equip_name, equip_status, quantity, equip_availability, temp_id, fname, lname, statusNum);
		fclose(fileptr1);
		fclose(fptrborrow);
	}
	
	char x;
	printf("\n>Do you want to return another one?(Y/N)\n");
	scanf("%c", &x);
	fflush(stdin);
	system("cls");
	if(x == 'Y'){
		returnEquip(fixed_id);
	} else if(x == 'N'){
		userMain(fixed_id);
	} else {
		printf("Invalid input");
		exit(0);
	}
}

void ouChangePPass(int fixed_id){
	int i, num, row = 0, column = 0, confirm = 0, confirmation = 0, id, count = 0, line, is_deleted;
	FILE *fp, *fptr, *fp1, *fp2;
	char newPass1[25], newPass2[25], buffer[1025], temp[1025], *token, pass[25];
	char str[255] = "", fname[25], lname[25], email[25], role[25], str_id[255], str_isDeleted[255];
	char temp1[] = "tempOuChangePPass.txt";	

	fp = fopen("accountDB.txt", "r");
	if(fp == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fp1 = fopen("accountDB.txt", "r");
	if(fp1 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	fp2 = fopen(temp1, "w");
	if(fp2 == NULL){
		printf("Failed to open file.");
		exit(0);
	}
	
	printf(">1 Change Personal Password\n");
	printf(">2 Return to User Main Menu\n");
	printf("\nChoose what to do next\n>");
	scanf("%d", &num);
	system("cls");
	fflush(stdin);
	if(num == 1){
		printf(">New Password:\n>");
		gets(newPass1);
		printf("\n>Repeat Password:\n>");
		gets(newPass2);
		fflush(stdin);
		
		if(strcmp(newPass1, newPass2) == 0){
			while(fgets(buffer, 1025, fp)){
				confirmation = 0;
				column = 0;
				row++;
				token = strtok(buffer, ", ");
				while(token != NULL){
					if(column == 0){
						id = atoi(token);
						if(id == fixed_id){
							line = row;
							confirmation++;
						} else {
							break;
						}
					}
					if(column == 1){
						strcpy(fname, token);
						confirmation++;
					}
					if(column == 2){
						strcpy(lname, token);
						confirmation++;
					}
					if(column == 3){
						strcpy(email, token);
						confirmation++;
					}
					if(column == 4){
						strcpy(pass, newPass1);
						confirmation++;
					}
					if(column == 5){
						strcpy(role, token);
						confirmation++;
					}
					if(column == 6){
						is_deleted = atoi(token);
						confirmation++;
					}
					if(confirmation == 7 && is_deleted == 0){
						break;
					}
					token = strtok(NULL, ", ");
					column++;
				}
				if(confirmation == 7 && is_deleted == 0){
					break;
				}
			}
			if(confirmation == 7 && is_deleted == 0){
				itoa(id, str_id, 10);
				itoa(is_deleted, str_isDeleted, 10);
				strcat(str, str_id);
				strcat(str, ", ");
				strcat(str, fname);
				strcat(str, ", ");
				strcat(str, lname);
				strcat(str, ", ");
				strcat(str, email);
				strcat(str, ", ");
				strcat(str, newPass1);
				strcat(str, ", ");
				strcat(str, role);
				strcat(str, ", ");
				strcat(str, str_isDeleted);
				strcat(str, "\n");
			}
			fclose(fp);
			
			 while ((fgets(temp, 1025, fp1)) != NULL){
		        count++;
		
		        if (count == line)
		            fputs(str, fp2);
		        else
		            fputs(temp, fp2);
		    }
		    fclose(fp1);
		    fclose(fp2);
		
		    remove("accountDB.txt");
		 	rename(temp1, "accountDB.txt");
		    printf("\nSuccessfully changed password!\n");sleep(1);
			for(i = 0; i < 1; i++){
				printf("Redirecting you to User Main screen!");
				printf(".");sleep(1);
				printf(".");sleep(1);
				printf(".\n");sleep(1);
				system("cls");
			}
			userMain(fixed_id);
		} else {
			printf("Passwords do not match!\n");sleep(1);
			for(i = 0; i < 1; i++){
				printf("Please try again!");
				printf(".");sleep(1);
				printf(".");sleep(1);
				printf(".\n");sleep(1);
				system("cls");
			}
			staffChangePPass(fixed_id);
		}
	}  else if(num == 2){
		userMain(fixed_id);
	} else {
		printf("Invalid input!\n");
		ouChangePPass(fixed_id);
	}
}



























