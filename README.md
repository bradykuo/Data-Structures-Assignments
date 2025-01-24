# Data Structures Assignments Collection

A comprehensive implementation of fundamental data structure algorithms in C++.<br>
<br>
（成大工資系｜資料結構｜作業）

## Assignment Details

### HW1: Insertion Sort 
- Implementation of insertion sort with three measurement approaches:
  - Single run timing with before/after results 
  - Average time over 10,000 runs
  - Running until 1-minute threshold
- Template implementation for handling different data types 
- File structure:
  ```
  hw1/
  ├── insertion sort.cpp     # Basic implementation 
  ├── template.cpp          # Template version
  ```

### HW2: Train Bento Game
- Circular linked list implementation
- Game mechanics:
  - N players (2-10) arranged in circle
  - 10 topics with word lists
  - Random word selection each round
  - Player elimination on repeated words
- Files:
  ```
  hw2/
  ├── link list.cpp
  ├── data.txt         # Topic and word data
  ```

### HW3: Binary Search Tree
- Complete BST implementation with:
  - Insert/Delete operations
  - Search with path tracking
  - Tree visualization
  - Bonus: Complete BST conversion
- Files:
  ```
  hw3/
  ├── BST.cpp                 # Basic implementation
  ├── Complete BST.cpp        # With bonus features
  ```

### HW4: Floyd's Shortest Path
- Graph algorithm implementation for store routing
- Features:
  - Adjacency matrix/list conversion
  - Distance calculation
  - Path visualization
  - Interactive path finding
- Files:
  ```
  hw4/
  ├── Floyd's Shortest Paths.cpp
  ├── adjacency_matrix.txt
  ├── distance_matrix.txt
  ```

## Technical Requirements

### Development Environment
- C++ 11 or later
- Code::Blocks IDE (recommended)
- Text editor for viewing input files

### Build Instructions
```bash
# Compile with g++
g++ -std=c++11 filename.cpp -o output

# Run the program
./output
```

## Implementation Notes

### HW1: Insertion Sort
- Time complexity: O(n²)
- Space complexity: O(1)
- Template implementation supports multiple data types
- Timing measurements use chrono library

### HW2: Linked List Game
- Circular structure for player rotation
- Dynamic memory management
- UTF-8 support for Chinese characters
- Random word selection using mt19937

### HW3: Binary Search Tree
- Node structure with parent pointers
- Memory leak prevention
- Tree balancing algorithms
- Visualization using hierarchical printing

### HW4: Floyd-Warshall Algorithm
- Matrix operations for path finding
- Path reconstruction
- Interactive user interface
- File I/O for matrix data

## Testing

Each assignment includes test cases and sample data:
- Input validation
- Edge cases handling
- Performance metrics
- Memory leak checking

## Directory Structure
```
data-structures/
├── hw1/
│   ├── insertion sort.cpp
│   └── template.cpp
├── hw2/
│   ├── link list.cpp
│   └── data.txt
├── hw3/
│   ├── BST.cpp
│   └── Complete BST.cpp
├── hw4/
│   ├── Floyd's Shortest Paths.cpp
│   ├── adjacency_matrix.txt
│   └── distance_matrix.txt
└── README.md
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is available for academic and educational purposes.

