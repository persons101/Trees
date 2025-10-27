#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <algorithm>
#include <iostream>
#include "BSTNode.h"
#include "BSTNodeVisitor.h"

class BinarySearchTree {
private:
   BSTNode* root;
   
   void DeleteTree(BSTNode* treeRoot) {
      if (treeRoot) {
         DeleteTree(treeRoot->left);
         DeleteTree(treeRoot->right);
         delete treeRoot;
      }
   }

protected:
   int GetHeight(BSTNode* node) const {
      if (node == nullptr) {
         return -1;
      }
      int leftHeight = GetHeight(node->left);
      int rightHeight = GetHeight(node->right);
      return 1 + std::max(leftHeight, rightHeight);
   }
   
   void InOrder(BSTNode* node, BSTNodeVisitor& visitor) {
      if (node) {
         InOrder(node->left, visitor);
         visitor.Visit(node);
         InOrder(node->right, visitor);
      }
   }
   
   void InsertNode(BSTNode* newNode) {
      // Check if tree is empty
      if (root == nullptr) {
         root = newNode;
      }
      else {
         BSTNode* currentNode = root;
         while (currentNode) {
            if (newNode->key < currentNode->key) {
               // If no left child exists, add the new node
               // here; otherwise repeat from the left child
               if (currentNode->left == nullptr) {
                  currentNode->left = newNode;
                  currentNode = nullptr;
               }
               else {
                  currentNode = currentNode->left;
               }
            }
            else {
               // If no right child exists, add the new node
               // here; otherwise repeat from the right child
               if (currentNode->right == nullptr) {
                  currentNode->right = newNode;
                  currentNode = nullptr;
               }
               else {
                  currentNode = currentNode->right;
               }
            }
         }
      }
   }
   
   BSTNode* Search(int key) {
      BSTNode* currentNode = root;
      while (currentNode) {
         // Return the node if the key matches
         if (key == currentNode->key) {
            return currentNode;
         }
         
         // Navigate to the left if the search key is
         // less than the node's key
         else if (key < currentNode->key) {
            currentNode = currentNode->left;
         }
         
         // Navigate to the right if the search key is
         // greater than the node's key
         else {
            currentNode = currentNode->right;
         }
      }
      
      // The key was not found in the tree
      return nullptr;
   }

public:
   BinarySearchTree() {
      root = nullptr;
   }
   
   virtual ~BinarySearchTree() {
      DeleteTree(root);
   }
   
   bool Contains(int key) {
      return Search(key) != nullptr;
   }
   
   int GetHeight() const {
      return GetHeight(root);
   }

   BSTNode* GetRoot() const {
      return root;
   }
   
   bool InsertKey(int key) {
      if (Contains(key)) {
         // Duplicate keys not allowed
         return false;
      }
      
      // Create and insert a new node for the key and return true
      InsertNode(new BSTNode(key));
      return true;
   }
   
   // Performs an inorder traversal of the BST, calling the visitor's Visit()
   // function for each node
   void InOrder(BSTNodeVisitor& visitor) {
      InOrder(root, visitor);
   }
   
   bool Remove(int key) {
      BSTNode* parent = nullptr;
      BSTNode* currentNode = root;
      
      // Search for the node
      while (currentNode) {
         // Check if currentNode has a matching key
         if (currentNode->key == key) {
            if (currentNode->left == nullptr && currentNode->right == nullptr) {
               // Remove leaf
               
               if (parent == nullptr) { // Node is root
                  root = nullptr;
               }
               else if (parent->left == currentNode) { 
                  parent->left = nullptr;
               }
               else {
                  parent->right = nullptr;
               }
               delete currentNode;
               return true; // Node found and removed
            }
            else if (currentNode->left && currentNode->right == nullptr) {
               // Remove node with only left child
               
               if (parent == nullptr) { // Node is root
                  root = currentNode->left;
               }
               else if (parent->left == currentNode) {
                  parent->left = currentNode->left;
               }
               else {
                  parent->right = currentNode->left;
               }
               delete currentNode;
               return true; // Node found and removed
            }
            else if (currentNode->left == nullptr && currentNode->right) {
               // Remove node with only right child
               
               if (parent == nullptr) { // Node is root
                  root = currentNode->right;
               }
               else if (parent->left == currentNode) {
                  parent->left = currentNode->right;
               }
               else {
                  parent->right = currentNode->right;
               }
               delete currentNode;
               return true; // Node found and removed
            }
            else {
               // Remove node with two children
               
               // Find successor (leftmost child of right subtree)
               BSTNode* successor = currentNode->right;
               while (successor->left) {
                  successor = successor->left;
               }
               currentNode->key = successor->key; // Copy successor's key to current node
               parent = currentNode;
               
               // Reassign currentNode and key so that loop continues with new key
               currentNode = currentNode->right;
               key = successor->key;
            }
         }
         else if (currentNode->key < key) {
            // Search right
            
            parent = currentNode;
            currentNode = currentNode->right;
         }
         else {
            // Search left
            
            parent = currentNode;
            currentNode = currentNode->left;
         }
      }
      return false; // Node not found
   }

};

#endif