#include <iostream>
#include <string>
#include <vector>
#include "BinarySearchTree.h"
#include "BSTPrint.h"
using namespace std;

int main() {
   // The following values are inserted in order to build the tree
   vector<int> valuesToInsert = { 3, 10, 7, 2, 8, 4, 9, 5, 1, 6 };
   
   // Then the following values are removed from the tree
   vector<int> valuesToRemove = { 5, 3 };
   
   BinarySearchTree tree;
   
   // Insert values
   for (int value : valuesToInsert) {
      tree.InsertKey(value);
   }
      
   // Show the tree
   cout << "Initial tree:" << endl;
   cout << BSTPrint::TreeToString(tree.GetRoot()) << endl;
      
   // Remove values
   for (int valueToRemove : valuesToRemove) {
      cout << endl;
      if (tree.Remove(valueToRemove)) {
         cout << "Tree after removing " << valueToRemove << ":" << endl;
         cout << BSTPrint::TreeToString(tree.GetRoot()) << endl;
      }
      else {
         cout << "Key " << valueToRemove << " not found" << endl;
      }
   }
   
   return 0;
}