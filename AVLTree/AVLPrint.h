#ifndef AVLPRINT_H
#define AVLPRINT_H

#include <algorithm>
#include <string>
#include <vector>
#include "AVLNode.h"

class AVLPrint {
private:
   static std::string GetRepeated(char toRepeat, int numberOfTimes) {
      if (numberOfTimes <= 0) {
         return std::string();
      }

      char chars[numberOfTimes + 1];
      for (int i = 0; i < numberOfTimes; i++) {
         chars[i] = toRepeat;
      }
      chars[numberOfTimes] = '\0';
      return std::string(chars);
   }
   
   static std::string GetSpaces(int numberOfSpaces) {
      return GetRepeated(' ', numberOfSpaces);
   }
   
   static void IndentLines(std::vector<std::string>& lines, int numberOfSpaces) {
      if (numberOfSpaces <= 0) {
         return;
      }
       
      // Prepend indentation to each line
      std::string indent = GetSpaces(numberOfSpaces);
      for (int i = 0; i < lines.size(); i++) {
         lines[i] = indent + lines[i];
      }
   }
   
   static std::vector<std::string> TreeToLines(AVLNode* subtreeRoot) {
      std::vector<std::string> result;
      if (!subtreeRoot) {
         return result;
      }
      
      // Make a string with the subtreeRoot's key enclosed in brackets
      std::string rootString = "[" + std::to_string(subtreeRoot->GetKey()) +
         "]";
      int rootStrLen = rootString.length();
      
      // Case 1: subtreeRoot is a leaf
      if (subtreeRoot->GetLeft() == nullptr && subtreeRoot->GetRight() == nullptr) {
         result.push_back(rootString);
         return result;
      }
      
      // Recursively make line strings for each child
      std::vector<std::string> leftLines = TreeToLines(subtreeRoot->GetLeft());
      std::vector<std::string> rightLines = TreeToLines(subtreeRoot->GetRight());
      
      int lineCount = leftLines.size();
      if (rightLines.size() > lineCount) {
         lineCount = rightLines.size();
      }
      std::vector<std::string> allLines;
      allLines.resize(lineCount + 2);
      
      // Case 2: subtreeRoot has no left child
      if (!subtreeRoot->GetLeft()) {
         // Create the first 2 lines, not yet indented
         allLines[0] = rootString;
         allLines[1] = GetSpaces(rootStrLen) + "\\";
         
         // Find where the right child starts
         int rightChildIndent = (int)rightLines[0].find('[');
         
         // Goal: Indent lines appropriately so that the parent's right branch 
         // character ('\') matches up with the right child's '['.
         
         if (rightChildIndent <= rootStrLen) {
            // Indent all lines below
            IndentLines(rightLines, rootStrLen - rightChildIndent);
         }
         else {
            // Indent first 2 lines
            std::string indent = GetSpaces(rightChildIndent - rootStrLen);
            allLines[0] = indent + allLines[0];
            allLines[1] = indent + allLines[1];
         }
         
         // Copy rightLines into allLines starting at index 2
         for (int i = 0; i < rightLines.size(); i++) {
            allLines[i + 2] = rightLines[i];
         }
         
         return allLines;
      }
      
      // Case 3: subtreeRoot has no right child
      if (subtreeRoot->GetRight() == nullptr) {
         // Goal: Indent lines appropriately so that the parent's left branch 
         // character ('/') matches up with the left child's ']'.
         
         // Create the first 2 lines
         std::string indent = GetSpaces(leftLines[0].find(']'));
         allLines[0] = indent + " " + rootString;
         allLines[1] = indent + "/";
         
         // Copy leftLines into allLines starting at index 2
         for (int i = 0; i < leftLines.size(); i++) {
            allLines[i + 2] = leftLines[i];
         }
         
         return allLines;
      }
      
      // Case 4: subtreeRoot has both a left and right child
      
      // The goal is to have the two child nodes as close to the parent as 
      // possible without overlap on any level.
      
      // Compute absolute indentation, in number of spaces, needed for right lines
      int indentNeeded = 0;
      if (rightLines.size() > 0) {
         // Indent should at least get the immediate right child to be to the 
         // right of the root
         indentNeeded = std::max(0,
            (int)(leftLines[0].length() + rootString.length()) - 
            (int)rightLines[0].find('['));
      }
      for (int i = 0; i < leftLines.size() && i < rightLines.size(); i += 2) {
         // Lines with branches are skipped, so the line of interest has only 
         // nodes. The difference between where the left line ends and the 
         // right line begins should be at least 3 spaces for clarity.
         int rightBegin = rightLines[i].find('[');
         
         int forThisLine = leftLines[i].length() + 3 - rightBegin;
         indentNeeded = std::max(indentNeeded, forThisLine);
      }
      
      // Build final lines in allLines starting at index 2
      std::string absoluteIndent = GetSpaces(indentNeeded);
      for (int i = 0; i < leftLines.size() || i < rightLines.size(); i++) {
         // If no right line, just take the left
         if (i >= rightLines.size()) {
            allLines[2 + i] = leftLines[i];
         }
         else {
            std::string left;
            if (i < leftLines.size()) {
               left = leftLines[i];
            }
            std::string right = absoluteIndent + rightLines[i];
            allLines[2 + i] = left + right.substr(left.length());
         }
      }
      
      // The first 2 lines remain. allLines[2] has the proper string for the 
      // 2 child nodes, and thus can be used to create branches in allLines[1].
      int leftIndex = allLines[2].find(']');
      int rightIndex = allLines[2].find_last_of('[');
      allLines[1] = GetSpaces(leftIndex) + "/" + 
         GetSpaces(rightIndex - leftIndex - 1) + "\\";
      
      // The space between leftIndex and rightIndex is the space that 
      // subtreeRoot's string should occupy. If rootString is too short, put 
      // underscores on the sides.
      rootStrLen = rightIndex - leftIndex - 1;
      if (rootString.length() < rootStrLen) {
         int difference = rootStrLen - rootString.length();
         std::string underscores = GetRepeated('_', difference / 2);
         if (difference % 2 == 0) {
            rootString = underscores + rootString + underscores;
         }
         else {
            rootString = underscores + rootString + underscores + "_";
         }
      }
      allLines[0] = GetSpaces(leftIndex + 1) + rootString;
      
      return allLines;
   }

public:
   static std::string TreeToString(AVLNode* subtreeRoot) {
      if (subtreeRoot == nullptr) {
         return "(empty tree)";
      }
      
      // First convert the tree to a vector of line strings
      std::vector<std::string> lines = TreeToLines(subtreeRoot);
      
      // Combine all lines into 1 string
      std::string treeString = lines[0];
      for (int i = 1; i < lines.size(); i++) {
         treeString += ("\n" + lines[i]);
      }
      return treeString;
   }
};

#endif