/**
*projectName FinalProject
*author  Zeyuan Song
*studentID 19096216
*Date 12/05/2020
*/
#include "EventResult.h"

EventResult::EventResult(QObject *parent) : QObject(parent)
{

}
void EventResult::ResultJudge(){
    if(stamina==0||health==0){
        flag=0;
        emit this->lost();
    }/*else if(flag==1){

    }*/else if(flag==2){
        emit won();
        //flag=2;

    }

}
