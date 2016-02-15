//=================================
// CharNode definition
//
// Used by: ArrayClass
//=================================

#ifndef ARRAY_NODE_STRUCTURE
#define ARRAY_NODE_STRUCTURE

// Define a node used in the ARRAY structure.

struct CharNode {

  CharNode *last;
  CharNode *next;
  int nodeGenes[11];
};

#endif