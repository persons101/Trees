#include <iostream>
#include <vector>
#include "AVLTree.h"
using namespace std;

int main() {
   // Declare keys to insert and keys to subsequently remove
   vector<int> keysToInsert = { 10, 20, 5, 22, 15, 47, 19, 3, 12, 18 };
   vector<int> keysToRemove = {
      12, // Removing 12 causes a right rotation at node 10
      20,
      30  // 30 is not in the tree, so RemoveKey() will return false
   };
   
   bool showTreeAfterEachInsertion = false;
   
   // Create an empty AVLTree object
   AVLTree tree;

   // Insert keys
   for (int key : keysToInsert) {
      tree.InsertKey(key);
      
      if (showTreeAfterEachInsertion) {
         cout << "Tree after inserting " << key << ":" << endl;
         tree.PrintTree(cout);
         cout << endl << endl;
      }
   }
      
   // Print the tree after all inserts are complete.
   cout << "Tree after initial insertions:" << endl;
   tree.PrintTree(cout);
   cout << endl << endl;
   
   // Remove keys
   for (int key : keysToRemove) {
      if (tree.RemoveKey(key)) {
         cout << "Removed key " << key << ":" << endl;
         tree.PrintTree(cout);
         cout << endl << endl;
      }
      else {
         cout << "Failed to remove key " << key << " (not found)" << endl;
      }
   }
   
   return 0;
}