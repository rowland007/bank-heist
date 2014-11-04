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


//------------------------------------------------------------------------methods for EnterMineAndDigForNugget
EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance()
{
  static EnterMineAndDigForNugget instance;

  return &instance;
}


void EnterMineAndDigForNugget::Enter(Robber* pRobber)
{
  //if the Robber is not already located at the goldmine, he must
  //change location to the gold mine
  if (pRobber->Location() != bank)
  {
    cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "Walkin' to the goldmine";

    pRobber->ChangeLocation(bank);
  }
}


void EnterMineAndDigForNugget::Execute(Robber* pRobber)
{
  //Now the Robber is at the goldmine he digs for gold until he
  //is carrying in excess of MaxNuggets. If he gets thirsty during
  //his digging he packs up work for a while and changes state to
  //gp to the saloon for a whiskey.
  pRobber->AddToGoldCarried(1);

  pRobber->IncreaseFatigue();

  cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "Pickin' up a nugget";

  //if enough gold mined, go and put it in the bank
  if (pRobber->PocketsFull())
  {
    pRobber->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance());
  }

  if (pRobber->Thirsty())
  {
    pRobber->GetFSM()->ChangeState(QuenchThirst::Instance());
  }
}


void EnterMineAndDigForNugget::Exit(Robber* pRobber)
{
  cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": "
       << "Ah'm leavin' the goldmine with mah pockets full o' sweet gold";
}


bool EnterMineAndDigForNugget::OnMessage(Robber* pRobber, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------methods for VisitBankAndDepositGold

VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
  static VisitBankAndDepositGold instance;

  return &instance;
}

void VisitBankAndDepositGold::Enter(Robber* pRobber)
{
  //on entry the Robber makes sure he is located at the bank
  if (pRobber->Location() != bank)
  {
    cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "Goin' to the bank. Yes siree";

    pRobber->ChangeLocation(bank);
  }
}


void VisitBankAndDepositGold::Execute(Robber* pRobber)
{
  //deposit the gold
  pRobber->AddToWealth(pRobber->GoldCarried());

  pRobber->SetGoldCarried(0);

  cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": "
       << "Depositing gold. Total savings now: "<< pRobber->Wealth();

  //wealthy enough to have a well earned rest?
  if (pRobber->Wealth() >= ComfortLevel)
  {
    cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": "
         << "WooHoo! Rich enough for now. Back home to mah li'lle lady";

    pRobber->GetFSM()->ChangeState(GoHomeAndSleepTilRested::Instance());
  }

  //otherwise get more gold
  else
  {
    pRobber->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
  }
}


void VisitBankAndDepositGold::Exit(Robber* pRobber)
{
  cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "Leavin' the bank";
}


bool VisitBankAndDepositGold::OnMessage(Robber* pRobber, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}
//------------------------------------------------------------------------methods for GoHomeAndSleepTilRested

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
  static GoHomeAndSleepTilRested instance;

  return &instance;
}

void GoHomeAndSleepTilRested::Enter(Robber* pRobber)
{
  if (pRobber->Location() != safehouse)
  {
    cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "Walkin' home";

    pRobber->ChangeLocation(safehouse);

    //let the wife know I'm home
    Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
                              pRobber->ID(),        //ID of sender
                              ent_Elsa,            //ID of recipient
                              Msg_HiHoneyImHome,   //the message
                              NO_ADDITIONAL_INFO);
  }
}

void GoHomeAndSleepTilRested::Execute(Robber* pRobber)
{
  //if Robber is not fatigued start to dig for nuggets again.
  if (!pRobber->Fatigued())
  {
     cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": "
          << "All mah fatigue has drained away. Time to find more gold!";

     pRobber->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
  }

  else
  {
    //sleep
    pRobber->DecreaseFatigue();

    cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "ZZZZ... ";
  }
}

void GoHomeAndSleepTilRested::Exit(Robber* pRobber)
{
}


bool GoHomeAndSleepTilRested::OnMessage(Robber* pRobber, const Telegram& msg)
{
   SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

   switch(msg.Msg)
   {
   case Msg_StewReady:

     cout << "\nMessage handled by " << GetNameOfEntity(pRobber->ID())
     << " at time: " << Clock->GetCurrentTime();

     SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);

     cout << "\n" << GetNameOfEntity(pRobber->ID())
          << ": Okay Hun, ahm a comin'!";

     pRobber->GetFSM()->ChangeState(EatStew::Instance());

     return true;

   }//end switch

   return false; //send message to global message handler
}

//------------------------------------------------------------------------QuenchThirst

QuenchThirst* QuenchThirst::Instance()
{
  static QuenchThirst instance;

  return &instance;
}

void QuenchThirst::Enter(Robber* pRobber)
{
  if (pRobber->Location() != saloon)
  {
    pRobber->ChangeLocation(saloon);

    cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "Boy, ah sure is thusty! Walking to the saloon";
  }
}

void QuenchThirst::Execute(Robber* pRobber)
{
  pRobber->BuyAndDrinkAWhiskey();

  cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "That's mighty fine sippin' liquer";

  pRobber->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
}


void QuenchThirst::Exit(Robber* pRobber)
{
  cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "Leaving the saloon, feelin' good";
}


bool QuenchThirst::OnMessage(Robber* pRobber, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------EatStew

EatStew* EatStew::Instance()
{
  static EatStew instance;

  return &instance;
}


void EatStew::Enter(Robber* pRobber)
{
  cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "Smells Reaaal goood Elsa!";
}

void EatStew::Execute(Robber* pRobber)
{
  cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "Tastes real good too!";

  pRobber->GetFSM()->RevertToPreviousState();
}

void EatStew::Exit(Robber* pRobber)
{
  cout << "\n" << GetNameOfEntity(pRobber->ID()) << ": " << "Thankya li'lle lady. Ah better get back to whatever ah wuz doin'";
}


bool EatStew::OnMessage(Robber* pRobber, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}
