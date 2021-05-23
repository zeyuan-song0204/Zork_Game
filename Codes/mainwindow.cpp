/**
*projectName FinalProject
*author  Zeyuan Song
*studentID 19096216
*Date 12/05/2020
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QModelIndexList>
#include <ui_mainwindow.h>
#include "QProgressBar"
#include "QCheckBox"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    print_original_Map();
    createRooms();
    printWelcome();
    printMap();
    giveHealth(event.health);
    giveStamina(event.stamina);
    givefightCapabel(event.fightCapable);
    setCheckBox();
    connect(&event,SIGNAL(won()),this,SLOT(on_won()));
    connect(&event,SIGNAL(lost()),this,SLOT(on_lost()));
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::giveHealth(int health){
    ui->healthBar->setValue(health);
}
void MainWindow::giveStamina(int stamina){
    ui->staminaBar->setValue(stamina);
}
void MainWindow::givefightCapabel(int fightCapabel){
    ui->fightCapacity->setValue(fightCapabel);
}
void MainWindow::giveBossHealth(int health){
    ui->Boss_health->setValue(health);
}
void MainWindow::createRooms()  {


    a = new Room("a");
        a->addItem(new Item("Weapon"));//fightCapabel+50
    b = new Room("b");
        b->addItem(new Item("Water"));//health+10
    c = new Room("c");
        //c->addItem(new Item(""));//
    d = new Room("d");
        d->addItem(new Item("Helmet"));//fightCapabel+10
    e = new Room("e");
        e->addItem(new Item("First-Aid Packet"));//health+50
    f = new Room("f");
        f->addItem(new Item("Shield"));//fightCapabel+10
    g = new Room("g");
        g->addItem(new Item("Shose"));//+5 half expend on stamina
    h = new Room("h");
        h->addItem(new Item("Bread"));//health+20
    i = new Room("i");
        i->addItem(new Item("Key"));//key for the goalDoor
    boss = new Room("boss");

    goal=new Room("Goal");


//             (N, E, S, W)
    a->setExits(f, b, d, c);
    b->setExits(NULL, boss, NULL, a);
    c->setExits(NULL, a, NULL, NULL);
    d->setExits(a, e, NULL, i);
    e->setExits(NULL, NULL, NULL, d);
    f->setExits(NULL, g, a, h);
    g->setExits(NULL, NULL, NULL, f);
    h->setExits(NULL, f, NULL, NULL);
    i->setExits(NULL, d, NULL, NULL);
    boss->setExits(NULL,goal,NULL,b);

        currentRoom = a;
}

/**
 *  Main play routine.  Loops until end of play.
 */
/*void MainWindow::print_Help(){
    QMessageBox::information(NULL, "Help Information", "There is a Ghost and it will track you all the time!\n"
                                                       "It will attack you when you move to a room!\n"
                                                       "The Ghost will stay infront of the BossRoom when you get in the BossRoom\n"
                                                       "When you stay in same room with Ghost,you can kill it.\n");
}*/
void MainWindow::play() {
    printWelcome();
    //createRooms();
    // Enter the main command loop.  Here we repeatedly read commands and
    // execute them until the ZorkUL game is over.

    bool finished = false;
    while (!finished) {
        // Create pointer to command and give it a command.
        Command* command = parser.getCommand();
        // Pass dereferenced command and check for end of game.
        finished = processCommand(*command);
        // Free the memory allocated by "parser.getCommand()"
        //   with ("return new Command(...)")
        delete command;
    }
    ui->show->setText(QString::fromStdString("\nend\n"));
    //cout << endl;
   // cout << "end" << endl;
}

