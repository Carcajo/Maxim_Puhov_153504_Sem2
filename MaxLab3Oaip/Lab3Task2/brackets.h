#ifndef BRACKETS_H
#define BRACKETS_H
#include<qchar.h>

class Brackets
{

public:
    Brackets(QChar &symbol, int &position, int block,int blockPos):symbol(symbol), position(position), block(block), blockPos(blockPos)
    {
        if(this->symbol=='{' || this->symbol=='(' ||this->symbol=='['){
            adder=1;
        }
        else{
            adder=-1;
        }
    };
    Brackets(){};

    QChar getSymvol() const{
         return symbol;
    };
    int getAdd() const{
        return adder;
    };
    int getPosition() const{
        return this->position;
    };
    int getBlock(){
        return this->block;
    }
    int getBlockPos(){
        return this->blockPos;
    }
private:

    QChar symbol;
    int position;
    int adder;
    int block;
    int blockPos;
};
#endif // BRACKETS_H
