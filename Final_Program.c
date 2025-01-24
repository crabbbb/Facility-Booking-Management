#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<ctype.h>
#include<conio.h>
#pragma warning (disable : 4996)
#define MAX_SIZE_BOOK 10
#define MAX_SIZE_MEMBER 10
#define MAX_SIZE_FACILITY 10
#define MAX_SIZE_STAFF 10

typedef struct {
	int hours, minute;
}Time;

typedef struct {
	char typeF[30];
	int male, female, ttl;
}CheckType;

struct Date {
	int day, month, year;
};

typedef struct {
	int hrs;
	char pmOrAm[3];
}TimeBook;

struct Facility {
	char id[5], type[15], description[25], venue[20], staffInCharge[10], firstChar;
	int max;
	struct Date buildDate;
};//type 30 - 15 venue 50 - 20

struct Password {
	char pwd[10], pwdRecovery[20];
};

typedef struct {
	char staffId[7];
	struct Password pass;
	char staffName[20], position[30], staffGender;
	int age;
	struct Date staffBirthday;
}Staff;

typedef struct {
	char bookId[6];
	struct Date todayDate;
	struct Date bookDate;
	TimeBook formTime;
	TimeBook toTime;
	char memberId[6], facilityId[5], memberName[30];
}Booking;

typedef struct {
	char memberID[6], memberName[30];
	char password[10], passwordRecover[20], gender, icNum[15], phoneNum[12], category[10];
	struct Date joinedDate;
}Member;

void submenuBook();
FILE* readXJ(int choice, FILE* fptr);
void addBook();
void checkTime(int* strH, int* endH, char strPmOrAm[3], char endPmOrAm[3]);
void displayBook();
int displayAllData();
void monthR(int numM, char monthWord[5]);
int dateChecking(int bDate, int bMonth, int bYear);
int checkTimeAvaliable(int startingTime, int endTime, char end[3], char start[3]);
void searchBook();
void checkNull(char* userChoice, char fileName[], char readFile[], char addFile[]);
void modifyBook();
void askSureModify(Booking book[MAX_SIZE_BOOK], int nRecord, Booking modify, int change);
int checkOneDay(char memberId[6], int bDay, int bMonth, int bYear);
void deleteBook();
void reportBook();
int checkFacilityType(CheckType check[MAX_SIZE_FACILITY]);
void maleFemale(CheckType check[MAX_SIZE_FACILITY], char bookId[6], char memId[6], char gender, char fType[30], int getType);
void mainBook();
void delAllUnnecessary();
void delMBook(char type);
void delUseIdBook();
int checkInput(char userInput[6]);

int loginStaff();
void autoCreateStaffId(int* error, char id[7]);
void addStaff();
void submenuStaff();
void displayStaff();
void searchStaff();
void deleteStaff();
void passwordRecoveryStaff(char* valid);
void modifyStaff();
void mainStaff();

void submenuFacility();
void addFacility();
void displayFacility();
void searchFacility();
void modifyFacility();
void deleteFacility();
void reportFacility();
void checkReport(char facility, int totalFacility, int percentage, int highestAllow);
void line(int length);
void mainFacility();
void readLastFacility(char type[]);

void menuStaff();
void menuMember();
int memberSignIn();
void memberPasswordRecovery(char* valid);
void autoCreateId(int* error, char id[6], char fileName[], char fileType[]);
void addMember();
void searchMember();
void modifyMember();
void deleteMember();
void displayMember();
void mainMember();

