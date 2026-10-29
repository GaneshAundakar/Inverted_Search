#include "InvertedSearch.h"

void file_validation_n_file_list(Flist **f_head, char *argv[])  // function to validate files and create a linked list of valid files
{
    int i = 1; // argv[0] (executable) is excluded
    int empty;

    while (argv[i] != NULL)
    {
        empty = isFileEmpty(argv[i]);

        if (empty == FILE_NOTAVAILABLE)  // Check if the file is not available
        {
            printf(COLOR_RED "[-] File " COLOR_BLUE "\"%s\"" COLOR_RED " is not available.\n" COLOR_RESET, argv[i]);

            printf(COLOR_YELLOW "    -> Skipping file from list.\n" COLOR_RESET);

            i++;
            continue;
        }
        else if (empty == FILE_EMPTY)  // Check if the file is empty 
        {
            printf(COLOR_RED "[-] File " COLOR_BLUE "\"%s\"" COLOR_RED " is empty.\n" COLOR_RESET, argv[i]);

            printf(COLOR_YELLOW "    -> Skipping file from list.\n" COLOR_RESET);
            i++;
            continue;
        }
        else
        {
            int ret_val = create_list_of_files(f_head, argv[i]);

            if (ret_val == SUCCESS)
            {
                printf(COLOR_GREEN "[+] Successfully added " COLOR_BLUE "\"%s\"" COLOR_GREEN " to the file list.\n" COLOR_RESET, argv[i]);
            }
            else if (ret_val == REPEATATION)
            {
                printf(COLOR_YELLOW "[!] Duplicate file " COLOR_BLUE "\"%s\"" COLOR_YELLOW " ignored.\n" COLOR_RESET, argv[i]);
            }
            else
            {
                printf(COLOR_RED "[-] Error: Failed to add \"%s\" (Memory allocation error).\n" COLOR_RESET, argv[i]);
            }

            i++; // avoids infinite loop on valid files
        }
    }
}

// Function to check file availability and content
int isFileEmpty(char *filename)
{
    FILE *fptr = fopen(filename, "r");

    if (fptr == NULL)
    {
        return FILE_NOTAVAILABLE;
    }

    fseek(fptr, 0, SEEK_END);

    if (ftell(fptr) == 0)
    {
        fclose(fptr);
        return FILE_EMPTY;
    }

    fclose(fptr);
    return SUCCESS;
}

// Create the file linked list
int create_list_of_files(Flist **f_head, char *name)
{
    // 1. Check for duplicates
    Flist *temp = *f_head;
    Flist *prev = NULL;

    while (temp != NULL)
    {
        if (strcmp(temp -> file_name, name) == 0)
        {
            return REPEATATION;
        }
        prev = temp;
        temp = temp -> link;
    }

    // 2. Allocate memory for new file node
    Flist *new_node = (Flist *) malloc( sizeof(Flist));

    if (new_node == NULL)
    {
        return FAILURE;
    }

    // 3. Populate node data
    strncpy(new_node -> file_name, name, FNAME_SIZE - 1);
    
    new_node -> file_name[FNAME_SIZE - 1] = '\0';
    new_node -> link = NULL;

    // 4. Attach node to list
    if (*f_head == NULL)
    {
        *f_head = new_node;
    }
    else
    {
        prev -> link = new_node;
    }

    return SUCCESS;
}
