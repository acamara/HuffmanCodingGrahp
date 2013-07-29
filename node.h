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

    double freq;
    int code;
    Node *left;
    Node *right;
};

#endif // MYNODE_H
