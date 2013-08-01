#ifndef MYNODE_H
#define MYNODE_H

class Node
{
public:
    Node();
    Node(double newData);
    Node(double newData,int newCode);
    bool operator<(const Node& n2) const;
    bool operator>(const Node& n2) const;
    bool operator==(const Node& n2) const;
    void setCode(int newCode);
    void setColumn(int newColumn);
    int getColumn();

    double freq;
    int code;
    Node *left;
    Node *right;
    int column;

};

#endif // MYNODE_H
