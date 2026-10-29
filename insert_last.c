#include "InvertedSearch.h"

extern char *file_name; // Global variable to hold the current file name being processed

int insert_at_last(Wlist **head, data_t *data)
{
    if (head == NULL || data == NULL)
    {
        return FAILURE;
    }

    // 1. Create and allocate the Wlist node
    Wlist *new_wlist = (Wlist *)malloc(sizeof(Wlist));

    if (new_wlist == NULL)
    {
        printf(COLOR_RED "[-] Error: Memory allocation failed for word node \"%s\".\n" COLOR_RESET, data);
        return FAILURE;
    }

    // 2. Initialize word fields safely
    new_wlist -> file_count = 1;
    
    strncpy(new_wlist -> word, data, WORD_SIZE - 1);
    
    new_wlist -> word[WORD_SIZE - 1] = '\0';
    
    new_wlist -> Tlink = NULL;
    
    new_wlist -> link = NULL;

    // 3. Create initial Ltable node for the current file
    if (update_link_table(&new_wlist) == FAILURE)
    {
        printf(COLOR_RED "[-] Error: Failed to create file link table for word \"%s\".\n" COLOR_RESET, data);
        free(new_wlist);
  
        return FAILURE;
    }

    // 4. If bucket list is empty, insert at head
    if (*head == NULL)
    {
        *head = new_wlist;
        return SUCCESS;
    }

    // 5. Traverse to the end and link the new node
    Wlist *temp = *head;
  
    while (temp -> link != NULL)
    {
        temp = temp -> link;
    }
    temp -> link = new_wlist;

    return SUCCESS;
}

int update_link_table(Wlist *head[])
{
    if (head == NULL || *head == NULL)
    {
        return FAILURE;
    }

    if (file_name == NULL)
    {
        printf(COLOR_YELLOW "[!] Warning: No active filename specified for link table.\n" COLOR_RESET);
        return FAILURE;
    }

    // 1. Allocate memory for new Ltable entry
    Ltable *new_table = (Ltable *)malloc(sizeof(Ltable));
    
    if (new_table == NULL)
    {
        printf(COLOR_RED "[-] Error: Memory allocation failed for Ltable node.\n" COLOR_RESET);
        return FAILURE;
    }

    // 2. Populate Ltable attributes safely
    new_table -> word_count = 1;
    
    strncpy(new_table -> file_name, file_name, FNAME_SIZE - 1);
    
    new_table -> file_name[FNAME_SIZE - 1] = '\0';
    
    new_table -> table_link = NULL;

    // 3. Attach as primary link table node
    (*head) -> Tlink = new_table;

    return SUCCESS;
}
