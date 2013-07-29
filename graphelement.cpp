#include "graphelement.h"

GraphElement::GraphElement(double val, int  code_bit)
{
    Pressed = false;
    value = val;
    bit = code_bit;
}

QRectF GraphElement::boundingRect() const
{
    return QRectF(0,0,64,36);
}

void GraphElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::white);
    painter->setFont(QFont("Arial", 11, QFont::Normal));

    painter->fillRect(rec,brush);
    painter->drawText(0, 0, 64, 36, Qt::AlignHCenter | Qt::AlignVCenter, QString::number(value));
    painter->drawRect(rec);
}

double GraphElement::getValue()
{
    return value;
}

void GraphElement::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void GraphElement::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
