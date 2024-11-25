// Cazhia Reese Lleva
// CMSC 123 - U3L

// A C program that demonstrate the hash table data structure. 

#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Define constant for lazy deletion
#define deleted "\0"

//Function that prints the data of the hash table
void printTable(HASH_TABLE_PTR H){
	if(isEmpty(H)) {
		printf("*empty\n");
		return;
	}

	for(int index=0; index<H->tableSize; index++){
		printf("Cell#%d: ", index);
		if(H->list[index]){
			printf("%s\n", H->list[index]);
		}else{
			printf("*empty*\n");
		}
	}
}

//Create your own hash functions

//Insert the implementations of the functions found in the header file

// Create a hashTable and initialize list contents to contain NULL elements
HASH_TABLE_PTR createHashTable(int tableSize){
	HASH_TABLE_PTR hashNew = (HASH_TABLE_PTR) malloc(sizeof(HASH_TABLE));

	hashNew -> size = 0;
	hashNew -> tableSize = tableSize;
	hashNew -> list = (STRING_ARRAY_PTR) malloc(sizeof(char*) * tableSize);
	// put NULL as initialization of list
	for (int i = 0; i<tableSize; i++)
		hashNew->list[i] = NULL;
	

	return hashNew;

}

// check if hash table is empty
int isEmpty(HASH_TABLE_PTR H){
	if (H->size == 0)
		return 1;
	return 0;
}
// check if hash table is full
int isFull(HASH_TABLE_PTR H){
	if (H->size == H->tableSize)
		return 1;
	return 0;
}

// this function calculates the index(key) for the hash table
// double hashing is implemented for collission resolution
int hashFunction (STRING key, int i, int table_size)
{
	int keyLen, h2, h1,index;
	
	keyLen = strlen(key);
	h1 = 0;
	// summation of odd ASCII equivalent of the key is h1
	for (int j = 0; j<keyLen; j++)
	{
		if (key[j] % 2 != 0)
			h1 += key[j];
	}

	// h2
	h2 = 37 - h1 % 26;

	// calculate actual index depending on collissions
	index = (h1 + i * h2) % table_size;
	return index;

}

// put() function for inserting key:value pairs in the hash function
void put(HASH_TABLE_PTR H, STRING key, STRING data){
	// check if hash table is full
	if (isFull(H))
	{
		printf("Hash Table is full. \n");
		return;
	}

	int i = 0;
	int index = hashFunction(key, i, H->tableSize);
	// calculate index
	// collission resolution is double hashing

	// perform an insert on that index if NULL or marked as deleted
	while (H->list[index] != NULL)
	{
		
		if (strcmp(H->list[index], deleted) == 0) break;
		i++;
		index = hashFunction(key, i, H->tableSize);
	}
	
	// perform actual insertion, strcpy passed string literal
	STRING dataCopy = (STRING) malloc(sizeof(char) * strlen(data));
	strcpy(dataCopy, data);
	H->list [index] = dataCopy;
	H->size += 1;
}


// find function takes a key and find associated data
STRING find(HASH_TABLE_PTR H, STRING key, STRING data){
	// check if hash table is empty
	if(isEmpty(H))
	{
		printf("Hash Table is empty! \n");
		return NULL;
	}

	int i = 0;
	int index = hashFunction(key, i, H->tableSize);
	// iterate over hash table, check if data is equivalent to what we are looking for, else continue searching
	while (H->list[index] != NULL )
	{
		if (strcmp(H->list[index], data) == 0) return H->list[index];
		i++;
		index = hashFunction(key, i, H->tableSize);

		// break loop if number of collissions is greater than table size (the iterations went over the limit)
		if (i >= H-> tableSize) break;
	}

	return NULL;
}

// delete a key value pair using lazy deletion
STRING erase(HASH_TABLE_PTR H, STRING key, STRING data){
	// cant erase if hash table is empty
	if(isEmpty(H))
	{
		printf("Hash Table is empty! \n");
		return NULL;
	}

	// find the location of element we are deleting using find() function
	STRING location = find(H, key, data);
	// if found, store the data we are deleting then return
	if (location){
		STRING returnedString = (STRING) malloc((sizeof(char) * strlen(location) + 1));
		strcpy(returnedString, location);
		strcpy(location, deleted); 
		(H-> size) --;
		return returnedString;
	}else{
		// if not found, dont return anything
		printf("Not found. \n");
		return NULL;
	} 
}

// free nodes inside the hash table (list)
void destroy(HASH_TABLE_PTR H){
	for (int i = 0; i < H->tableSize; i++)
	{
		if (H->list[i] != NULL)
		{
			// free node then turn back the content of the char pointer array to NULL
			if (strcmp(H->list[i], deleted) != 0) (H->size)--;
			free(H->list[i]);
			H->list[i] = NULL;
			
		}
	}
}


int main(){

	char command;
	STRING key;
	STRING data;
	STRING result;

	int tsize;
	HASH_TABLE_PTR H;
	
	// get table size then maxsize
	scanf("%d\n", &tsize); 
	H = createHashTable(tsize);

	// assume max key size is 20
	key = (STRING)malloc(sizeof(char)*20);
	key[0] = '\0';
	// assume max data size is 100
	data = (STRING)malloc(sizeof(char)*100);
	data[0] = '\0';

	while(1){
		scanf(" %c", &command);

		switch(command){
			case '+':
				scanf(" k:%s d:%s", key, data);
				printf("Inserting data %s with key %s\n", data, key);
				put(H, key, data);
				break;
			case '-':
				scanf(" k:%s d:%s", key, data);
				printf("Deleting data with key %s\n", key);
				result = erase(H, key, data); 
				// result is unused. print if u want
				break;
			case '?':
				scanf(" k:%s d:%s", key, data);
				printf("Searching data with key: %s. Location: %p\n", key, find(H, key, data));
				// (nil) means NULL pointer
				break;
			case 'p':
				printf("Hash Table: \n");
				printTable(H);
				printf("\n");
				break;
			case 'E':
				printf("Hash table %s empty.\n", isEmpty(H)?"is":"is not");
				break;
			case 'F':
				printf("Hash table %s full.\n", isFull(H)?"is":"is not");
				break;
			case 'C':
				printf("Deleting all contents.\n");
				destroy(H);
				break;
			case 'Q':
				free(key); free(data);
				destroy(H); // ensure deletion
				free(H->list);
				free(H);
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}
	
	return 0;
}