void MainWindow::printWelcome() {

    ui->show->append(QString::fromStdString("Reach the Goal room\n" + currentRoom->longDescription()+"\n"));
    ui->Attack->setEnabled(false);
    ui->BossAttack->setEnabled(false);
    ui->Use1->setDisabled(true);
    ui->Use2->setDisabled(true);
    ui->Use3->setDisabled(true);
    ui->Ghost_health->setValue(100);
    ui->Boss_health->setValue(Mhealth);

}
bool MainWindow::processCommand(Command command) {
    if (command.isUnknown()) {
        ui->show->append(QString::fromStdString("invalid input\n"));
        //cout << "invalid input"<< endl;
        return false;
    }

    string commandWord = command.getCommandWord();
    if (commandWord.compare("info") == 0)
    {

    }
        //printHelp();

    else if (commandWord.compare("map") == 0)
        {
        ui->map->append(QString::fromStdString("h --- f --- g\n"
                                               "      |         \n"
                                               "      |         \n"
                                               "c --- a --- b --- !Boss!---[Goal]\n"
                                               "      |         \n"
                                               "      |         \n"
                                               "i --- d --- e"));
        }
    return false;
}
/** COMMANDS **/

string MainWindow::go(string direction) {
    //Make the direction lowercase
    //transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
    //Move to the next room

    Room* nextRoom = currentRoom->nextRoom(direction);

    if(direction == "random"){
        pre_currentRoom=c;
        //mainwindow.on_pushButton_6_clicked();
        srand( (unsigned)time( NULL ) );
        int x=(rand()%10-1+1)+1;
        switch(x){
            case 1:
                currentRoom=a;
                break;
            case 2:
                currentRoom=b;
                break;
            case 3:
                currentRoom=c;
                break;
            case 4:
                 currentRoom=d;
                 break;
            case 5:
                 currentRoom=e;
                 break;
            case 6:
                currentRoom=f;
                break;
            case 7:
                currentRoom=g;
                break;
            case 8:
                currentRoom=h;
                break;
            case 9:
                currentRoom=i;
                break;

        }
        ui->show->append((currentRoom->longDescription()+"\n").c_str());
        printMap();
    }
    else if(nextRoom == NULL){
        return("direction null");
    }
    else
    {
        pre_currentRoom=currentRoom;
        currentRoom = nextRoom;
        if(currentRoom!=boss&&currentRoom!=goal){
            ui->show->append(QString::fromStdString(currentRoom->longDescription()+"\n"));
            printMap();
        }else if(currentRoom==boss){
            printMap();


            /*if(Mhealth-event.fightCapable<0){
                Mhealth=0;
            }else{
                Mhealth=Mhealth-event.fightCapable;
            }*/
            if(Mhealth!=0){
                ui->BossAttack->setEnabled(true);
                QString a = QString::number(MfightCapabel);
                QString b = QString::number(Mhealth);
                ui->show->append("Monster is here!!\n"
                                 "        fightCapabel="+a+"\n"
                                 "        Health="+b+"\n"
                                 "You can fight or escape!!!\n");
            }

            //giveHealth(event.health);
           // event.ResultJudge();
        }
        else if(currentRoom==goal){
            //event.flag=2;
            //use function template
            swap<int>(event.win,event.flag);
            event.ResultJudge();
        }

    }
    return currentRoom->longDescription();

}
void MainWindow::on_BossAttack_clicked()
{

        Mhealth=Mhealth-event.fightCapable+10;
        if(Mhealth<0){
            Mhealth=0;
        }
        int x=event.fightCapable-MfightCapabel;
        if(x<0){
            event.health=event.health+x;
        }else if(x>=0){
            event.health=event.health-x;
        }
        if(event.health<0){
            event.health=0;
        }


    if(Mhealth==0){
        ui->BossAttack->setEnabled(false);
    }else{
        ui->BossAttack->setEnabled(true);
    }
    if(Mhealth!=0){
        ui->show->append("You attacked the Monster!!!\n");
    }else{
        ui->show->append("Monster is dead!!\nNow you need find the KEY to open the door of Goal\n");
    }

    giveHealth(event.health);
    giveBossHealth(Mhealth);

    event.ResultJudge();
}
void MainWindow::openButtoms(){
    ui->goeast->setDisabled(false);
    ui->gowest->setDisabled(false);
    ui->gonorth->setDisabled(false);
    ui->gosouth->setDisabled(false);
    ui->teleport->setDisabled(false);
}
void MainWindow::offButtoms(){
    Room* nextRoomNorth = currentRoom->nextRoom("north");
    if(nextRoomNorth==NULL){
        ui->gonorth->setDisabled(true);
    }else{
        ui->gonorth->setDisabled(false);
    }
    Room* nextRoomSouth = currentRoom->nextRoom("south");
    if(nextRoomSouth==NULL){
        ui->gosouth->setDisabled(true);
    }else{
        ui->gosouth->setDisabled(false);
    }
    Room* nextRoomEast = currentRoom->nextRoom("east");
    if(nextRoomEast==NULL){
        ui->goeast->setDisabled(true);
    }else{
        if(nextRoomEast==goal&&(Mhealth!=0||i1!=1)){
            ui->goeast->setDisabled(true);
        }else{
            ui->goeast->setDisabled(false);
        }
    }
    Room* nextRoomWest = currentRoom->nextRoom("west");
    if(nextRoomWest==NULL){
        ui->gowest->setDisabled(true);
    }else{
        ui->gowest->setDisabled(false);
    }
}
void MainWindow::offCheckButtom(){
    ui->Weapon->setChecked(false);
    ui->Water->setChecked(false);
    ui->Helmet->setChecked(false);
    ui->Shose->setChecked(false);
    ui->Firstaid->setChecked(false);
    ui->Bread->setChecked(false);
    ui->Shield->setChecked(false);
    ui->Key->setChecked(false);
    ui->Attack->setEnabled(false);
    ui->BossAttack->setEnabled(false);
}
void MainWindow::on_won(){
    ui->show->append("Congratulations You Win!!");
    ui->Use1->setDisabled(true);
    ui->Use2->setDisabled(true);
    ui->Use3->setDisabled(true);
}
void MainWindow::on_lost(){
    ui->show->append("Unfortunately You Lost!!");
    ui->Use1->setDisabled(true);
    ui->Use2->setDisabled(true);
    ui->Use3->setDisabled(true);
}
void MainWindow::checkStamina(){
    if(event.stamina<0){
        event.stamina=0;
        giveStamina(event.stamina);
        event.ResultJudge();
    }
}
void MainWindow::on_gonorth_clicked()
{
    event.ResultJudge();
    if(event.flag==1){
        go("north");
        if(g1==1){
            event.stamina=event.stamina-2;
            checkStamina();
        }else if(g1==0){
            event.stamina=event.stamina-4;
            checkStamina();
        }
        if(ghost==1){
            event.health=event.health-5;
        }
        giveHealth(event.health);
        giveStamina(event.stamina);
        offButtoms();
    }


}

