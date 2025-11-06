#ifndef NODE_H
#define NODE_H

class AVLNode {
private:
   int key;
   AVLNode* parent;
   AVLNode* left;
   AVLNode* right;
   int height;

public:
   // Constructs an AVLNode with the given key
   AVLNode(int nodeKey) {
      key = nodeKey;
      parent = nullptr;
      left = nullptr;
      right = nullptr;
      height = 0;
   }
   
   // Calculates this node's balance factor, defined as:
   // height(left subtree) - height(right subtree)
   int GetBalance() const {
      // Get current height of left subtree, or -1 if null
      int leftHeight = -1;
      if (left) {
         leftHeight = left->height;
      }
            
      // Get current height of right subtree, or -1 if null
      int rightHeight = -1;
      if (right) {
         rightHeight = right->height;
      }
            
      // Calculate the balance factor.
      return leftHeight - rightHeight;
   }
   
   // Returns this node's key
   int GetKey() const {
      return key;
   }
   
   // Returns this node's left child node
   AVLNode* GetLeft() const {
      return left;
   }
   
   // Returns this node's parent node
   AVLNode* GetParent() const {
      return parent;
   }
   
   // Returns this node's right child node
   AVLNode* GetRight() const {
      return right;
   }
   
   // Replaces a current child with a new child. Determines if the current
   // child is the left or right, then calls SetLeft() or SetRight() with the
   // new node appropriately. Returns true if the new child is assigned, false
   // otherwise.
   bool ReplaceChild(AVLNode* currentChild, AVLNode* newChild) {
      if (left == currentChild) {
         SetLeft(newChild);
         return true;
      }
      else if (right == currentChild) {
         SetRight(newChild);
         return true;
      }
      
      // currentChild is not a child of this node
      return false;
   }
   
   // Reassigns this node's key with the new key
   void SetKey(int newKey) {
      key = newKey;
   }
   
   // Reassigns this node's left child with the new child. If non-null, the
   // new left child's parent is assigned with a pointer to this node.
   // After assigning the new child, this node's height is updated.
   void SetLeft(AVLNode* newLeftChild) {
      // Assign new left child
      left = newLeftChild;
      
      // If new child is non-null, assign parent
      if (left) {
         left->parent = this;
      }
      
      // A new child may change this node's height, so call UpdateHeight()
      UpdateHeight();
   }
   
   // Reassigns this node's parent node with the new parent
   void SetParent(AVLNode* newParent) {
      parent = newParent;
   }
   
   // Reassigns this node's right child with the new child. If non-null, the
   // new right child's parent is assigned with a pointer to this node.
   // After assigning the new child, this node's height is updated.
   void SetRight(AVLNode* newRightChild) {
      // Assign new right child
      right = newRightChild;
      
      // If new child is non-null, assign parent
      if (right) {
         right->parent = this;
      }
      
      // A new child may change this node's height, so call UpdateHeight()
      UpdateHeight();
   }
   
   // Recalculates the current height of the subtree rooted at this node.
   // Usually called after a subtree has been modified.
   void UpdateHeight() {
      // Get current height of left subtree, or -1 if null
      int leftHeight = -1;
      if (left) {
         leftHeight = left->height;
      }
            
      // Get current height of right subtree, or -1 if null
      int rightHeight = -1;
      if (right) {
         rightHeight = right->height;
      }

      // Assign height with calculated node height.
      height = ((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1;
   }
};

#endif