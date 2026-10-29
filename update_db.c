#include "InvertedSearch.h"

int update_database(Wlist *head[], Flist **f_head)
{
    // 1. Ensure database exists before updating
    int db_empty = 1;

    for (int i = 0; i < 27; i++)
    {
        if (head[i] != NULL)
        {
            db_empty = 0;
            break;
        }
    }

    if (db_empty)
    {
        printf(COLOR_RED "Error: Database is empty! Please create database first (Option 1).\n" COLOR_RESET);
        return FAILURE;
    }

    // 2. Prompt user for the new file name
    char file_name[FNAME_SIZE];

    printf("Enter the file to be added to the database: ");
    scanf("%31s", file_name);

    // 3. Validation: Check if file exists and can be opened
    FILE *fptr = fopen(file_name, "r");

    if (fptr == NULL)
    {
        printf(COLOR_RED "Error: File \"%s\" does not exist or cannot be opened.\n" COLOR_RESET, file_name);
        return FILE_NOTAVAILABLE;
    }

    // 4. Validation: Check if file is empty
    fseek(fptr, 0, SEEK_END);

    if (ftell(fptr) == 0)
    {
        printf(COLOR_YELLOW "Error: File \"%s\" is empty.\n" COLOR_RESET, file_name);
        fclose(fptr);

        return FILE_EMPTY;
    }
    fclose(fptr);

    // 5. Validation: Check for duplicates in existing file list
    Flist *temp = *f_head;
    Flist *prev = NULL;

    while (temp != NULL)
    {
        if (strcmp(temp->file_name, file_name) == 0)
        {
            printf(COLOR_YELLOW "Warning: File \"%s\" is already present in the database.\n" COLOR_RESET, file_name);
            return REPEATATION;
        }
        prev = temp;
        temp = temp -> link;
    }

    // 6. Allocate and insert new file node at the end of the file list
    Flist *new_file = (Flist *) malloc( sizeof(Flist) );

    if (new_file == NULL)
    {
        printf(COLOR_RED "Error: Memory allocation failed for new file node.\n" COLOR_RESET);
        return FAILURE;
    }

    strncpy( new_file -> file_name, file_name, FNAME_SIZE - 1);
    
    new_file -> file_name[FNAME_SIZE - 1] = '\0';
    
    new_file -> link = NULL;

    if (*f_head == NULL)
    {
        *f_head = new_file;
    }
    else
    {
        prev -> link = new_file;
    }

    // 7. Index ONLY the newly added file into the database
    read_datafile(new_file, head, new_file -> file_name);

    printf(COLOR_GREEN "Successfully added \"%s\" and updated the database.\n" COLOR_RESET, file_name);
    return SUCCESS;
}
