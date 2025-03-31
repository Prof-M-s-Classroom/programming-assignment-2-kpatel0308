CS210 Data Structures SP25

Programming Assignment 2: Text-Based RPG Using Decision Trees

Student Name: Khush Patel  
Student ID: 130086980



## 1. Project Overview

This project implements a text-based RPG using a binary decision tree. Each game event is represented as a node, and the player progresses by choosing between two paths at each stage. The storyline is loaded from an external text file (`story.txt`), which is parsed to construct the decision tree. The game ends when a leaf node (with -1 as left and right children) is reached.


## 2. Folder & File Structure

- `main.cpp` → Contains the main game loop. It loads the decision tree and starts the player interaction process.
- `GameDecisionTree.h` → Implements the `GameDecisionTree<T>` class, which handles file parsing, tree construction, and game traversal.
- `Node.h` → Defines a templated `Node<T>` class with left and right child pointers to build the binary tree structure.
- `Story.h` → Contains the `Story` class definition with event number, description, and pointers to left and right child events.
- `Story.cpp` → Implements the constructors and functions for the `Story` class.
- `story.txt` → Contains the RPG storyline in the format: `eventNumber|description|leftChildEventNumber|rightChildEventNumber`.

---

## 3. Decision Tree Construction

Each line in the `story.txt` file is parsed into a `Story` object. These objects are then stored in a map by `eventNumber` for quick access. The tree is built by connecting nodes based on their `leftEventNumber` and `rightEventNumber`.

If a left or right event number is `-1`, it means there is no further path in that direction, and the node becomes a leaf node.

---

## 4. Game Traversal

The game begins at the root node. At each node, the player is prompted to make a decision:
- 1 → Go left
- 2 → Go right

Based on the choice, the game moves to the left or right child. This continues until a leaf node is reached. If both left and right children are `-1`, the game ends.

There is a special case where two or more parent nodes point to the same child node. This is handled by storing a single node in memory and pointing multiple parents to it (shared outcome).

---

## 5. File Parsing & Data Loading

The file is read line by line and parsed using the `|` delimiter. Each part is converted into its respective `Story` object values.

All story events are loaded first, and then their left and right pointers are connected using the map of `eventNumber` to node references.

Challenge: Ensuring all nodes were created before linking. This was solved by using a two-pass approach:
1. Parse and store all nodes in a map.
2. Link children based on their event numbers.

---

## 6. Debugging Process (Errors & Fixes)

At one point, my game would crash whenever I typed a letter instead of a number. I realized I wasn’t handling bad input properly, so I added input validation with cin.fail() and cin.clear(). After fixing that, it worked smoothly.
Another issue was invalid user input (e.g., non-numeric characters). To fix this, the program now checks input validity before proceeding.

---

## 7. Sample Output & Walkthrough
You wake up in a forest clearing. There are two paths.
Enter your choice (1 for left, 2 for right): 1
You follow the path to the left and encounter a river.
Enter your choice (1 for left, 2 for right): 2
You find a hidden passageway that leads to a secret room.
Enter your choice (1 for left, 2 for right): 1
You discover an underground library filled with magical books.
End of game. Thank you for playing!
## 8. Big-O Analysis of Core Methods

- Loading the tree from the file → O(n), where n is the number of events
- Searching for an event in the tree (via map) → O(1)
- Game traversal efficiency → O(h), where h is the height of the decision tree

---

## 9. Edge Cases & Testing

Tested the following edge case:
- Player reaches a dead-end (leaf node with both children as -1). The game correctly ends and displays an appropriate message.

Also tested:
- Invalid input (e.g., characters or numbers other than 1 or 2). The program prompts the player again without crashing.




 