#include "InvertedSearch.h"

int save_database(Wlist *head[]) // function to save the entire database into a file
{
    // 1. Check if database contains any data before proceeding
    int is_empty = 1;

    for (int i = 0; i < 27; i++)
    {
        if (head[i] != NULL)
        {
            is_empty = 0;
            break;
        }
    }

    if (is_empty)
    {
        printf(COLOR_RED "[-] Error: Database is empty! Nothing to save.\n" COLOR_RESET);
        return FAILURE;
    }

    // 2. Prompt user for filename
    char file_name[FNAME_SIZE];

    printf(COLOR_CYAN "Enter the filename to save the database (.txt / .csv): " COLOR_RESET);
    scanf("%14s", file_name);

    // 3. Extension validation
    char *ext = strrchr(file_name, '.');

    if (ext == NULL || (strcmp(ext, ".txt") != 0 && strcmp(ext, ".csv") != 0))
    {
        printf(COLOR_YELLOW "[!] Warning: Invalid file format. File must end with .txt or .csv\n" COLOR_RESET);
        return FAILURE;
    }

    // 4. Open file for writing
    FILE *fptr = fopen(file_name, "w");

    if (fptr == NULL)
    {
        printf(COLOR_RED "[-] Error: Failed to open file \"%s\" for saving.\n" COLOR_RESET, file_name);
        return FAILURE;
    }

    // 5. Write records bucket by bucket
    for (int i = 0; i < 27; i++)
    {
        if (head[i] != NULL)
        {
            write_databasefile(head[i], &fptr);
        }
    }

    // 6. Close file descriptor
    fclose(fptr);

    printf(COLOR_GREEN "[+] Success: Database successfully saved to " COLOR_BLUE "\"%s\"" COLOR_GREEN "!\n" COLOR_RESET, file_name);
    return SUCCESS;
}

// Inverted index save format: #[index];word;file_count;file_name;word_count;...#
void write_databasefile(Wlist *head, FILE **databasefile)
{
    if (head == NULL || databasefile == NULL || *databasefile == NULL)
    {
        return;
    }

    while (head != NULL)
    {
        // Safe index determination
        int index;
        if( isalpha( (unsigned char) head -> word[0] ))
        {
            index = tolower( (unsigned char) head -> word[0]) - 'a';
        }
        else
        {
            index = 26;
        }

        // Write #[index];word;file_count;
        fprintf(*databasefile, "#[%d];%s;%d;", index, head -> word, head -> file_count);

        // Write list of files and respective counts
        Ltable *Thead = head->Tlink;
        
        while (Thead != NULL)
        {
            fprintf(*databasefile, "%s;%d;", Thead->file_name, Thead->word_count);
            Thead = Thead->table_link;
        }

        // Close entry marker
        fprintf(*databasefile, "#\n");

        head = head->link;
    }
}
