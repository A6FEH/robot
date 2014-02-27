#ifndef FEHDRIVETRAINA6_H
#define FEHDRIVETRAINA6_H

#include <FEHMotor.h>
#include <FEHWONKA.h>

/*Should include
*overloaded drive function
*stopping
*swing and pivot turns
*/
class FEHDriveTrainA6
{
public:

FEHDriveTrainA6(FEHMotor *left, FEHMotor *right);
FEHDriveTrainA6(FEHMotor *left, FEHMotor *right, FEHWONKA *rps);

void stop();

void drive(int power);
//void driveDistance(int distance); 
void drive(int power, int time);
void drive(int power, float time);
void drive(float distance); 

void swingTurnAboutLeft();
void swingTurnAboutLeft(int angle);
void swingTurnAboutRight();
void swingTurnAboutRight(int angle);
//void swingTurnAboutRightToDirection(int direction); //0=N, 1=E,2=S,3=W
void swingTurnAboutLeftToDirection(int direction);

void pivotTurn(float angle);

void pivotTurnLeft(int power);
void pivotTurnRight(int power);

void pivotTurn(int power, float angle);
void pivotTurn(float angle, int power);

void pivotTurn(int power, int direction); 

/*Temporary method*/
void pivotIncrement();
void pivotIncrementSmall();
float getSwing();
float getPivot();
/*End temp*/

private:

FEHMotor *_left; FEHMotor *_right; FEHWONKA *_rps;

void swingTurnAboutLeftIndefinite(int power);
void swingTurnAboutRightIndefinite(int power);

void pivotTurnIndefinite(int power);

float swingTime; float pivotTime;

};
#endif
