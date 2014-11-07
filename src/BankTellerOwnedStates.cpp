/************************************************************************
 Program: bank-heist
 Author: Randall D. Rowland Jr.
 Class: BankTellerOwnedStates.cpp
 Instructor:
 Date: Nov 6, 2014
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
7NOV14	 Corrected Tellers output text.
 ************************************************************************/

#include "BankTeller.h"
#include "BankTellerOwnedStates.h"
#include "RobberOwnedStates.h"
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

BankTellerGlobalState* BankTellerGlobalState::Instance()
{
  static BankTellerGlobalState instance;

  return &instance;
}


void BankTellerGlobalState::Execute(BankTeller* teller)
{
  //1 in 10 chance of needing to do this
  //if ( (RandFloat() < 0.1) &&
       //!teller->GetFSM()->isInState(*BankTellerState::Instance()) )
  //{
    //teller->GetFSM()->ChangeState(BankTellerState::Instance());
  //}
}

bool BankTellerGlobalState::OnMessage(BankTeller* teller, const Telegram& msg)
{
  SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

  switch(msg.Msg)
  {
  case Msg_ThisIsAStickUp:
   {
       cout << "\nMessage handled by " << GetNameOfEntity(teller->ID()) << " at time: "
       << Clock->GetCurrentTime();

     SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(teller->ID()) <<
          ": We're getting robbed!";

     teller->GetFSM()->ChangeState(GettingRobbed::Instance());
   }

   return true;

  }//end switch

  return false;
}

//-------------------------------------------------------------------------BankTellerDoingBankThings

BankTellerDoingBankThings* BankTellerDoingBankThings::Instance()
{
  static BankTellerDoingBankThings instance;

  return &instance;
}


void BankTellerDoingBankThings::Enter(BankTeller* teller)
{
  cout << "\n" << GetNameOfEntity(teller->ID()) << ": Money! Money! Money!";
}


void BankTellerDoingBankThings::Execute(BankTeller* teller)
{
  switch(RandInt(0,2))
  {
  case 0:

    cout << "\n" << GetNameOfEntity(teller->ID()) << ": Let me deposit this check.";

    break;

  case 1:

    cout << "\n" << GetNameOfEntity(teller->ID()) << ": I need to refill my cash drawer.";

    break;

  case 2:

    cout << "\n" << GetNameOfEntity(teller->ID()) << ": Next in line please!";

    break;
  }
}

void BankTellerDoingBankThings::Exit(BankTeller* teller)
{
}

bool BankTellerDoingBankThings::OnMessage(BankTeller* teller, const Telegram& msg)
{
  return false;
}

//------------------------------------------------------------------------GettingRobbed

GettingRobbed* GettingRobbed::Instance()
{
  static GettingRobbed instance;

  return &instance;
}


void GettingRobbed::Enter(BankTeller* teller)
{
  cout << "\n" << GetNameOfEntity(teller->ID()) << ": He has a gun!";
}


void GettingRobbed::Execute(BankTeller* teller)
{
  cout << "\n" << GetNameOfEntity(teller->ID()) << ": Here just take our money and get out!";

  teller->GetFSM()->RevertToPreviousState();
}

void GettingRobbed::Exit(BankTeller* teller)
{
  cout << "\n" << GetNameOfEntity(teller->ID()) << ": Glad everyone is safe...";
}


bool GettingRobbed::OnMessage(BankTeller* teller, const Telegram& msg)
{
  return false;
}

