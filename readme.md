Jake O'Reilly D00256438

---

# Implementing and using a TreeMap in C++

### Worth 20%

### Due: 28th November 2024

---

### Notes

I am using [Catch2 v2](https://github.com/catchorg/Catch2/blob/v2.x/single_include/catch2/catch.hpp) for Unit Testing instead of the Microsoft Testing Framework, this is because I am not using Visual Studio 2022.

The [Catch2](https://github.com/catchorg/Catch2/blob/v2.x/single_include/catch2/catch.hpp) header file (catch.hpp) is already in the repo, so you shouldn't need to do anything extra for the testing to work.

I am using [Visual Studio Code](https://code.visualstudio.com/) and [Notepad++](https://notepad-plus-plus.org/) for coding, [g++](https://gcc.gnu.org/) (from GCC) for compiling, and [Catch2](https://github.com/catchorg/Catch2/blob/v2.x/single_include/catch2/catch.hpp) for Unit Testing.

---

### Building / Compiling / Project Structure

I build with g++ with these commands from the ```Proyecto/``` directory:

App Compiling
```
g++ src/app_name.cpp -o ./build/bin/app_name.exe
```

Tests Compiling
```
g++ testing/test_file_name.cpp -o ./build/bin/test_file_name.exe
```

---

# Stage 1

Turn the provided Binary Search Tree code into TreeMap code, and implement these functions:

| Signature | Function |
| --- | --- |
| void clear() | Removes all entries from the Map. |
| bool containsKey(K key) | Returns true if this map contains a mapping for the specified key. |
| V& get(K key) | Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key. |
| BinaryTree<K> keySet() | Returns a Set view of the keys contained in this map. |
| void put(K key, V value) | Associates the specified value with the specified key in this map. |
| int size() | Returns the number of key-value mappings in this map. |
| bool removeKey(K key) | Removes the item denoted by the given key. |
| V& operator\[K key\] | Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key. |

---

# Stage 2

Using your TreeMap and Binary Search Tree, make a CLI App that reads a .txt file and sorts and stores all unique words by their first letter.

In the App, the user can view:
- List of letters that have 1+ words stored.
- All of the words for a given letter.

Modify the print() method of the Binary Search Tree code for display.

---

# Stage 3

Make a .csv file with at least 100 rows of data. 
There should be at least 5 fields of at least 2 different data types. 
You may use online data generation tools to generate your data.

---

# Stage 4

Make a CLI App that lets the user view and search Stage 3's data.

In the App, the user can:
- Create an index on one of the data fields and display the: 
- - Unique entries for that field.
- - Number of rows that contain that value.
- View a subset of the data, based on a user-given value for any ONE field.

All data should be clearly and neatly presented.
Efficient Memory Management must be applied.