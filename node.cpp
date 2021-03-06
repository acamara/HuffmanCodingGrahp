#include "node.h"
#include <QDebug>

Node::Node(){
    left = NULL;
    right = NULL;
}

Node::Node(double newData) {
    left = NULL;
    right = NULL;
    freq = newData;
}

Node::Node(double newData, int newCode) {
    left = NULL;
    right = NULL;
    freq = newData;
    code = newCode;
}

void Node::setCode(int newCode){
    code = newCode;
}

void Node::setColumn(int newColumn){
    column = newColumn;
}

int Node::getColumn(){
    return column;
}

bool Node::operator <(const Node& n2)const
{
    return (freq <n2.freq);
}

bool Node::operator >(const Node& n2)const
{
    return(freq>n2.freq);
}

bool Node::operator==(const Node& n2)const
{
    return (freq==n2.freq);
}