void MainWindow::on_goeast_clicked()
{
    event.ResultJudge();
    if(event.flag==1){
        go("east");
        if(g1==1){
            event.stamina=event.stamina-2;
            checkStamina();
        }else if(g1==0){
            event.stamina=event.stamina-4;
            checkStamina();
        }
        if(ghost==1){
            event.health=event.health-5;
        }
        giveHealth(event.health);
        giveStamina(event.stamina);
        offButtoms();
    }

}

void MainWindow::on_gosouth_clicked()
{
    event.ResultJudge();
    if(event.flag==1){
        go("south");
        if(g1==1){
            event.stamina=event.stamina-2;
            checkStamina();
        }else if(g1==0){
            event.stamina=event.stamina-4;
            checkStamina();
        }
        if(ghost==1){
            event.health=event.health-5;
        }
        giveHealth(event.health);
        giveStamina(event.stamina);
        offButtoms();
    }

}

void MainWindow::on_gowest_clicked()
{
    event.ResultJudge();
    if(event.flag==1){
        go("west");
        if(g1==1){
            event.stamina=event.stamina-2;
            checkStamina();
        }else if(g1==0){
            event.stamina=event.stamina-4;
            checkStamina();
        }
        if(ghost==1){
            event.health=event.health-5;
        }
        giveHealth(event.health);
        giveStamina(event.stamina);
        offButtoms();
        ui->BossAttack->setEnabled(false);
        event.ResultJudge();
    }

}

void MainWindow::on_teleport_clicked()
{
    event.ResultJudge();
    if(event.flag==1){
        go("random");
        if(g1==1){
            event.stamina=event.stamina-8;
            checkStamina();
        }else if(g1==0){
            event.stamina=event.stamina-16;
            checkStamina();
        }
        if(ghost==1){
            event.health=event.health-5;
        }
        giveHealth(event.health);
        giveStamina(event.stamina);
        offButtoms();
    }
}


