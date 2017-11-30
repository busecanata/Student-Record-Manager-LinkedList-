// Lab 5: Linked List
// Created by Leighton Tidwell

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void printMenu();
void printRecords();
int isEmpty();
void addRecord(char fn[20], char ln[20], char zc[20], double score);
int removeRecord(char ln[20]);
void searchZip(char zc[5]);
void searchRange(double x, double y);
void findMedian();
void sortScores(double* s, int n);

// Declare nodes
struct students{
	char firstName[20];
	char lastName[20];
	double score;
	char zipcode[5];
	struct students *next;
};
struct students *front = NULL;
struct students *rear = NULL;

int numRecords = 0;

int main(){
	char firstName[20];
	char lastName[20];
	char zipcode[5];
	int i,j,recordsToEnter,choice;
	double minScore,maxScore;
	double score;

	printf("WELCOME TO THE STUDENT RECORD MANAGER 100 V 1.0! \n");
	printf("Please indicate the number of student records you want to enter (min 5): \n");
	scanf("%d",&recordsToEnter);

	if(recordsToEnter < 5){
		printf("You must enter more than five... terminating. \n");
		return 0;
	}
	printf("Please enter the values for each student (firstName lastName score zipcode) pressing enter after each: \n");
	for(i = 0; i < recordsToEnter; i ++){
		// add record
		printf("%d > ",i+1);
		scanf("%s %s %lf %s",&firstName, &lastName, &score, &zipcode);
		addRecord(firstName,lastName,zipcode,score);
	}

	// Generate menu and do actions
	do{
		printMenu();
		scanf("%d",&choice);

		switch(choice){
			case 1:
				printRecords();
				break;
			case 2:
				printf("Please enter the value you would like to add (firstName lastName score zipcode):\n");
				scanf("%s %s %lf %s",&firstName, &lastName, &score, &zipcode);
				addRecord(firstName,lastName,zipcode,score);
				break;
			case 3:
				printf("Please enter the last name of the student(s) you'd like to delete: \n");
				scanf("%s",&lastName);
				removeRecord(lastName);
				break;
			case 4:
				printf("Please enter the zip code you would like to search for: \n");
				scanf("%s",&zipcode);
				searchZip(zipcode);
				break;
			case 5:
				printf("Please enter the score range you would like to search from(min max): \n");
				scanf("%lf %lf",&minScore,&maxScore);
				searchRange(minScore,maxScore);
				break;
			case 6:
				findMedian();
				break;
			case 7:
				return 0;
				break;
			case 0:
				return 0;
		}
		
	}
	while(1);
		return 0;
}

// Print user menu
void printMenu(){
	printf("\tMain Menu\t\n"
		"============================\n"
		" > Print records (press 1) \n"
		" > Add a new record (press 2) \n"
		" > Delete a record (press 3) \n"
		" > Search by zip code (press 4)\n"
		" > Search by score range (press 5) \n"
		" > Find median score (press 6) \n"
		" > Exit the program (press 0)\n"
		"============================\n"
		"Please select an option: ");
}
void printRecords(){
	if(!isEmpty()){
		struct students *temp = front;
		temp = front;
		while(temp != NULL){
			printf(" > %s %s %0.2lf %s \n",temp->firstName,temp->lastName,temp->score,temp->zipcode);
			temp = temp->next;
		}
	}
	else{
		printf("List is empty... \n");
	}
}
int isEmpty(){
	if(front == NULL && rear == NULL){
		// list empty
		return 1;
	}
	else{
		return 0;
	}
}

void addRecord(char fn[20], char ln[20], char zc[5], double score){
	// all global
	if(isEmpty()){
		struct students *temp = malloc(sizeof(struct students));
		strcpy(temp->firstName,fn);
		strcpy(temp->lastName,ln);
		strcpy(temp->zipcode,zc);
		temp->score = score;
		front = temp;
		rear = temp;
		numRecords++;
	}
	else{
		struct students *temp = malloc(sizeof(struct students));
		strcpy(temp->firstName,fn);
		strcpy(temp->lastName,ln);
		strcpy(temp->zipcode,zc);
		temp->score = score;
		rear->next = temp;
		rear = temp;
		numRecords++;
	}
}
// remove record
int removeRecord(char ln[20]){
	if(!isEmpty()){
		struct students *temp = front;
		struct students *old;
		int location; 
		temp = front;
		while(temp != NULL){
			location++;
			if(strcmp(temp->lastName,ln) == 0){
				if(temp == front && temp == rear){
					front = NULL;
					rear = NULL;
				}
				else if(temp == front){
					front = temp->next;
				}
				else if(temp == rear){
					rear = old;
				}
				else{
					old->next = temp->next;
				}
				free(temp);
			}
			old = temp;
			temp = temp->next;
		}
	}
	else{

	}
}

void searchZip(char zc[5]){
	if(!isEmpty()){
		struct students *temp = front;
		temp = front;
		while(temp != NULL){
			if(strcmp(zc,temp->zipcode) == 0){
				printf(" > %s %s %0.2lf %s \n",temp->firstName,temp->lastName,temp->score,temp->zipcode);
			}
			temp = temp->next;
		}
	}
	else{
		printf("List is empty... \n");
	}
}

void searchRange(double x, double y){
	if(!isEmpty()){
		struct students *temp = front;
		temp = front;
		while(temp != NULL){
			if(temp->score > x && temp->score < y){
				printf(" > %s %s %0.2lf %s \n",temp->firstName,temp->lastName,temp->score,temp->zipcode);
			}
			temp = temp->next;
		}
	}
	else{
		printf("List is empty... \n");
	}
}

void findMedian(){
	if(!isEmpty()){
		double *scores = malloc(numRecords);
		int count = 0;
		struct students *temp = front;
		temp = front;
		while(temp != NULL){
			scores[count] = temp->score;
			temp = temp->next;
			count++;
		}
		// sort
		sortScores(scores,numRecords);
		int medianRecord = numRecords/2;
		printf("The median score is: %0.2lf \n",scores[medianRecord]);

		printf("These students have ABOVE the median score: \n");
		temp = front;
		while(temp != NULL){
			if(temp->score > scores[medianRecord]){
				printf(" > %s %s %0.2lf %s \n",temp->firstName,temp->lastName,temp->score,temp->zipcode);
			}
			temp = temp->next;
		}

	}
	else{
		printf("List is empty... \n");
	}
}

// Recursive bubble sort for score
void sortScores(double* s,int n){
	int i;
	double tempF;
	if(n == 1)
		return;
	for(i=0;i<n-1;i++){
		if(s[i+1] > s[i]){
			tempF = *(s+i+1);
			*(s+i+1) = *(s+i);
			*(s+i) = tempF;
		}
	}

	sortScores(s,n-1);
}

