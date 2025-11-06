#include <iostream>
#include <string>
#include <vector>
#include "BinarySearchTree.h"
#include "BSTNodePrintVisitor.h"
#include "BSTNodeCountVisitor.h"
#include "BSTNodeVectorVisitor.h"
using namespace std;


int main() {
   vector<int> valuesToInsert = {
      83, 25, 76, 67, 88, 12, 19, 54, 26, 73, 23, 44, 81
   };
   
   // Create a tree and add values
   BinarySearchTree tree;
   for (int value : valuesToInsert) {
      tree.InsertKey(value);
   }
   
   // Create one of each visitor
   vector<BSTNodeVisitor*> visitors = {
      new BSTNodePrintVisitor(),
      new BSTNodeCountVisitor(),
      new BSTNodeVectorVisitor()
   };
   
   // Perform an inorder traversal with each visitor and print a summary
   for (BSTNodeVisitor* visitor : visitors) {
      tree.InOrder(*visitor);
      visitor->PrintSummary(cout);
      cout << endl;
      
      // The visitor will not be used again, so delete
      delete visitor;
   }
   
   return 0;
}