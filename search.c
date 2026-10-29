#include "InvertedSearch.h"

int search(Wlist *head, char *word)  // function to search for a word in the database
{
    // 1. Check if the index list is empty
    if (head == NULL)
    {
        printf(COLOR_YELLOW "Search list is empty for this character bucket.\n" COLOR_RESET);
        return FAILURE;
    }

    // 2. Traverse the list in this bucket
    while (head != NULL)
    {
        // Compare current node's word with search word
        if (strcmp(head -> word, word) == 0)
        {
            printf("\nWord " COLOR_GREEN "\"%s\"" COLOR_RESET " is present in " COLOR_MAGENTA "%d" COLOR_RESET " file(s):\n", word, head -> file_count);

            Ltable *Thead = head -> Tlink;

            while (Thead != NULL)
            {
                printf("  " COLOR_CYAN "->" COLOR_RESET " File: " COLOR_BLUE "%-15s" COLOR_RESET 
                       " | Count: " COLOR_BOLD "%d\n" COLOR_RESET, 
                       Thead -> file_name, Thead -> word_count);

                Thead = Thead -> table_link;
            }
            printf("\n");
            return SUCCESS; // Stop and return once found
        }
        head = head -> link;
    }

    // 3. Word not found in this bucket
    printf(COLOR_RED "Word \"%s\" not found in the database.\n" COLOR_RESET, word);
    return FAILURE;
}
