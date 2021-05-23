/**
*projectName FinalProject
*author  Zeyuan Song
*studentID 19096216
*Date 12/05/2020
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Character.h"
#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "QProgressBar"
#include "QCheckBox"
#include <QMainWindow>
#include <QModelIndexList>
#include <QPushButton>
#include "EventResult.h"
#include <vector>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
    /*****friend*****/
    friend class Room;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:

    void printMap();

    void on_gonorth_clicked();

    void on_goeast_clicked();

    void on_gosouth_clicked();

    void on_gowest_clicked();

    void on_teleport_clicked();

    void on_pushButton_clicked();
    void on_won();
    void on_lost();

    void on_PickItem_clicked();

    void on_Use1_clicked();

    void on_Use2_clicked();

    void on_Use3_clicked();

    //void print_Help();
    void on_Attack_clicked();
    void print_original_Map();
    void on_Help_clicked();

    void on_BossAttack_clicked();

private:

    int ghost=1;

    int a1=0,b1=0,c1=0,d1=0,e1=0,f1=0,g1=0,h1=0,i1=0,e2=0,b2=0,h2=0;
    int MfightCapabel=80;
    int Mhealth=100;
    Room *a, *b, *c, *d, *e, *f, *g,  *h, *i,*boss,*goal;
    Ui::MainWindow *ui;
    Parser parser;
    Room *currentRoom;
    Room *pre_currentRoom;
    Room *checkRoom;
    vector <string> bag;
    //Character *character;
    void addItems(string Item);
    void createRooms();
    void printWelcome();
    bool processCommand(Command command);
    void goRoom(Command command);
    void createItems();
    void displayItems();
    void DisableButtons();
    void giveHealth(int health);
    void giveStamina(int stamina);
    void givefightCapabel(int fightCapabel);
    void giveBossHealth(int health);
    void offButtoms();
    void offCheckButtom();
    void openButtoms();
    void reStart();
    void checkRoomItem();
    void checkStamina();
    void setCheckBox();
    void how_to_printHelp(MainWindow* p){
        p->print_Help();
    }
public:
    EventResult event;
    double gamewin=0.5;
    double gamelose=0.5;
    void play();
    string go(string direction);
    /*****templete*****/
    template<typename T> void Tswap(T& t1, T& t2);
/*****abstract class and pure virtual function*****/
public:
    //virtual void result()=0;
/******virtual function & polymorphism*****/
public:
    virtual void print_Help(){
        QMessageBox::information(NULL, "Help Information", "There is a Ghost and it will track you all the time!\n"
                                                           "It will attack you when you move to a room!\n"
                                                           "The Ghost will stay infront of the BossRoom when you get in the BossRoom\n"
                                                           "When you stay in same room with Ghost,you can kill it.\n");
    }
};


#endif // MAINWINDOW_H
