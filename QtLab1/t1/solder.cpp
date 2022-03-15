#include "solder.h"

void solder::draw()
{
    QRectF head (x-50,y-50,100,100);
    headItem=new QGraphicsEllipseItem(head);
    QRectF body(x-75,y,150,200);
    bodyItem=new QGraphicsRectItem(body);
    QPolygon moveHand;
    moveHand<<QPoint(x-75,y)<<QPoint(x-100,y+50);
    moveHandItem= new QGraphicsPolygonItem(moveHand);
    QPolygon hand;
    hand<<QPoint(x+75,y)<<QPoint(x1,y1);
    handItem= new QGraphicsPolygonItem (hand);
    QPolygon leg1;
    leg1<<QPoint(x-75,y+200)<<QPoint(x-100,y+300);
    leg1Item= new QGraphicsPolygonItem (leg1);
    QPolygon leg2;
    leg2<<QPoint(x+75,y+200)<<QPoint(x+100,y+300);
    leg2Item= new QGraphicsPolygonItem (leg2);

    scene->addItem(headItem);
    scene->addItem(bodyItem);
    scene->addItem(moveHandItem);
    scene->addItem(handItem);
    scene->addItem(leg1Item);
    scene->addItem(leg2Item);
}
