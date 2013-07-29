#include "binarytree.h"
#include <iostream>
#include <queue>
#include <QStringList>
#include <QDebug>

using namespace std;

BinaryTree::BinaryTree(QObject *parent) :
    QObject(parent)
{
    root = NULL;
    root->left = NULL;
    root->right = NULL;
}

BinaryTree::BinaryTree(Node *root)
{
    root = root;
}

/*
 Given a binary tree, return true if a node
 with the target data is found in the tree. Recurs
 down the tree, chooses the left or right
 branch by comparing the target to each node.
*/
bool BinaryTree::lookup(Node *node, double target)
{
    // 1. Base case == empty tree
    // in that case, the target is not found so return false
    if (node == NULL) {
        return(false);
    }
    else {
        // 2. see if found here
        if (target == node->freq){
            return(true);
        }
        else {
            // 3. otherwise recur down the correct subtree
            if (target < node->freq) {
                return(lookup(node->left, target));
            }
            else{
                return(lookup(node->right, target));
            }
        }
    }
}

/*
 Give a binary search tree and a number, inserts a new node
 with the given number in the correct place in the tree.
 Returns the new root pointer which the caller should
 then use (the standard trick to avoid using reference
 parameters).
*/
Node *BinaryTree::insert(Node* node, double data) {
    // 1. If the tree is empty, return a new, single node
    if (node == NULL) {
      return(new Node(data));
    }
    else {
      // 2. Otherwise, recur down the tree
      if (data <= node->freq){
          node->left = insert(node->left, data);
      }
      else{
          node->right = insert(node->right, data);
      }
      return(node); // return the (unchanged) node pointer
    }
}

/*
 Given a binary search tree, print out
 its data elements in increasing
 sorted order.
*/
void BinaryTree::printTree(Node* node) {
  if (node == NULL) return;
  printTree(node->left);
  std::cout<<node->freq<<std::endl;
  printTree(node->right);
}

void BinaryTree::printLevelOrder(Node *root) {
  if (!root) return;
  queue<Node*> currentLevel, nextLevel;
  currentLevel.push(root);
  while (!currentLevel.empty()) {
    Node *currNode = currentLevel.front();
    currentLevel.pop();
    if (currNode) {
      cout << currNode->freq << " ";
      nextLevel.push(currNode->left);
      nextLevel.push(currNode->right);
    }
    if (currentLevel.empty()) {
      cout << endl;
      swap(currentLevel, nextLevel);
    }
  }
}

/*
 Given a binary tree, print its
 nodes according to the "bottom-up"
 postorder traversal.
*/
void BinaryTree::printPostorder(Node* node){
  if (node == NULL) return;
  // first recur on both subtrees
  printTree(node->left);
  printTree(node->right);

  // then deal with the node
  std::cout<<node->freq<<std::endl;
}

/*
 Given a binary tree, print out all of its root-to-leaf
 paths, one per line. Uses a recursive helper to do the work.
*/
void BinaryTree::printPaths(Node *node) {
  double path[1000];
  printPathsRecur(node, path, 0);
}

/*
 Recursive helper function -- given a node, and an array containing
 the path from the root node up to but not including this node,
 print out all the root-leaf paths.
*/
void BinaryTree::printPathsRecur(Node* node, double path[], int pathLen) {
  if (node==NULL) return;

  // append this node to the path array
  path[pathLen] = node->freq;
  pathLen++;

  // it's a leaf, so print the path that led to here
  if (node->left==NULL && node->right==NULL) {
    printArray(path, pathLen);
  }
  else {
  // otherwise try both subtrees
    printPathsRecur(node->left, path, pathLen);
    printPathsRecur(node->right, path, pathLen);
  }
}

/* Utility that prints out an array on a line.*/
void BinaryTree::printArray(double ints[], int len) {
  for (int i=0; i<len; i++) {
      std::cout<<ints[i]<<" ";
  }
  std::cout<<std::endl;
}

/*
 Given a tree and a sum, return true if there is a path from the root
 down to a leaf, such that adding up all the values along the path
 equals the given sum.
 Strategy: subtract the node value from the sum when recurring down,
 and check to see if the sum is 0 when you run out of tree.
*/
bool BinaryTree::hasPathSum(Node* node, double sum) {
  // return true if we run out of tree and sum==0
  if (node == NULL) {
    return(sum == 0);
  }
  else {
  // otherwise check both subtrees
    int subSum = sum - node->freq;
    return(hasPathSum(node->left, subSum) ||
           hasPathSum(node->right, subSum));
  }
}

/* Helper function for getLevel().  It returns level of the data if data is
   present in tree, otherwise returns 0.*/
int BinaryTree::getLevelUtil(Node *node, double data, int level)
{
    if (node == NULL)
        return 0;

    if (node->freq == data)
        return level;

    int downlevel = getLevelUtil(node->left, data, level+1);
    if (downlevel != 0)
        return downlevel;

    downlevel = getLevelUtil(node->right, data, level+1);
    return downlevel;
}

/* Returns level of given data value */
int BinaryTree::getLevel(Node *node, double data)
{
    return getLevelUtil(node,data,1);
}

Node* BinaryTree::getRightLeave(Node *node)
{
    return node->right;
}

Node* BinaryTree::getLeftLeave(Node *node)
{
    return node->left;
}

Node* BinaryTree::search(Node *node, double target)
{
    if(node != NULL){
        if(node->freq == target){
            return node;
        }
        else {
            Node *tmp = search(node->left,target);
            if (tmp != NULL) { // if we find it at left
                return tmp; // we return it
            }
            // else we return the result of the search in the right node
            return search(node->right, target);
        }
    }
    return NULL;
}

int BinaryTree::countNodes(Node *root )
{
    // Count the nodes in the binary tree to which
    // root points, and return the answer.
    if ( root == NULL )
        return 0;  // The tree is empty.  It contains no nodes.
    else {
        int count = 1;   // Start by counting the root.
        count += countNodes(root->left);  // Add the number of nodes
                                           //     in the left subtree.
        count += countNodes(root->right); // Add the number of nodes
                                           //    in the right subtree.
        return count;  // Return the total.
    }
}

/*
 Compute the "maxDepth" of a tree -- the number of nodes along
 the longest path from the root node down to the farthest leaf node.
*/
int BinaryTree::maxDepth (Node *pstNode)
{
    /* verify if the structure is empty */
    if (pstNode == NULL){
        return 0;
    }
    else{
        /* get the depth of the each subtree */
        int iLeftDepth = maxDepth (pstNode->left);
        int iRightDepth = maxDepth (pstNode->right);

        /* use the larger depth */
        if (iLeftDepth > iRightDepth){
            return (iLeftDepth + 1);
        }
        else{
            return (iRightDepth + 1);
        }
    }
}
