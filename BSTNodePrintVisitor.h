#ifndef BSTNODEPRINTVISITOR_H
#define BSTNODEPRINTVISITOR_H

#include <iostream>
#include "BSTNodeVisitor.h"

class BSTNodePrintVisitor : public BSTNodeVisitor {
public:
   virtual void PrintSummary(std::ostream& output) override {
      output << "BSTNodePrintVisitor is done visiting nodes" << std::endl;
   }
   
   virtual void Visit(BSTNode* node) override {
      std::cout << node->key << " ";
   }
};

#endif