#include "cell.h"
#include <time.h>

Cell::Cell(ushort &chanceToBeAlive, const bool &doChange, QObject *parent) : QObject(parent), m_AllowChange(doChange)
{
    m_health = 0;
    if(chanceToBeAlive > 100)
        chanceToBeAlive = 100;

    int random = arc4random()/*rand()*/ % 100;
    if(random < chanceToBeAlive)
        m_Alive = true;
    else
        m_Alive = false;
}

void Cell::setAlive(const bool &b)
{
    if(m_AllowChange){
        if(b != m_Alive){
            m_Alive = b;
            if(b)
                emit cellBirthed();
            else
                emit cellDied();

            emit aliveChanged();
        }
    }
}

void Cell::setHealth(const uint &v)
{
    m_health = v;
}

void Cell::newCycle()
{
    if(!alive()){
        if(m_health == 3){
            setAlive(true);
        }
    }else{
        if(m_health <2){
            //Died through onlyness
            setAlive(false);
        }else if(m_health > 3) {
            //Died through overpopulation
            setAlive(false);
        }
        //else keeps on living
    }
}
