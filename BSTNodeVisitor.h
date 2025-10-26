#ifndef BSTNODEVISITOR_H
#define BSTNODEVISITOR_H

#include <iostream>
#include "BSTNode.h"

class BSTNodeVisitor {
public:
   virtual ~BSTNodeVisitor() {
   }
   
   virtual void PrintSummary(std::ostream& output) = 0;
   
   virtual void Visit(BSTNode* node) = 0;
};

#endif