/*****************************************************
 *
 *		  Name : main.c
 *  Created on : Aug 12, 2024
 *      Author : Marwan Elsayed
 * Description : Student information management system
 *
*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 50

/*****************************************************/

/* Structure of student data*/
struct student{
	int id;
	char name[SIZE];
	int age;
	float gpa;
};


/* Linked List Node Definition */
struct node {
	struct student data;
	struct node *next;
};

/* HEAD of the linked list */
struct node *head = NULL;

/*****************************************************/
/* Functions prototype */

void displayLine(void);		// Print a line of "-" to separate block of text
void addStudent(const struct student *const ptr);		// Add new student data
void displayStudents(void);		// Display all students information
void searchStudentByID(int id);		// Search for a student by id and display it's information
void updateStudent(int id);		// Update a student information by id
float calculateAverageGPA(void);		// calculate average GPA of all students
void searchHighestGPA(void);		// Search for student with highest GPA and display it's information
void deleteStudent(int id);		// Delete all information of specific student by id

/*****************************************************/

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	int operation = 0;		/* Variable to store operation index */
	int id = 0 ;

	do{

		/* Program Menu */
		printf("1. Add student\n");
		printf("2. Display students\n");
		printf("3. Search student by ID\n");
		printf("4. Update student information\n");
		printf("5. Delete student\n");
		printf("6. Calculate Average GPA\n");
		printf("7. Search for student with highest GPA\n");
		printf("8. Exit\n");
		printf("Enter choice:\t");
		scanf("%d",&operation);
		displayLine();

		switch (operation)
		{
			case 0:
					continue;

			case 1:
					struct student newStudent;		/* Stuct To Store New Student Data */
					printf("Enter Student ID :\t");
					scanf("%d",&newStudent.id);
					printf("Enter Name:\t");
					scanf("%s",&newStudent.name);
					printf("Enter Age :\t");
					scanf("%d",&newStudent.age);
					printf("Enter GPA :\t");
					scanf("%f",&newStudent.gpa);
					addStudent(&newStudent);
					break;

			case 2:
					displayStudents();
					break;

			case 3:
					printf("Enter student ID to search :\t");
					scanf("%d",&id);
					searchStudentByID(id);
					break;

			case 4:
					printf("Enter student ID to update it's information :\t");
					scanf("%d",&id);
					updateStudent(id);
					break;

			case 5:
					printf("Enter student ID to delete it's information :\t");
					scanf("%d",&id);
					deleteStudent(id);
					break;

			case 6:
					printf("average gpa = %f\n",calculateAverageGPA());
					break;

			case 7:
					searchHighestGPA();
					break;

			case 8:
					printf("EXITING...\n");
					break;

			default:
					printf("INVALID INPUT\n");
		}

		displayLine();

	} while (operation != 8);
}

/*****************************************************/
/* Function Definition */

/*****************************************************/
/* Print Line */

void displayLine(void)
{
	printf("------------------------------------------------\n");
	return;
}

/*****************************************************/
/* Add new student data */

void addStudent(const struct student *const ptr)
{
	/* Pointer that holds head address */
	struct node *current = head;

	/* Check if the student's ID already exists */
	while (current != NULL)
		{
			if (ptr->id == current->data.id)
			{
				displayLine();
				printf("THIS ID IS ALREADY RESERVED\n");
				return ;
			}
			current = current->next;
		}

	/* Allocating memory for the new node */
	struct node* link = (struct node*) malloc (sizeof(struct node));

	/* Inserting New Nodes At First */
	/* Inserting the data into the new node and make it the new head */
	link->data = *ptr;
	link->next = head;
	head = link;

}

/*****************************************************/
/* Display all students information */

void displayStudents(void)
{
	struct node *current = head;

	if (head == NULL)
	{
		printf("THERE IS NO DATA ADDED\n");
		printf("PLEASE ADD STUDENT DATA FIRST\n");
		return;
	}

	while (current != NULL)
	{
		printf("[  ID: %d, NAME: %s, AGE: %d, GPA: %f ]\n",
				current->data.id,current->data.name,current->data.age,current->data.gpa);
		current = current->next;
	}
}

