#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>


//defining macros
#define FAILURE   -1
#define SUCCESS    0
#define FNAME_SIZE 32
#define WORD_SIZE 32
#define FILE_EMPTY -2
#define FILE_NOTAVAILABLE -3
#define REPEATATION -4


// ANSI Color Codes
#define CLEAR_SCREEN  "\033[2J\033[H"   // Clear the terminal screen and move the cursor to the top-left corner
#define COLOR_RESET   "\033[0m"  		// Reset all attributes to default
#define COLOR_BOLD    "\033[1m"         // Set text to bold
#define COLOR_RED     "\033[1;31m"      // Set text color to red
#define COLOR_GREEN   "\033[1;32m"      // Set text color to green
#define COLOR_YELLOW  "\033[1;33m"		// Set text color to yellow
#define COLOR_BLUE    "\033[1;34m"		// Set text color to blue
#define COLOR_MAGENTA "\033[1;35m"		// Set text color to magenta
#define COLOR_CYAN    "\033[1;36m"		// Set text color to cyan
#define COLOR_GRAY    "\033[0;90m"		// Set text color to gray (dim)

// ANSI Background Colors
#define BG_HEADER         "\033[48;5;236m"   // Dark Slate Gray Background
#define BG_BORDER         "\033[38;5;244m"   // Light Border Gray
#define BG_ROW_ALT        "\033[48;5;234m"   // Subtle dark alternate row


//Structure for file list
typedef char data_t;

typedef struct file_node
{
	data_t file_name[FNAME_SIZE];
	struct file_node *link;

}Flist;

//Structure for link table
typedef struct linkTable_node
{
	int word_count;
	data_t file_name[FNAME_SIZE];
	struct linkTable_node *table_link;
}Ltable;

//structure to store word count
typedef struct word_node
{
	int file_count;
	data_t word[WORD_SIZE];
	Ltable *Tlink;
	struct word_node *link;

}Wlist;


/* --- Fucntions Prototypes ---  */

/* 1. File functions*/

// create files
int create_list_of_files(Flist **f_head, char *name);

// read contents of a file
Wlist *read_datafile(Flist *file, Wlist *head[], char *filename);

int isFileEmpty(char *filename);

void file_validation_n_file_list(Flist **f_head, char *argv[]);

int isfile_exist(char *filename);

int hash_function(const char *word);


/* 2. Linked list functions*/

// create word_list
int insert_at_last(Wlist **head, data_t *data);

// update linktable
int update_link_table(Wlist *head[]);

// update word count
int update_word_count(Wlist ** head, char * file_name);

// print_word_count
int print_word_count(Wlist *head);

//searching a word
int search( Wlist *head, char *word);


/* 3. Database functions*/

// create database
void create_database(Flist *f_head, Wlist *head[]);

//display database 
void display_database( Wlist *head[]);

//update database	
int update_database( Wlist *head[], Flist **f_head);

//save_database
int save_database( Wlist *head[]);

//write in to file
void write_databasefile(Wlist *head, FILE** databasefile);

#endif