void MainWindow::on_pushButton_clicked()
{
    reStart();
}
void MainWindow::addItems(string item){
    bag.push_back(item);
}
void MainWindow::checkRoomItem(){
    if(a1==1)
        ui->Weapon->setChecked(true);
    if(b1==1){
        ui->Water->setChecked(true);
        if(b2==1){
            ui->Use2->setDisabled(false);
        }else{
            b2=0;
        }
    }
    if(d1==1)
        ui->Helmet->setChecked(true);
    if(e1==1){
        ui->Firstaid->setChecked(true);
        if(e2==1){
            ui->Use1->setDisabled(false);
        }else{
            e2=0;
        }
    }
    if(f1==1)
        ui->Shield->setChecked(true);
    if(g1==1)
        ui->Shose->setChecked(true);
    if(h1==1){
        ui->Bread->setChecked(true);
        if(h2==1){
            ui->Use3->setDisabled(false);
        }else{
            h2=0;
        }
    }
    if(i1==1)
    {
        ui->Key->setChecked(true);
    }

}

void MainWindow::on_PickItem_clicked()
{
    string item=currentRoom->roomItems();
    if(item!=""){
        addItems(item);

        if(item=="Weapon"){
            a1=1;
            currentRoom->deleteItem(0);
            event.fightCapable+=50;
            givefightCapabel(event.fightCapable);
        }else if(item=="Water"){
            b1=1;
            b2=1;
            currentRoom->deleteItem(1);
        }else if(item=="Helmet"){
            d1=1;
            currentRoom->deleteItem(2);
            event.fightCapable+=10;
            givefightCapabel(event.fightCapable);
        }else if(item=="First-Aid Packet"){
            e1=1;
            e2=1;
            currentRoom->deleteItem(3);
        }else if(item=="Shield"){
            f1=1;
            currentRoom->deleteItem(4);
            event.fightCapable+=15;
            givefightCapabel(event.fightCapable);
        }else if(item=="Shose")
        {
            g1=1;
            currentRoom->deleteItem(5);
            event.fightCapable+=10;
            givefightCapabel(event.fightCapable);
        }else if(item=="Bread"){
            h1=1;
            h2=1;
            currentRoom->deleteItem(6);
        }else if(item=="Key"){
            i1=1;
            currentRoom->deleteItem(7);
        }

    }else if(event.flag==1){
        ui->show->append("Sorry!There is no any item in this room,please go anothers");
    }else if(event.flag==2){
        ui->show->append("Congratulations You Win!!");
    }else if(event.flag==0){
        ui->show->append("Unfortunately You Lost!!");
    }
    checkRoomItem();

}


void MainWindow::on_Use1_clicked()
{
    if((event.health+50)>=100){
        event.health=100;
    }else{
        event.health+=50;
    }
    giveHealth(event.health);
    ui->Firstaid->setChecked(false);
    e2=0;
    e1=0;
    ui->Use1->setDisabled(true);
}

void MainWindow::on_Use2_clicked()
{
    if((event.stamina+10)>=100){
        event.stamina=100;
    }else{
        event.stamina+=10;
    }
    giveStamina(event.stamina);
    ui->Water->setChecked(false);
    b2=0;
    b1=0;
    ui->Use2->setDisabled(true);
}
void MainWindow::on_Use3_clicked()
{
    if((event.health+20)>=100){
        event.health=100;
    }else{
        event.health+=20;
    }
    giveHealth(event.health);
    ui->Bread->setChecked(false);
    h2=0;
    h1=0;
    ui->Use3->setDisabled(true);
}
void MainWindow::setCheckBox(){
    ui->Helmet->setEnabled(false);
    ui->Weapon->setEnabled(false);
    ui->Water->setEnabled(false);
    ui->Firstaid->setEnabled(false);
    ui->Bread->setEnabled(false);
    ui->Shield->setEnabled(false);
    ui->Shose->setEnabled(false);
    ui->Key->setEnabled(false);
}

