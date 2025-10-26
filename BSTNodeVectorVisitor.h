#ifndef BSTNODEVECTORVISITOR_H
#define BSTNODEVECTORVISITOR_H

#include <vector>
#include "BSTNodeVisitor.h"

class BSTNodeVectorVisitor : public BSTNodeVisitor {
private:
   std::vector<BSTNode*> visitedNodes;

public:
   virtual void PrintSummary(std::ostream& output) override {
      output << "BSTNodeVectorVisitor visited " << visitedNodes.size();
      output << " nodes: ";
      for (BSTNode* node : visitedNodes) {
         output << node->key << " ";
      }
      output << std::endl;
   }
   
   virtual void Visit(BSTNode* node) override {
      visitedNodes.push_back(node);
   }
};

#endif