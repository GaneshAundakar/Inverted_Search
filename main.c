#include "InvertedSearch.h"

int main(int argc, char *argv[])
{
    printf(CLEAR_SCREEN); // Clear the terminal screen for better readability

    int option;
    Wlist *head[27] = {NULL}; // 26 for letters + 1 for non-alphabetic characters
    Flist *f_head = NULL;     // head of the file linked list

    if (argc <= 1) // Check if at least one file is provided as an argument
    {
        printf(COLOR_RED "\n[-] Error: Insufficient arguments.\n" COLOR_RESET);
        printf(COLOR_YELLOW "Usage: " COLOR_CYAN "%s <file1.txt> <file2.txt> ...\n" COLOR_RESET, argv[0]);
        return FAILURE;
    }

    // Validate and build the initial file linked list
    file_validation_n_file_list(&f_head, argv);

    if (f_head == NULL)
    {
        printf(COLOR_RED "\n[-] No valid files were added to the list.\n" COLOR_RESET);
        printf(COLOR_RED "[-] Process terminated.\n" COLOR_RESET);
        return FAILURE;
    }

    char choice = 'y';

    while (choice == 'y' || choice == 'Y')  // Loop until user decides to exit
    {
        printf("\n\n" COLOR_CYAN COLOR_BOLD "======================================\n");
        printf("        INVERTED SEARCH ENGINE        \n");
        printf("======================================\n" COLOR_RESET);
        printf(COLOR_YELLOW "1." COLOR_RESET " Create Database\n");
        printf(COLOR_YELLOW "2." COLOR_RESET " Display Database\n");
        printf(COLOR_YELLOW "3." COLOR_RESET " Search Database\n");
        printf(COLOR_YELLOW "4." COLOR_RESET " Update Database\n");
        printf(COLOR_YELLOW "5." COLOR_RESET " Save Database\n");
        printf(COLOR_YELLOW "6." COLOR_RESET " Exit\n");
        printf(COLOR_CYAN "======================================\n" COLOR_RESET);

        printf(COLOR_BOLD "Enter your choice (1-6): " COLOR_RESET);
        if (scanf("%d", &option) != 1)
        {
            printf(COLOR_RED "\n[-] Invalid input! Exiting program.\n" COLOR_RESET);
            break;
        }

        switch (option)
        {
            case 1:
                printf(COLOR_BLUE "\n\n[*] Creating Database...\n" COLOR_RESET);
                create_database(f_head, head);
                printf(COLOR_GREEN "[+] Database creation completed.\n" COLOR_RESET);
                break;

            case 2:
                printf(COLOR_BLUE "\n\n[*] Displaying Database:\n" COLOR_RESET);
                display_database(head);
                break;

            case 3: {
                char word[WORD_SIZE];
                printf(COLOR_CYAN "\nEnter the word to search: " COLOR_RESET);
                scanf("%14s", word);

                int index;
                if (isalpha((unsigned char)word[0]))
                {
                    index = tolower((unsigned char)word[0]) - 'a'; // Bucket 0 to 25
                }
                else
                {
                    index = 26; // Non-alphabetic bucket
                }

                if (search(head[index], word) == FAILURE)
                {
                    printf(COLOR_RED "\n[-] Word \"%s\" not found in database.\n" COLOR_RESET, word);
                }
                break;
            }

            case 4:
                printf(COLOR_BLUE "\n[*] Updating Database...\n" COLOR_RESET);
                update_database(head, &f_head);
                break;

            case 5:
                printf(COLOR_BLUE "\n[*] Saving Database...\n" COLOR_RESET);
                save_database(head);
                break;

            case 6:
                printf(COLOR_MAGENTA "\n[*] Exiting program. Goodbye!\n" COLOR_RESET);
                return SUCCESS;

            default:
                printf(COLOR_RED "\n[-] Invalid choice! Please select a valid number between 1 and 6.\n" COLOR_RESET);
                break;
        }

        printf(COLOR_CYAN "\nDo you want to continue? (y/n): " COLOR_RESET);
        scanf(" %c", &choice);

        if(choice != 'y' && choice != 'Y')  // If the user chooses not to continue, exit the loop
        {
            printf(COLOR_MAGENTA "\n[*] Exiting program. Goodbye!\n" COLOR_RESET); 
        }

        if(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') // If the user enters an invalid choice, exit the program
        {
            printf(COLOR_RED "\n[-] Invalid input! Exiting program.\n" COLOR_RESET);
            break;
        }

    }

    return SUCCESS;
}
