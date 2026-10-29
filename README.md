# Inverted Search Engine

A high-performance C-based implementation of an **Inverted Index Search Engine** developed as an advanced Data Structures project. This engine indexes words across multiple text files using a hash table combined with doubly/singly linked lists to deliver rapid multi-file lookups, frequency tracking, database serialization to CSV, and persistence restoration.

---

## 📌 Features

- **Document Validation & Filtering**: Automatically filters out duplicate filenames, empty files, and non-existent paths before building the database.
- **Inverted Index Data Structure**: Maps indexed words directly to the files where they appear along with occurrence frequencies.
- **CSV Database Export & Import**:
  - **Save Database**: Serializes the in-memory inverted index directly into structured CSV files (`db_backup.csv`, `file.csv`).
  - **Update Database**: Restores a previously saved database backup without having to re-parse original input text files.
- **Word Search**: Fast lookup retrieving the exact list of files and word frequency per document.
- **Interactive Console Menu**: Complete interface to validate, build, display, search, save, and update the index.

---

## 🏗️ Architecture & Core Data Structures

The system architecture utilizes a Hash Table array indexed alphabetically where each bucket heads a linked list of unique words, linked to a sub-table tracking file occurrences:

```text
[Hash Table Index] (e.g. 0 to 26 based on first letter)
        │
        ▼
   [Word Node] ───> [File Count] ───> [Sub Node: File Record] ───> [Next File...]
        │                                     │
        │                                 [File Name]
        │                                 [Word Count]
        ▼
   [Next Word Node]
```

📂 Project Structure

InvertedSearch/
├── main.c                  # Application entry point & interactive menu loop
├── InvertedSearch.h        # Struct definitions, macros, and function prototypes
├── file_validation.c       # Validates CLI arguments (checks empty, duplicate, existence)
├── create_database.c       # Word tokenization, hashing, and inverted index generation
├── display_database.c      # Outputs indexed records in a structured tabular format
├── search.c                # Search engine query processor for specific words
├── save_db.c               # Serializes in-memory database to CSV format (e.g., db_backup.csv)
├── update_db.c             # Parses saved CSV files to reconstruct the database in memory
├── insert_last.c           # Linked list manipulation helper routines
├── Makefile                # Automated compilation rules (generates invert.exe / a.out)
│
├── file1.txt               # Sample input document
├── file2.txt               # Sample input document
├── file3.txt               # Sample input document
├── file4.txt               # Sample input document
├── file_update.txt         # Input file for update routines
├── db_backup.csv           # Backup database storage file
└── file.csv                # Primary CSV database export


🚀 Getting Started

## Prerequisites

Compiler: GCC / Clang
Build Tool: GNU Make

Compilation : Compile the project using the provided Makefile: make  
This compiles all modules (main.c, create_database.c, display_database.c, search.c, save_db.c, update_db.c, file_validation.c, insert_last.c) and generates the executable target (invert.exe)

To clean build artifacts: make clean 

💻 Usage

Run the program by supplying one or more text files as command-line arguments: ./invert.exe file1.txt file2.txt file3.txt

🛡️ Validation & Error Handling

Duplicate CLI Arguments: Discards identical file arguments passed in argv to avoid duplicate indexing.

Missing or Empty Files: Validates file existence and tests whether file size is greater than zero before parsing.

Duplicate Database Creation: Restricts re-running database creation over an active index to protect data integrity.

Zero Result Search: Informs the user when a search query is not present across any indexed document.
