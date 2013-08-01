#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <math.h>
#include <QDebug>

bool myLessThan( const Node *a, const Node *b )
{
   return (*a) < (*b);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, true);

    int ncol=2, nrow=4;
    model = new QStandardItemModel(nrow, ncol, this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Frequency")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Code")));

    // Asignando el modelo al TableView
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::read_frequencys(){
    slist = ui->lineEdit->text().split("/");

    for (int i=0; i<slist.size(); i++) {
        lnodes.append(new Node(slist.at(i).toDouble()));
    }
    numfreq = slist.size();
}

void MainWindow::calculate_Entropy(){
    double entropy = 0.00;

    for (int i=0; i<slist.size(); i++) {
        entropy+=slist.at(i).toDouble()*log2(slist.at(i).toDouble());
    }

    ui->lineEdit_entropy->setText("H = "+QString::number(entropy*(-1))+" bits");
}

void MainWindow::calculate_AverageLength(){
    double averagelength = 0.00;

    for (int i=0;i<slist.size();i++) {
        averagelength+=slist.at(i).toDouble()*lcodes.at(i).size();
    }

    ui->lineEdit_averagelength->setText("R = "+QString::number(averagelength)+" bits");
}

void MainWindow::calculate(){
    while(lnodes.size()>1){
        qSort(lnodes.begin(), lnodes.end(), myLessThan );
        double mixfre=lnodes.at(0)->freq+lnodes.at(1)->freq;
        //qDebug()<<"Nodes: "<<lnodes.at(0)->freq<<" "<<lnodes.at(1)->freq;
        //qDebug()<<"Mix: "<<mixfre;

        root = new Node(mixfre);
        lnodes.at(1)->setCode(1);
        root->left = lnodes.at(1);
        lnodes.at(0)->setCode(0);
        root->right = lnodes.at(0);
        lnodes.removeFirst();
        lnodes.removeFirst();
        lnodes.push_front(root);
    }

    binarytree = new BinaryTree(root);
    //binarytree->printPaths(root);
}

void MainWindow::showCodes(){
    QString code;
    getCodesRecur(root->left,code);
    getCodesRecur(root->right,code);

    for(int i = 0;i<lcodes.size();i++){
        model->setItem(i,1,new QStandardItem(lcodes.at(i)));
    }
}

void MainWindow::getCodesRecur(Node *node, QString code){
    if (node==NULL) return;

    // append this node to the path array
    code.append(QString::number(node->code));

    // it's a leaf, so add code to list codes
    if (node->left==NULL && node->right==NULL) {
        lcodes.append(code);
        //qDebug()<<code<<" "<<lcodes;
    }
    else {
    // otherwise try both subtrees
      getCodesRecur(node->left, code);
      getCodesRecur(node->right,code);
    }
}

void MainWindow::preCalPosition(Node* node, int &col) {
  if (node == NULL) return;
  preCalPosition(node->left,col);
  node->setColumn(col);
  //qDebug()<< node->freq<<" col: "<<col;
  col++;
  preCalPosition(node->right,col);
}

void MainWindow::paintTree(Node *root){
    int col = 0;
    preCalPosition(root,col);

    pen = QPen(Qt::black);

    freqpos =0;
    int k = 0;

    leave[k] = new GraphElement(root->freq,0);
    leave[k]->setPos(root->getColumn()*64,0);
    scene->addItem(leave[k]);
    k++;

    paintTreeRecur(root,k);
}

void MainWindow::paintTreeRecur(Node *node, int k){
    if (node==NULL) return;

    //qDebug()<<"Freq: "<<node->freq<<" Column: "<<node->column;

    // it's a leaf
    if (node->left==NULL && node->right==NULL) {
        //leave[k-1]->setPos(0,leave[k-1]->y());
        model->setItem(freqpos, 0, new QStandardItem(QString::number(node->freq)));
        freqpos++;
    }
    else {
    // otherwise try both subtrees
        leave[k] = new GraphElement(node->left->freq,0);
        //qDebug()<<"Freq: "<<node->left->freq<<"col: "<<node->left->getColumn();
        leave[k]->setPos(node->left->getColumn()*64,leave[k-1]->y()+108);
        scene->addItem(leave[k]);
        scene->addLine(leave[k-1]->x()+32,leave[k-1]->y()+36,leave[k]->x()+32,leave[k]->y(),pen);
        k++;
        paintTreeRecur(node->left, k);

        leave[k] = new GraphElement(node->right->freq,0);
        //qDebug()<<"Freq: "<<node->right->freq<<"col: "<<node->right->getColumn();
        leave[k]->setPos(node->right->getColumn()*64,leave[k-1]->y());
        scene->addItem(leave[k]);
        scene->addLine(leave[k-2]->x()+32,leave[k-2]->y()+36,leave[k]->x()+32,leave[k]->y(),pen);
        k++;
        paintTreeRecur(node->right,k);
    }
}


void MainWindow::on_pushButton_generate_clicked()
{
    model->clear();
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Probabilities")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Code")));

    lcodes.clear();
    lnodes.clear();
    scene->clear();

    read_frequencys();
    calculate_Entropy();
    calculate();
    showCodes();
    calculate_AverageLength();
    paintTree(root);
}
