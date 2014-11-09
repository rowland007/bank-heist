/************************************************************************
 Program: bank-heist
 Author: Randall D. Rowland Jr.
 Class: RobberOwnedStates.cpp
 Instructor:
 Date: Nov 4, 2014
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
9NOV2014 Added a message dispatch to be sent to tellers and cops.
9NOV2014 Added Message handling from cops to change state.
 ************************************************************************/
#include "RobberOwnedStates.h"
#include "FSM/State.h"
#include "Robber.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------methods for EnterBankAndRobTellers
EnterBankAndRobTellers* EnterBankAndRobTellers::Instance()
{
  static EnterBankAndRobTellers instance;

  return &instance;
}


void EnterBankAndRobTellers::Enter(Robber* pRobber)
{
  //if the Robber is not already located at the bank, he must
  //change location to the bank
  if (pRobber->Location() != bank)
  {
    cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "Let's go rob a bank!";

    pRobber->ChangeLocation(bank);

    Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
                                 pRobber->ID(),        //ID of sender
                                 ent_Teller,            //ID of recipient
                                 Msg_ThisIsAStickUp,   //the message
                                 NO_ADDITIONAL_INFO);

    Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
                                 pRobber->ID(),        //ID of sender
                                 ent_Cop,            //ID of recipient
                                 Msg_ThisIsAStickUp,   //the message
                                 NO_ADDITIONAL_INFO);
  }
}


void EnterBankAndRobTellers::Execute(Robber* pRobber)
{
  //Now the Robber is at the bank he robs tellers until he
  //is carrying in excess of MaxMoney. If the heat gets too high during
  //his robbing he leaves to not get caught by the cops.
  pRobber->AddToMoneyCarried(1);

  cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "Give me all your money!";

  //if enough money, go and put it in the safe house
  if (pRobber->PocketsFull())
  {
    pRobber->GetFSM()->ChangeState(GoToSafeHouse::Instance());
  }

  if (pRobber->Heat())
  {
    pRobber->GetFSM()->ChangeState(GotCaughtAndGoToJail::Instance());
  }
}


void EnterBankAndRobTellers::Exit(Robber* pRobber)
{
  cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": "
       << "That's enough money for now. Need to get out of here before the cops show up.";
}


bool EnterBankAndRobTellers::OnMessage(Robber* pRobber, const Telegram& msg)
{
  switch(msg.Msg)
  {
  case Msg_StopPolice:
  {
	  pRobber->GetFSM()->ChangeState(GotCaughtAndGoToJail::Instance());
  }
  return false;
}

//------------------------------------------------------------------------methods for GoToSafeHouse

GoToSafeHouse* GoToSafeHouse::Instance()
{
  static GoToSafeHouse instance;

  return &instance;
}

void GoToSafeHouse::Enter(Robber* pRobber)
{
  //on entry the Robber makes sure he is located at the safe house
  if (pRobber->Location() != safehouse)
  {
    cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "Need to get to the safe house!";

    pRobber->ChangeLocation(safehouse);
  }
}


void GoToSafeHouse::Execute(Robber* pRobber)
{
  //deposit the money
  pRobber->AddToWealth(pRobber->MoneyCarried());

  pRobber->SetMoneyCarried(0);

  cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": "
       << "Stashing the money. Total savings now: "<< pRobber->Wealth();

  //wealthy enough to have a well earned rest?
  if (pRobber->Wealth() >= ComfortLevel)
  {
    cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": "
         << "Rich enough for now. Let's just chill here until the heat dies down";

    pRobber->GetFSM()->ChangeState(GoToSafeHouse::Instance());
  }

  //otherwise get more money
  else
  {
    pRobber->GetFSM()->ChangeState(EnterBankAndRobTellers::Instance());
  }
}


void GoToSafeHouse::Exit(Robber* pRobber)
{
  cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "I'm getting bored here in the safe house.";
}


bool GoToSafeHouse::OnMessage(Robber* pRobber, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}


//------------------------------------------------------------------------GotCaughtAndGoToJail

GotCaughtAndGoToJail* GotCaughtAndGoToJail::Instance()
{
  static GotCaughtAndGoToJail instance;

  return &instance;
}

void GotCaughtAndGoToJail::Enter(Robber* pRobber)
{
  if (pRobber->Location() != jail)
  {
    pRobber->ChangeLocation(jail);

    cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "Oh man, the 5-O!";
  }
}

void GotCaughtAndGoToJail::Execute(Robber* pRobber)
{
  cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "Sentenced to life in prison.";

  pRobber->GetFSM()->ChangeState(EnterBankAndRobTellers::Instance());
}


void GotCaughtAndGoToJail::Exit(Robber* pRobber)
{
  cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "No more robbing banks. GAME OVER";

  //wait for a keypress before exiting
  PressAnyKeyToContinue();

  return 0;
}


bool GotCaughtAndGoToJail::OnMessage(Robber* pRobber, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}
