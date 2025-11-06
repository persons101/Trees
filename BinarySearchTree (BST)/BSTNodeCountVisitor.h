#ifndef BSTNODECOUNTVISITOR_H
#define BSTNODECOUNTVISITOR_H

#include "BSTNodeVisitor.h"

class BSTNodeCountVisitor : public BSTNodeVisitor {
private:
   int nodeCount;

public:
   BSTNodeCountVisitor() {
      nodeCount = 0;
   }
   
   virtual void PrintSummary(std::ostream& output) override {
      output << "BSTNodeCountVisitor visited " << nodeCount;
      output << " nodes" << std::endl;
   }
   
   virtual void Visit(BSTNode* node) override {
      nodeCount++;
   }
};

#endif