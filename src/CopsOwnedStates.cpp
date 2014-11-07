/************************************************************************
 Program: bank-heist
 Author: Randall D. Rowland Jr.
 Class: CopsOwnedStates.cpp
 Instructor:
 Date: Nov 1, 2014
 Description:
 Input:
 Output:
 Compilation instructions:
 Usage:
 Known bugs/missing features:

 This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 International Public License. To view a copy of this license, visit
 https://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative
 Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.

 Modifications:
 Date                Comment
 ----    ------------------------------------------------
7NOV14	 Corrected CopsGlobalState to use ChaseRobber.
 ************************************************************************/

#include "CopsOwnedStates.h"
#include "RobberOwnedStates.h"
#include "Cops.h"
#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//-----------------------------------------------------------------------Global state

CopsGlobalState* CopsGlobalState::Instance()
{
  static CopsGlobalState instance;

  return &instance;
}


void CopsGlobalState::Execute(Cops* cop)
{
  //1 in 10 chance of needing to do this
  if ( (RandFloat() < 0.1) &&
       !cop->GetFSM()->isInState(*ChaseRobber::Instance()) )
  {
    cop->GetFSM()->ChangeState(ChaseRobber::Instance());
  }
}

bool CopsGlobalState::OnMessage(Cops* cop, const Telegram& msg)
{
  SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

  switch(msg.Msg)
  {
  case Msg_ThisIsAStickUp:
   {
       cout << "\nMessage handled by " << GetNameOfEntity(cop->ID()) << " at time: "
       << Clock->GetCurrentTime();

     SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(cop->ID()) <<
          ": There's a robbery in progress!";

     cop->GetFSM()->ChangeState(ChaseRobber::Instance());
   }

   return true;

  }//end switch

  return false;
}

//-------------------------------------------------------------------------ChaseRobber

ChaseRobber* ChaseRobber::Instance()
{
  static ChaseRobber instance;

  return &instance;
}


void ChaseRobber::Enter(Cops* cop)
{
  cout << "\n" << GetNameOfEntity(cop->ID()) << ": Let's catch this robber!";
}


void ChaseRobber::Execute(Cops* cop)
{
  switch(RandInt(0,2))
  {
  case 0:

    cout << "\n" << GetNameOfEntity(cop->ID()) << ": Which bank is he robbing?";

    break;

  case 1:

    cout << "\n" << GetNameOfEntity(cop->ID()) << ": This could be a high speed pursuit.";

    break;

  case 2:

    cout << "\n" << GetNameOfEntity(cop->ID()) << ": Call for backup!";

    break;
  }
}

void ChaseRobber::Exit(Cops* cop)
{
}

bool ChaseRobber::OnMessage(Cops* cop, const Telegram& msg)
{
  return false;
}

//------------------------------------------------------------------------CaughtRobber

CaughtRobber* CaughtRobber::Instance()
{
  static CaughtRobber instance;

  return &instance;
}


void CaughtRobber::Enter(Cops* cop)
{
  cout << "\n" << GetNameOfEntity(cop->ID()) << ": WE CAUGHT HIM!";
}


void CaughtRobber::Execute(Cops* cop)
{
  cout << "\n" << GetNameOfEntity(cop->ID()) << ": You're sentenced to life in prison!";

  cop->GetFSM()->RevertToPreviousState();
}

void CaughtRobber::Exit(Cops* cop)
{
  cout << "\n" << GetNameOfEntity(cop->ID()) << ": You're never robbing banks again! GAME OVER";
}


bool CaughtRobber::OnMessage(Cops* cop, const Telegram& msg)
{
  return false;
}
