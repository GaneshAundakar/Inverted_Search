#include "InvertedSearch.h"


void display_database(Wlist *head[])  // function to display the entire database in a tabular format
{
    int is_empty = 1;

    for (int i = 0; i < 27; i++)
    {
        if (head[i] != NULL)
        {
            is_empty = 0;
            break;
        }
    }

    if (is_empty)  // Check if the database is empty
    {
        printf(COLOR_RED "[-] Database is empty. Please create or update the database first.\n" COLOR_RESET);
        return;
    }

    // Top Box Border
    printf(BG_BORDER "┌────────────┬────────────────────┬────────────────┬────────────────────┬────────────┐\n" COLOR_RESET);

    // Box Header with Slate Background
    printf(BG_BORDER "│" BG_HEADER COLOR_CYAN COLOR_BOLD "   Index    " BG_BORDER "│"
           BG_HEADER COLOR_CYAN COLOR_BOLD "        Word        " BG_BORDER "│"
           BG_HEADER COLOR_CYAN COLOR_BOLD "   File Count   " BG_BORDER "│"
           BG_HEADER COLOR_CYAN COLOR_BOLD "     File Name      " BG_BORDER "│"
           BG_HEADER COLOR_CYAN COLOR_BOLD " Word Count " BG_BORDER "│\n" COLOR_RESET);

    // Separator under header
    printf(BG_BORDER "├────────────┼────────────────────┼────────────────┼────────────────────┼────────────┤\n" COLOR_RESET);

    for (int i = 0; i < 27; i++)
    {
        if (head[i] != NULL)
        {
            print_word_count(head[i]);
        }
    }

    // Bottom Box Border
    printf(BG_BORDER "└────────────┴────────────────────┴────────────────┴────────────────────┴────────────┘\n" COLOR_RESET);
}

int print_word_count(Wlist *head)
{
    if (head == NULL)
    {
        return FAILURE;
    }

    while (head != NULL)
    {
        int index;
        if (isalpha((unsigned char)head->word[0]))
        {
            index = tolower((unsigned char)head->word[0]) - 'a';  // 0 to 25 for alphabetic characters
        }
        else
        {
            index = 26;
        }

        // Format fixed-width data into string buffers (exact column widths)
        char idx_buf[16];
        char word_buf[32];
        char fcount_buf[16];
        char fname_buf[32];
        char wcount_buf[16];

        snprintf(idx_buf, sizeof(idx_buf), "[%d]", index);
        snprintf(word_buf, sizeof(word_buf), "%-18s", head->word);
        snprintf(fcount_buf, sizeof(fcount_buf), "%-14d", head->file_count);

        Ltable *Thead = head->Tlink;

        if (Thead != NULL)
        {
            snprintf(fname_buf, sizeof(fname_buf), "%-18s", Thead->file_name);
            snprintf(wcount_buf, sizeof(wcount_buf), "%-10d", Thead->word_count);

            // Primary Row with Box Dividers
            printf(BG_BORDER "│ " COLOR_YELLOW  "%-10s " 
                   BG_BORDER "│ " COLOR_GREEN   "%s " 
                   BG_BORDER "│ " COLOR_MAGENTA "%s " 
                   BG_BORDER "│ " COLOR_BLUE    "%s " 
                   BG_BORDER "│ " COLOR_BOLD    "%s " 
                   BG_BORDER "│\n" COLOR_RESET,
                   idx_buf, word_buf, fcount_buf, fname_buf, wcount_buf);

            Thead = Thead->table_link;

            // Secondary Rows for words in multiple files
            while (Thead != NULL)
            {
                snprintf(fname_buf, sizeof(fname_buf), "%-18s", Thead->file_name);
                snprintf(wcount_buf, sizeof(wcount_buf), "%-10d", Thead->word_count);

                printf(BG_BORDER "│ %-10s │ %-18s │ %-14s │ "
                       COLOR_BLUE "%s " BG_BORDER "│ " 
                       COLOR_BOLD "%s " BG_BORDER "│\n" COLOR_RESET,
                       "", "", "", fname_buf, wcount_buf);

                Thead = Thead->table_link;
            }
        }

        head = head->link;
    }

    return SUCCESS;
}
