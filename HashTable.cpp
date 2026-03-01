//============================================================================
// Name        : HashTable.cpp
// Author      : Withney Villarreal
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Lab 4-2 Hash Table
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
    // Define structures to hold bids
    struct Node {
        Bid bid;
        unsigned int key;
        Node *next;

        // default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }

        // initialize with a bid
        Node(Bid aBid) : Node() {
            bid = aBid;
        }

        // initialize with a bid and a key
        Node(Bid aBid, unsigned int aKey) : Node(aBid) {
            key = aKey;
        }
    };

    vector<Node> nodes;

    unsigned int tableSize = DEFAULT_SIZE;

    unsigned int hash(int key);

public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
    size_t Size();
};

/**
 * Default constructor
 */
HashTable::HashTable() {
    // FIXME (1): Initialize the structures used to hold bids
    this->tableSize = DEFAULT_SIZE;
    // Initalize node structure by resizing tableSize
    // Initialize table with empty nodes
    nodes.resize(tableSize);
}

/**
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size) {
    // invoke local tableSize to size with this->
    // resize nodes size
    this->tableSize = size;
    nodes.resize(tableSize);
}


/**
 * Destructor
 */
HashTable::~HashTable() {
    // FIXME (2): Implement logic to free storage when class is destroyed
    for (unsigned int i = 0; i < tableSize; ++i) {
        Node* current = nodes[i].next;

        while (current != nullptr) {
            Node* temp = current->next;
            delete current;
            current = temp;
        }
    }
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
    // FIXME (3): Implement logic to calculate a hash value
    //return key tableSize
    return key % tableSize;
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
    // FIXME (4): Implement logic to insert a bid
    // create the key for the given bid
    // retrieve node using key
    // if no entry found for the key
        // assign this node to the key position
    // else if node is not used
         // assing old node key to UNIT_MAX, set to key, set old node to bid and old node next to null pointer
    // else find the next open node
            // add new newNode to end
    unsigned int key = hash(stoi(bid.bidId));

    // If bucket is empty (unused)
    if (nodes[key].key == UINT_MAX) {
        nodes[key] = Node(bid, key);
        return;
    }

    // Otherwise, append to the chain
    Node* current = &nodes[key];

    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = new Node(bid, key);
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    // FIXME (5): Implement logic to print all bids
    // for node begin to end iterate
    //   if key not equal to UINT_MAx
            // output key, bidID, title, amount and fund
            // node is equal to next iter
            // while node not equal to nullptr
               // output key, bidID, title, amount and fund
               // node is equal to next node
    for (unsigned int i = 0; i < tableSize; ++i) {

        if (nodes[i].key != UINT_MAX) {
            Node* current = &nodes[i];

            while (current != nullptr) {
                std:: cout << "Key " << i << ": "
                    << current->bid.bidId << " | "
                    << current->bid.title << " | "
                    << current->bid.amount << " | "
                    << current->bid.fund << endl;

                current = current->next;
            }
        }
    }
}

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {
    // FIXME (6): Implement logic to remove a bid
    // set key equal to hash atoi bidID cstring
    // erase node begin and key
    unsigned int key = hash(stoi(bidId));

    Node* current = &nodes[key];
    Node* previous = nullptr;

    // If bucket is empty
    if (current->key == UINT_MAX) {
        return;
    }

    // If the head node matches
    if (current->bid.bidId == bidId) {

        // Case 1: head has a chain
        if (current->next != nullptr) {
            Node* nextNode = current->next;
            nodes[key] = *nextNode;   // copy next node into head
            delete nextNode;
        }
        else {
            // Case 2: head is the only node
            nodes[key] = Node(); // reset to empty
        }
        return;
    }

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */

 // Otherwise search the chain
    previous = current;
    current = current->next;

    while (current != nullptr) {
        if (current->bid.bidId == bidId) {
            previous->next = current->next;
            delete current;
            return;
        }
        previous = current;
        current = current->next;
    }
}


    Bid HashTable::Search(string bidId) {
        Bid bid;

        // FIXME (7): Implement logic to search for and return a bid
        unsigned int key = hash(stoi(bidId));

        Node* current = &nodes[key];
        // create the key for the given bid
        // if entry found for the key
             //return node bid
        if (current->key == UINT_MAX) {
            return Bid(); // empty
        }
        // if no entry found for the key
          // return bid
        // while node not equal to nullptr
            // if the current node matches, return it
            //node is equal to next node
        while (current != nullptr) {
            if (current->bid.bidId == bidId) {
                return current->bid;
            }
            current = current->next;
        }
        return bid;
    }
    size_t HashTable::Size() {
    return 0;
}




//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    std::cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, HashTable* hashTable) {
    std::cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        std::cout << c << " | ";
    }
    std::cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            hashTable->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98223";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
        bidKey = "98223";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable;

    Bid bid;
    bidTable = new HashTable();
    
    int choice = 0;
    while (choice != 9) {
        std::cout << "Menu:" << endl;
        std::cout << "  1. Load Bids" << endl;
        std::cout << "  2. Display All Bids" << endl;
        std::cout << "  3. Find Bid" << endl;
        std::cout << "  4. Remove Bid" << endl;
        std::cout << "  9. Exit" << endl;
        std::cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bidTable);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            std::cout << "time: " << ticks << " clock ticks" << endl;
            std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bidTable->PrintAll();
            break;

        case 3:
            ticks = clock();

            bid = bidTable->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
                std::cout << "Bid Id " << bidKey << " not found." << endl;
            }

            std::cout << "time: " << ticks << " clock ticks" << endl;
            std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 4:
            bidTable->Remove(bidKey);
            break;
        }
    }

    std::cout << "Good bye." << endl;

    return 0;
}
