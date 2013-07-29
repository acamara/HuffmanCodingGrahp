#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <QString>
#include <QObject>
#include "node.h"

class BinaryTree: public QObject
{
    Q_OBJECT
public:
    explicit BinaryTree(QObject *parent = 0);
    BinaryTree(Node *root);

    bool lookup(Node *node, double target);
    bool hasPathSum(Node* node, double sum);
    void printTree(Node *node);
    void printPostorder(Node* node);
    void printPaths(Node *node);
    void printLevelOrder(Node *root);
    int  getLevel(Node *node, double data);
    int  countNodes(Node *root );
    int  maxDepth (Node *pstNode);
    Node* getRightLeave(Node *node);
    Node* getLeftLeave(Node *node);
    Node* search(Node *node, double target);
    Node* insert(Node *node, double data);
    Node* minNode(Node* node);

private:
    void printArray(double ints[], int len);
    void printPathsRecur(Node *node, double path[], int pathLen);
    int  getLevelUtil(Node *node, double data, int level);
    Node *root;
};

#endif // BINARYTREE_H
