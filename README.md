# Library Management Software

A console-based library management system built in C++ that allows users to manage books, patrons, and library operations efficiently.

## Overview

This software provides a complete solution for managing a library's inventory and patron records. It features a simple text-based menu interface with robust data persistence using JSON file storage.

## Features

### Book Management
- **Add Books**: Register new books with title, author, and publication year
- **Update Books**: Modify book details including title, author, year, and availability status
- **Remove Books**: Delete books from inventory (with validation for checked-out books)
- **List Books**: View all books or filter by:
  - Name/Title
  - Author
  - Status (Available/Borrowed)

### Patron Management
- **Add Patrons**: Register new library members
- **Update Patrons**: Modify patron information
- **Remove Patrons**: Delete patron records (prevents deletion if books are checked out)
- **List Patrons**: View all patrons or search by name
- **View Patron History**: See books currently checked out by each patron

### Library Operations
- **Checkout Books**: Patrons can borrow available books
- **Return Books**: Process book returns and update availability
- **Real-time Status Updates**: Automatic synchronization between book status and patron records
- **Data Validation**: Prevents invalid operations (e.g., deleting borrowed books)

## Data Models

### Book
- **Book ID**: Unique auto-generated identifier
- **Title**: Book name
- **Author**: Book author
- **Year of Publication**: Publishing year
- **Status**: Available or Borrowed

### Patron
- **Patron ID**: Unique auto-generated identifier
- **Name**: Patron's full name
- **Books Checked Out**: List of currently borrowed book IDs

## Prerequisites

- C++ compiler with C++17 support (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.8 or higher
- nlohmann/json library (included in `externals/`)

## Compilation

### Using CMake (Recommended)

1. Navigate to the project directory:
```bash
cd LibraryManager
```

2. Create and navigate to build directory:
```bash
mkdir -p build
cd build
```

3. Configure and build:
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

### Alternative: Ninja Build System
```bash
cmake -DCMAKE_BUILD_TYPE=Release -G Ninja ..
ninja
```

## Running the Software

After compilation, run the executable from the build directory:

```bash
./LibraryManager
```

## Usage Guide

### Navigation
- Use numeric keys (1, 2, 3, etc.) to select menu options
- Press **B** and Enter anytime to go back to the previous menu
- Follow on-screen prompts for all operations

### First Time Setup
The software automatically creates necessary files and directories:
- `res/library.json` - Book database
- `res/patrons.json` - Patron database

If these files don't exist, they will be created with the default structure on first run.

### Example Workflow

1. **Add Books to Library**
   - Main Menu → Library → Add book
   - Enter book details when prompted
   
2. **Register a Patron**
   - Main Menu → Patrons → Add patron
   - Enter patron name
   
3. **Checkout a Book**
   - Main Menu → Operations → Checkout book
   - Select patron ID
   - Select book ID from available books
   
4. **Return a Book**
   - Main Menu → Operations → Return book
   - Select patron ID
   - Select book ID from patron's checked-out books

## Project Structure

```
LibraryManager/
├── CMakeLists.txt           # Build configuration
├── README.md                # This file
├── includes/                # Header files
│   ├── library.h           # Book management
│   ├── patron.h            # Patron management
│   ├── terminal.hpp        # Terminal utilities
│   └── Pages/              # Page system headers
├── src/                    # Source files
│   ├── main.cpp           # Entry point
│   └── Pages/             # Page implementations
├── externals/              # External libraries
│   └── nlohmann/          # JSON library
├── res/                    # Data storage (auto-created)
│   ├── library.json       # Book database
│   └── patrons.json       # Patron database
└── build/                  # Build output (created by CMake)
```

## Technical Details

### Data Storage
- **Format**: JSON
- **Location**: `res/` directory
- **Auto-save**: Changes are immediately persisted to disk
- **Schema**:
  - Each book/patron has a unique numeric ID
  - IDs are auto-incremented from `maxID` counter
  - Referential integrity maintained between books and patrons

#### JSON Schema Examples

**library.json**:
```json
{
  "maxID": 2,
  "books": {
    "1": {
      "title": "1984",
      "author": "George Orwell",
      "year": 1949,
      "status": "Available"
    },
    "2": {
      "title": "To Kill a Mockingbird",
      "author": "Harper Lee",
      "year": 1960,
      "status": "Borrowed"
    }
  }
}
```

**patrons.json**:
```json
{
  "maxID": 1,
  "patrons": {
    "1": {
      "name": "John Doe",
      "booksCheckedOut": ["2"]
    }
  }
}
```

### Key Features Implementation

**Error Handling**:
- Input validation for all user entries
- Prevents deletion of borrowed books
- Prevents deletion of patrons with checked-out books
- Book ID existence validation before updates
- Graceful handling of missing or corrupted data files

**Data Integrity**:
- Automatic status synchronization (Book ↔ Patron)
- Silent updates for system-initiated changes
- Transaction-like operations for checkout/return

**User Experience**:
- Clear terminal between page transitions
- Alphabetically sorted listings
- Case-insensitive search functionality
- Filtered views (e.g., only available books for removal)

## Code Quality

- **Standards**: C++17 with modern features (structured bindings, filesystem)
- **Architecture**: Page-based navigation system with centralized page management
- **Memory Management**: Smart pointers (unique_ptr) for automatic cleanup
- **Data Flow**: Separation of concerns (UI ↔ Business Logic ↔ Data Storage)

## Error Handling

The software handles various error scenarios:
- Invalid user input (non-numeric, out of range)
- Missing or corrupted data files
- Attempting to remove borrowed books
- Attempting to remove patrons with outstanding books
- Non-existent IDs during update/delete operations
- Duplicate book/patron entries

## Author

Chitic David - C++ Library Management System