/*****************************************************/
/* Search for a student by id and display it's information */

void searchStudentByID(int id)
{
	struct node *current = head;

	if (head == NULL)
	{
		printf("THERE IS NO DATA ADDED\n");
		printf("PLEASE ADD STUDENT DATA FIRST\n");
		return;
	}

	while (current != NULL)
	{
		if (id == current->data.id)
		{
			printf("STUDENT FOUND :\n");
			printf("[  ID: %d, NAME: %s, AGE: %d, GPA: %f ]\n",
					current->data.id,current->data.name,current->data.age,current->data.gpa);

			return;
		}
		current = current->next;
	}

	printf("STUDENT WITH ID %d NOT FOUND\n",id);
}

/*****************************************************/
/* Update a student information by id */

void updateStudent(int id)
{
	struct node *current = head;

	if (head == NULL)
	{
		printf("THERE IS NO DATA ADDED\n");
		printf("PLEASE ADD STUDENT DATA FIRST\n");
		return;
	}

	while (current != NULL)
	{
		if (id == current->data.id)
		{
			/* updating student details */
			printf("Enter new details for student with ID %d :\n",id);
			printf("Enter Name:\t");
			scanf("%s",&current->data.name);
			printf("Enter Age :\t");
			scanf("%d",&current->data.age);
			printf("Enter GPA :\t");
			scanf("%f",&current->data.gpa);
			printf("student details updated successfully\n");
			return;

		}
		current = current->next;
	}

	printf("STUDENT WITH ID %d NOT FOUND\n",id);
}

/****************************************************/
/* calculate average GPA of all students */

float calculateAverageGPA(void)
{
	struct node *current = head;
	float sum = 0;
	float count = 0;

	/* if no student added yet */
	if (head == NULL)
	{
		return 0;
	}

	while (current != NULL)
	{
		sum += current->data.gpa ;
		count ++;
		current = current->next;
	}

	/*Return the average of all GPAs*/
	return (sum/count) ;
}

/*****************************************************/
/* Search for student with highest GPA and display it's information */

void searchHighestGPA(void)
{
	struct node *current = head;	/* Pointer that holds head address */
	struct student *highestGPAstudent = NULL;
	int highestGPA = 0;

	if (head == NULL)
	{
		printf("THERE IS NO DATA ADDED\n");
		printf("PLEASE ADD STUDENT DATA FIRST\n");
		return;
	}

	while (current != NULL)
	{
		if (highestGPA < current->data.gpa)
		{
			highestGPA = current->data.gpa;
			highestGPAstudent = &(current->data);
		}
		current = current->next;
	}

	printf("STUDENT FOUND :\n");
	printf("[  ID: %d, NAME: %s, AGE: %d, GPA: %f ]\n",
			highestGPAstudent->id,highestGPAstudent->name,highestGPAstudent->age
		    ,highestGPAstudent->gpa);

}

/*****************************************************/
/* Delete all information of specific student by id */

void deleteStudent(int id)
{
	struct node *current = NULL;
	struct node *previous = NULL;

	if (head == NULL)
	{
		printf("THERE IS NO DATA ADDED\n");
		printf("PLEASE ADD STUDENT DATA FIRST\n");
		return;
	}

	/* Check first node */
	if (id == head->data.id)
	{
		printf("STUDENT WITH ID %d DELETED SUCCESSFULLY\n",id);
		previous = head ;
		head = head->next;
		free(previous);
		return;
	}

	/* Check the rest of nodes */
	current = head->next;
	previous = head;
	while (current != NULL)
	{
		if (id == current->data.id)
		{
			printf("STUDENT WITH ID %d DELETED SUCCESSFULLY\n",id);
			previous->next = current->next;
			free(current);
			return;
		}
		previous = current ;
		current = current->next;
	}

	printf("STUDENT WITH ID %d NOT FOUND\n",id);
}

/*****************************************************/
