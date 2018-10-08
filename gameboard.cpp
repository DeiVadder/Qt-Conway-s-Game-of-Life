#include "gameboard.h"

#include "cell.h"

#include <QTimer>
GameBoard::GameBoard(QObject *parent) : QObject(parent)
{
    m_Running = false;

    m_Heigth = 50;
    m_Width = 100;
    intervall = 50;
    m_ChanceToBeAlive = 30;
    m_Border = Alive;

    liveCycle = new QTimer(this);

    connect(this, &GameBoard::boardHeightChanged,       this, [=]{setRunning(false);});
    connect(this, &GameBoard::boardWidthChanged,        this, [=]{setRunning(false);});
    connect(this, &GameBoard::borderBehaviourChanged,   this, [=]{setRunning(false);});
    connect(this, &GameBoard::chanceToBeAliveChanged,   this, [=]{setRunning(false);});

    setupBoard();
}

void GameBoard::setupBoard()
{

    qDeleteAll(m_Cells);
    m_Cells.clear();

    for(int x(0); x < m_Heigth; x++){
        for(int y(0); y <m_Width; y++){
            bool borderCell = (x == 0 || x == m_Heigth -1 || y == 0 || y == m_Width-1) ? true : false;
            bool change;

            if(borderCell && (m_Border == Alive || m_Border == Dead))
                change = false;
            else
                change = true;

            ushort chance = m_ChanceToBeAlive;
            if(borderCell){
                if(m_Border == Alive)
                    chance = 100;
                else if(m_Border == Dead)
                    chance = 0;
            }


            Cell *c = new Cell(chance, change ,this);
            m_Cells.append(c);
        }
    }

    for(int i(0); i < m_Width; i++){
        for(int j(0); j < m_Heigth; j++){
            int index1D = j * m_Width + i;

            Cell *c1 = qobject_cast<Cell*>(m_Cells.at(index1D));
            if(c1){
                int health = 0;
                connect(liveCycle, &QTimer::timeout, c1, &Cell::newCycle);

                //Connect nearest neighbour's change
                for(int x(i-1); x < (i+2); x++){
                    for(int y(j-1); y < (j+2); y++){
                        int a(x), b(y);
                        if(x < 0) a = m_Width-1;
                        if( x >= m_Width) a = 0;
                        if(y < 0) b = m_Heigth -1;
                        if(y >= m_Heigth) b = 0;

                        int index = b * m_Width + a;
                        Cell *c2 = qobject_cast<Cell*>(m_Cells.at(index));
                        if(c2 &&  c1!=c2){
                            if(c2->alive())
                                health++;
                            connect(c1, &Cell::cellBirthed, c2, &Cell::addHealth,Qt::QueuedConnection);
                            connect(c1, &Cell::cellDied, c2, &Cell::subHealth,Qt::QueuedConnection);
                        }
                    }
                }
                c1->setHealth(health);
            }
        }
    }

    emit newCells();
}

void GameBoard::setRunning(const bool &running)
{
    if(running != m_Running){
        if(m_Running)
            liveCycle->stop();
        else
            liveCycle->start(intervall);
        m_Running = running;
        emit runningChanged();
    }
}

void GameBoard::setChanceToBeAlive(ushort chance)
{
    //Chance in 0-100%
    if(chance > 100)
        chance = 100;
    if(chance != m_ChanceToBeAlive){
        m_ChanceToBeAlive = chance;
        emit chanceToBeAliveChanged();
    }
}

void GameBoard::setBorderBehaviour(const int &behaviour)
{
    BorderBehaviour beha = static_cast<BorderBehaviour>(behaviour);
    if(beha != m_Border){
        m_Border = beha;
        emit borderBehaviourChanged();
    }
}

void GameBoard::setBoardWidth(const int &w)
{
    if(w != m_Width && w > 0){
        m_Width = w;
        emit boardWidthChanged();
    }
}

void GameBoard::setBoardHeight(const int &h)
{
    if(h != m_Heigth && h > 0){
        m_Heigth = h;
        emit boardHeightChanged();
    }
}

