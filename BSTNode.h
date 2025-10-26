#ifndef BSTNODE_H
#define BSTNODE_H

class BSTNode {
public:
   int key;
   BSTNode* left;
   BSTNode* right;
   
   BSTNode(int nodeKey, BSTNode* leftChild = nullptr, BSTNode*
      rightChild = nullptr) {
      
      key = nodeKey;
      left = nullptr;
      right = nullptr;
   }
};

#endif