//\001 happy face \002 hv color de happy face \003 love \004 diamond \005 meihua \006 hongtao //hv not 007
int main() {

	int choice;
	do
	{
		system("cls");
		Sleep(600);//\033[0;31m \033[0m
		printf("\n\033[31;5m\t\t\t        OOO                 OOO\033[0m\n");//red
		Sleep(600);
		printf("\033[1;31;5m\t\t\t    OO       OO         OO       OO\033[0m\n");//orange
		Sleep(600);
		printf("\033[33;5m\t\t\t   OO    \033[31;5m\003\033[33;5m    OO       OO    \033[31;5m\003\033[33;5m    OO \033[0m\n");//yellow
		Sleep(600);
		printf("\033[32;5m\t\t\t   OO         OO       OO         OO \033[0m\r\n");//green
		Sleep(600);
		printf("\033[34;5m\t\t\t    OO       OO         OO       OO\033[0m\n");//light blue
		Sleep(600);
		printf("\033[35;5m\t\t\t        OOO        O        OOO\033[0m\n");//purple
		Sleep(600);


		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m1\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m2\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m        STAFF MODULE        \033[0;35m|\t       \033[0;31m|\033[0m        MEMBER MODULE       \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n");
		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m3\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m4\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m       FACILITY MODULE      \033[0;35m|\t       \033[0;31m|\033[0m        BOOKING MODULE      \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n");
		printf("\n\t                  \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m5\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0m");
		printf("\n\t                  \033[1;31m|                            \033[0;34m|\033[0m\t");
		printf("\n\t                  \033[0;33m|\033[0m             EXIT           \033[0;35m|\033[0m\t");
		printf("\n\t                  \033[0;32m|                            \033[0;31m|\033[0m\t");
		printf("\n\t                  \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0m\t\n");

		printf("Enter your choice > ");
		rewind(stdin);
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			mainStaff(); break;
		case 2:
			mainMember(); break;
		case 3:
			mainFacility(); break;
		case 4:
			mainBook(); break;
		case 5:
			break;
		default:
			printf("\033[0;31mInvalid input please enter again\033[0m\n");
			system("pause");
		}
	} while (choice != 5);

	return 0;
}

//xinjie
void mainBook() {

	int choice, getnum;

	do
	{
		system("cls");
		//menu login

		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m1\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m2\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m        MEMBER LOGIN        \033[0;35m|\t       \033[0;31m|\033[0m         STAFF LOGIN        \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n");
		printf("\n\t                  \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m3\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0m");
		printf("\n\t                  \033[1;31m|                            \033[0;34m|\033[0m\t");
		printf("\n\t                  \033[0;33m|\033[0m             EXIT           \033[0;35m|\033[0m\t");
		printf("\n\t                  \033[0;32m|                            \033[0;31m|\033[0m\t");
		printf("\n\t                  \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0m\t\n");

		//user input
		printf("Enter your choice > ");
		rewind(stdin);
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			getnum = memberSignIn();
			if (getnum == 1)// 1  0
			{
				addBook();
			}
			break;
		case 2:
			getnum = loginStaff();
			if (getnum == 1)
			{
				submenuBook();
			}
			break;
		case 3:
			break;
		default:
			printf("\033[0;31mInvalid choice, please enter again \033[0m\n");
			system("pause");
		}
	} while (choice != 3);

}

void submenuBook() {
	int choice;

	do
	{
		system("cls");
		//submenu for staff
		printf("\n                                - BOOKING MODULE MENU -\n\n");
		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m1\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m2\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m    CREATE A NEW BOOKING    \033[0;35m|\t       \033[0;31m|\033[0m  SEARCH THE BOOKING DETAIL \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n");
		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m3\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m4\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m  MODIFY THE BOOKING DETAIL \033[0;35m|\t       \033[0;31m|\033[0m DISPLAY ALL BOOKING DETAIL \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n");
		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m5\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m6\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m   DELETE BOOKING DETAIL    \033[0;35m|\t       \033[0;31m|\033[0m  REPORT FOR BOOKING DETAIL \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n");
		printf("\n\t                  \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m7\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0m");
		printf("\n\t                  \033[1;31m|                            \033[0;34m|\033[0m\t");
		printf("\n\t                  \033[0;33m|\033[0m             EXIT           \033[0;35m|\033[0m\t");
		printf("\n\t                  \033[0;32m|                            \033[0;31m|\033[0m\t");
		printf("\n\t                  \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0m\t\n");

		printf("Enter your choice > ");
		rewind(stdin);
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			addBook();
			break;
		case 2:
			searchBook();
			break;
		case 3:
			modifyBook();
			break;
		case 4:
			displayBook();
			break;
		case 5:
			deleteBook();
			break;
		case 6:
			reportBook();
			break;
		case 7:
			break;
		default:
			printf("\033[0;31mInvalid choice, please enter again\033[0m\n");
			system("pause");
		}
	} while (choice != 7);
}

void addBook() {

	system("cls");
	SYSTEMTIME today;
	GetLocalTime(&today);

	Member mem[MAX_SIZE_MEMBER];
	Booking book;
	struct Facility show[MAX_SIZE_FACILITY];

	char userInputMem[6], yorN, userInputFID[5], id[6], userChoice = 'Y', yorN2, registerPage = 'N', facilityStaff = 'N';
	int i, getSizeMem, choice, check = 0, plus = 0, compare, noFound, noFoundMem = 0, error = 0, invalid, no, getNum = 0, upper, invalid2;

	checkNull(&userChoice, "xinjie.bin", "rb", "ab");

	if (toupper(userChoice) == 'Y') {

		system("cls");
		do
		{
			printf("Welcome to add function page ....\n");
			//user input check id
			printf("Please enter your member ID : ");
			rewind(stdin);
			scanf("%s", &userInputMem);

			for (i = 0; i < 6; i++)
			{
				userInputMem[i] = toupper(userInputMem[i]);
			}

			FILE* fileFind = fopen("kaixin.txt", "r");
			if (fileFind == NULL)
			{
				printf("\033[0;31mUnable to open the file!!\033[0m\n");
				do
				{
					printf("Do you want to turn into member register page ?? ('Y' = yes 'N' = no) > ");
					rewind(stdin);
					scanf("%c", &registerPage);
					switch (toupper(registerPage)) {
					case 'Y':
						addMember(); break;
					case 'N':
						break;
					default:
						printf("\033[0;31mInvalid input, please enter again\033[0m\n");
					}
				} while (toupper(registerPage) != 'N' && toupper(registerPage) != 'Y');
				/*if (toupper(registerPage) == 'Y' && toupper(registerPage) == 'N')
				{
					break;
				}*/
			}
			else {
				i = 0;
				getSizeMem = 0;
				while (fscanf(fileFind, "%[^|]|%[^|]|%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%d-%d-%d\n", &mem[i].memberID, &mem[i].memberName, &mem[i].password, &mem[i].passwordRecover, &mem[i].gender, &mem[i].icNum, &mem[i].phoneNum, &mem[i].category, &mem[i].joinedDate.day, &mem[i].joinedDate.month, &mem[i].joinedDate.year) != EOF)
				{
					++i;
					++getSizeMem;
				}
				fclose(fileFind);

				//strcmp the member ID
				noFoundMem = 0;
				for (i = 0; i < getSizeMem; i++)
				{
					if (strcmp(userInputMem, mem[i].memberID) == 0)
					{
						printf("Member ID   > %s\n", mem[i].memberID);
						printf("Member Name > %s\n", mem[i].memberName);
						printf("Member Gender > %c\n", mem[i].gender);

						do
						{
							printf("Is that your information ? ('Y' = yes 'N' = no) : ");
							rewind(stdin);
							scanf("%c", &yorN);
							if (toupper(yorN) == 'Y')
							{
								strcpy(book.memberName, mem[i].memberName);
								strcpy(book.memberId, mem[i].memberID);

								FILE* fileFacility = fopen("sauwei.bin", "rb");
								if (fileFacility == NULL) {
									printf("\033[0;31mUnable to open the file\033[0m\n");
									do
									{
										printf("Staff Only...\n");
										printf("Do you want to create a new facility ?? ('Y' = yes 'N' = no) > ");
										rewind(stdin);
										scanf("%c", &facilityStaff);
										switch (toupper(facilityStaff)) {
										case 'Y':
											getNum = loginStaff();
											if (getNum == 1)
											{
												addFacility();
											}
											break;
										case 'N':
											break;
										default:
											printf("\033[0;31mInvalid input, please enter again\033[0m\n");
										}
									} while (toupper(facilityStaff) != 'Y' && toupper(facilityStaff) != 'N');
								}
								else {
									printf("Facility menu ...\n");
									printf("%-4s%3s%-10s%3s%-30s\n", "No", "", "ID", " ", "Facility type");
									line(40);
									plus = 0;
									no = 1;
									while (fread(&show[plus], sizeof(show[0]), 1, fileFacility) != 0)
									{
										printf("%-4d%3s%-10s%3s%-30s\n", no++, "", show[plus].id, "", show[plus].type);
										++plus;
									}
									fclose(fileFacility);

									do
									{
										printf("Enter the facility ID book > ");
										rewind(stdin);
										scanf("%s", &userInputFID);

										//change to uppercase
										for (upper = 0; upper < 5; upper++)
										{
											userInputFID[upper] = toupper(userInputFID[upper]);
										}

										noFound = 0;
										for (compare = 0; compare < plus; compare++)
										{

											if (strcmp(userInputFID, show[compare].id) == 0)
											{
												strcpy(book.facilityId, userInputFID);

												//today date
												book.todayDate.day = today.wDay;
												book.todayDate.month = today.wMonth;
												book.todayDate.year = today.wYear;
												printf("Today date (dd-mm-yyyy)  : %d-%d-%d\n", book.todayDate.day, book.todayDate.month, book.todayDate.year);

												//booking date 

												do
												{
													do
													{
														do
														{
															printf("Booking date (dd-mm-yyyy): ");
															rewind(stdin);
															scanf("%d-%d-%d", &book.bookDate.day, &book.bookDate.month, &book.bookDate.year);

															invalid = dateChecking(book.bookDate.day, book.bookDate.month, book.bookDate.year);

														} while (invalid != 0);

														// check cannot one day have more booking
														invalid2 = checkOneDay(userInputMem, book.bookDate.day, book.bookDate.month, book.bookDate.year);
													} while (invalid2 != 0);

													//check before one day...
													if (book.bookDate.year > book.todayDate.year + 1 || book.bookDate.year < book.todayDate.year) {
														printf("\033[0;31mDate format is not available please enter again\033[0m\n");
													}
													else if (book.bookDate.year == book.todayDate.year) {
														//for same year checking
														if (book.bookDate.month > book.todayDate.month)
														{
															checkTime(&book.formTime.hrs, &book.toTime.hrs, book.formTime.pmOrAm, book.toTime.pmOrAm);
															autoCreateId(&error, id, "xinjie.bin", "rb");
															if (error == 1) {
																break;
															}
															else {
																strcpy(book.bookId, id);

																FILE* filePaste = readXJ(3, &filePaste);
																fwrite(&book, sizeof(Booking), 1, filePaste);

																fclose(filePaste);
															}

														}
														else if (book.bookDate.month == book.todayDate.month) {
															if (book.bookDate.day > book.todayDate.day) {

																checkTime(&book.formTime.hrs, &book.toTime.hrs, book.formTime.pmOrAm, book.toTime.pmOrAm);
																autoCreateId(&error, id, "xinjie.bin", "rb");
																if (error == 1) {
																	break;
																}
																else {
																	strcpy(book.bookId, id);

																	FILE* filePaste = readXJ(3, &filePaste);
																	fwrite(&book, sizeof(Booking), 1, filePaste);

																	fclose(filePaste);
																}
															}
															else {
																printf("\033[0;31mThe booking date must be one day before\033[0m\n");
															}
														}
														else {
															printf("\033[0;31mThe booking date must be one day before\033[0m\n");
														}
													}
													else {//book.bookDate.year == book.todayDate.year || book.bookDate.year == book.todayDate.year + 1

														checkTime(&book.formTime.hrs, &book.toTime.hrs, book.formTime.pmOrAm, book.toTime.pmOrAm);
														autoCreateId(&error, id, "xinjie.bin", "rb");
														if (error == 1) {
															break;
														}
														else {
															strcpy(book.bookId, id);

															FILE* filePaste = readXJ(3, &filePaste);
															fwrite(&book, sizeof(Booking), 1, filePaste);

															fclose(filePaste);
														}
													}

												} while ((book.bookDate.year > book.todayDate.year + 1 || book.bookDate.year < book.todayDate.year) || ((book.bookDate.year == book.todayDate.year) && (book.bookDate.month == book.todayDate.month) && (book.bookDate.day < book.todayDate.day)) || ((book.bookDate.year == book.todayDate.year) && (book.bookDate.month < book.todayDate.month)) || ((book.bookDate.year == book.todayDate.year) && (book.bookDate.month == book.todayDate.month) && (book.bookDate.day == book.todayDate.day)));
											}//(book.bookDate.year > book.todayDate.year + 1 || book.bookDate.year < book.todayDate.year) || ((book.bookDate.year == book.todayDate.year) && (book.bookDate.month < book.todayDate.month)) || ((book.bookDate.year == book.todayDate.year) && (book.bookDate.month == book.todayDate.month) && (book.bookDate.day < book.todayDate.day))
											else
											{
												++noFound;
											}
										}

										if (noFound == plus)
										{
											printf("\033[0;31mInvalid input please enter again\033[0m\n");
										}
									} while (noFound == plus);
								}

							}
							else if (toupper(yorN) == 'N') {
								printf("\033[0;31mWrong Input\033[0m\n");
								printf("Do you need to add or edit the member information ? \n");
								printf("1. Create a new member ID\n");
								printf("2. Edit member information\n");
								printf("3. Exit\n");
								do
								{
									printf("Enter your choice > ");
									rewind(stdin);
									scanf("%d", &choice);
									switch (choice) {
									case 1:
										addMember();
										break;
									case 2:
										modifyMember();
										break;
									case 3:
										printf("Turning back to the menu...\n");
										Sleep(500);
										break;
									default:
										printf("\033[0;31mInvalid choice please enter again\033[0m\n");
									}
								} while (choice != 3);
							}
							else {
								printf("\033[0;31mInvalid input please enter again!!\033[0m\n");
							}
						} while ((toupper(yorN) != 'Y' && toupper(yorN) != 'N') || (toupper(facilityStaff) != 'Y' && toupper(facilityStaff) != 'N'));
					}
					else {
						++noFoundMem;
					}
				}
				if (noFoundMem == getSizeMem) {
					printf("\033[0;31mNo record found!!\033[0m\n");
				}

				do
				{
					//ask continue
					printf("Continues ?? ('Y' = yes 'N' = no) > ");
					rewind(stdin);
					scanf("%c", &yorN2);
					switch (toupper(yorN2)) {
					case 'Y':
						system("cls");
						break;
					case 'N':
						break;
					default:
						printf("\033[0;31mInvalid code please enter again\033[0m\n");
					}
				} while (toupper(yorN2) != 'Y' && toupper(yorN2) != 'N');
			}
		} while (toupper(yorN2) != 'N' || (toupper(registerPage) == 'Y' && toupper(registerPage) == 'N') || (toupper(facilityStaff) != 'Y' && toupper(facilityStaff) != 'N'));
	}

}

FILE* readXJ(int choice, FILE* fptr) {
	char userChoice = 'Y';

	if (choice == 1)//read
	{
		fptr = fopen("xinjie.bin", "rb");
		if (fptr == NULL) {
			printf("\033[0;31mFile open got problem please return back to the Booking menu\033[0m\n");
		}

	}
	else if (choice == 2) {//write
		fptr = fopen("xinjie.bin", "wb");

	}
	else if (choice == 3) {//add
		fptr = fopen("xinjie.bin", "ab");

	}
}

void checkTime(int* strH, int* endH, char strPmOrAm[3], char endPmOrAm[3]) {

	int start, end, invalid, i;

	do
	{
		do
		{
			printf("Enter starting time > ");
			rewind(stdin);
			scanf("%d%s", &start, strPmOrAm);

			for (i = 0; i < 3; i++)
			{
				strPmOrAm[i] = tolower(strPmOrAm[i]);
			}

			printf("Enter ending time   > ");
			rewind(stdin);
			scanf("%d%s", &end, endPmOrAm);

			for (i = 0; i < 3; i++)
			{
				endPmOrAm[i] = tolower(endPmOrAm[i]);
			}

			*strH = start;
			*endH = end;

			if (strcmp(strPmOrAm, "am") != 0 && strcmp(strPmOrAm, "pm") != 0)//T T T , TF T
			{
				printf("\033[0;31mInvalid time format!! Please enter with using pm/am\033[0m\n");
			}
			else if (strcmp(endPmOrAm, "am") != 0 && strcmp(endPmOrAm, "pm") != 0) {
				printf("\033[0;31mInvalid time format!! Please enter with using pm/am\033[0m\n");
			}
		} while ((strcmp(strPmOrAm, "am") != 0 && strcmp(strPmOrAm, "pm") != 0) || (strcmp(endPmOrAm, "am") != 0 && strcmp(endPmOrAm, "pm") != 0));

		//check the time cannot more than 1 hours and validation format 1~12
		invalid = checkTimeAvaliable(start, end, endPmOrAm, strPmOrAm);

	} while (invalid != 0);

}

//add cannot more than MAX SIZE one day cannot booking two times
void displayBook() {

	system("cls");

	int nSize;
	char month1[5], month2[5], userChoice = 'Y', yesNo;

	Booking book;
	checkNull(&userChoice, "xinjie.bin", "rb", "ab");

	if (toupper(userChoice) == 'Y') {

		printf("Welcome to display function...\n\n");

		FILE* fileRead = readXJ(1, &fileRead);


		printf("%-10s%2s%-15s%4s%-15s%3s%-10s%3s%-10s%3s%-15s%6s%-17s%13s%-10s\n", "BOOKING ID", "", "SUBMISSION DATE", "", "BOOKING DATE", "", "START TIME", "", "END TIME", "", "MEMBER ID", "", "MEMBER NAME", "", "FACILITY ID");
		line(150);

		nSize = 0;
		while (fread(&book, sizeof(Booking), 1, fileRead) != 0) {

			++nSize;

			monthR(book.todayDate.month, month1);

			printf("%-6s%6s%2d %4s %4d", book.bookId, "", book.todayDate.day, month1, book.todayDate.year);

			monthR(book.bookDate.month, month2);

			printf("%6s%2d %4s %4d%10s%2d%2s%8s%2d%2s%9s%-15s%3s%-30s%3s%-10s\n", "", book.bookDate.day, month2, book.bookDate.year, "", book.formTime.hrs, book.formTime.pmOrAm, "", book.toTime.hrs, book.toTime.pmOrAm, "", book.memberId, "", book.memberName, "", book.facilityId);
		}

		if (nSize == 0)
		{
			printf("\t\t\t\033[0;31mNo Record Found\033[0m\n");
		}

		fclose(fileRead);
		line(150);
		printf("\n");
		printf("There is \033[4;33m%d\033[0m booking have record!!\n", nSize);//yellow + line

		system("pause");
	}
}

void monthR(int numM, char monthWord[5]) {
	switch (numM) {
	case 1:
		strcpy(monthWord, "Jan"); break;
	case 2:
		strcpy(monthWord, "Feb"); break;
	case 3:
		strcpy(monthWord, "Mar"); break;
	case 4:
		strcpy(monthWord, "Apr"); break;
	case 5:
		strcpy(monthWord, "May"); break;
	case 6:
		strcpy(monthWord, "Jun"); break;
	case 7:
		strcpy(monthWord, "Jul"); break;
	case 8:
		strcpy(monthWord, "Aug"); break;
	case 9:
		strcpy(monthWord, "Sept"); break;
	case 10:
		strcpy(monthWord, "Oct"); break;
	case 11:
		strcpy(monthWord, "Nov"); break;
	case 12:
		strcpy(monthWord, "Dec"); break;
	}
}

int dateChecking(int bDate, int bMonth, int bYear) {

	int wrong = 0;

	//check date format
	if (bMonth == 2)
	{
		if (bYear % 4 == 0) {
			if (bDate < 1 || bDate > 28)
			{
				printf("\033[0;31mWrong input format!\033[0m\n");
				wrong++;
			}
		}
		else {
			if (bDate < 1 || bDate > 29)
			{
				printf("\033[0;31mWrong input format!\033[0m\n");
				wrong++;
			}
		}
	}
	else if (bMonth == 4 || bMonth == 6 || bMonth == 9 || bMonth == 11) {
		if (bDate < 1 || bDate > 30)
		{
			printf("\033[0;31mWrong input format!\033[0m\n");
			wrong++;
		}
	}
	else if (bMonth == 1 || bMonth == 3 || bMonth == 5 || bMonth == 7 || bMonth == 8 || bMonth == 10 || bMonth == 12) {
		if (bDate < 1 || bDate > 31)
		{
			printf("\033[0;31mWrong input format!\033[0m\n");
			wrong++;
		}
	}
	else {
		printf("\033[0;31mWrong input format!\033[0m\n");
		wrong++;
	}
	return wrong;// 0 1
}

int checkTimeAvaliable(int startingTime, int endTime, char end[3], char start[3]) {
	int wrong = 0;

	if ((startingTime < 12 && startingTime >= 1) && (endTime < 12 && endTime >= 1))
	{
		if (strcmp(start, "am") == 0) {
			if (startingTime <= 7 && startingTime > 0)
			{
				printf("\033[0;31mThe facility is close at 12am to 7am\033[0m\n");
				wrong++;
			}
			else if ((strcmp(end, "am") == 0) && (endTime > startingTime))
			{
				if ((endTime - startingTime) > 1)
				{
					printf("\033[0;31mThe duration time cannot more than 1 hours\033[0m\n");
					wrong++;
				}
			}
			else if (strcmp(end, "pm") == 0) {
				if (((endTime + 12) - startingTime) > 1)
				{
					printf("\033[0;31mThe duration time cannot more than 1 hours\033[0m\n");
					wrong++;
				}
			}
			else {
				printf("\033[0;31mThe duration time must be 1 hours\033[0m\n");
				wrong++;
			}

		}
		else {
			if (strcmp(end, "am") == 0 || ((strcmp(end, "pm") == 0) && (endTime < startingTime))) {
				printf("\033[0;31mThe duration time must be 1 hours\033[0m\n");
				wrong++;
			}
			else if ((endTime - startingTime) > 1) {
				printf("\033[0;31mThe duration time cannot more than 1 hours\033[0m\n");
				wrong++;
			}
		}
	}
	else if (startingTime == 12 || endTime == 12) {
		if (((strcmp(start, "am") == 0) && startingTime == 12) || ((strcmp(end, "am") == 0) && endTime == 12))
		{
			printf("\033[0;31mThe facility is close at 12am to 7am\033[0m\n");
			wrong++;
		}
		else if ((strcmp(start, "pm") == 0) && startingTime == 12) {
			if (strcmp(end, "pm") == 0)
			{
				if (((endTime + 12) - startingTime) > 1)
				{
					printf("\033[0;31mThe duration time cannot more than 1 hours\033[0m\n");
					wrong++;
				}
			}
			else {
				printf("\033[0;31mThe duration time must be 1 hours\033[0m\n");
				wrong++;
			}
		}
		else if ((strcmp(end, "pm") == 0) && endTime == 12) {
			if ((strcmp(start, "am") == 0))
			{
				if ((endTime - startingTime) > 1)
				{
					printf("\033[0;31mThe duration time cannot more than 1 hours\033[0m\n");
					wrong++;
				}
			}
			else {
				printf("\033[0;31mThe duration time must be 1 hours\033[0m\n");
				wrong++;
			}
		}
	}
	else {
		printf("\033[0;31mInvalid time format please enter again\033[0m\n");
		wrong++;
	}
	return wrong;
}

int checkInput(char userInput[6]) {

	char ch;
	int i;

	for (i = 0; i < 5; i++) {
		ch = getch();
		if (i == 0)//127 = char del
		{
			if (toupper(ch) == 'B')
			{
				userInput[0] = toupper(ch);
				printf("\033[4;32m%c\033[0m", ch);
			}
			else {
				printf("\033[4;32m%c\033[0m", ch);
				printf("\n\033[0;31mPlease enter following the booking id format eg : B0001\033[0m\n");
				break;
			}
		}
		else if (i > 0) {
			if ((int)ch >= 48 && (int)ch <= 57)
			{
				userInput[i] = ch;
				printf("\033[4;32m%c\033[0m", ch);
			}
			else {
				printf("\033[4;32m%c\033[0m", ch);
				printf("\n\033[0;31mPlease enter following the booking id format eg : B0001\033[0m\n");
				break;
			}
		}
	}
	userInput[i] = '\0';
	printf("\n");

	return i;
}

void searchBook() {

	char userChoice = 'Y', userInput[6], yesNo, month1[5], month2[5], create;
	int notFound, nSize, valid;

	checkNull(&userChoice, "xinjie.bin", "rb", "ab");

	if (toupper(userChoice) == 'Y');
	{
		system("cls");
		Booking book;

		do
		{
			printf("Welcome to search page ...\n\n");
			do
			{
				printf("Enter the booking id > ");
				//rewind(stdin);
				//scanf("%s", &userInput);

				valid = checkInput(userInput);
				//((i == 0) && (toupper(ch) != 'B')) || ((i > 0) && ((int)ch < 48 || (int)ch > 57))
			} while (valid != 5);

			FILE* fileRead = readXJ(1, &fileRead);
			nSize = 0;
			notFound = 0;
			while (fread(&book, sizeof(Booking), 1, fileRead) != 0)
			{
				nSize++;
				if (strcmp(userInput, book.bookId) == 0)
				{
					printf("Booking ID    : %s\n", book.bookId);
					printf("Member        : %s - %s\n", book.memberId, book.memberName);
					printf("Facility ID   : %s\n", book.facilityId);
					monthR(book.todayDate.month, month1);
					printf("Booking at    : %2d %4s %4d\n", book.todayDate.day, month1, book.todayDate.year);
					monthR(book.bookDate.month, month2);
					printf("Booking for   : %2d %4s %4d\n", book.bookDate.day, month2, book.bookDate.year);
					printf("Time duration : %d%s - %d%s\n", book.formTime.hrs, book.formTime.pmOrAm, book.toTime.hrs, book.toTime.pmOrAm);
				}
				else {
					++notFound;
				}
			}
			fclose(fileRead);
			if (notFound == nSize)
			{
				printf("\033[0;31mNo record found!!\033[0m\n");
				do
				{
					printf("Create a new booking ? ('Y' = yes 'N' = no) > ");
					rewind(stdin);
					scanf("%c", &create);

					switch (toupper(create)) {
					case 'Y':
						addBook(); break;
					case 'N':
						break;
					default:
						printf("\033[0;31mInvalid code please enter again\033[0m\n");
					}
				} while (toupper(create) != 'N' && toupper(create) != 'Y');
			}

			do
			{
				printf("Continues ?? ('Y' = yes 'N' = no) > ");
				rewind(stdin);
				scanf("%c", &yesNo);
				switch (toupper(yesNo)) {
				case 'Y':
					system("cls");
					break;
				case 'N':
					break;
				default:
					printf("\033[0;31mInvalid choice, please enter again\033[0m\n");
				}
			} while (toupper(yesNo) != 'N' && toupper(yesNo) != 'Y');
		} while (toupper(yesNo) != 'N');

	}

}

void modifyBook() {

	char userChoice = 'Y', userInput[6], yesNo, userInputMem[6], yesNo2, userInputFacility[5], yesNo3;
	int nRecord, i, noFoundMem, nMem, plus, no, upper, noFoundFacility, compare, invalid, noFoundBook, valid;

	Booking book[MAX_SIZE_BOOK];
	Booking modify;
	Member mem;
	struct Facility show[MAX_SIZE_FACILITY];

	checkNull(&userChoice, "xinjie.bin", "rb", "ab");

	if (toupper(userChoice) == 'Y')
	{
		system("cls");

		do
		{
			printf("Welcome to modify function....\n");
			nRecord = displayAllData();

			if (nRecord == 0)
			{
				printf("\033[0;31mThere have no record found in file!!\033[0m\n");
				do
				{
					printf("Do you want to add a new booking ('Y' = yes 'N' = no) > ");
					rewind(stdin);
					scanf("%c", &yesNo);
					switch (toupper(yesNo))
					{
					case 'Y':
						addBook(); break;
					case 'N':
						break;
					default:
						printf("\033[0;31mInvalid code please enter again\033[0m\n");
					}
				} while (toupper(yesNo) != 'Y' && toupper(yesNo) != 'N');
			}
			else {
				do
				{
					printf("Please enter the booking ID > ");
					/*rewind(stdin);
					scanf("%s", &userInput);*/

					valid = checkInput(userInput);

				} while (valid != 5);

				FILE* fileRead = readXJ(1, &fileRead);

				//save the value inside array
				i = 0;
				while (fread(&book[i], sizeof(book[0]), 1, fileRead) != 0)
				{
					i++;
				}
				fclose(fileRead);

				noFoundBook = 0;
				for (i = 0; i < nRecord; i++)
				{
					if (strcmp(userInput, book[i].bookId) == 0) {

						printf("Booking ID    : %s\n", book[i].bookId);
						printf("Member        : %s - %s\n", book[i].memberId, book[i].memberName);
						printf("Facility ID   : %s\n", book[i].facilityId);
						printf("Booking at    : %2d - %d - %4d\n", book[i].todayDate.day, book[i].todayDate.month, book[i].todayDate.year);
						printf("Booking for   : %2d - %d - %4d\n", book[i].bookDate.day, book[i].bookDate.month, book[i].bookDate.year);
						printf("Time duration : %d%s - %d%s\n", book[i].formTime.hrs, book[i].formTime.pmOrAm, book[i].toTime.hrs, book[i].toTime.pmOrAm);

						printf("\nStart Modify ....\n");
						printf("Booking ID            : %s\n", book[i].bookId);

						strcpy(modify.bookId, book[i].bookId);
						printf("Enter member ID       : ");
						rewind(stdin);
						scanf("%s", &userInputMem);

						nMem = 0;
						noFoundMem = 0;
						FILE* fileMember = fopen("kaixin.txt", "r");
						while (fscanf(fileMember, "%[^|]|%[^|]|%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%d-%d-%d\n", &mem.memberID, &mem.memberName, &mem.password, &mem.passwordRecover, &mem.gender, &mem.icNum, &mem.phoneNum, &mem.category, &mem.joinedDate.day, &mem.joinedDate.month, &mem.joinedDate.year) != EOF)
						{
							nMem++;
							if (strcmp(userInputMem, mem.memberID) == 0)
							{
								printf("Member Name           : %s\n", mem.memberName);
								printf("Member ID             : %s\n", mem.memberID);
								printf("Gender                : %c\n", mem.gender);

								do
								{
									printf("Is that your information ('Y' = yes 'N' = no) > ");
									rewind(stdin);
									scanf("%c", &yesNo2);
									if (toupper(yesNo2) == 'Y')
									{
										strcpy(modify.memberName, mem.memberName);
										strcpy(modify.memberId, mem.memberID);

										//facility show
										printf("Facility menu ...\n");
										printf("%-4s%3s%-10s%3s%-30s\n", "No", "", "ID", " ", "Facility type");
										line(40);

										FILE* fileFacility = fopen("sauwei.bin", "rb");
										plus = 0;
										no = 1;
										while (fread(&show[plus], sizeof(show[0]), 1, fileFacility) != 0)
										{
											printf("%-4d%3s%-10s%3s%-30s\n", no++, "", show[plus].id, "", show[plus].type);
											++plus;
										}
										fclose(fileFacility);

										do
										{
											printf("Enter the facility ID : ");
											rewind(stdin);
											scanf("%s", &userInputFacility);

											//change to uppercase
											for (upper = 0; upper < 5; upper++)
											{
												userInputFacility[upper] = toupper(userInputFacility[upper]);
											}

											noFoundFacility = 0;
											for (compare = 0; compare < plus; compare++)
											{

												if (strcmp(userInputFacility, show[compare].id) == 0)
												{
													strcpy(modify.facilityId, userInputFacility);

													//today date cannot be modify
													modify.todayDate.day = book[i].todayDate.day;
													modify.todayDate.month = book[i].todayDate.month;
													modify.todayDate.year = book[i].todayDate.year;
													printf("Submission date (dd-mm-yyyy)  : %d-%d-%d\n", modify.todayDate.day, modify.todayDate.month, modify.todayDate.year);

													//booking date 
													do
													{
														do
														{
															do
															{
																printf("Date booking (dd-mm-yyyy) : ");
																rewind(stdin);
																scanf("%d-%d-%d", &modify.bookDate.day, &modify.bookDate.month, &modify.bookDate.year);

																invalid = dateChecking(modify.bookDate.day, modify.bookDate.month, modify.bookDate.year);

															} while (invalid != 0);

															// check cannot one day have more booking
															invalid = checkOneDay(userInputMem, modify.bookDate.day, modify.bookDate.month, modify.bookDate.year);
														} while (invalid != 0);

														//check before one day...
														if (modify.bookDate.year > modify.todayDate.year + 1 || modify.bookDate.year < modify.todayDate.year) {
															printf("\033[0;31mDate format is not available please enter again\033[0m\n");
														}
														else if (modify.bookDate.year == modify.todayDate.year) {
															//for same year checking
															if (modify.bookDate.month > modify.todayDate.month)
															{
																checkTime(&modify.formTime.hrs, &modify.toTime.hrs, modify.formTime.pmOrAm, modify.toTime.pmOrAm);
																//ask sure 
																askSureModify(book, nRecord, modify, i);

															}
															else if (modify.bookDate.month == modify.todayDate.month) {
																if (modify.bookDate.day > modify.todayDate.day) {

																	checkTime(&modify.formTime.hrs, &modify.toTime.hrs, modify.formTime.pmOrAm, modify.toTime.pmOrAm);
																	//ask sure
																	askSureModify(book, nRecord, modify, i);
																}
																else {
																	printf("\033[0;31mThe booking date must be one day before\033[0m\n");
																}
															}
															else {
																printf("\033[0;31mThe booking date must be one day before\033[0m\n");
															}
														}
														else {//book.bookDate.year == book.todayDate.year || book.bookDate.year == book.todayDate.year + 1

															checkTime(&modify.formTime.hrs, &modify.toTime.hrs, modify.formTime.pmOrAm, modify.toTime.pmOrAm);
															//ask sure
															askSureModify(book, nRecord, modify, i);
														}

													} while ((modify.bookDate.year > modify.todayDate.year + 1 || modify.bookDate.year < modify.todayDate.year) || ((modify.bookDate.year == modify.todayDate.year) && (modify.bookDate.month == modify.todayDate.month) && (modify.bookDate.day < modify.todayDate.day)) || ((modify.bookDate.year == modify.todayDate.year) && (modify.bookDate.month < modify.todayDate.month)));
												}
												else
												{
													++noFoundFacility;
												}
											}

											if (noFoundFacility == plus)
											{
												printf("\033[0;31mInvalid input please enter again\033[0m\n");
											}
										} while (noFoundFacility == plus);
									}
									else if (toupper(yesNo2) == 'N') {
										printf("\033[0;31mNo Record Found\033[0m\n");
									}
									else {
										printf("\033[0;31mInvalid input please enter again\033[0m\n");
									}
								} while (toupper(yesNo2) != 'N' && toupper(yesNo2) != 'Y');
							}
							else {
								noFoundMem++;
							}
						}
						fclose(fileMember);
						if (noFoundMem == nMem)
						{
							printf("\033[0;31mNo record found\033[0m\n");
						}

					}
					else {
						noFoundBook++;
					}
				}
				if (noFoundBook == nRecord)
				{
					printf("\033[0;31mNo Record Found\033[0m\n");
				}

			}
			do
			{
				printf("Continues ?? ('Y' = yes 'N' = no) > ");
				rewind(stdin);
				scanf("%c", &yesNo3);
				switch (toupper(yesNo3)) {
				case 'Y':
					system("cls");
					break;
				case 'N':
					break;
				default:
					printf("\033[0;31mInvalid input please enter again\033[0m\n");
				}
			} while (toupper(yesNo3) != 'Y' && toupper(yesNo3) != 'N');
		} while (toupper(yesNo3) != 'N');

	}
}

void checkNull(char* userChoice, char fileName[], char readFile[], char addFile[]) {

	//checkNull(&userChoice, "erika.txt", "r", "a");
	FILE* fileRead = fopen(fileName, readFile);//fopen("xinjie.bin", "rb");

	if (fileRead == NULL)
	{
		printf("\033[0;31mUnable to open the file\033[0m\n");
		do
		{
			printf("Do you want to create a file? ('Y' yes , 'N' no) > ");
			rewind(stdin);
			scanf("%c", &*userChoice);
			switch (toupper(*userChoice))
			{
			case 'Y':;
				FILE* fileAdd = fopen(fileName, addFile);//"a"
				fclose(fileAdd);
				printf("\033[2;36mFile create successfully..\033[0m\n");
				system("pause");
				Sleep(500);
				break;
			case 'N':
				printf("Turn back to the booking menu..\n"); break;
			default:
				printf("\033[0;31mInvalid code , please enter again\033[0m\n");
			}
		} while (toupper(*userChoice) != 'N' && toupper(*userChoice) != 'Y');
	}
	//fclose(fileRead);
}

int displayAllData() {

	FILE* fileRead = readXJ(1, &fileRead);

	int nSize = 0;

	Booking book;

	printf("%-10s%2s%-15s%4s%-15s%3s%-10s%3s%-10s%3s%-15s%6s%-17s%13s%-10s\n", "BOOKING ID", "", "SUBMISSION DATE", "", "BOOKING DATE", "", "START TIME", "", "END TIME", "", "MEMBER ID", "", "MEMBER NAME", "", "FACILITY ID");
	line(150);

	while (fread(&book, sizeof(Booking), 1, fileRead) != 0) {
		nSize++;
		printf("%-6s%8s%2d-%2d -%4d%6s%2d-%2d -%4d%10s%2d%2s%8s%2d%2s%9s%-15s%3s%-30s%3s%-10s\n", book.bookId, "", book.todayDate.day, book.todayDate.month, book.todayDate.year, "", book.bookDate.day, book.bookDate.month, book.bookDate.year, "", book.formTime.hrs, book.formTime.pmOrAm, "", book.toTime.hrs, book.toTime.pmOrAm, "", book.memberId, "", book.memberName, "", book.facilityId);

		/*printf("%10s%2d-%2d-%4d%10s%2d%s%8s%2d%s%9s%-15s%3s%-15s\n", "", book.bookDate.day, book.bookDate.month, book.bookDate.year, "", book.formTime.hrs, book.formTime.pmOrAm, "", book.toTime.hrs, book.toTime.pmOrAm, "", book.memberId, "", book.facilityId);*/
	}

	if (nSize == 0)
	{
		printf("\033[0;31m\t\t\tNo Record Found\033[0m\n");
	}
	fclose(fileRead);
	line(150);

	return nSize;
}

void askSureModify(Booking book[MAX_SIZE_BOOK], int nRecord, Booking modify, int change) {
	char yesNo;
	int i;

	do
	{
		printf("Sure to modify ?? ('Y' = yes 'N' = no) > ");
		rewind(stdin);
		scanf("%c", &yesNo);

		if (toupper(yesNo) == 'Y')
		{
			FILE* fileModify = fopen("xinjie.bin", "wb");
			for (i = 0; i < nRecord; i++)
			{
				if (change == i)
				{
					fwrite(&modify, sizeof(Booking), 1, fileModify);
				}
				else {
					fwrite(&book[i], sizeof(book[0]), 1, fileModify);
				}
			}
			fclose(fileModify);
			printf("\033[2;36mModify successful\033[0m\n");
		}
		else if (toupper(yesNo) == 'N') {
			printf("\033[0;31mModify unsuccessful\033[0m\n");
		}
		else {
			printf("\033[0;31mInvalid input please enter again\033[0m\n");
		}
	} while (toupper(yesNo) != 'N' && toupper(yesNo) != 'Y');
}

//through id to check the date cannot have more than one booking at 1 day
int checkOneDay(char memberId[6], int bDay, int bMonth, int bYear) {
	int invalid = 0;

	Booking book;

	FILE* fileCheck = readXJ(1, &fileCheck);

	while (fread(&book, sizeof(Booking), 1, fileCheck) != 0) {
		if (strcmp(memberId, book.memberId) == 0)
		{
			if ((bDay == book.bookDate.day) && (bMonth == book.bookDate.month) && (bYear == book.bookDate.year))
			{
				printf("\033[0;31mIt is unable to book more than one booking per day\033[0m\n");
				invalid++;
			}
		}
	}
	return invalid;
}

void deleteBook() {

	char userChoice = 'Y';
	int choice;

	checkNull(&userChoice, "xinjie.bin", "rb", "ab");

	if (toupper(userChoice) == 'Y')
	{
		do
		{
			system("cls");
			printf("Welcome to delete page ...\n");

			printf("1. Delete with booking id \n");
			printf("2. Fast delete all unrecord data \n");
			printf("3. Exit\n");
			printf("Enter your choice > ");
			rewind(stdin);
			scanf("%d", &choice);
			switch (choice) {
			case 1:
				delUseIdBook(); break;
			case 2:
				delAllUnnecessary(); break;
			case 3:
				break;
			default:
				printf("\033[0;31mInvaid input please enter again\033[0m\n");
			}
		} while (choice != 3);
	}
}

void delUseIdBook() {

	char userInput[6], month1[5], month2[5], yesNo, yesNo2;
	int nRecord, i, noFound, del, write, valid;

	Booking book[MAX_SIZE_BOOK];

	do
	{
		system("cls");
		nRecord = displayAllData();

		do
		{
			printf("Please enter the booking ID : ");
			/*rewind(stdin);
			scanf("%s", &userInput);*/

			valid = checkInput(userInput);

		} while (valid != 5);

		FILE* fileRead = fopen("xinjie.bin", "rb");
		i = 0;
		while (fread(&book[i], sizeof(book[0]), 1, fileRead) != 0)
		{
			i++;
		}
		fclose(fileRead);

		noFound = 0;
		for (i = 0; i < nRecord; i++)
		{
			if (strcmp(userInput, book[i].bookId) == 0) {
				printf("Show detail...\n");
				printf("BOOKING ID    : %s\n", book[i].bookId);
				printf("MEMBER ID     : %s\n", book[i].memberId);
				printf("MEMBER NAME   : %s\n", book[i].memberName);
				monthR(book[i].todayDate.month, month1);
				printf("DATE BOOK     : %d %s %d\n", book[i].todayDate.day, month1, book[i].todayDate.year);
				monthR(book[i].bookDate.month, month2);
				printf("BOOKING DATE  : %d %s %d\n", book[i].bookDate.day, month2, book[i].bookDate.year);
				printf("STARTING TIME : %d%s\n", book[i].formTime.hrs, book[i].formTime.pmOrAm);
				printf("END TIME      : %d%s\n", book[i].toTime.hrs, book[i].toTime.pmOrAm);
				printf("MEMBER ID     : %s\n", book[i].memberId);
				printf("MEMBER NAME   : %s\n", book[i].memberName);
				printf("FACILITY ID   : %s\n", book[i].facilityId);

				//ask confirm
				do
				{
					printf("Confirm to delete ?? ('Y' = yes 'N' = no) > ");
					rewind(stdin);
					scanf("%c", &yesNo);
					if (toupper(yesNo) == 'Y')
					{
						for (del = i; del < nRecord; del++)
						{
							if (del == nRecord - 1)
							{
								break;
							}
							else {
								strcpy(book[del].bookId, book[del + 1].bookId);
								strcpy(book[del].memberId, book[del + 1].memberId);
								strcpy(book[del].facilityId, book[del + 1].facilityId);
								strcpy(book[del].memberName, book[del + 1].memberName);
								strcpy(book[del].formTime.pmOrAm, book[del + 1].formTime.pmOrAm);
								strcpy(book[del].toTime.pmOrAm, book[del + 1].toTime.pmOrAm);
								book[del].bookDate.day = book[del + 1].bookDate.day;
								book[del].bookDate.month = book[del + 1].bookDate.month;
								book[del].bookDate.year = book[del + 1].bookDate.year;
								book[del].todayDate.day = book[del + 1].todayDate.day;
								book[del].todayDate.month = book[del + 1].todayDate.month;
								book[del].todayDate.year = book[del + 1].todayDate.year;
								book[del].formTime.hrs = book[del + 1].formTime.hrs;
								book[del].toTime.hrs = book[del + 1].toTime.hrs;
							}
						}

						FILE* fileWrite = fopen("xinjie.bin", "wb");
						for (write = 0; write < nRecord - 1; write++)
						{
							fwrite(&book[write], sizeof(book[0]), 1, fileWrite);
						}
						fclose(fileWrite);
						printf("\033[2;36mDelete successful\033[0m\n");

					}
					else if (toupper(yesNo) == 'N') {
						printf("\033[0;31mDelete unsuccessful\033[0m\n");
					}
					else {
						printf("\033[0;31mInvalid input please enter again\033[0m\n");
					}
				} while (toupper(yesNo) != 'N' && toupper(yesNo) != 'Y');
			}
			else {
				noFound++;
			}
		}
		if (noFound == nRecord)
		{
			printf("\033[0;31mNo record found\033[0m\n");
		}

		do
		{
			printf("Continue ?? ('Y' = yes 'N' = no) > ");
			rewind(stdin);
			scanf("%c", &yesNo2);
			switch (toupper(yesNo2)) {
			case 'Y':
				break;
			case 'N':
				break;
			default:
				printf("\033[0;31mInvalid input please enter again\033[0m\n");
			}
		} while (toupper(yesNo2) != 'N' && toupper(yesNo2) != 'Y');
	} while (toupper(yesNo2) != 'N');
}

//guai guai der...
void reportBook() {

	char userChoice = 'Y', monthW[5], yesNo;
	int size, month, year, male, female, ttlBook, i, highValue, highPlace[MAX_SIZE_FACILITY], placeSize, percentageM, percentageF;

	system("cls");

	checkNull(&userChoice, "xinjie.bin", "rb", "ab");

	if (toupper(userChoice) == 'Y')
	{
		CheckType check[MAX_SIZE_FACILITY];
		Booking book;
		struct Facility facility;
		Member mem;

		do
		{
			system("cls");

			printf("Welcome to report function....\n");
			size = checkFacilityType(check);//return back the struct array check

			printf("Enter month > ");
			rewind(stdin);
			scanf("%d", &month);

			printf("Enter year  > ");
			rewind(stdin);
			scanf("%d", &year);

			//compare date -> compare facility(typeF) -> compare member(M/F)

			FILE* fileBook = fopen("xinjie.bin", "rb");

			male = 0;
			female = 0;
			while (fread(&book, sizeof(Booking), 1, fileBook) != 0) {

				if ((month == book.bookDate.month) && (year == book.bookDate.year))//date compare
				{
					FILE* fileFacility = fopen("sauwei.bin", "rb");//compare facility id to get type
					while (fread(&facility, sizeof(struct Facility), 1, fileFacility) != 0) {

						if (strcmp(book.facilityId, facility.id) == 0)
						{
							FILE* fileMember = fopen("kaixin.txt", "r");//open to get the gender
							while (fscanf(fileMember, "%[^|]|%[^|]|%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%d-%d-%d\n", &mem.memberID, &mem.memberName, &mem.password, &mem.passwordRecover, &mem.gender, &mem.icNum, &mem.phoneNum, &mem.category, &mem.joinedDate.day, &mem.joinedDate.month, &mem.joinedDate.year) != EOF)
							{
								if (strcmp(book.memberId, mem.memberID) == 0) {

									if (mem.gender == 'M') {
										male++;
										maleFemale(check, book.bookId, mem.memberID, mem.gender, facility.type, size);
									}
									else {
										female++;
										maleFemale(check, book.bookId, mem.memberID, mem.gender, facility.type, size);
									}
								}
							}
							fclose(fileMember);
						}
					}
					fclose(fileFacility);
				}
			}
			fclose(fileBook);

			//print out the report
			monthR(month, monthW);
			printf("\nReport on %s %d\n", monthW, year);
			line(40);
			ttlBook = male + female;
			printf("\nTotal number booking in this month have %d\n", ttlBook);
			printf("No of Male booking in this month > %d\n", male);
			printf("No of Female booking in this month > %d\n\n", female);
			line(40);
			printf("For each type of facility : \n\n");

			highValue = 0;
			placeSize = 0;
			for (i = 0; i < size; i++)
			{
				check[i].ttl = check[i].male + check[i].female;

				//if same value or high
				if (check[i].ttl > highValue)
				{
					highPlace[0] = i;
					highValue = check[i].ttl;
					placeSize = 0;
				}
				else if (check[i].ttl == highValue) {
					++placeSize;
					highPlace[placeSize] = i;
				}

				printf("\033[1;4;35m%s\033[0m facility have total %d people book\n", check[i].typeF, check[i].ttl);
				printf("Male have %d people\n", check[i].male);
				printf("Female have %d people\n", check[i].female);

				if (check[i].ttl != 0)
				{
					percentageM = check[i].male / check[i].ttl;
					percentageF = check[i].female / check[i].ttl;

					if (percentageM > percentageF)
					{
						printf("The ratio between male and female is %d : %d the booking of male is more than female\n\n", percentageM, percentageF);
					}
					else {
						printf("The ratio between male and female is %d : %d the booking of female is more than male\n\n", percentageM, percentageF);
					}
				}
				else {
					printf("The ratio between male and female is 0 : 0\n\n");
				}
			}

			if (highValue == 0)
			{
				printf("There are no booking in this month\n");
			}
			else {
				if (placeSize == 0)//just got one highest
				{
					printf("The highest booking facility in %s %d is %s it have %d booking in month\n", monthW, year, check[highPlace[0]].typeF, highValue);
				}
				else {//got multiple highest
					printf("Have %d highest booking facility in %s %d is ", placeSize + 1, monthW, year);
					for (i = 0; i < placeSize + 1; i++)
					{
						if (i == placeSize)
						{
							printf("and %s ", check[highPlace[i]].typeF);
						}
						else {
							printf("%s ", check[highPlace[i]].typeF);
						}
					}
					printf("it have %d booking in month\n", highValue);
				}
			}

			do
			{
				printf("Continue ?? ('Y' = yes 'N' = no) > ");
				rewind(stdin);
				scanf("%c", &yesNo);
				switch (toupper(yesNo)) {
				case 'Y':
					break;
				case 'N':
					break;
				default:
					printf("\033[0;31mInvalid input please enter again\033[0m\n");
				}
			} while (toupper(yesNo) != 'Y' && toupper(yesNo) != 'N');
		} while (toupper(yesNo) != 'N');
	}
}

int checkFacilityType(CheckType check[MAX_SIZE_FACILITY]) {
	//char bookId[6], char memId[6], char gender, char fType
	int getType = 0, i, compare, noEqual;

	struct Facility show[MAX_SIZE_FACILITY];
	//CheckType check[MAX_SIZE_FACILITY];
	//Booking book;

	FILE* fileFacility = fopen("sauwei.bin", "rb");

	i = 0;
	while (fread(&show[i], sizeof(show[0]), 1, fileFacility) != 0)
	{
		if (i == 0)
		{
			strcpy(check[0].typeF, show[i].type);
			check[0].male = 0;
			check[0].female = 0;
			getType++;
		}
		else {
			//check different
			noEqual = 0;
			for (compare = 0; compare < getType; compare++)
			{
				if (strcmp(check[compare].typeF, show[i].type) != 0)
				{
					noEqual++;
				}
			}
			if (noEqual == getType)
			{
				strcpy(check[getType].typeF, show[i].type);
				check[getType].male = 0;
				check[getType].female = 0;
				getType++;
			}
		}
		i++;
	}
	fclose(fileFacility);
	return getType;
}

void maleFemale(CheckType check[MAX_SIZE_FACILITY], char bookId[6], char memId[6], char gender, char fType[30], int getType) {

	//bookfile
	Booking book;
	int i;

	FILE* fileBook = readXJ(1, &fileBook);

	while (fread(&book, sizeof(Booking), 1, fileBook) != 0)
	{
		if (strcmp(book.bookId, bookId) == 0)
		{
			if (strcmp(book.memberId, memId) == 0)
			{
				for (i = 0; i < getType; i++)
				{
					//printf("%s", check[i].typeF);
					//printf("%s\n", fType);
					if (strcmp(fType, check[i].typeF) == 0)
					{
						if (gender == 'M')
						{
							check[i].male = check[i].male + 1;
						}
						else {
							check[i].female = check[i].female + 1;
						}
					}
				}
			}
		}
	}
	fclose(fileBook);
}

void delAllUnnecessary() {
	char choice;

	do
	{
		system("cls");

		printf("What you need to delete.. \n");
		printf("M : Member \n");
		printf("F : Facility\n");
		printf("X : Exit\n");

		printf("Enter your choice : ");
		rewind(stdin);
		scanf("%c", &choice);

		switch (toupper(choice)) {
		case 'M':
			delMBook('M'); break;
		case 'F':
			delMBook('F'); break;
		case 'X':
			break;
		default:
			printf("\033[0;31mInvalid choice please enter again\033[0m\n");
		}
	} while (toupper(choice) != 'X');
}

void delMBook(char type) {

	int i, nSize, same, del, nodel;
	char month1[5], month2[5], yesNo, userChoice = 'Y';

	Booking book[MAX_SIZE_BOOK];
	Member mem;
	struct Facility facility;

	checkNull(&userChoice, "xinjie.bin", "rb", "ab");

	if (toupper(userChoice) == 'Y')
	{
		system("cls");
		FILE* fileBook = readXJ(1, &fileBook);

		i = 0;
		nSize = 0;
		while (fread(&book[i], sizeof(book[0]), 1, fileBook) != 0)
		{
			i++;
			nSize++;
		}
		fclose(fileBook);

		if (i == 0)
		{
			printf("\033[0;31mThe file is empty..\033[0m\n");
		}
		else {
			nodel = 0;//record how many record need del;
			for (i = 0; i < nSize; i++)
			{
				//check got compare or not ..
				if (toupper(type) == 'M')
				{
					same = 0;
					FILE* fileMem = fopen("kaixin.txt", "r");
					while (fscanf(fileMem, "%[^|]|%[^|]|%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%d-%d-%d\n", &mem.memberID, &mem.memberName, &mem.password, &mem.passwordRecover, &mem.gender, &mem.icNum, &mem.phoneNum, &mem.category, &mem.joinedDate.day, &mem.joinedDate.month, &mem.joinedDate.year) != EOF)
					{
						if (strcmp(book[i].memberName, mem.memberName) == 0)
						{
							++same;
							break;
						}
					}
				}
				else {
					same = 0;
					FILE* fileFacility = fopen("sauwei.bin", "rb");
					while (fread(&facility, sizeof(struct Facility), 1, fileFacility) != 0)
					{
						if (strcmp(book[i].facilityId, facility.id) == 0)
						{
							++same;
							break;
						}
					}
				}

				if (same == 0)
				{
					system("cls");
					if (toupper(type) == 'M')
					{
						printf("\033[0;31m%s member id no found!!\033[0m\n", book[i].bookId);
					}
					else {
						printf("\033[0;31m%s facility id no found!!\033[0m\n", book[i].bookId);
					}
					printf("BOOKING ID    : %s\n", book[i].bookId);
					printf("MEMBER ID     : %s\n", book[i].memberId);
					printf("MEMBER NAME   : %s\n", book[i].memberName);
					monthR(book[i].todayDate.month, month1);
					printf("DATE BOOK     : %d %s %d\n", book[i].todayDate.day, month1, book[i].todayDate.year);
					monthR(book[i].bookDate.month, month2);
					printf("BOOKING DATE  : %d %s %d\n", book[i].bookDate.day, month2, book[i].bookDate.year);
					printf("STARTING TIME : %d%s\n", book[i].formTime.hrs, book[i].formTime.pmOrAm);
					printf("END TIME      : %d%s\n", book[i].toTime.hrs, book[i].toTime.pmOrAm);
					printf("MEMBER ID     : %s\n", book[i].memberId);
					printf("MEMBER NAME   : %s\n", book[i].memberName);
					printf("FACILITY ID   : %s\n", book[i].facilityId);

					do
					{
						//ask del
						printf("Confirm to delete ?? ('Y' = yes 'N' = no) > ");
						rewind(stdin);
						scanf("%c", &yesNo);

						if (toupper(yesNo) == 'Y')
						{
							i--;
							++nodel;
							for (del = i + 1; del < nSize; del++)
							{
								if (del == (nSize - nodel))
								{
									break;
								}
								else {
									strcpy(book[del].bookId, book[del + 1].bookId);
									strcpy(book[del].memberId, book[del + 1].memberId);
									strcpy(book[del].facilityId, book[del + 1].facilityId);
									strcpy(book[del].memberName, book[del + 1].memberName);
									strcpy(book[del].formTime.pmOrAm, book[del + 1].formTime.pmOrAm);
									strcpy(book[del].toTime.pmOrAm, book[del + 1].toTime.pmOrAm);
									book[del].bookDate.day = book[del + 1].bookDate.day;
									book[del].bookDate.month = book[del + 1].bookDate.month;
									book[del].bookDate.year = book[del + 1].bookDate.year;
									book[del].todayDate.day = book[del + 1].todayDate.day;
									book[del].todayDate.month = book[del + 1].todayDate.month;
									book[del].todayDate.year = book[del + 1].todayDate.year;
									book[del].formTime.hrs = book[del + 1].formTime.hrs;
									book[del].toTime.hrs = book[del + 1].toTime.hrs;
								}
							}
							printf("\033[2;36mDelete successful\033[0m\n");
						}
						else if (toupper(yesNo) == 'N') {
							printf("\033[0;31mDelete unsuccessful\033[0m\n");
						}
						else {
							printf("\033[0;31mInvalid input please enter again\033[0m\n");
						}
					} while (toupper(yesNo) != 'Y' && toupper(yesNo) != 'N');
					if ((nSize - nodel) == 0)
					{
						break;
					}
				}
			}

			if (nodel != 0)
			{
				FILE* fileWrite = readXJ(2, &fileWrite);
				for (i = 0; i < (nSize - nodel); i++)
				{
					fwrite(&book[i], sizeof(book[0]), 1, fileWrite);
				}
				fclose(fileWrite);
				printf("\033[2;36mNo matching data found again\033[0m\n");
			}
			else {
				printf("\033[0;31mNo matching data found\033[0m\n");
			}
		}
		system("pause");
	}

}

void mainStaff() {

	int select, getNum;

	do
	{
		system("cls");

		printf("\t                     LOGIN OR CREATE A NEW ACCOUNT    \n");

		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m1\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m2\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m            LOGIN           \033[0;35m|\t       \033[0;31m|\033[0m      CREATE A NEW ACC      \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n");
		printf("\n\t                  \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m3\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0m");
		printf("\n\t                  \033[1;31m|                            \033[0;34m|\033[0m\t");
		printf("\n\t                  \033[0;33m|\033[0m             EXIT           \033[0;35m|\033[0m\t");
		printf("\n\t                  \033[0;32m|                            \033[0;31m|\033[0m\t");
		printf("\n\t                  \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0m\t\n");


		printf("Enter your choice > ");
		rewind(stdin);
		scanf("%d", &select);

		switch (select) {
		case 1:
			getNum = loginStaff();
			if (getNum == 1) {
				submenuStaff();
			}
			break;
		case 2:
			addStaff();
			break;
		case 3:
			break;
		default:
			printf("\033[0;31mInvalid choice, please enter again\033[0m\n");
		}
	} while (select != 3);

	Sleep(600);
}

int loginStaff() {

	Staff info[MAX_SIZE_STAFF];

	int i, searchError, compare, nStaff, returnValue = 0, wrgPass;
	char staffInput[7], staffPass[10], userChoice = 'Y', choice, recovery = 'Y', valid;

	checkNull(&userChoice, "erika.txt", "r", "a");

	if (toupper(userChoice) == 'Y') {

		system("cls");

		FILE* staff = fopen("erika.txt", "r");

		//read inside array
		nStaff = 0;
		i = 0;
		while (fscanf(staff, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c|%d|%d-%d-%d\n", &info[i].staffId, &info[i].staffName, &info[i].pass.pwd, &info[i].pass.pwdRecovery, &info[i].position, &info[i].staffGender, &info[i].age, &info[i].staffBirthday.day, &info[i].staffBirthday.month, &info[i].staffBirthday.year) != EOF)
		{
			++nStaff;
			++i;
		}
		fclose(staff);

		//start login
		printf("\n");
		printf("\033[0;32m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35-\033[0;31m-\033[1;31m-\033[0;33m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[0;32m+\033[0m\n");
		printf(" WELCOME TO STAFF LOGIN PAGE! \n");
		printf("\033[0;32m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35-\033[0;31m-\033[1;31m-\033[0;33m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[0;32m+\033[0m\n");

		wrgPass = 0;
		do
		{
			printf("Enter your Staff Id : ");
			rewind(stdin);
			scanf("%s", &staffInput);

			printf("Enter your password : ");
			rewind(stdin);
			scanf("%s", &staffPass);

			compare = 0;
			searchError = 0;

			//compare the staff id and password
			for (i = 0; i < nStaff; i++)
			{
				if (strcmp(staffInput, info[i].staffId) == 0)
				{
					if (strcmp(staffPass, info[i].pass.pwd) == 0) {
						printf("\033[2;36mLogin successful!\033[0m\n\n");
						compare += i;
						returnValue++;// 0 = > 1
						system("pause");
					}
					else {
						printf("\033[0;31mIncorrect password!!\033[0m\n");
						//ID True Password False
						wrgPass++;
						if (wrgPass >= 3) {
							//ask recovery
							do
							{
								printf("Do you want to recovery your password? ('Y' = yes 'N' = no) > ");
								rewind(stdin);
								scanf("%c", &recovery);
								switch (toupper(recovery)) {
								case 'Y':
									passwordRecoveryStaff(&valid);
									system("cls");
									if (valid == 'T')
									{
										printf("\033[2;36mPassword Recovery successful please login again..\033[0m\n");
									}
									else {
										printf("\033[0;31mPassword Recovery unsuccessful please try again\033[0m\n");
									}
									Sleep(600);
									break;
								case 'N':
									break;
								default:
									printf("\033[0;31mInvalid code please enter again\033[0m\n");
								}
							} while (toupper(recovery) != 'N' && toupper(recovery) != 'Y');

						}
					}
				}
				else {
					++searchError;
				}
			}//if id false will breakout

			if (toupper(recovery) == 'N')
			{
				printf("\033[0;31mSorry you have enter wrong password 3 time please try again later\033[0m\n");
				system("pause");
				break;
			}
		} while ((strcmp(staffInput, info[compare].staffId) == 0) && (strcmp(staffPass, info[compare].pass.pwd) != 0));
		//strcmp(staffInput, info[i].staffId) == 0 && strcmp(staffPass, info[i].pass.pwd) == 0

		if (searchError == nStaff) {
			printf("\n\033[0;31mStaff ID no found!!\033[0m\n");
			do
			{
				printf("Apply for a new Staff ID ? ('Y' = Yes , 'N' = No) : ");
				rewind(stdin);
				scanf("%c", &choice);
				//Check choice
				switch (toupper(choice)) {
				case 'Y':
					addStaff();
					break;
				case 'N':
					break;
				default:
					printf("\033[0;31mInvalid code please enter again\033[0m\n");
				}
			} while (toupper(choice) != 'Y' && toupper(choice) != 'N');
		}
	}

	return returnValue;
}

void addStaff() {

	Staff info;//"a"

	char id[7], userChoice = 'Y', yesNo;
	int invalid, error;

	checkNull(&userChoice, "erika.txt", "r", "a");

	if (toupper(userChoice) == 'Y')
	{
		do
		{
			system("cls");
			printf("\n");
			printf("\033[0;32m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35-\033[0;31m-\033[1;31m-\033[0;33m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;32m+\033[0m\n");
			printf(" WELCOME TO ADD A NEW STAFF PAGE! \n");
			printf("\033[0;32m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35-\033[0;31m-\033[1;31m-\033[0;33m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;32m+\033[0m\n");

			Sleep(600);

			printf("Enter your staff name                      : ");
			rewind(stdin);
			scanf("%[^\n]", &info.staffName);

			printf("Enter your password                        : ");
			rewind(stdin);
			scanf("%s", &info.pass.pwd);

			printf("-----Set the password recovery question ----\n");
			printf("What the movie you like                    : ");
			rewind(stdin);
			scanf("%[^\n]", &info.pass.pwdRecovery);

			printf("Enter your position                        : ");
			rewind(stdin);
			scanf("%s", &info.position);

			do
			{
				printf("Enter your gender ('M' = male 'F' = female) : ");//m 
				rewind(stdin);
				scanf("%c", &info.staffGender);

				if (toupper(info.staffGender) != 'F' && toupper(info.staffGender) != 'M') {
					printf("\033[0;31mInvalid code please enter again\033[0m\n");
				}
			} while (toupper(info.staffGender) != 'F' && toupper(info.staffGender) != 'M');

			printf("Enter your age                               : ");
			rewind(stdin);
			scanf("%d", &info.age);

			do
			{
				printf("Enter your birth date (dd-mm-yyyy)           : ");
				rewind(stdin);
				scanf("%d-%d-%d", &info.staffBirthday.day, &info.staffBirthday.month, &info.staffBirthday.year);

				invalid = dateChecking(info.staffBirthday.day, info.staffBirthday.month, info.staffBirthday.year);//wrong++

			} while (invalid != 0);

			autoCreateStaffId(&error, id);//auto creating

			if (error == 1) {
				printf("\033[0;31mSorry the adding is unsucessful..\033[0m\n");
			}
			else {
				strcpy(info.staffId, id);

				FILE* fileAdd = fopen("erika.txt", "a");
				fprintf(fileAdd, "%s|%s|%s|%s|%s|%c|%d|%d-%d-%d\n", info.staffId, info.staffName, info.pass.pwd, info.pass.pwdRecovery, info.position, toupper(info.staffGender), info.age, info.staffBirthday.day, info.staffBirthday.month, info.staffBirthday.year);
				fclose(fileAdd);
			}

			do
			{
				printf("\nContinue ?? ('Y' = yes 'N' = no) > ");
				rewind(stdin);
				scanf("%c", &yesNo);
				switch (toupper(yesNo)) {
				case 'Y':
					break;
				case 'N':
					break;
				default:
					printf("\033[0;31mInvalid code please enter again\033[0m\n");
				}
			} while (toupper(yesNo) != 'N' && toupper(yesNo) != 'Y');
		} while (toupper(yesNo) != 'N');
	}
}

void autoCreateStaffId(int* error, char id[7]) {

	int i, firstNum, secondNum, thirdNum, fourthNum;//ascii table 
	char str[7];//ST0001
	*error = 0;
	FILE* staff = fopen("erika.txt", "r");

	Staff info[MAX_SIZE_STAFF];
	i = 0;
	while (fscanf(staff, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c|%d|%d-%d-%d\n", &info[i].staffId, &info[i].staffName, &info[i].pass.pwd, &info[i].pass.pwdRecovery, &info[i].position, &info[i].staffGender, &info[i].age, &info[i].staffBirthday.day, &info[i].staffBirthday.month, &info[i].staffBirthday.year) != EOF) {
		++i;//get the last id use 
	}
	fclose(staff);

	if (i == 0)
	{
		strcpy(id, "ST0001");
		printf("\033[2;36mProcess successfull, your staff ID is %s\033[0m\n", id);
	}
	else {

		strcpy(str, info[i - 1].staffId);
		//printf("%s", str);
		//copy the id from the array to get the last staff id

		firstNum = (int)str[5] + 1;//char 1 => int 49
		if (firstNum > 57) {//char 9 == int 57 ST0010 ST9999
			firstNum = 48;//char 0
			str[5] = (char)firstNum;

			secondNum = (int)str[4] + 1;
			if (secondNum > 57)
			{
				secondNum = 48;
				str[4] = (char)secondNum;

				thirdNum = (int)str[3] + 1;
				if (thirdNum > 57)
				{
					thirdNum = 48;
					str[3] = (char)thirdNum;

					fourthNum = (int)str[2] + 1;
					if (fourthNum > 57)
					{
						printf("\033[0;31mThe Staff is until the maximum number, it is unable to add\033[0m\n");
						*error = 1;//can delete der
					}
					else {
						str[2] = (char)thirdNum;
						strcpy(id, str);
						printf("\033[2;36mProcess successfull, your staff ID is %s\033[0m\n", id);
					}
				}
				else {
					str[3] = (char)thirdNum;
					strcpy(id, str);
					printf("\033[2;36mProcess successfull, your staff ID is %s\033[0m\n", id);
				}
			}
			else {
				str[4] = (char)secondNum;
				strcpy(id, str);
				printf("\033[2;36mProcess successfull, your staff ID is %s\033[0m\n", id);
			}
		}
		else {
			str[5] = (char)firstNum;
			strcpy(id, str);//strcpy to let id output the char
			printf("\033[2;36mProcess successfull, your staff ID is %s\033[0m\n", id);
		}
	}

}

void submenuStaff() {

	int choice;
	do
	{
		system("cls");

		printf("\n\t\t\t   MAIN MENU-STAFF INFORMATION SYSTEM\n");
		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m1\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m2\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m     ADD NEW STAFF ACC      \033[0;35m|\t       \033[0;31m|\033[0m     DISPLAY STAFF INFO     \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n");
		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m3\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m4\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m     SEARCH STAFF INFO      \033[0;35m|\t       \033[0;31m|\033[0m     DELETE STAFF INFO      \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n");
		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m5\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m6\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m      EDIT STAFF INFO       \033[0;35m|\t       \033[0;31m|\033[0m            EXIT            \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n\n");

		printf("Please enter your option (1~6) : ");
		rewind(stdin);
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			addStaff();
			break;
		case 2:
			displayStaff();
			break;
		case 3:
			searchStaff();
			break;
		case 4:
			deleteStaff();
			break;
		case 5:
			modifyStaff();
			break;
		case 6:
			printf("\nThank you!\n");
			break;
		default:
			printf("\033[0;31mInvalid choice!, please enter again\033[0m\n\n");
		}
	} while (choice != 6);
}

void displayStaff() {

	system("cls");

	char userChoice = 'Y';
	int i = 0;

	Staff info;

	checkNull(&userChoice, "erika.txt", "r", "a");

	if (toupper(userChoice) == 'Y')
	{
		printf("\n");
		printf("\033[0;32m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35-\033[0;31m-\033[1;31m-\033[0;33m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;32m+\033[0m\n");
		printf(" Welcome To Display Staff Information!\n");
		printf("\033[0;32m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35-\033[0;31m-\033[1;31m-\033[0;33m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;32m+\033[0m\n");
		printf("\n");
		printf("+--------+     +--------------+     +---------------+     +--------+     +-------+     +---------+\n");
		printf(" Staff ID         Staff Name         Staff positions        Gender          Age          Brithday \n");
		printf("+--------+     +--------------+     +---------------+     +--------+     +-------+     +---------+\n");

		FILE* staff = fopen("erika.txt", "r");

		while (fscanf(staff, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c|%d|%d-%d-%d\n", &info.staffId, &info.staffName, &info.pass.pwd, &info.pass.pwdRecovery, &info.position, &info.staffGender, &info.age, &info.staffBirthday.day, &info.staffBirthday.month, &info.staffBirthday.year) != EOF) {
			printf("%8s %18s %22s %12s%c %14d %10d-%d-%d\n", info.staffId, info.staffName, info.position, "", info.staffGender, info.age, info.staffBirthday.day, info.staffBirthday.month, info.staffBirthday.year);
			i++;
		}
		fclose(staff);

		if (i == 0)
		{
			printf("\t\t\t\033[0;31mNo Record Found\033[0m\n");
		}

		printf("+--------+     +--------------+     +---------------+     +--------+     +-------+     +---------+\n");
		printf("\n< %d staff listed >\n\n", i);
		printf("\n");

		system("pause");
	}
}

void searchStaff() {

	Staff info;

	char userChoice = 'Y', searchId[7], searchAgain;
	int nSize, notFound;

	checkNull(&userChoice, "erika.txt", "r", "a");

	if (toupper(userChoice) == 'Y')
	{


		do
		{
			system("cls");

			printf("\n");
			printf("\033[0;32m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35-\033[0;31m-\033[1;31m-\033[0;33m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;32m+\033[0m\n");
			printf(" WELCOME TO SEARCH STAFF PAGE! \n");
			printf("\033[0;32m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35-\033[0;31m-\033[1;31m-\033[0;33m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;32m+\033[0m\n");

			printf("Search Staff with ID : ");
			rewind(stdin);
			scanf("%s", searchId);

			printf("\nprocessing...\n\n");
			Sleep(500);

			FILE* staff = fopen("erika.txt", "r");
			nSize = 0;
			notFound = 0;
			while (fscanf(staff, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c|%d|%d-%d-%d\n", &info.staffId, &info.staffName, &info.pass.pwd, &info.pass.pwdRecovery, &info.position, &info.staffGender, &info.age, &info.staffBirthday.day, &info.staffBirthday.month, &info.staffBirthday.year) != EOF) {
				nSize++;
				if (strcmp(searchId, info.staffId) == 0)
				{
					printf("+----------------------------+\n");
					printf(" Staff ID        : %s\n", info.staffId);
					printf(" Staff Name      : %s\n", info.staffName);
					printf(" Staff Position  : %s\n", info.position);
					printf(" Staff Gender    : %c\n", info.staffGender);
					printf(" Staff Age       : %d\n", info.age);
					printf(" Staff Brithday  : %d-%d-%d\n", info.staffBirthday.day, info.staffBirthday.month, info.staffBirthday.year);
					printf("+----------------------------+\n\n");
				}
				else {
					notFound++;
				}
			}
			fclose(staff);
			if (notFound == nSize)
			{
				printf("\033[0;31mNo Record Found\033[0m\n");
			}
			do
			{
				printf("Continues ?? ('Y' = yes 'N' = no) > ");
				rewind(stdin);
				scanf("%c", &searchAgain);
				switch (toupper(searchAgain)) {
				case 'Y':
					system("cls");
					break;
				case 'N':
					break;
				default:
					printf("\033[0;31mInvalid code please enter again\033[0m\n");
				}
			} while (toupper(searchAgain) != 'N' && toupper(searchAgain) != 'Y');
		} while (toupper(searchAgain) != 'N');
	}
}

void deleteStaff() {

	Staff info[MAX_SIZE_STAFF];

	char userChoice = 'Y', userInput[7], yesNo, delAgain;
	int i, nRecord, change, noFound, reWrite, check = 1, del;

	checkNull(&userChoice, "erika.txt", "r", "a");

	if (toupper(userChoice) == 'Y')
	{

		do
		{
			system("cls");
			printf("\n");
			printf("\033[0;32m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35-\033[0;31m-\033[1;31m-\033[0;33m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;32m+\033[0m\n");
			printf(" WELCOME TO DELETE STAFF PAGE! \n");
			printf("\033[0;32m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35-\033[0;31m-\033[1;31m-\033[0;33m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;32m+\033[0m\n");

			FILE* fileRead = fopen("erika.txt", "r");
			i = 0;
			nRecord = 0;
			while (fscanf(fileRead, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c|%d|%d-%d-%d\n", &info[i].staffId, &info[i].staffName, &info[i].pass.pwd, &info[i].pass.pwdRecovery, &info[i].position, &info[i].staffGender, &info[i].age, &info[i].staffBirthday.day, &info[i].staffBirthday.month, &info[i].staffBirthday.year) != EOF)
			{
				++nRecord;
				i++;
			}
			fclose(fileRead);

			printf("Enter Staff ID : ");
			rewind(stdin);
			scanf("%s", &userInput);

			noFound = 0;
			for (i = 0; i < nRecord; i++)
			{
				if (strcmp(userInput, info[i].staffId) == 0)
				{
					printf("+----------------------------+\n");
					printf(" Staff ID          : %s\n", info[i].staffId);
					printf(" Staff Name        : %s\n", info[i].staffName);
					printf(" Password          : %s\n", info[i].pass.pwd);
					printf(" Password Recovery : %s\n", info[i].pass.pwdRecovery);
					printf(" Staff Position    : %s\n", info[i].position);
					printf(" Staff Gender      : %c\n", info[i].staffGender);
					printf(" Staff Age         : %d\n", info[i].age);
					printf(" Staff Brithday    : %d-%d-%d\n", info[i].staffBirthday.day, info[i].staffBirthday.month, info[i].staffBirthday.year);
					printf("+----------------------------+\n\n");
					do
					{
						printf("Confirm to delete ? ('Y' = yes 'N' = no) > ");
						rewind(stdin);
						scanf("%c", &yesNo);
						if (toupper(yesNo) == 'Y')
						{
							for (change = i; change < nRecord; change++)
							{
								//nRecord = 6 null
								//0 1 2 3 4 5 6 6
								if (change == nRecord - 1)
								{
									break;
								}
								else {
									strcpy(info[change].staffId, info[change + 1].staffId);
									strcpy(info[change].staffName, info[change + 1].staffName);
									strcpy(info[change].pass.pwd, info[change + 1].pass.pwd);
									strcpy(info[change].pass.pwdRecovery, info[change + 1].pass.pwdRecovery);
									strcpy(info[change].position, info[change + 1].position);
									info[change].staffGender = info[change + 1].staffGender;
									info[change].age = info[change + 1].age;
									info[change].staffBirthday.day = info[change + 1].staffBirthday.day;
									info[change].staffBirthday.month = info[change + 1].staffBirthday.month;
									info[change].staffBirthday.year = info[change + 1].staffBirthday.year;
								}
							}
							FILE* fileWrite = fopen("erika.txt", "w");
							for (del = 0; del < nRecord - 1; del++)
							{
								fprintf(fileWrite, "%s|%s|%s|%s|%s|%c|%d|%d-%d-%d\n", info[del].staffId, info[del].staffName, info[del].pass.pwd, info[del].pass.pwdRecovery, info[del].position, toupper(info[del].staffGender), info[del].age, info[del].staffBirthday.day, info[del].staffBirthday.month, info[del].staffBirthday.year);
							}
							fclose(fileWrite);

							printf("Record is delete successful\n");

						}
						else if (toupper(yesNo) == 'N') {
							printf("The information for %s have not delete\n", userInput);
						}
						else {
							printf("Invalid code please enter again\n");
						}
					} while (toupper(yesNo) != 'N' && toupper(yesNo) != 'Y');
				}
				else {
					noFound++;
				}
			}

			if (noFound == nRecord) {
				printf("\033[0;31mNo Record Found\033[0m\n");
			}

			do
			{
				printf("Continues ?? ('Y' = yes 'N' = no) > ");
				rewind(stdin);
				scanf("%c", &delAgain);
				switch (toupper(delAgain)) {
				case 'Y':
					system("cls");
					break;
				case 'N':
					break;
				default:
					printf("\033[0;31mInvalid code please enter again\033[0m\n");
				}
			} while (toupper(delAgain) != 'N' && toupper(delAgain) != 'Y');
		} while (toupper(delAgain) != 'N');
	}

}

void passwordRecoveryStaff(char* valid) {

	char userChoice = 'Y', staffId[7], securityPass[20], yesNo;
	int wrgSecurityAns = 0, noFound, nSize;

	*valid = 'F';

	Staff info;
	checkNull(&userChoice, "erika.txt", "r", "a");

	if (toupper(userChoice) == 'Y')
	{
		do
		{
			do
			{
				system("cls");
				printf("\n");
				printf("\033[0;32m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35-\033[0;31m-\033[1;31m-\033[0;33m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;32m+\033[0m\n");
				printf(" WELCOME TO PASSWORD RECOVERY PAGE! \n");
				printf("\033[0;32m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35-\033[0;31m-\033[1;31m-\033[0;33m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;32m+\033[0m\n");

				printf("Enter your Staff ID : ");
				rewind(stdin);
				scanf("%s", &staffId);

				printf("-----Security question -----\n");
				printf("What the movie you like ? : ");
				rewind(stdin);
				scanf("%[^\n]", &securityPass);

				noFound = 0;
				nSize = 0;
				FILE* staff = fopen("erika.txt", "r");
				while (fscanf(staff, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c|%d|%d-%d-%d\n", &info.staffId, &info.staffName, &info.pass.pwd, &info.pass.pwdRecovery, &info.position, &info.staffGender, &info.age, &info.staffBirthday.day, &info.staffBirthday.month, &info.staffBirthday.year) != EOF)
				{
					nSize++;
					if (strcmp(staffId, info.staffId) == 0)
					{
						if (strcmp(securityPass, info.pass.pwdRecovery) == 0)
						{
							printf("Your password and details are showing...\n");
							Sleep(500);
							printf("+------------------------------+\n");
							printf(" Staff ID          : %s\n", info.staffId);
							printf(" Staff Name        : %s\n", info.staffName);
							printf(" Password          : %s\n", info.pass.pwd);
							printf(" Password Recovery : %s\n", info.pass.pwdRecovery);
							printf(" Staff Position    : %s\n", info.position);
							printf(" Staff Gender      : %c\n", info.staffGender);
							printf(" Staff Age         : %d\n", info.age);
							printf(" Staff Brithday    : %d-%d-%d\n", info.staffBirthday.day, info.staffBirthday.month, info.staffBirthday.year);
							printf("+------------------------------+\n\n");
							*valid = 'T';
							break;
						}
						else {
							printf("\033[0;31mIncorrect secuirty answer, please ender again.\033[0m\n");
							wrgSecurityAns++;
							break;
						}
					}
					else {
						noFound++;
					}
				}
				fclose(staff);

				if (wrgSecurityAns > 2)
				{
					printf("\033[0;31mSorry, you have insect wrong answer more than two times please try again later\033[0m\n");
					break;
				}
			} while ((strcmp(staffId, info.staffId) == 0) && (strcmp(securityPass, info.pass.pwdRecovery) != 0));

			if (noFound == nSize)
			{
				printf("\033[0;31mNo record found\033[0m\n");
			}

			do
			{
				printf("Turn back to staff menu ('Y' = yes 'N' = no) > ");
				rewind(stdin);
				scanf("%c", &yesNo);
				switch (toupper(yesNo)) {
				case 'Y':
					break;
				case 'N':
					if (wrgSecurityAns > 2)
					{
						printf("\033[0;31mSorry, you have insect wrong answer two times please try again later\033[0m\n");
						system("pause");
					}
					system("cls");
					break;
				default:
					printf("\033[0;31mInvalid choice please enter again\033[0m\n");
				}
			} while (toupper(yesNo) != 'N' && toupper(yesNo) != 'Y');

			if (wrgSecurityAns > 2)
			{
				if (toupper(yesNo) == 'N')
				{
					break;
				}
			}
		} while (toupper(yesNo) != 'Y');

	}
}

void modifyStaff() {

	char userChoice = 'Y', userInput[7], yesNo, yesNo2;
	int noFound, nSize, i, invalid, compare, change;

	Staff info[MAX_SIZE_STAFF];
	Staff modify;

	checkNull(&userChoice, "erika.txt", "r", "a");

	if (toupper(userChoice) == 'Y')
	{
		do
		{
			system("cls");
			printf("\033[0;32m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0m\n");
			printf(" WELCOME TO MODIFY PAGE! \n");
			printf("\033[0;32m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0m\n");

			printf("Enter the Staff ID : ");
			rewind(stdin);
			scanf("%s", &userInput);

			FILE* fileRead = fopen("erika.txt", "r");

			nSize = 0;
			i = 0;
			while (fscanf(fileRead, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c|%d|%d-%d-%d\n", &info[i].staffId, &info[i].staffName, &info[i].pass.pwd, &info[i].pass.pwdRecovery, &info[i].position, &info[i].staffGender, &info[i].age, &info[i].staffBirthday.day, &info[i].staffBirthday.month, &info[i].staffBirthday.year) != EOF)
			{
				nSize++;
				i++;
			}

			fclose(fileRead);

			noFound = 0;
			for (i = 0; i < nSize; i++)
			{
				if (strcmp(userInput, info[i].staffId) == 0) {
					printf("Show the detail...\n");
					printf("+----------------------------+\n");
					printf(" Staff ID          : %s\n", info[i].staffId);
					printf(" Staff Name        : %s\n", info[i].staffName);
					printf(" Password          : %s\n", info[i].pass.pwd);
					printf(" Password Recovery : %s\n", info[i].pass.pwdRecovery);
					printf(" Staff Position    : %s\n", info[i].position);
					printf(" Staff Gender      : %c\n", info[i].staffGender);
					printf(" Staff Age         : %d\n", info[i].age);
					printf(" Staff Birthday    : %d-%d-%d\n", info[i].staffBirthday.day, info[i].staffBirthday.month, info[i].staffBirthday.year);
					printf("+----------------------------+\n\n");

					printf(" Start to modify\n");
					strcpy(modify.staffId, info[i].staffId);
					printf(" Staff ID                             : %s\n", modify.staffId);

					printf(" Staff Name                           : ");
					rewind(stdin);
					scanf("%[^\n]", &modify.staffName);

					printf(" Password                             : ");
					rewind(stdin);
					scanf("%s", &modify.pass.pwd);

					printf("-----Set the password recovery question ----\n");
					printf(" What the movie you like              : ");
					rewind(stdin);
					scanf("%[^\n]", &modify.pass.pwdRecovery);

					printf(" Staff Position                       : ");
					rewind(stdin);
					scanf("%[^\n]", &modify.position);

					do
					{
						printf(" Staff Gender (F = female M = male)   : ");
						rewind(stdin);
						scanf("%c", &modify.staffGender);//m

						if (toupper(modify.staffGender) != 'M' && toupper(modify.staffGender) != 'F')
						{
							printf("\033[0;31mInvalid code please enter again\033[0m\n");
						}
					} while (toupper(modify.staffGender) != 'M' && toupper(modify.staffGender) != 'F');

					printf(" Staff Age                            : ");
					rewind(stdin);
					scanf("%d", &modify.age);

					do
					{
						printf(" Staff Birthday  (dd-mm-yyyy)         : ");
						rewind(stdin);
						scanf("%d-%d-%d", &modify.staffBirthday.day, &modify.staffBirthday.month, &modify.staffBirthday.year);
						invalid = dateChecking(modify.staffBirthday.day, modify.staffBirthday.month, modify.staffBirthday.year);
					} while (invalid != 0);

					//ask confirm
					do
					{
						printf("Confirm to modify it ? ('Y' = yes 'N' = no) > ");
						rewind(stdin);
						scanf("%c", &yesNo);
						switch (toupper(yesNo)) {
						case 'Y':
							strcpy(info[i].staffName, modify.staffName);
							strcpy(info[i].pass.pwd, modify.pass.pwd);
							strcpy(info[i].pass.pwdRecovery, modify.pass.pwdRecovery);
							strcpy(info[i].position, modify.position);
							info[i].staffGender = toupper(modify.staffGender);
							info[i].age = modify.age;
							info[i].staffBirthday.day = modify.staffBirthday.day;
							info[i].staffBirthday.month = modify.staffBirthday.month;
							info[i].staffBirthday.year = modify.staffBirthday.year;

							FILE* fileWrite = fopen("erika.txt", "w");
							for (change = 0; change < nSize; change++)
							{
								fprintf(fileWrite, "%s|%s|%s|%s|%s|%c|%d|%d-%d-%d\n", info[change].staffId, info[change].staffName, info[change].pass.pwd, info[change].pass.pwdRecovery, info[change].position, info[change].staffGender, info[change].age, info[change].staffBirthday.day, info[change].staffBirthday.month, info[change].staffBirthday.year);
							}
							fclose(fileWrite);
							printf("\033[2;36mModify successful\033[0m\n");
							break;
						case 'N':
							printf("\033[0;31mModify unsucessful\033[0m\n");
							break;
						default:
							printf("\033[0;31mInvalid choice please enter again\033[0m\n");
						}
					} while (toupper(yesNo) != 'N' && toupper(yesNo) != 'Y');

				}
				else {
					noFound++;
				}
			}
			if (noFound == nSize)
			{
				printf("\033[0;31mNo record found\033[0m\n");
			}

			do
			{
				printf("Continues ?? ('Y' = yes 'N' = no) > ");
				rewind(stdin);
				scanf("%c", &yesNo2);
				if (toupper(yesNo2) != 'N' && toupper(yesNo2) != 'Y')
				{
					printf("\033[0;31mInvalid choice please enter again\033[0m\n");
				}
				else if (toupper(yesNo2) == 'Y') {
					system("cls");
				}
			} while (toupper(yesNo2) != 'N' && toupper(yesNo2) != 'Y');

		} while (toupper(yesNo2) != 'N');
	}
}

void mainFacility() {

	int getNum, choice1;

	do
	{
		system("cls");

		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m1\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m2\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m         STAFF LOGIN        \033[0;35m|\t       \033[0;31m|\033[0m            EXIT            \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n");


		/*	printf("\n\t +----------- ^-^  #1---------+        +----------- ^-^ #2----------+");
			printf("\n\t |                            |\t       |                            |");
			printf("\n\t |        STAFF LOGIN         |\t       |            EXIT	         |");
			printf("\n\t |                            |\t       |                            |");
			printf("\n\t +----------------------------+\t       +----------------------------+\n");*/

		printf("Enter your choice > ");
		rewind(stdin);
		scanf("%d", &choice1);

		switch (choice1) {
		case 1:
			getNum = loginStaff();
			if (getNum == 1)
			{
				submenuFacility();
			}
			break;
		case 2:
			break;
		default:
			printf("\033[0;31mInvalid choice, please enter again\033[0m\n");
		}
	} while (choice1 != 2);

}

void submenuFacility() {

	int choice;
	do
	{
		system("cls");

		printf("\n\t                     ---- FACILITY OF THE CLUB ----           \n");
		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m1\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m2\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m             ADD            \033[0;35m|\t       \033[0;31m|\033[0m            DISPLAY         \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n");
		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m3\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m4\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m            SEARCH          \033[0;35m|\t       \033[0;31m|\033[0m            MODIFY          \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n");
		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m5\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m6\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m            DELETE          \033[0;35m|\t       \033[0;31m|\033[0m            REPORT          \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n\n");
		printf("\n\t                  \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m0\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0m");
		printf("\n\t                  \033[1;31m|                            \033[0;34m|\033[0m\t");
		printf("\n\t                  \033[0;33m|\033[0m             EXIT           \033[0;35m|\033[0m\t");
		printf("\n\t                  \033[0;32m|                            \033[0;31m|\033[0m\t");
		printf("\n\t                  \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0m\t\n");



		/*printf("\n\t                     ---- FACILITY OF THE CLUB ----           \n");
		printf("\n\t +----------- ^-^  #1---------+\t       +----------- ^-^ #2----------+");
		printf("\n\t |                            |\t       |                            |");
		printf("\n\t |             ADD            |\t       |           DISPLAY          |");
		printf("\n\t |                            |\t       |                            |");
		printf("\n\t +----------------------------+\t       +----------------------------+\n");
		printf("\n\t +----------- ^-^  #3---------+\t       +----------- ^-^ #4----------+");
		printf("\n\t |                            |\t       |                            |");
		printf("\n\t |           SEARCH           |\t       |           MODIFY           |");
		printf("\n\t |                            |\t       |                            |");
		printf("\n\t +----------------------------+\t       +----------------------------+\n");
		printf("\n\t +----------- ^-^  #5---------+\t       +----------- ^-^ #6----------+");
		printf("\n\t |                            |\t       |                            |");
		printf("\n\t |           DELETE           |\t       |           REPORT           |");
		printf("\n\t |                            |\t       |                            |");
		printf("\n\t +----------------------------+\t       +----------------------------+\n\n");
		printf("\n\t                  +----------- ^-^  #0---------+");
		printf("\n\t                  |                            |\t");
		printf("\n\t                  |             EXIT           |\t");
		printf("\n\t                  |                            |\t");
		printf("\n\t                  +----------------------------+\t\n");*/

		printf("  Enter your choice : ");
		rewind(stdin);
		scanf("%d", &choice);
		printf("\n");

		switch (choice) {
		case 1:
			addFacility();
			break;
		case 2:
			displayFacility();
			break;
		case 3:
			searchFacility();
			break;
		case 4:
			modifyFacility();
			break;
		case 5:
			deleteFacility();
			break;
		case 6:
			reportFacility();
			break;
		case 0:
			break;
		default:
			printf("\033[0;31mInvalid choice, pls enter again...\033[0m\n");
		}
		printf("\n");
	} while (choice != 0);
}

void displayFacility() {

	char userChoice = 'Y';
	int i;

	checkNull(&userChoice, "sauwei.bin", "rb", "ab");

	if (toupper(userChoice) == 'Y')
	{
		system("cls");
		struct Facility f;

		printf("\t\t\t\t\t- DISPLAY FACILITY RECORD -\n\n");
		line(130);
		printf("%5s %13s %28s %20s %25s %15s %14s\n", "ID", "TYPE", "DESCIPTION", "VENUE", "MAX ALLOWABLE USER", "STAFF ID", "DATE");
		line(130);

		FILE* fp = fopen("sauwei.bin", "rb");

		i = 0;
		while (fread(&f, sizeof(struct Facility), 1, fp) != 0) {
			printf("%5s %15s %28s %20s %15d %22s %5s    %02d/%02d/%04d\n\n", f.id, f.type, f.description, f.venue, f.max, f.staffInCharge, "", f.buildDate.day, f.buildDate.month, f.buildDate.year);
			i++;
		}
		fclose(fp);
		line(130);
		printf("\n< %d Facility have record >\n\n", i);

		system("pause");
	}

}

void searchFacility() {

	char userChoice = 'Y', searchId[10], yesNo;
	int totalRecord, noFound, nRecord;

	struct Facility f;

	checkNull(&userChoice, "sauwei.bin", "rb", "ab");

	if (toupper(userChoice) == 'Y')
	{
		/*SYSTEMTIME t;
		GetLocalTime(&t);*/
		system("cls");

		printf("\t\t\t- SEARCH FACILITY RECORD -\n");
		do
		{
			printf("\n  Enter ID to search : ");
			rewind(stdin);
			scanf("%s", &searchId);

			FILE* fp = fopen("sauwei.bin", "rb");

			nRecord = 0;
			noFound = 0;
			while (fread(&f, sizeof(struct Facility), 1, fp) != 0)
			{
				nRecord++;
				if (strcmp(searchId, f.id) == 0)
				{
					printf("\n  Id of facility              : %s\n", f.id);

					printf("  New type of facility        : %s\n", f.type);

					printf("  New description of facility : %s\n", f.description);

					printf("  New venue of facility       : %s\n", f.venue);

					printf("  New maximum allowable users : %d\n", f.max);

					printf("  Staff in charge             : %s\n", f.staffInCharge);

					printf("  Build Time of the facility  : %02d/%02d/%04d\n", f.buildDate.day, f.buildDate.month, f.buildDate.year);
				}
				else {
					noFound++;
				}
			}
			fclose(fp);
			if (nRecord == noFound)
			{
				printf("\033[0;31mNo record found\033[0m\n");
			}

			printf("\n");

			do
			{
				printf("Continue ?? ('Y' = yes 'N' = no) > ");
				rewind(stdin);
				scanf("%c", &yesNo);
				switch (toupper(yesNo)) {
				case 'Y':
					system("cls");
					break;
				case 'N':
					break;
				default:
					printf("\033[0;31mInvalid input please enter again\033[0m\n");
				}
			} while (toupper(yesNo) != 'Y' && toupper(yesNo) != 'N');
		} while (toupper(yesNo) != 'N');
	}
}

void addFacility() {

	char userChoice = 'Y', comfirm;
	int add, i, upper, invalid = 0;

	Staff info;
	struct Facility addF;
	struct Facility f;

	checkNull(&userChoice, "sauwei.bin", "rb", "ab");

	if (toupper(userChoice) == 'Y')
	{
		system("cls");
		printf("\t\t\t- ADD FACILITY RECORD -\n");

		do
		{
			printf("  Enter how many record need to add : ");
			rewind(stdin);
			scanf("%d", &add);

			for (i = 0; i < add; i++)
			{
				printf("  Enter type of facility : ");
				rewind(stdin);
				scanf("%s", &addF.type);

				for (upper = 0; upper < 15; upper++)
				{
					addF.type[upper] = toupper(addF.type[upper]);
				}

				addF.firstChar = addF.type[0];

				do
				{
					readLastFacility(addF.type);

					printf("\n  Enter the facility id : ");
					rewind(stdin);
					scanf("%s", &addF.id);

					if ((addF.id[0] != addF.type[0]) || (addF.id[1] != addF.type[1]))
					{
						printf("\033[0;31mPlease set the id starting with %c%c\033[0m\n", addF.type[0], addF.type[1]);
					}

					FILE* fileRead = fopen("sauwei.bin", "rb");
					while (fread(&f, sizeof(struct Facility), 1, fileRead) != 0)
					{
						if (strcmp(addF.id, f.id) == 0)
						{
							printf("\033[0;31mThe facility id have been use please enter again\033[0m\n");
							break;
						}
					}
					fclose(fileRead);

				} while (((addF.id[0] != addF.type[0]) || (addF.id[1] != addF.type[1])) || (strcmp(addF.id, f.id) == 0));

				printf("  Enter description of facility : ");
				rewind(stdin);
				scanf("%[^\n]", &addF.description);

				printf("  Enter venue of facility       : ");
				rewind(stdin);
				scanf("%[^\n]", &addF.venue);

				printf("  Enter maximum allowable users : ");
				rewind(stdin);
				scanf("%d", &addF.max);

				do
				{
					printf("  Enter the staff Id in charge  : ");
					rewind(stdin);
					scanf("%[^\n]", &addF.staffInCharge);

					FILE* fileStaff = fopen("erika.txt", "r");
					while (fscanf(fileStaff, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c|%d|%d-%d-%d\n", &info.staffId, &info.staffName, &info.pass.pwd, &info.pass.pwdRecovery, &info.position, &info.staffGender, &info.age, &info.staffBirthday.day, &info.staffBirthday.month, &info.staffBirthday.year) != EOF)
					{
						if (strcmp(addF.staffInCharge, info.staffId) == 0)
						{
							break;
						}
					}
					fclose(fileStaff);
					if (strcmp(addF.staffInCharge, info.staffId) != 0)
					{
						printf("\033[0;31mStaff id no found please enter again\033[0m\n");
					}
				} while (strcmp(addF.staffInCharge, info.staffId) != 0);

				do
				{
					printf("  Enter the build time(date month year)	: ");
					rewind(stdin);
					scanf("%d %d %d", &addF.buildDate.day, &addF.buildDate.month, &addF.buildDate.year);
					invalid = dateChecking(addF.buildDate.day, addF.buildDate.month, addF.buildDate.year);
				} while (invalid != 0);

				FILE* fileWrite = fopen("sauwei.bin", "ab");
				fwrite(&addF, sizeof(struct Facility), 1, fileWrite);
				fclose(fileWrite);

				printf("\n\033[2;36m  Added successfully...\033[0m\n");

			}

			do {
				printf("\n\n  Still have ? (Y = yes || N = no )  : ");
				rewind(stdin);
				scanf("%c", &comfirm);
				switch (toupper(comfirm)) {
				case 'Y':
					system("cls"); break;
				case 'N':
					break;
				default:
					printf("\033[0;31mInvalid code, please enter again!!\033[0m\n");
				}
			} while (toupper(comfirm) != 'N' && toupper(comfirm) != 'Y');
		} while (toupper(comfirm) != 'N');
	}
}

void readLastFacility(char type[]) {
	struct Facility f;

	printf("  The id of %s facility have been use are > ", type);

	FILE* fileRead = fopen("sauwei.bin", "rb");
	while (fread(&f, sizeof(struct Facility), 1, fileRead) != 0)
	{
		if (strcmp(type, f.type) == 0)
		{
			printf("%s  ", f.id);
		}
	}

	fclose(fileRead);

	printf("\n");

}

void line(int length) {
	int i;
	for (i = 0; i < length; i++)
	{
		printf("=");
	}
	printf("\n");
}

void reportFacility() {

	int i = 0, totalKaraoke = 0, totalSnooker = 0, totalTable = 0, totalGym = 0, totalRecord = 0,
		num = 0, percentage = 0, highest = 0, highestAllowK = 0, highestAllowS = 0, highestAllowT = 0, highestAllowG = 0;

	char userChoice = 'Y';

	checkNull(&userChoice, "sauwei.bin", "rb", "ab");

	if (toupper(userChoice) == 'Y')
	{
		system("cls");
		struct Facility f[MAX_SIZE_FACILITY];
		SYSTEMTIME t;
		GetLocalTime(&t);

		FILE* fileRead = fopen("sauwei.bin", "rb");
		while (fread(&f[i], sizeof(f[0]), 1, fileRead) != 0) {
			++totalRecord;
			++i;
		}
		fclose(fileRead);

		printf("\t\t\t REPORT FOR FACILITY   \n\n");
		printf("\t\t\t %d/%d/%d  %02d:%02d:%02d \n\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond);

		FILE* fp = fopen("sauwei.bin", "rb");
		while (fread(&f[i], sizeof(f[0]), 1, fp) == 1) {
			if (toupper(f[i].firstChar) == 'K') {
				totalKaraoke++;

				if (f[i].max > highestAllowK) {
					highestAllowK = f[i].max;
				}

				//if (percentage > highest) {
				//	highest = percentage;
				//}
			}
			else if (toupper(f[i].firstChar) == 'S') {
				totalSnooker++;

				if (f[i].max > highestAllowS) {
					highestAllowS = f[i].max;
				}

				/*if (percentage > highest) {
					highest = percentage;
				}*/
			}
			else if (toupper(f[i].firstChar) == 'T') {
				totalTable++;

				if (f[i].max > highestAllowT) {
					highestAllowT = f[i].max;
				}

				/*if (percentage > highest) {
					highest = percentage;
				}*/
			}
			else if (toupper(f[i].firstChar) == 'G') {
				totalGym++;

				if (f[i].max > highestAllowG) {
					highestAllowG = f[i].max;
				}

				/*if (percentage > highest) {
					highest = percentage;
				}*/
			}
			else
				break;
		}

		if (totalRecord == 0) {
			printf("\033[0;31m\t\t\t No record found...\033[0m\n\n");
		}

		checkReport('K', totalKaraoke, percentage, highestAllowK);
		checkReport('S', totalSnooker, percentage, highestAllowS);
		checkReport('T', totalTable, percentage, highestAllowT);
		checkReport('G', totalGym, percentage, highestAllowG);

		//printf(" The highest percentage of facility >>>> %d%%\n\n", highest);

		fclose(fp);

	}
	system("pause");

}

void checkReport(char facility, int totalFacility, int percentage, int highestAllow) {
	struct Facility f[MAX_SIZE_FACILITY];
	int i = 0, totalRecord = 0;

	FILE* fileRead = fopen("sauwei.bin", "rb");
	while (fread(&f[i], sizeof(f[0]), 1, fileRead) != 0) {
		++totalRecord;
		++i;
	}
	fclose(fileRead);

	fileRead = fopen("sauwei.bin", "rb");
	while (fread(&f[i], sizeof(f[0]), 1, fileRead) != 0) {
		if (facility == f[i].firstChar) {
			printf("- %s -\n", f[i].type);
			printf(" Total %s facility - %d\n", f[i].type, totalFacility);
			percentage = (100 / totalRecord * totalFacility);
			printf(" Percentage of %s >>>>> %d %%\n", f[i].type, percentage);
			printf(" The highest allowable user is %d \n\n", highestAllow);
			break;
		}
		++i;
	}
}

void modifyFacility() {

	char userChoice = 'Y', userInput[5], yesNo, yesNo2;
	int nSize, i, change, invalid, noFound, mod;

	struct Facility f[MAX_SIZE_FACILITY];
	struct Facility modify;
	Staff info;

	checkNull(&userChoice, "sauwei.bin", "rb", "ab");

	if (toupper(userChoice) == 'Y')
	{
		system("cls");
		printf("\t\t\t- MODIFY FACILITY RECORD -\n");

		do
		{
			printf("Enter facility id : ");
			rewind(stdin);
			scanf("%s", &userInput);

			nSize = 0;
			i = 0;
			FILE* fileRead = fopen("sauwei.bin", "rb");
			while (fread(&f[i], sizeof(f[0]), 1, fileRead) != 0) {
				nSize++;
				i++;
			}
			fclose(fileRead);

			noFound = 0;
			for (i = 0; i < nSize; i++)
			{
				if (strcmp(userInput, f[i].id) == 0) {
					//show printf
					printf("Show detail...\n");
					printf("  Id of facility              : %s\n", f[i].id);

					printf("  Type of facility            : %s\n", f[i].type);

					printf("  Description of facility     : %s\n", f[i].description);

					printf("  Venue of facility           : %s\n", f[i].venue);

					printf("  Maximum allowable users     : %d\n", f[i].max);

					printf("  Staff in charge             : %s\n", f[i].staffInCharge);

					printf("  Build Time of the facility  : %02d/%02d/%04d\n\n", f[i].buildDate.day, f[i].buildDate.month, f[i].buildDate.year);

					printf("Start to modify...\n\n");
					strcpy(modify.id, f[i].id);
					printf("  Facility id                       : %s\n", modify.id);

					strcpy(modify.type, f[i].type);
					printf("  Type of facility                  : %s\n", modify.type);

					modify.firstChar = f[i].firstChar;

					printf("  Enter new description of facility : ");
					rewind(stdin);
					scanf("%[^\n]", &modify.description);

					printf("  Enter new venue of facility       : ");
					rewind(stdin);
					scanf("%[^\n]", &modify.venue);

					printf("  Enter new maximum allowable users : ");
					rewind(stdin);
					scanf("%d", &modify.max);

					do
					{
						printf("  Enter the new staff Id in charge  : ");//STOOO
						rewind(stdin);
						scanf("%[^\n]", &modify.staffInCharge);

						FILE* fileStaff = fopen("erika.txt", "r");
						while (fscanf(fileStaff, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c|%d|%d-%d-%d\n", &info.staffId, &info.staffName, &info.pass.pwd, &info.pass.pwdRecovery, &info.position, &info.staffGender, &info.age, &info.staffBirthday.day, &info.staffBirthday.month, &info.staffBirthday.year) != EOF)
						{
							if (strcmp(modify.staffInCharge, info.staffId) == 0)
							{
								break;
							}
						}
						fclose(fileStaff);
						if (strcmp(modify.staffInCharge, info.staffId) != 0)
						{
							printf("\033[0;31mStaff id no found please enter again\033[0m\n");
						}
					} while (strcmp(modify.staffInCharge, info.staffId) != 0);//F


					do
					{
						printf("  Enter new the build time(dd mm yyyy)	: ");
						rewind(stdin);
						scanf("%d %d %d", &modify.buildDate.day, &modify.buildDate.month, &modify.buildDate.year);
						invalid = dateChecking(modify.buildDate.day, modify.buildDate.month, modify.buildDate.year);
					} while (invalid != 0);

					do
					{
						printf("\nConfirm to change ('Y' = yes 'N' = no) > ");
						rewind(stdin);
						scanf("%c", &yesNo);
						switch (toupper(yesNo)) {
						case 'Y':
							strcpy(f[i].id, modify.id);
							strcpy(f[i].type, modify.type);
							strcpy(f[i].description, modify.description);
							strcpy(f[i].venue, modify.venue);
							strcpy(f[i].staffInCharge, modify.staffInCharge);
							f[i].firstChar = modify.firstChar;
							f[i].max = modify.max;
							f[i].buildDate.day = modify.buildDate.day;
							f[i].buildDate.month = modify.buildDate.month;
							f[i].buildDate.year = modify.buildDate.year;

							FILE* fileWrite = fopen("sauwei.bin", "wb");

							for (mod = 0; mod < nSize; mod++)
							{
								fwrite(&f[mod], sizeof(f[0]), 1, fileWrite);
							}
							fclose(fileWrite);
							printf("\033[2;36mModify successful\033[0m\n");
							break;
						case 'N':
							printf("\033[0;31mModify unsuccessful\033[0m\n");
							break;
						default:
							printf("\033[0;31mInvalid input please enter again\033[0m\n");
						}
					} while (toupper(yesNo) != 'N' && toupper(yesNo) != 'Y');

				}
				else {
					noFound++;
				}
			}
			if (noFound == nSize)
			{
				printf("\033[0;31mNo record found\033[0m\n");
			}

			do
			{
				printf("\nContinues ?? ('Y' = yes 'N' = no) > ");
				rewind(stdin);
				scanf("%c", &yesNo2);
				switch (toupper(yesNo2)) {
				case 'Y':
					system("cls"); break;
				case 'N':
					break;
				default:
					printf("\033[0;31mInvalid choice please enter again\033[0m\n");
				}
			} while (toupper(yesNo2) != 'N' && toupper(yesNo2) != 'Y');
		} while (toupper(yesNo2) != 'N');
	}
}

void deleteFacility() {

	struct Facility f[MAX_SIZE_FACILITY];

	char userChoice = 'Y', userInput[7], yesNo, delAgain;
	int i, nRecord, change, noFound, reWrite, check = 1, del;

	checkNull(&userChoice, "sauwei.bin", "rb", "ab");

	if (toupper(userChoice) == 'Y')
	{
		system("cls");
		printf("\t\t\t- DELETE FACILITY RECORD -\n");

		do
		{
			FILE* fileRead = fopen("sauwei.bin", "rb");
			i = 0;
			nRecord = 0;
			while (fread(&f[i], sizeof(f[0]), 1, fileRead) != 0)
			{
				++nRecord;
				i++;
			}
			fclose(fileRead);

			printf("Enter Facility ID : ");
			rewind(stdin);
			scanf("%s", &userInput);

			noFound = 0;
			for (i = 0; i < nRecord; i++)
			{
				if (strcmp(userInput, f[i].id) == 0)
				{
					printf("\n  Id of facility              : %s\n", f[i].id);

					printf("  Type of facility            : %s\n", f[i].type);

					printf("  Description of facility     : %s\n", f[i].description);

					printf("  Venue of facility           : %s\n", f[i].venue);

					printf("  Maximum allowable users     : %d\n", f[i].max);

					printf("  Staff in charge             : %s\n", f[i].staffInCharge);

					printf("  Build Time of the facility  : %02d/%02d/%04d\n\n", f[i].buildDate.day, f[i].buildDate.month, f[i].buildDate.year);
					do
					{
						printf("Confirm to delete ? ('Y' = yes 'N' = no) > ");
						rewind(stdin);
						scanf("%c", &yesNo);
						if (toupper(yesNo) == 'Y')
						{
							for (change = i; change < nRecord; change++)
							{
								if (change == nRecord - 1)
								{
									break;
								}
								else {
									strcpy(f[change].id, f[change + 1].id);
									strcpy(f[change].type, f[change + 1].type);
									strcpy(f[change].description, f[change + 1].description);
									strcpy(f[change].venue, f[change + 1].venue);
									strcpy(f[change].staffInCharge, f[change + 1].staffInCharge);
									f[change].firstChar = f[change + 1].firstChar;
									f[change].max = f[change + 1].max;
									f[change].buildDate.day = f[change + 1].buildDate.day;
									f[change].buildDate.month = f[change + 1].buildDate.month;
									f[change].buildDate.year = f[change + 1].buildDate.year;

								}
							}
							FILE* fileWrite = fopen("sauwei.bin", "wb");
							for (del = 0; del < nRecord - 1; del++)
							{
								fwrite(&f[del], sizeof(f[0]), 1, fileRead);
							}
							fclose(fileWrite);

							printf("\033[2;36mRecord is delete successful\033[0m\n");

						}
						else if (toupper(yesNo) == 'N') {
							printf("\033[0;31mThe information for %s have not delete\033[0m\n", userInput);
						}
						else {
							printf("\033[0;31mInvalid code please enter again\033[0m\n");
						}
					} while (toupper(yesNo) != 'N' && toupper(yesNo) != 'Y');
				}
				else {
					noFound++;
				}
			}


			if (noFound == nRecord) {
				printf("\033[0;31mNo Record Found\033[0m\n");
			}

			do
			{
				printf("Continues ?? ('Y' = yes 'N' = no) > ");
				rewind(stdin);
				scanf("%c", &delAgain);
				switch (toupper(delAgain)) {
				case 'Y':
					system("cls");
					break;
				case 'N':
					break;
				default:
					printf("\033[0;31mInvalid code please enter again\033[0m\n");
				}
			} while (toupper(delAgain) != 'N' && toupper(delAgain) != 'Y');
		} while (toupper(delAgain) != 'N');
	}

}

void autoCreateId(int* error, char id[6], char fileName[], char fileType[]) {

	int i, firstNum, secondNum, thirdNum, fourthNum;
	char str[6];
	*error = 0;
	FILE* fileRead = fopen(fileName, fileType);

	Booking book[MAX_SIZE_BOOK];
	Member mem[MAX_SIZE_MEMBER];

	if (strcmp(fileType, "rb") == 0)
	{
		i = 0;
		while (fread(&book[i], sizeof(Booking), 1, fileRead) != 0) {
			++i;
		}
		if (i >= MAX_SIZE_BOOK) {
			*error = 1;
		}
	}
	else {
		i = 0;
		while (fscanf(fileRead, "%[^|]|%[^|]|%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%d-%d-%d\n", &mem[i].memberID, &mem[i].memberName, &mem[i].password, &mem[i].passwordRecover, &mem[i].gender, &mem[i].icNum, &mem[i].phoneNum, &mem[i].category, &mem[i].joinedDate.day, &mem[i].joinedDate.month, &mem[i].joinedDate.year) != EOF) {
			++i;
		}
	}
	fclose(fileRead);

	if (i == 0)
	{
		if (strcmp(fileType, "rb") == 0)
		{
			if (*error == 1)
			{
				printf("\033[0;31mThe booking is until the maximum size, it is unable to book\033[0m\n");
			}
			else {
				strcpy(id, "B0001");
				printf("\033[2;36mBooking successful, your booking ID is %s\033[0m\n", id);
			}
		}
		else {
			strcpy(id, "M0001");
			printf("\033[2;36mRegister successful, your member ID is %s\033[0m\n", id);
		}
	}
	else {
		if (strcmp(fileType, "rb") == 0)
		{
			strcpy(str, book[i - 1].bookId);
		}
		else {
			strcpy(str, mem[i - 1].memberID);
		}
		//printf("%s", str);
		//B1116

		firstNum = (int)str[4] + 1;
		if (firstNum > 57) {
			firstNum = 48;
			str[4] = (char)firstNum;

			secondNum = (int)str[3] + 1;
			if (secondNum > 57)
			{
				secondNum = 48;
				str[3] = (char)secondNum;

				thirdNum = (int)str[2] + 1;
				if (thirdNum > 57)
				{
					thirdNum = 48;
					str[2] = (char)thirdNum;

					fourthNum = (int)str[1] + 1;
					if (fourthNum > 57)
					{
						if (strcmp(fileType, "rb") == 0)
						{
							printf("\033[0;31mThe booking is until the maximum size, it is unable to book\033[0m\n");
						}
						else {
							printf("\033[0;31mThe member register is until the maximum size, it is unable to register\033[0m\n");
						}
						*error = 1;
					}
					else {
						str[1] = (char)thirdNum;
						strcpy(id, str);

						if (strcmp(fileType, "rb") == 0)
						{
							if (*error == 1)
							{
								printf("\033[0;31mThe booking is until the maximum size, it is unable to book\033[0m\n");
							}
							else {
								printf("\033[2;36mBooking successful, your booking ID is %s\033[0m\n", id);
							}
						}
						else {
							printf("\033[2;36mRegister successful, your member ID is %s\033[0m\n", id);
						}
					}
				}
				else {
					str[2] = (char)thirdNum;
					strcpy(id, str);

					if (strcmp(fileType, "rb") == 0)
					{
						if (*error == 1)
						{
							printf("\033[0;31mThe booking is until the maximum size, it is unable to book\033[0m\n");
						}
						else {
							printf("\033[2;36mBooking successful, your booking ID is %s\033[0m\n", id);
						}
					}
					else {
						printf("\033[2;36mRegister successful, your member ID is %s\033[0m\n", id);
					}
				}
			}
			else {
				str[3] = (char)secondNum;
				strcpy(id, str);

				if (strcmp(fileType, "rb") == 0)
				{
					if (*error == 1)
					{
						printf("\033[0;31mThe booking is until the maximum size, it is unable to book\033[0m\n");
					}
					else {
						printf("\033[2;36mBooking successful, your booking ID is %s\033[0m\n", id);
					}
				}
				else {
					printf("\033[2;36mRegister successful, your member ID is %s\033[0m\n", id);
				}
			}
		}
		else {
			str[4] = (char)firstNum;
			strcpy(id, str);

			if (strcmp(fileType, "rb") == 0)
			{
				if (*error == 1)
				{
					printf("\033[0;31mThe booking is until the maximum size, it is unable to book\033[0m\n");
				}
				else {
					printf("\033[2;36mBooking successful, your booking ID is %s\033[0m\n", id);
				}
			}
			else {
				printf("\033[2;36mRegister successful, your member ID is %s\033[0m\n", id);
			}
		}
	}
}

void mainMember() {

	int option, getNum;

	//Determine whether the user is a staff or member
	do {
		system("cls");
		printf("\t                      ------ Who you are? ------\n");
		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m1\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m2\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m        I AM A STAFF        \033[0;35m|\t       \033[0;31m|\033[0m        I AM A MEMBER       \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n");
		printf("\n\t                  \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m3\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0m");
		printf("\n\t                  \033[1;31m|                            \033[0;34m|\033[0m\t");
		printf("\n\t                  \033[0;33m|\033[0m             EXIT           \033[0;35m|\033[0m\t");
		printf("\n\t                  \033[0;32m|                            \033[0;31m|\033[0m\t");
		printf("\n\t                  \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0m\t\n");

		printf("Enter your option (1/2/3) : ");
		rewind(stdin);
		scanf("%d", &option);
		printf("\n");

		switch (option) {
		case 1:
			getNum = loginStaff();
			if (getNum == 1)
			{
				menuStaff();
			}
			break;
		case 2: menuMember(); break;
		case 3: break;
		default:
			printf("\033[0;31mInvalid option. Please re-enter\033[0m\n");
			system("pause");
		}
	} while (option != 3);
}

void menuStaff() {

	int option;

	do {
		system("cls");
		printf("Hello Staff.\n");
		printf("What would you like to do?\n");

		//Display introduction screen
		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m1\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m2\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m   ADD MEMBER INFORMATION   \033[0;35m|\t       \033[0;31m|\033[0m SEARCH MEMBER INFORMATION  \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n");
		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m3\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m4\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m  MODIFY MEMBER INFORMATION \033[0;35m|\t       \033[0;31m|\033[0m    DELETE MEMBER RECORDS   \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n");
		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m5\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m6\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|                            \033[0;34m|\t       \033[0;35m|                            \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m DISPLAY MEMBER INFORMATION \033[0;35m|\t       \033[0;31m|\033[0m            EXIT            \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|                            \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n");

		printf("Enter your option (1/2/3/4/5/6) : ");
		rewind(stdin);
		scanf("%d", &option);
		printf("\n");

		switch (option) {
		case 1: addMember(); break;
		case 2: searchMember(); break;
		case 3: modifyMember(); break;
		case 4: deleteMember(); break;
		case 5: displayMember(); break;
		case 6: break;
		default:
			printf("\033[0;31mInvalid option. Please re-enter\033[0m\n");
			system("pause");
		}
	} while (option != 6);
}

void menuMember() {

	int option;

	do {
		system("cls");

		printf("Hello Member.\n");
		printf("What would you like to do?\n");

		printf("\n\t \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m1\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m        +\033[0;34m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m ^\033[0;35m-\033[0;31m^\033[1;31m #\033[0;33m2\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m+\033[0m");
		printf("\n\t \033[1;31m|\033[0m           SIGN IN          \033[0;34m|\t       \033[0;35m|\033[0m        NOT A MEMBER?       \033[0;33m|\033[0m");
		printf("\n\t \033[0;33m|\033[0m        TO ACCESS THE       \033[0;35m|\t       \033[0;31m|\033[0m        REGISTER NOW!       \033[0;32m|\033[0m");
		printf("\n\t \033[0;32m|\033[0m    RECREATION FACILITIES   \033[0;31m|\t       \033[1;31m|                            \033[0;34m|\033[0m");
		printf("\n\t \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0;34m\t       +\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m+\033[0m\n");
		printf("\n\t                  \033[0;31m+\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32-\033[0;34m-\033[0;35m-\033[0;31m  ^\033[1;31m-\033[0;33m^\033[0;32m  #\033[0;34m3\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0m");
		printf("\n\t                  \033[1;31m|                            \033[0;34m|\033[0m\t");
		printf("\n\t                  \033[0;33m|\033[0m             EXIT           \033[0;35m|\033[0m\t");
		printf("\n\t                  \033[0;32m|                            \033[0;31m|\033[0m\t");
		printf("\n\t                  \033[0;34m+\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m-\033[0;34m-\033[0;35m-\033[0;31m-\033[1;31m-\033[0;33m-\033[0;32m+\033[0m\t\n");

		printf("Enter your option (1/2/3) : ");
		rewind(stdin);
		scanf("%d", &option);
		printf("\n");

		switch (option) {
		case 1: memberSignIn(); break;
		case 2: addMember(); break;
		case 3: break;
		default:
			printf("\033[0;31mInvalid option. Please re-enter\033[0m\n");
			system("pause");
		}
	} while (option != 3);
}

int memberSignIn() { //In order to use the facility, one must register as a member

	char inputID[6], inputPw[10], ch, userChoice = 'Y', pwRecovery = 'Y', choice, valid;
	int i, j, nMember, compare, invalidPw, errorID, returnValue = 0;

	Member mem[MAX_SIZE_MEMBER];

	checkNull(&userChoice, "kaixin.txt", "r", "a");

	if (toupper(userChoice) == 'Y') {
		system("cls");

		FILE* fileRead = fopen("kaixin.txt", "r");

		//Read into array
		nMember = 0;
		i = 0;
		while (fscanf(fileRead, "%[^|]|%[^|]|%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%d-%d-%d\n", &mem[i].memberID, &mem[i].memberName, &mem[i].password, &mem[i].passwordRecover, &mem[i].gender, &mem[i].icNum, &mem[i].phoneNum, &mem[i].category, &mem[i].joinedDate.day, &mem[i].joinedDate.month, &mem[i].joinedDate.year) != EOF) {
			nMember++;
			i++;
		}
		fclose(fileRead);

		//Display Introduction Screen
		printf("\n");
		printf("\t\t+----------------------------+\n");
		printf("\t\t WELCOME TO MEMBER LOGIN PAGE!\n");
		printf("\t\t+----------------------------+\n");
		printf("\n");

		invalidPw = 0;

		do {
			printf(" Enter your member ID               : ");
			rewind(stdin);
			scanf("%s", &inputID);

			printf(" Enter your password <8 characters> : ");

			//Masking password with *
			for (j = 0; j < 8; j++) {
				ch = getch();
				inputPw[j] = ch;
				ch = '*';
				printf("%c", ch);
			}
			inputPw[j] = '\0';

			//Compare ID and password

			errorID = 0;
			returnValue = 0;
			compare = 0;

			for (i = 0; i < nMember; i++) {
				if (strcmp(inputID, mem[i].memberID) == 0) {
					if (strcmp(inputPw, mem[i].password) == 0) {
						printf(" \n\033[2;36mLogin Successful!\033[0m\n");
						compare += i;
						++returnValue;
						system("pause");
					}
					else {
						printf("\n \033[0;31mIncorrect password. Please re-enter.\033[0m\n\n");
						++invalidPw;

						//Password recovery (if wrong pw >= 3, can ask for recovery)
						if (invalidPw >= 3) {
							do {
								printf(" Would you like to perform a password recovery? ('Y' = Yes, 'N' = No): ");
								rewind(stdin);
								scanf("%c", &pwRecovery);

								switch (toupper(pwRecovery)) {
								case 'Y':
									memberPasswordRecovery(&valid);
									system("cls");
									if (valid == 'T')
									{
										printf(" \033[2;36mSuccessful password recovery. Please sign in again.\033[0m\n\n");
									}
									else {
										printf(" \033[0;31mUnsuccessful password recovery, please try again\033[0m\n");
									}
									Sleep(600);
									break;
								case 'N':
									break;
								default:
									printf(" \033[0;31mInvalid option. Please re-enter.\033[0m\n");
								}
							} while (toupper(pwRecovery) != 'Y' && toupper(pwRecovery) != 'N');
						}
					}
				}
				else {
					++errorID;
				}
			}

			if (toupper(pwRecovery) == 'N')
			{
				printf(" \033[0;31mSorry you have enter wrong password 3 time please try again later\033[0m\n");
				system("pause");
				break;
			}

		} while ((strcmp(inputID, mem[compare].memberID) == 0) && (strcmp(inputPw, mem[compare].password) != 0));

		if (errorID == nMember) {
			printf("\n \033[0;31mMember ID not found.\033[0m\n\n");

			do {
				printf(" Would you like to register a new account? ('Y' = Yes, 'N' = No): ");
				rewind(stdin);
				scanf("%c", &choice);

				//Check user's choice
				switch (toupper(choice)) {
				case 'Y':
					addMember();
					break;
				case 'N':
					break;
				default:
					printf(" \033[0;31mInvalid option. Please re-enter.\033[0m\n");
				}
			} while (toupper(choice) != 'Y' && toupper(choice) != 'N');
		}
	}
	return returnValue;
}

void memberPasswordRecovery(char* valid) {

	char userChoice = 'Y', memID[6], securityPass[20], yesNo;
	int wrgSecurityAns, notFound, nSize;

	*valid = 'F';

	Member mem;
	checkNull(&userChoice, "kaixin.txt", "r", "a");

	wrgSecurityAns = 0;
	if (toupper(userChoice) == 'Y') {

		do {
			system("cls");
			printf("\n");
			printf("+----------------------------------+\n");
			printf(" WELCOME TO PASSWORD RECOVERY PAGE! \n");
			printf("+----------------------------------+\n");

			do
			{
				printf(" Enter your Member ID : ");
				rewind(stdin);
				scanf("%s", &memID);

				printf("\n -----Security Question -----\n");
				printf(" What city were you born in? : ");
				rewind(stdin);
				scanf("%[^\n]", &securityPass);


				notFound = 0;
				nSize = 0;

				FILE* member = fopen("kaixin.txt", "r");

				while (fscanf(member, "%[^|]|%[^|]|%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%d-%d-%d\n", &mem.memberID, &mem.memberName, &mem.password, &mem.passwordRecover, &mem.gender, &mem.icNum, &mem.phoneNum, &mem.category, &mem.joinedDate.day, &mem.joinedDate.month, &mem.joinedDate.year) != EOF) {
					nSize++;
					if (strcmp(memID, mem.memberID) == 0) {
						if (strcmp(securityPass, mem.passwordRecover) == 0) {
							//Print the details
							printf("\n Password and Member Information\n");
							printf(" -------------------------------\n");
							printf(" Member ID            : %s\n", mem.memberID);
							printf(" Member Name          : %s\n", mem.memberName);
							printf(" Password             : %s\n", mem.password);
							printf(" Password Recovery    : %s\n", mem.passwordRecover);
							printf(" Member Gender        : %c\n", mem.gender);
							printf(" Member IC Number     : %s\n", mem.icNum);
							printf(" Member Phone Number  : %s\n", mem.phoneNum);
							printf(" Membership Category  : %s\n", mem.category);
							printf(" Member Joined Date   : %d-%d-%d\n", mem.joinedDate.day, mem.joinedDate.month, mem.joinedDate.year);

							*valid = 'T';
							break;
						}
						else {
							printf(" \033[0;31mIncorrect security answer, please re-enter.\033[0m\n");
							wrgSecurityAns++;

							/*if (wrgSecurityAns > 2)
							{
								break;
							}*/
							break;
						}
					}
					else {
						notFound++;
					}
				}
				fclose(member);
				if (wrgSecurityAns > 2)
				{
					printf(" \033[0;31mSorry, you have insert wrong answer two times please try again later\033[0m\n");
					break;
				}
			} while ((strcmp(memID, mem.memberID) == 0) && (strcmp(securityPass, mem.passwordRecover) != 0));

			if (notFound == nSize) {
				printf(" \033[0;31mNo record found.\033[0m\n");
			}

			do {
				printf(" Return back to member menu? ('Y' = Yes 'N' = No): ");
				rewind(stdin);
				scanf("%c", &yesNo);

				switch (toupper(yesNo)) {
				case 'Y':
					break;
				case 'N':
					if (wrgSecurityAns > 2) {
						printf(" \033[0;31mSorry, you had enter wrong answer until maximum, please try again later.\033[0m\n");
						system("pause");
					}
					system("cls");
					break;
				default:
					printf(" \033[0;31mInvalid choice. Please re-enter.\033[0m\n");
				}
			} while (toupper(yesNo) != 'N' && toupper(yesNo) != 'Y');

			if (wrgSecurityAns > 2) {

				if (toupper(yesNo) == 'N') {
					break;
				}
			}
		} while (toupper(yesNo) != 'Y');
	}
}

void addMember() {

	char memberID[6], userChoice = 'Y', yesNo;
	int invalid, error;

	Member mem;

	checkNull(&userChoice, "kaixin.txt", "r", "a");

	if (toupper(userChoice) == 'Y') {
		do {
			system("cls");
			printf("\n");
			printf("+---------------------------+\n");
			printf(" WELCOME TO ADD MEMBER PAGE! \n");
			printf("+---------------------------+\n");

			printf(" Member Name                                  : ");
			rewind(stdin);
			scanf("%[^\n]", &mem.memberName);

			printf("\n Password <8 characters>                      : ");
			rewind(stdin);
			scanf("%s", &mem.password);

			printf("\n ---Set the password security question---\n");
			printf(" What city were you born in?                  : ");
			rewind(stdin);
			scanf("%[^\n]", &mem.passwordRecover);

			do
			{
				printf("\n Member Gender ('M' = Male, 'F' = Female)     : ");
				rewind(stdin);
				scanf("%c", &mem.gender);

				if (toupper(mem.gender) != 'M' && toupper(mem.gender) != 'F') {
					printf(" \033[0;31mInvalid gender. Please re-enter.\033[0m\n");
				}
			} while (toupper(mem.gender) != 'M' && toupper(mem.gender) != 'F');

			do {
				printf("\n Member IC Number (xxxxxx-xx-xxxx)            : ");
				rewind(stdin);
				scanf("%s", &mem.icNum);

				if (mem.icNum[6] != '-' && mem.icNum[9] != '-') {
					printf(" \033[0;31mInvalid format. Please re-enter according to xxxxxx-xx-xxxx\033[0m\n");
				}
			} while (mem.icNum[6] != '-' && mem.icNum[9] != '-');

			printf("\n Member Phone Number (01x-xxxxxxx)            : ");
			rewind(stdin);
			scanf("%s", &mem.phoneNum);

			printf("\n Membership Category (Classic/Silver/Gold)    : ");
			rewind(stdin);
			scanf("%[^\n]", &mem.category);

			do {
				printf("\n Member Joined Date (dd-mm-yyyy)              : ");
				rewind(stdin);
				scanf("%d-%d-%d", &mem.joinedDate.day, &mem.joinedDate.month, &mem.joinedDate.year);
				invalid = dateChecking(mem.joinedDate.day, mem.joinedDate.month, mem.joinedDate.year);

			} while (invalid != 0);

			autoCreateId(&error, memberID, "kaixin.txt", "r"); //Member ID auto create

			if (error == 1) {
				printf("\033[0;31mSorry, the adding is unsucessful.\033[0m\n");
			}
			else {
				strcpy(mem.memberID, memberID);

				FILE* fileAdd = fopen("kaixin.txt", "a");
				fprintf(fileAdd, "%s|%s|%s|%s|%c|%s|%s|%s|%d-%d-%d\n", mem.memberID, mem.memberName, mem.password, mem.passwordRecover, mem.gender, mem.icNum, mem.phoneNum, mem.category, mem.joinedDate.day, mem.joinedDate.month, mem.joinedDate.year);

				fclose(fileAdd);
			}

			do {
				printf("\n Continue? ('Y' = Yes 'N' = No): ");
				rewind(stdin);
				scanf("%c", &yesNo);

				switch (toupper(yesNo)) {
				case 'Y':
					break;
				case 'N':
					break;
				default:
					printf("\033[0;31mInvalid code. Please re-enter.\033[0m\n");
				}
			} while (toupper(yesNo) != 'N' && toupper(yesNo) != 'Y');
		} while (toupper(yesNo) != 'N');
	}
}

void searchMember() {

	system("cls");

	char userChoice = 'Y', searchId[6], searchAgain;
	int nSize, notFound;

	Member mem;

	checkNull(&userChoice, "kaixin.txt", "r", "a");

	if (toupper(userChoice) == 'Y') {
		system("cls");
		printf("\n");
		printf("+-----------------------------+ \n");
		printf(" WELCOME TO SEARCH MEMBER PAGE! \n");
		printf("+-----------------------------+ \n");

		do {
			printf(" Member ID to search: ");
			rewind(stdin);
			scanf("%s", searchId);

			FILE* fileSearch = fopen("kaixin.txt", "r");
			nSize = 0;
			notFound = 0;

			while (fscanf(fileSearch, "%[^|]|%[^|]|%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%d-%d-%d\n", &mem.memberID, &mem.memberName, &mem.password, &mem.passwordRecover, &mem.gender, &mem.icNum, &mem.phoneNum, &mem.category, &mem.joinedDate.day, &mem.joinedDate.month, &mem.joinedDate.year) != EOF) {
				nSize++;

				if (strcmp(searchId, mem.memberID) == 0) {
					//Print the details
					printf("\n Password and Member Information\n");
					printf(" -------------------------------\n");
					printf(" Member ID            : %s\n", mem.memberID);
					printf(" Member Name          : %s\n", mem.memberName);
					printf(" Password             : %s\n", mem.password);
					printf(" Password Recovery    : %s\n", mem.passwordRecover);
					printf(" Member Gender        : %c\n", mem.gender);
					printf(" Member IC Number     : %s\n", mem.icNum);
					printf(" Member Phone Number  : %s\n", mem.phoneNum);
					printf(" Membership Category  : %s\n", mem.category);
					printf(" Member Joined Date   : %d-%d-%d\n", mem.joinedDate.day, mem.joinedDate.month, mem.joinedDate.year);
				}
				else {
					notFound++;
				}
			}
			fclose(fileSearch);

			if (notFound == nSize) {
				printf(" \033[0;31mNo Record Found.\033[0m\n");
			}

			do {
				printf("\n Continue? ('Y' = yes 'N' = no) > ");
				rewind(stdin);
				scanf("%c", &searchAgain);

				switch (toupper(searchAgain)) {
				case 'Y':
					system("cls");
					break;
				case 'N':
					break;
				default:
					printf(" \033[0;31mInvalid code. Please re-enter.\033[0m\n");
				}
			} while (toupper(searchAgain) != 'N' && toupper(searchAgain) != 'Y');
		} while (toupper(searchAgain) != 'N');
	}
}

void modifyMember() {

	char userChoice = 'Y', userInput[6], yesNo, yesNo2;
	int notFound, nSize, i, invalid, compare, del;

	Member mem[MAX_SIZE_MEMBER];
	Member modify;

	checkNull(&userChoice, "kaixin.txt", "r", "a");

	if (toupper(userChoice) == 'Y') {
		system("cls");
		printf("\n");
		printf("+-----------------------+\n");
		printf(" WELCOME TO MODIFY PAGE! \n");
		printf("+-----------------------+\n");

		do
		{
			printf(" Enter your Member ID : ");
			rewind(stdin);
			scanf("%s", &userInput);

			FILE* fileRead = fopen("kaixin.txt", "r");

			nSize = 0;
			i = 0;

			while (fscanf(fileRead, "%[^|]|%[^|]|%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%d-%d-%d\n", &mem[i].memberID, &mem[i].memberName, &mem[i].password, &mem[i].passwordRecover, &mem[i].gender, &mem[i].icNum, &mem[i].phoneNum, &mem[i].category, &mem[i].joinedDate.day, &mem[i].joinedDate.month, &mem[i].joinedDate.year) != EOF) {
				nSize++;
				i++;
			}
			notFound = 0;

			for (i = 0; i < nSize; i++)
			{
				if (strcmp(userInput, mem[i].memberID) == 0) {
					//Print the details
					printf("\n Member Information\n");
					printf(" ------------------\n");
					printf(" Member ID            : %s\n", mem[i].memberID);
					printf(" Member Name          : %s\n", mem[i].memberName);
					printf(" Password             : %s\n", mem[i].password);
					printf(" Password Recovery    : %s\n", mem[i].passwordRecover);
					printf(" Member Gender        : %c\n", mem[i].gender);
					printf(" Member IC Number     : %s\n", mem[i].icNum);
					printf(" Member Phone Number  : %s\n", mem[i].phoneNum);
					printf(" Membership Category  : %s\n", mem[i].category);
					printf(" Member Joined Date   : %d-%d-%d\n", mem[i].joinedDate.day, mem[i].joinedDate.month, mem[i].joinedDate.year);

					printf("\n Start to modify.\n");
					strcpy(modify.memberID, mem[i].memberID);
					printf("\n Member ID                                    : %s\n", modify.memberID);

					printf("\n Member Name                                  : ");
					rewind(stdin);
					scanf("%[^\n]", &modify.memberName);

					printf("\n Password <8 characters>                      : ");
					rewind(stdin);
					scanf("%s", &modify.password);

					printf("\n ---Set the password security question---\n");
					printf(" What city were you born in?                  : ");
					rewind(stdin);
					scanf("%[^\n]", &modify.passwordRecover);

					do {
						printf("\n Member Gender ('M' = Male, 'F' = Female)     : ");
						rewind(stdin);
						scanf("%c", &modify.gender);

						if (toupper(modify.gender) != 'M' && toupper(modify.gender) != 'F') {
							printf(" \033[0;31mInvalid gender. Please re-enter.\033[0m\n");
						}
					} while (toupper(modify.gender) != 'M' && toupper(modify.gender) != 'F');

					do {
						printf("\n Member IC Number (xxxxxx-xx-xxxx)            : ");
						rewind(stdin);
						scanf("%s", &modify.icNum);

						if (modify.icNum[6] != '-' && modify.icNum[9] != '-') {
							printf(" \033[0;31mInvalid format. Please re-enter according to xxxxxx-xx-xxxx\033[0m\n");
						}
					} while (modify.icNum[6] != '-' && modify.icNum[9] != '-');

					printf("\n Member Phone Number (01x-xxxxxxx)            : ");
					rewind(stdin);
					scanf("%s", &modify.phoneNum);

					printf("\n Membership Category (Classic/Silver/Gold)    : ");
					rewind(stdin);
					scanf("%[^\n]", &modify.category);

					do {
						printf("\n Member Joined Date (dd-mm-yyyy)              : ");
						rewind(stdin);
						scanf("%d-%d-%d", &modify.joinedDate.day, &modify.joinedDate.month, &modify.joinedDate.year);
						invalid = dateChecking(modify.joinedDate.day, modify.joinedDate.month, modify.joinedDate.year);

					} while (invalid != 0);

					//Ask for confirmation
					do {
						printf("\n Confirm to modify it? ('Y' = Yes 'N' = No)   : ");
						rewind(stdin);
						scanf("%c", &yesNo);

						switch (toupper(yesNo)) {
						case 'Y':
							strcpy(mem[i].memberID, modify.memberID);
							strcpy(mem[i].memberName, modify.memberName);
							strcpy(mem[i].password, modify.password);
							strcpy(mem[i].passwordRecover, modify.passwordRecover);
							mem[i].gender = toupper(modify.gender);
							strcpy(mem[i].icNum, modify.icNum);
							strcpy(mem[i].phoneNum, modify.phoneNum);
							strcpy(mem[i].category, modify.category);
							mem[i].joinedDate.day = modify.joinedDate.day;
							mem[i].joinedDate.month = modify.joinedDate.month;
							mem[i].joinedDate.year = modify.joinedDate.year;

							FILE* fileWrite = fopen("kaixin.txt", "w");

							for (del = 0; del < nSize; del++) {
								fprintf(fileWrite, "%s|%s|%s|%s|%c|%s|%s|%s|%d-%d-%d\n", mem[del].memberID, mem[del].memberName, mem[del].password, mem[del].passwordRecover, mem[del].gender, mem[del].icNum, mem[del].phoneNum, mem[del].category, mem[del].joinedDate.day, mem[del].joinedDate.month, mem[del].joinedDate.year);
							}
							fclose(fileWrite);
							printf(" \033[2;36mModify sucessful.\033[0m\n");
							break;
						case 'N':
							printf(" \033[0;31mModify unsucessful.\033[0m\n");
							break;
						default:
							printf(" \033[0;31mInvalid choice. Please re-enter.\033[0m\n");
						}
					} while (toupper(yesNo) != 'N' && toupper(yesNo) != 'Y');

				}
				else {
					notFound++;
				}
			}
			if (notFound == nSize) {
				printf(" \033[0;31mNo record found\033[0m\n");
			}

			do {
				printf("\n Continue? ('Y' = Yes 'N' = No): ");
				rewind(stdin);
				scanf("%c", &yesNo2);
				switch (toupper(yesNo2)) {
				case 'Y':
					system("cls"); break;
				case 'N':
					break;
				default:
					printf(" \033[0;31mInvalid choice. Please re-enter.\033[0m\n");
				}
			} while (toupper(yesNo2) != 'N' && toupper(yesNo2) != 'Y');

		} while (toupper(yesNo2) != 'N');
	}
}

void deleteMember() {

	char userChoice = 'Y', userInput[6], yesNo, delAgain;
	int i, nRecord, change, notFound, reWrite, check = 1;

	Member mem[MAX_SIZE_MEMBER];

	checkNull(&userChoice, "kaixin.txt", "r", "a");

	if (toupper(userChoice) == 'Y') {
		system("cls");
		printf("\n");
		printf("+-----------------------------+\n");
		printf(" WELCOME TO DELETE STAFF PAGE! \n");
		printf("+-----------------------------+\n");

		do {
			FILE* fileDel = fopen("kaixin.txt", "r");
			i = 0;
			nRecord = 0;

			while (fscanf(fileDel, "%[^|]|%[^|]|%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%d-%d-%d\n", &mem[i].memberID, &mem[i].memberName, &mem[i].password, &mem[i].passwordRecover, &mem[i].gender, &mem[i].icNum, &mem[i].phoneNum, &mem[i].category, &mem[i].joinedDate.day, &mem[i].joinedDate.month, &mem[i].joinedDate.year) != EOF) {
				++nRecord;
				i++;
			}
			fclose(fileDel);

			printf(" Member ID : ");
			rewind(stdin);
			scanf("%s", &userInput);

			notFound = 0;
			for (i = 0; i < nRecord; i++) {
				if (strcmp(userInput, mem[i].memberID) == 0) {
					//Print the details
					printf("\n Member Information\n");
					printf(" ------------------\n");
					printf(" Member ID            : %s\n", mem[i].memberID);
					printf(" Member Name          : %s\n", mem[i].memberName);
					printf(" Password             : %s\n", mem[i].password);
					printf(" Password Recovery    : %s\n", mem[i].passwordRecover);
					printf(" Member Gender        : %c\n", mem[i].gender);
					printf(" Member IC Number     : %s\n", mem[i].icNum);
					printf(" Member Phone Number  : %s\n", mem[i].phoneNum);
					printf(" Membership Category  : %s\n", mem[i].category);
					printf(" Member Joined Date   : %d-%d-%d\n", mem[i].joinedDate.day, mem[i].joinedDate.month, mem[i].joinedDate.year);

					do {
						printf("\n Confirm to delete ? ('Y' = Yes 'N' = No): ");
						rewind(stdin);
						scanf("%c", &yesNo);

						if (toupper(yesNo) == 'Y') {
							for (change = i; change < nRecord; change++) {
								if (change == nRecord - 1) {
									break;
								}
								else {
									strcpy(mem[change].memberID, mem[change + 1].memberID);
									strcpy(mem[change].memberName, mem[change + 1].memberName);
									strcpy(mem[change].password, mem[change + 1].password);
									strcpy(mem[change].passwordRecover, mem[change + 1].passwordRecover);
									mem[change].gender = mem[change + 1].gender;
									strcpy(mem[change].icNum, mem[change + 1].icNum);
									strcpy(mem[change].phoneNum, mem[change + 1].phoneNum);
									strcpy(mem[change].category, mem[change + 1].category);
									mem[change].joinedDate.day = mem[change + 1].joinedDate.day;
									mem[change].joinedDate.month = mem[change + 1].joinedDate.month;
									mem[change].joinedDate.year = mem[change + 1].joinedDate.year;
								}
							}
							FILE* fileWrite = fopen("kaixin.txt", "w");

							for (i = 0; i < nRecord - 1; i++) {
								fprintf(fileWrite, "%s|%s|%s|%s|%c|%s|%s|%s|%d-%d-%d\n", mem[i].memberID, mem[i].memberName, mem[i].password, mem[i].passwordRecover, mem[i].gender, mem[i].icNum, mem[i].phoneNum, mem[i].category, mem[i].joinedDate.day, mem[i].joinedDate.month, mem[i].joinedDate.year);
							}
							fclose(fileWrite);

							printf(" \033[2;36mRecord is delete successfully.\033[0m\n");
						}
						else if (toupper(yesNo) == 'N') {
							printf(" \033[0;31mThe information for %s have not deleted.\033[0m\n", userInput);
						}
						else {
							printf(" \033[0;31mInvalid code. Please re-enter.\033[0m\n");
						}
					} while (toupper(yesNo) != 'N' && toupper(yesNo) != 'Y');
				}
				else {
					notFound++;
				}
			}
			if (notFound == nRecord) {
				printf(" \033[0;31mNo Record Found.\033[0m\n");
			}

			do {
				printf("\n Continue? ('Y' = Yes 'N' = No): ");
				rewind(stdin);
				scanf("%c", &delAgain);

				switch (toupper(delAgain)) {
				case 'Y':
					system("cls");
					break;
				case 'N':
					break;
				default:
					printf(" \033[0;31mInvalid code. Please re-enter.\033[0m\n");
				}
			} while (toupper(delAgain) != 'N' && toupper(delAgain) != 'Y');
		} while (toupper(delAgain) != 'N');
	}
}

void displayMember() {

	Member mem;

	SYSTEMTIME t;
	GetLocalTime(&t); //get date/time from OS

	char userChoice = 'Y';
	int count = 0;

	if (toupper(userChoice) == 'Y') {
		system("cls");
		FILE* fileDisplay = fopen("kaixin.txt", "r");

		//Display Introduction Screen
		printf("\n");
		printf("\t\t+------------------------------------------+\n");
		printf("\t\t Welcome to Display Member Information Page!\n");
		printf("\t\t+------------------------------------------+\n");
		printf("\n");

		printf("\t\tMember Information Details as at %d-%d-%d, %02d:%02d\n\n",
			t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute);

		printf("MEMBER ID               NAME               PASSWORD    PASSWORD RECOVERY   GENDER (M/F)       IC NUMBER        PHONE NUMBER      CATEGORY    JOINED DATE\n");
		printf("---------   ---------------------------   ----------   -----------------   ------------   -----------------   --------------    ----------   -----------\n");

		while (fscanf(fileDisplay, "%[^|]|%[^|]|%[^|]|%[^|]|%c|%[^|]|%[^|]|%[^|]|%d-%d-%d\n", &mem.memberID, &mem.memberName, &mem.password, &mem.passwordRecover, &mem.gender, &mem.icNum, &mem.phoneNum, &mem.category, &mem.joinedDate.day, &mem.joinedDate.month, &mem.joinedDate.year) != EOF) {
			printf("%7s %27s %15s %15s %13s%c %23s %16s %13s %6d-%d-%d\n", mem.memberID, mem.memberName, mem.password, mem.passwordRecover, "", mem.gender, mem.icNum, mem.phoneNum, mem.category, mem.joinedDate.day, mem.joinedDate.month, mem.joinedDate.year);
			count++;
		}
		printf("---------   ---------------------------   ----------   -----------------   ------------   -----------------   --------------    ----------   -----------\n");
		printf("\n%d member information listed.\n", count);

		if (count == 0) {
			printf("\033[0;31mSorry. No record found.\033[0m\n");
		}

		fclose(fileDisplay);

		system("pause");
	}

}
