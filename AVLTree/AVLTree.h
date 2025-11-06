#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
#include "AVLNode.h"
#include "AVLPrint.h"

class AVLTree {
private:
   AVLNode* root;
   
   void DeleteTree(AVLNode* subtreeRoot) {
      if (subtreeRoot) {
         DeleteTree(subtreeRoot->GetLeft());
         DeleteTree(subtreeRoot->GetRight());
         delete subtreeRoot;
      }
   }
   
   void InsertNode(AVLNode* node) {
      // Check if tree is empty
      if (!root) {
         root = node;
      }
      else {
         // Step 1 - do a regular binary search tree insert.
         AVLNode* currentNode = root;
         while (currentNode) {
            // Choose to go left or right
            if (node->GetKey() < currentNode->GetKey()) {
               // Go left. If left child is null, insert the new
               // node here.
               if (currentNode->GetLeft() == nullptr) {
                  currentNode->SetLeft(node);
                  currentNode = nullptr;
               }
               else {
                  // Go left and do the loop again.
                  currentNode = currentNode->GetLeft();
               }
            }
            else {
               // Go right. If the right child is null, insert the
               // new node here.
               if (currentNode->GetRight() == nullptr) {
                  currentNode->SetRight(node);
                  currentNode = nullptr;
               }
               else {
                  // Go right and do the loop again.
                  currentNode = currentNode->GetRight();
               }
            }
         }

         // Step 2 - Rebalance along a path from the new node's parent up
         // to the root.
         node = node->GetParent();
         while (node) {
            Rebalance(node);
            node = node->GetParent();
         }
      }
   }
   
   // Updates the given node's height and rebalances the subtree if
   // the balancing factor is now -2 or +2. Rebalancing is done by
   // performing a rotation.
   void Rebalance(AVLNode* node) {
      // First update the height of this node.
      node->UpdateHeight();

      // Check for an imbalance.
      if (node->GetBalance() == -2) {
         // The subtree is too big to the right.
         if (node->GetRight()->GetBalance() == 1) {
            // Double rotation case. First do a right rotation
            // on the right child.
            RotateRight(node->GetRight());
         }

         // A left rotation will now make the subtree balanced.
         RotateLeft(node);
      }
      else if (node->GetBalance() == 2) {
         // The subtree is too big to the left
         if (node->GetLeft()->GetBalance() == -1) {
            // Double rotation case. First do a left rotation
            // on the left child.
            RotateLeft(node->GetLeft());
         }

         // A right rotation will now make the subtree balanced.
         RotateRight(node);
      }
   }
   
   bool RemoveNode(AVLNode* nodeToRemove) {
      // Base case: 
      if (!nodeToRemove) {
         return false;
      }
        
      // nodeToRemove's parent is needed for rebalancing
      AVLNode* parent = nodeToRemove->GetParent();
        
      // Case 1: Internal node with 2 children
      if (nodeToRemove->GetLeft() && nodeToRemove->GetRight()) {
         // Find successor
         AVLNode* successorNode = nodeToRemove->GetRight();
         while (successorNode->GetLeft()) {
            successorNode = successorNode->GetLeft();
         }
            
         // Copy the value from the node
         nodeToRemove->SetKey(successorNode->GetKey());
            
         // Recursively remove successor
         RemoveNode(successorNode);
            
         // Nothing left to do since the recursive call will have rebalanced
         return true;
      }
    
      // Case 2: Root node (with 1 or 0 children)
      else if (nodeToRemove == root) {
         if (nodeToRemove->GetLeft()) {
            root = nodeToRemove->GetLeft();
         }
         else {
            root = nodeToRemove->GetRight();
         }

         if (root) {
            root->SetParent(nullptr);
         }

         delete nodeToRemove;
         return true;
      }
      
      // Case 3: Internal with left child only
      else if (nodeToRemove->GetLeft()) {
         parent->ReplaceChild(nodeToRemove, nodeToRemove->GetLeft());
      }
        
      // Case 4: Internal with right child only OR leaf
      else {
         parent->ReplaceChild(nodeToRemove, nodeToRemove->GetRight());
      }
      
      // nodeToRemove is removed from the tree and can be deleted
      delete nodeToRemove;
        
      // Anything that was below nodeToRemove that has persisted is already 
      // correctly balanced, but ancestors of nodeToRemove may need rebalancing.
      AVLNode* nodeToRebalance = parent;
      while (nodeToRebalance) {
         Rebalance(nodeToRebalance);         
         nodeToRebalance = nodeToRebalance->GetParent();
      }
    
      return true;
   }
   
   // Performs a left rotation at the given node.
   void RotateLeft(AVLNode* node) {
      // Get pointers to the node's parent, right child, and right child's left
      // child
      AVLNode* parent = node->GetParent();
      AVLNode* rightChild = node->GetRight();
      AVLNode* rightLeftChild = rightChild->GetLeft();
      
      // First reassign node's right child
      node->SetRight(rightLeftChild);
      
      // Next, reassign former right child's left child
      rightChild->SetLeft(node);
      
      // Lastly, replace parent's child or reassign root if parent is null
      if (parent) {
         parent->ReplaceChild(node, rightChild);
      }
      else { // node is root
         root = rightChild;
         root->SetParent(nullptr);
      }
   }
   
   // Performs a right rotation at the given node.
   void RotateRight(AVLNode* node) {
      // Get pointers to the node's parent, left child, and left child's right
      // child
      AVLNode* parent = node->GetParent();
      AVLNode* leftChild = node->GetLeft();
      AVLNode* leftRightChild = leftChild->GetRight();
      
      // First reassign node's left child
      node->SetLeft(leftRightChild);
      
      // Next, reassign former left child's right child
      leftChild->SetRight(node);
      
      // Lastly, replace parent's child or reassign root if parent is null
      if (parent) {
         parent->ReplaceChild(node, leftChild);
      }
      else {
         root = leftChild;
         root->SetParent(nullptr);
      }
   }
   
   // Searches for a node with a matching key. Does a regular
   // binary search tree search operation. Returns the node with the
   // matching key, or nullptr if no matching key exists in the tree.
   AVLNode* Search(int desiredKey) {
      AVLNode* currentNode = root;
      while (currentNode) {
         // Return the node if the key matches
         if (currentNode->GetKey() == desiredKey) {
            return currentNode;
         }
         
         // Navigate to the left if the search key is
         // less than the node's key.
         else if (desiredKey < currentNode->GetKey()) {
            currentNode = currentNode->GetLeft();
         }
         
         // Navigate to the right if the search key is
         // greater than the node's key.
         else {
            currentNode = currentNode->GetRight();
         }
      }
      
      // The key was not found in the tree.
      return nullptr;
   }
   
public:
   AVLTree() {
      root = nullptr;
   }
   
   virtual ~AVLTree() {
      DeleteTree(root);
      root = nullptr;
   }
   
   bool Contains(int key) {
      return Search(key) != nullptr;
   }
   
   AVLNode* GetRoot() {
      return root;
   }
   
   bool InsertKey(int key) {
      if (Contains(key)) {
         return false;
      }
      
      InsertNode(new AVLNode(key));
      return true;
   }
   
   void PrintTree(std::ostream& output, std::string end = "") const {
      output << AVLPrint::TreeToString(root) << end;
   }
   
   // Attempts to remove a node with a matching key. If no node has a matching 
   // key then nothing is done and false is returned; otherwise the node is 
   // removed and true is returned.
   bool RemoveKey(int key) {
      AVLNode* node = Search(key);
      if (!node) {
         return false;
      }
      return RemoveNode(node);
   }
};

#endif