void MainWindow::reStart(){
    ui->show->setText(" ");
    event.stamina=100;
    event.health=100;
    event.fightCapable=1;
    Mhealth=100;
    ghost=1;
    createRooms();
    printWelcome();
    print_original_Map();
    giveHealth(event.health);
    giveStamina(event.stamina);
    givefightCapabel(event.fightCapable);
    openButtoms();
    offCheckButtom();
    a1=0,b1=0,c1=0,d1=0,e1=0,f1=0,g1=0,h1=0,i1=0,e2=0,b2=0,h2=0;
    event.flag=1;
}





void MainWindow::on_Attack_clicked()
{
    ui->Ghost_health->setValue(0);
    ghost=0;
    ui->show->append("You attacked the Ghost!\nGhost is dead!!\n"
                     "You are no longer be attacked by ghost while moving to a room!");
    ui->Attack->setEnabled(false);
}
void MainWindow::print_original_Map(){
    ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                            "      |         \n"
                                            "      |         \n"
                                            "!c!---[a]---b --- !Boss!---Goal\n"
                                            "      |         \n"
                                            "      |         \n"
                                            "i --- d --- e"));
}

void MainWindow::printMap(){
    if(ghost==1){
        if(currentRoom==a){
            if(pre_currentRoom==f){
                ui->map->setText(QString::fromStdString("h ---!f! --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "c --- [a] --- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i --- d --- e"));
            }
            if(pre_currentRoom==c){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "!c!---[a] --- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i --- d --- e"));
            }
            if(pre_currentRoom==d){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "c --- [a] --- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i ---!d!--- e"));
            }
            if(pre_currentRoom==b){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "c --- [a] ---!b!--- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i --- d --- e"));
            }

        }
        if(currentRoom==b){
            if(pre_currentRoom==a){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "c ---!a!--- [b] --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i --- d --- e"));
            }
            if(pre_currentRoom==boss){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "c --- a ---![b]!--- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i --- d --- e"));
                if(ghost==1){
                    ui->Attack->setEnabled(true);
                }else{
                    ui->Attack->setEnabled(false);
                }
            }
            if(pre_currentRoom==c){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "!c!---a ---[b] --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i --- d --- e"));
            }

        }
        if(currentRoom==c){
            if(pre_currentRoom==a){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "[c]---!a!--- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i --- d --- e"));
            }
            if(pre_currentRoom==c){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "![c]!---a --- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i --- d --- e"));
            }

        }
        if(currentRoom==d){
            if(pre_currentRoom==a){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "c--- !a!--- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i ---[d]--- e"));
            }
            if(pre_currentRoom==i){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "c --- a --- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "!i!---[d]---e"));
            }
            if(pre_currentRoom==e){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "c --- a --- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i--- [d]---!e!"));
            }
            if(pre_currentRoom==c){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "!c!---a --- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i ---[d]--- e"));
            }

        }
        if(currentRoom==e){
            if(pre_currentRoom==d){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "c --- a --- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i ---!d!---[e]"));
            }
            if(pre_currentRoom==c){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "!c!---a --- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i --- d ---[e]"));
            }

        }
        if(currentRoom==f){
            if(pre_currentRoom==a){
                ui->map->setText(QString::fromStdString("h ---[f] --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "c ---!a!--- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i --- d --- e "));
            }
            if(pre_currentRoom==h){
                ui->map->setText(QString::fromStdString("!h!--[f] --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "c --- a --- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i --- d --- e "));
            }
            if(pre_currentRoom==g){
                ui->map->setText(QString::fromStdString("h ---[f] ---!g!\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "c ---!a!--- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i --- d --- e "));
            }
            if(pre_currentRoom==c){
                ui->map->setText(QString::fromStdString("h ---[f]--- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "!c!---a --- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i --- d --- e"));
            }
        }
        if(currentRoom==g){
            if(pre_currentRoom==f){
                ui->map->setText(QString::fromStdString("h ---!f!--- [g]\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "c --- a --- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i --- d --- e"));
            }
            if(pre_currentRoom==c){
                ui->map->setText(QString::fromStdString("h --- f ---[g]\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "!c!---a --- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i --- d --- e"));
            }

        }
        if(currentRoom==h){
            if(pre_currentRoom==f){
                ui->map->setText(QString::fromStdString("[h]---!f!--- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "c --- a --- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i --- d --- e"));
            }
            if(pre_currentRoom==c){
                ui->map->setText(QString::fromStdString("[h]--- f --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "!c!---a --- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "i --- d --- e"));
            }

        }
        if(currentRoom==i){
            if(pre_currentRoom==d){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "c --- a --- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "[i]---!d!---e"));
            }
            if(pre_currentRoom==c){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "!c!---a --- b --- !Boss!---Goal\n"
                                                        "      |         \n"
                                                        "      |         \n"
                                                        "[i]--- d --- e"));
            }

        }
        if(currentRoom==boss){
            if(pre_currentRoom==b){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                       "      |         \n"
                                                       "      |         \n"
                                                       "c --- a ---!b!--- ![Boss]!---Goal\n"
                                                       "      |         \n"
                                                       "      |         \n"
                                                       "i --- d --- e"));
            }

        }
        if(currentRoom==goal){
            ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "c --- a ---!b!--- !Boss!---[Goal]\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "i --- d --- e"));
        }
    }else if(ghost==0){
        if(currentRoom==a){
            ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "c---[a]---b --- !Boss!---Goal\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "i --- d --- e"));
        }
        if(currentRoom==b){
            ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "c --- a --- [b] --- !Boss!---Goal\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "i --- d --- e"));
        }
        if(currentRoom==c){
            ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "[c]---a---b --- !Boss!---Goal\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "i --- d --- e"));
        }
        if(currentRoom==d){
            ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "c --- a---b --- !Boss!---Goal\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "i ---[d]--- e"));
        }
        if(currentRoom==e){
            ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "c --- a ---b --- !Boss!---Goal\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "i --- d ---[e]"));
        }
        if(currentRoom==f){
            ui->map->setText(QString::fromStdString("h ---[f]--- g\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "c --- a ---b --- !Boss!---Goal\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "i --- d --- e"));
        }
        if(currentRoom==g){
            ui->map->setText(QString::fromStdString("h --- f ---[g]\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "c --- a ---b --- !Boss!---Goal\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "i --- d --- e"));
        }
        if(currentRoom==h){
            ui->map->setText(QString::fromStdString("[h]--- f --- g\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "c --- a ---b --- !Boss!---Goal\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "i --- d --- e"));
        }
        if(currentRoom==i){
            ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "c --- a ---b --- !Boss!---Goal\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "[i]--- d --- e"));
        }
        if(currentRoom==boss){
                ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                       "      |         \n"
                                                       "      |         \n"
                                                       "c --- a --- b --- ![Boss]!---Goal\n"
                                                       "      |         \n"
                                                       "      |         \n"
                                                       "i --- d --- e"));
        }
        if(currentRoom==goal){
            ui->map->setText(QString::fromStdString("h --- f --- g\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "c --- a --- b --- !Boss!---[Goal]\n"
                                                    "      |         \n"
                                                    "      |         \n"
                                                    "i --- d --- e"));
        }
    }



    //Command command("map","");
    //processCommand(command);
}
/*****Inheritance*****/
class child: public MainWindow{
    public:
        //Initializer list
        int a=event.flag;
        child():a(1){}
        void print_help(){
            QMessageBox::information(NULL, "Help Information", "You won!!!\n");
        }
};
void MainWindow::on_Help_clicked()
{
    QMessageBox::about(NULL, "Prompt", "<font color='red'>Ghost</font> will follow you all the time and cost your <font color='red'>5% Health</font> for each step.\n"
                                        "You need to kill it(when the 'attack' buttom alive) befor you win. ");
}
/******operator overloading****/
MainWindow operator*(const MainWindow& m){
    MainWindow win;
    //win.gamewin=this->gamewin*m.gamewin;
    //return win;
}
/******templete*****/
template<typename  T> void Tswap(T& t1, T& t2) {
    T tmpT;
    tmpT = t1;
    t1 = t2;
    t2 = tmpT;
}
