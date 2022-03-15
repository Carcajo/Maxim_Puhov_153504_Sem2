#ifndef SOLDER_H
#define SOLDER_H
#include<QGraphicsView>
#include<QGraphicsItem>

class human
{
public:
   virtual~human(){};
    virtual void draw() = 0;
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
};

class solder:public human
{
public:
    //solder();
    solder(const int &x, const int &y, QGraphicsScene* scene): x(x), y(y),scene(scene),x1(x+100),y1(y+50){

    };
    void moveLeft() override{
        --x;
        --x1;
    };
    void moveRight() override{
        ++x;
        ++x1;
    };
    void draw()override;
    void up(){
        x1-=50;
        y1-=100;

    };
    void down(){
        x1+=50;
        y1+=100;
    }
    ~solder(){};
private:
    QGraphicsEllipseItem *headItem;
    QGraphicsRectItem *bodyItem;
    QGraphicsPolygonItem *moveHandItem;
    QGraphicsPolygonItem *handItem;
    QGraphicsPolygonItem *leg1Item;
    QGraphicsPolygonItem *leg2Item;
    int x,x1;
    int y,y1;
    QGraphicsScene *scene;
};

#endif // SOLDER_H

