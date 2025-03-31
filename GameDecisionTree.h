#ifndef GAMEDECISIONTREE_H
#define GAMEDECISIONTREE_H

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Node.h"
#include "Story.h"

template <typename T>
class GameDecisionTree {
private:
    Node<T>* root;
    // Map to keep track of nodes by event number (to support shared nodes)
    std::unordered_map<int, Node<T>*> nodeMap;

public:
    // Constructor: initialize root to nullptr
    GameDecisionTree() : root(nullptr){}

    // Function to load story data from a text file and build the binary tree.
    // Each line of the file should have the format:
    // eventNumber | description | leftChildEventNumber | rightChildEventNumber
    // A value of -1 indicates no child.
    void loadStoryFromFile(const std::string& filename, char delimiter) {
        std::ifstream inFile(filename);
        if(!inFile.is_open())
            {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return;
        }

        std::string line;
        // Read each line from the file
        while(std::getline(inFile, line)){
            if(line.empty())
                continue;
            std::istringstream ss(line);
            std::string token;

            // Parse event number
            std::getline(ss, token, delimiter);
            int eventNum = std::stoi(token);

            // Parse description
            std::getline(ss, token, delimiter);
            std::string desc = token;

            // Parse left child event number
            std::getline(ss, token, delimiter);
            int leftNum = std::stoi(token);

            // Parse right child event number
            std::getline(ss, token, delimiter);
            int rightNum = std::stoi(token);

            // Create or get the current node for eventNum
            Node<T>* currentNode;
            if(nodeMap.find(eventNum) == nodeMap.end()) {
                currentNode = new Node<T>(T());  // Create a new node with default T
                nodeMap[eventNum] = currentNode;
            }
            else{
                currentNode = nodeMap[eventNum];
            }
            // Set the Story data into the node (using the parameterized constructor)
            currentNode->data = T(eventNum, desc, leftNum, rightNum);

            // Set root pointer if not yet set
            if(root == nullptr) {
                root = currentNode;
            }

            // Process left child (if exists)
            if(leftNum != -1){
                Node<T>* leftChild;
                if (nodeMap.find(leftNum) == nodeMap.end()) {
                    leftChild = new Node<T>(T());
                    nodeMap[leftNum] = leftChild;
                } else{
                    leftChild = nodeMap[leftNum];
                }
                currentNode->left = leftChild;
            }

            // Process right child (if exists)
            if(rightNum != -1){
                Node<T>* rightChild;
                if (nodeMap.find(rightNum) == nodeMap.end()){
                    rightChild = new Node<T>(T());
                    nodeMap[rightNum] = rightChild;
                }
                else{
                    rightChild = nodeMap[rightNum];
                }
                currentNode->right = rightChild;
            }
        }

        inFile.close();
    }

    // Function to start the game and traverse the tree based on user input.
    // The game prints the current event description and prompts the user to choose a direction.
    // The game ends when a leaf node (no children) is reached.
    void playGame() {
        if(root == nullptr){
            std::cout << "No story loaded." << std::endl;
            return;
        }

        Node<T>* current = root;
        while(current != nullptr){
            // Display the current event description
            std::cout << current->data.description << std::endl;

            // Check if it is a leaf node (end of the game)
            if(current->left == nullptr && current->right == nullptr){
                std::cout << "End of game. Thank you for playing!" << std::endl;
                break;
            }

            int choice;
            bool valid = false;
            // Loop until a valid choice (1 or 2) is made
            while (!valid) {
                std::cout << "Enter your choice (1 for left, 2 for right): ";
                std::cin >> choice;
                if(std::cin.fail() || (choice != 1 && choice != 2)) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "Invalid choice. Please enter 1 or 2." << std::endl;
                }
                else{
                    valid = true;
                }
            }

            // Traverse to the chosen child node
            if(choice == 1){
                current = current->left;
            }
            else{
                current = current->right;
            }
        }
    }

    // Destructor: free dynamically allocated nodes.
    ~GameDecisionTree(){
        for (auto& pair : nodeMap) {
            delete pair.second;
        }
        nodeMap.clear();
    }
};

#endif // GAMEDECISIONTREE_H
