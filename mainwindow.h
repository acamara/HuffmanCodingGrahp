#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QGraphicsScene>
#include <QStandardItemModel>

#include "binarytree.h"
#include "node.h"
#include "graphelement.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    enum { max_node = 1000 };

private slots:
    void on_pushButton_generate_clicked();
    void calculate();
    void calculate_Entropy();
    void calculate_AverageLength();
    void read_frequencys();
    void getCodesRecur(Node *node, QString code);
    void showCodes();
    void paintTree(Node *root);
    void paintTreeRecur(Node *node, int k);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsLineItem *line[max_node];
    GraphElement *leave[max_node];

    QList<Node*> lnodes;
    QStringList lcodes;
    BinaryTree *binarytree;
    Node *root;
    QStandardItemModel *model;

    QPen pen;
    int freqpos;
};

#endif // MAINWINDOW_H
