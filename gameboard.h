#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>
#include <QVector>
#include <QVariant>

class QTimer;
class GameBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant cellModel READ cellModel NOTIFY newCells)

    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(ushort chanceToBeAlive READ chanceToBeAlive WRITE setChanceToBeAlive NOTIFY chanceToBeAliveChanged)
    Q_PROPERTY(int borderBehaviour READ borderBehaviour WRITE setBorderBehaviour NOTIFY borderBehaviourChanged)
    Q_PROPERTY(int boardWidth READ boardWidth WRITE setBoardWidth NOTIFY boardWidthChanged)
    Q_PROPERTY(int boardHeight READ boardHeight WRITE setBoardHeight NOTIFY boardHeightChanged)
public:
    explicit GameBoard(QObject *parent = nullptr);

    enum BorderBehaviour{
        Alive = 0,
        Dead,
        Loop
    };Q_ENUM(BorderBehaviour)

    Q_INVOKABLE void setupBoard();

    inline QVariant cellModel(){return QVariant::fromValue(m_Cells);}

    inline const bool &running(){return m_Running;}
    void setRunning(const bool &);

    inline const ushort &chanceToBeAlive(){return m_ChanceToBeAlive;}
    void setChanceToBeAlive(ushort);

    inline int borderBehaviour(){return static_cast<int>(m_Border);}
    void setBorderBehaviour(const int &);

    inline const int &boardWidth(){return m_Width;}
    void setBoardWidth(const int &);

    inline const int &boardHeight(){return m_Heigth;}
    void setBoardHeight(const int &);
signals:

    void newCells();

    void runningChanged();
    void chanceToBeAliveChanged();
    void borderBehaviourChanged();

    void boardWidthChanged();
    void boardHeightChanged();

private slots:

private:
    QList<QObject *> m_Cells;

    QTimer *liveCycle;

    quint16 intervall;

    bool m_Running;
    ushort m_ChanceToBeAlive;
    BorderBehaviour m_Border;

    int m_Width, m_Heigth;
};

#endif // GAMEBOARD_H
