#include "InvertedSearch.h"

char *file_name;

void create_database(Flist *f_head, Wlist *head[])
{
    while (f_head != NULL)
    {
        read_datafile(f_head, head, f_head -> file_name);
        f_head = f_head -> link;
    }
}

// Function to read the content of file and create database for each word
Wlist *read_datafile(Flist *file, Wlist *head[], char *filename)
{
    FILE *fptr = fopen(filename, "r");

    if (fptr == NULL)
    {
        perror("Error opening file");
        return NULL;
    }

    file_name = filename;
    char word[WORD_SIZE];

    while (fscanf(fptr, "%14s", word) != EOF)
    {
        int flag = 1;
        int index;

        // Determine bucket index safely
        if( isalpha( (unsigned char) word[0] ) )
        {
            index = tolower( (unsigned char) word[0] ) - 'a';  // 0 to 25 for alphabetic characters
        }
        else
        {
            index = 26;
        }

        // Search if word already exists in this index bucket
        if (head[index] != NULL)
        {
            Wlist *temp = head[index];
            while (temp != NULL)
            {
                if (strcmp(temp -> word, word) == 0)
                {
                    update_word_count(&temp, filename);
                    flag = 0;
                    break;
                }
                temp = temp -> link; // Moved pointer forward
            }
        }

        // If word does not exist, create a new word node
        if (flag == 1)
        {
            insert_at_last( &head[index], word);
        }
    }
    fclose(fptr);
    
    return head[0];
}



int update_word_count(Wlist **head, char *filename)
{
    if (head == NULL || *head == NULL)
    {
        return FAILURE;
    }

    Ltable *temp = (*head) -> Tlink;
    Ltable *prev = NULL;

    // Traverse the Ltable linked list
    while (temp != NULL)
    {
        // Case 1: Word appears again in the exact same file
        if (strcmp( temp -> file_name, filename) == 0)
        {
            temp -> word_count++;
            return SUCCESS;
        }
        prev = temp;
        temp = temp -> table_link;
    }

    // Case 2: Word appears in a new file -> create a new Ltable node
    Ltable *new_table = (Ltable *) malloc( sizeof(Ltable) );

    if (new_table == NULL)
    {
        return FAILURE;
    }

    new_table -> word_count = 1;
    
    strncpy( new_table -> file_name, filename, FNAME_SIZE - 1);
    
    new_table -> file_name[FNAME_SIZE - 1] = '\0';
    new_table -> table_link = NULL;

    // Increment distinct file count for this word
    (*head) -> file_count++;

    // Link the new node to the end of the Ltable chain
    if (prev != NULL)
    {
        prev -> table_link = new_table;
    }
    else
    {
        (*head) -> Tlink = new_table;
    }

    return SUCCESS;
}
