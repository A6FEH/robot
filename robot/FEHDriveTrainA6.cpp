#include <FEHMotor.h>
#include "FEHDriveTrainA6.h"
#include <FEHUtility.h>
#include <cmath>

float swingTime; float pivotTime;

FEHDriveTrainA6::FEHDriveTrainA6(FEHMotor *left, FEHMotor *right)
{
_left = left;
_right = right;
_rps=(FEHWONKA*)0;
swingTime=.76;
pivotTime=.426;
}

FEHDriveTrainA6::FEHDriveTrainA6(FEHMotor *left, FEHMotor *right, FEHWONKA *rps)
{
_left = left;
_right = right;
_rps = rps;
}

/*Temporary methods to determine pivot and swing times.*/

void FEHDriveTrainA6::pivotIncrement()
{
pivotTime+=.1;
}

void FEHDriveTrainA6::pivotIncrementSmall()
{
pivotTime+=.01;
}

float FEHDriveTrainA6::getSwing()
{
return swingTime;
}

float FEHDriveTrainA6::getPivot()
{
return pivotTime;
}

/*End temporary methods*/

/*Stops both motors*/
void FEHDriveTrainA6::stop()
{
_left->SetPercent(0);
_right->SetPercent(0);
}

void FEHDriveTrainA6::drive(int power)
{
_left->SetPercent(power);
_right->SetPercent(power);
}

void FEHDriveTrainA6::drive(int power, int time)
{
drive(power);
Sleep(time);
stop();
}

void FEHDriveTrainA6::drive(int power, float time)
{
drive(power);
Sleep(time);
stop();
}

void FEHDriveTrainA6::drive(float distance) 
{
    float currentX = _rps->X();
    float currentY = _rps->Y();
    while(_rps->distanceTo(currentX,currentY)>10)
    {
        drive(80);
    }
    while(_rps->distanceTo(currentX,currentY)>0)
    {
        drive(20);
    }
    stop();
}

/*Swing turn methods*/
void FEHDriveTrainA6::swingTurnAboutLeftIndefinite(int power)
{
_left->SetPercent(0);
_right->SetPercent(power);
}
void FEHDriveTrainA6::swingTurnAboutRightIndefinite(int power)
{
_right->SetPercent(0);
_left->SetPercent(power);
}

void FEHDriveTrainA6::swingTurnAboutLeft() /*Non-rps version*/
{
swingTurnAboutLeftIndefinite(100);
Sleep(swingTime);
stop();
}

void FEHDriveTrainA6::swingTurnAboutRight() /*Non-rps version*/
{
swingTurnAboutRightIndefinite(100);
Sleep(swingTime);
stop();
}

void FEHDriveTrainA6::swingTurnAboutLeft(int angle)
{
swingTurnAboutRightIndefinite(50);
Sleep(swingTime*(angle/90.0));
stop();
}

void FEHDriveTrainA6::swingTurnAboutRight(int angle)
{
swingTurnAboutRightIndefinite(50);
Sleep(swingTime*(angle/90.0));
stop();
}

/*void FEHDriveTrainA6::swingTurnAboutRightToDirection(int direction)
{

}*/

void FEHDriveTrainA6::swingTurnAboutLeftToDirection(int direction) 
{
    float currentHeading= _rps->Heading();
    if((currentHeading>direction&&currentHeading-direction>180)||(currentHeading<direction&&direction-currentHeading<180))
    {
        swingTurnAboutLeftIndefinite(70);
        while(std::abs(_rps->Heading()-direction)>5);
        stop();
    }
    else
    {
        swingTurnAboutRightIndefinite(70);
        while(std::abs(_rps->Heading()-direction)>5);
        stop();
    }
}

/*Pivot turn methods*/
void FEHDriveTrainA6::pivotTurnIndefinite(int power)
{
_left->SetPercent(power);
_right->SetPercent(power*-1);
}

void FEHDriveTrainA6::pivotTurnRight(int power)
{
pivotTurnIndefinite(power);
Sleep(pivotTime*(100.0/power));
stop();
}

void FEHDriveTrainA6::pivotTurnLeft(int power)
{
pivotTurnIndefinite(power*-1);
Sleep(pivotTime*(100.0/power));
stop();
}

void FEHDriveTrainA6::pivotTurn(float angle)
{
int power=100;
if(angle<0) {angle=angle*-1; power=power*-1;}
pivotTurnIndefinite(power);
Sleep(pivotTime*(angle/90.0));
stop();
}

void FEHDriveTrainA6::pivotTurn(int power, float angle)
{
pivotTurnIndefinite(power);
Sleep(pivotTime*(angle/90.0)*(100.0/power));
stop();
}

void FEHDriveTrainA6::pivotTurn(float angle, int power)
{
pivotTurnIndefinite(power);
Sleep(pivotTime*(angle/90.0)*(100.0/power));
stop();
}

void FEHDriveTrainA6::pivotTurn(int power, int direction) /*Don't even ask about this logic.*/
{
    float currentHeading = _rps->Heading();
    if(currentHeading<180&&direction>currentHeading+180)
        pivotTurn((float)(360-direction+currentHeading), power);
    else if(currentHeading<180&&direction<currentHeading+180)
        pivotTurn((-1)*(float)(direction-currentHeading),power);

    else if(currentHeading>180&&direction<currentHeading-180)
        pivotTurn((float)((-1)*(360.0-currentHeading+direction)),power);
    else if(currentHeading>180&&direction>currentHeading-180)
        pivotTurn((float)(currentHeading-direction),power);

    else if(currentHeading<180&&direction==currentHeading+180)
        pivotTurn((float)180.0,power);
    else if(currentHeading>180&&direction==currentHeading-180)
        pivotTurn((float)180.0,power);

}
