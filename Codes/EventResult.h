#ifndef EVENT_H
#define EVENT_H
/**
*projectName FinalProject
*author  Zeyuan Song
*studentID 19096216
*Date 12/05/2020
*/
#include <QObject>

class EventResult : public QObject
{

    Q_OBJECT
    /*****friend*****/
    friend class mainwindow;
public:
    explicit EventResult(QObject *parent = nullptr);

    void ResultJudge();
    int health=100;
    int stamina=100;
    int fightCapable=1;
    int flag=1;
    int lose=0;
    int win=2;
    /*****Destructure*****/
    ~EventResult(){
        void won();
        void lost();
    }
    //friend void ResultJudge();
signals:
    void won();
    void lost();

};

#endif // EVENT_H
