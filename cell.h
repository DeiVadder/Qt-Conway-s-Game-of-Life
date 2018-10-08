#ifndef CELL_H
#define CELL_H

#include <QObject>

class Cell : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool alive READ alive WRITE setAlive NOTIFY aliveChanged)

public:
    explicit Cell(ushort &chanceToBeAlive, const bool &doChange = true, QObject *parent = nullptr);

    inline const bool &alive(){return m_Alive;}
    void setAlive(const bool &);

    void setHealth(const uint &);
    Q_INVOKABLE int getHealth(){return m_health;}

signals:
    void aliveChanged();

    void cellDied();
    void cellBirthed();

public slots:
    void newCycle();

    void addHealth(){m_health++;if(m_health > 8)m_health = 8;}
    void subHealth(){m_health--; if(m_health < 0) m_health = 0;}

private:
    bool m_Alive;
    bool m_AllowChange;

    uchar m_health;
};

#endif // CELL_H
