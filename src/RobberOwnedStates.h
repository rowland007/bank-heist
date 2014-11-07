/************************************************************************
 Program: bank-heist
 Author: Randall D. Rowland Jr.
 Class: RobberOwnedStates.h
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
#ifndef ROBBEROWNEDSTATES_H_
#define ROBBEROWNEDSTATES_H_

#include "FSM/State.h"


class Robber;
struct Telegram;




//------------------------------------------------------------------------
//
//  In this state the robber will walk to a bank and rob the bank tellers
//  for money. If the robber already has enough money he'll change state
//  to GoToSafeHouse. If the heat gets too intense he'll change state
//  to GoToSafeHouse
//------------------------------------------------------------------------
class EnterBankAndRobTellers : public State<Robber>
{
private:

  EnterBankAndRobTellers(){}

  //copy ctor and assignment should be private
  EnterBankAndRobTellers(const EnterBankAndRobTellers&);
  EnterBankAndRobTellers& operator=(const EnterBankAndRobTellers&);

public:

  //this is a singleton
  static EnterBankAndRobTellers* Instance();

  virtual void Enter(Robber* robber);

  virtual void Execute(Robber* robber);

  virtual void Exit(Robber* robber);

  virtual bool OnMessage(Robber* agent, const Telegram& msg);

};

//------------------------------------------------------------------------
//
//  Entity will go to the safe house and store any bags of money he is carrying.
//  If the robber is subsequently wealthy enough he'll stay at the safe house home,
//  otherwise he'll keep robbing banks.
//------------------------------------------------------------------------
class GoToSafeHouse : public State<Robber>
{
private:

  GoToSafeHouse(){}

  //copy ctor and assignment should be private
  GoToSafeHouse(const GoToSafeHouse&);
  GoToSafeHouse& operator=(const GoToSafeHouse&);

public:

  //this is a singleton
  static GoToSafeHouse* Instance();

  virtual void Enter(Robber* robber);

  virtual void Execute(Robber* robber);

  virtual void Exit(Robber* robber);

  virtual bool OnMessage(Robber* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
//
//  robber changes location to the jail and game ends until
//------------------------------------------------------------------------
class GotCaughtAndGoToJail : public State<Robber>
{
private:

  GotCaughtAndGoToJail(){}

  //copy ctor and assignment should be private
  GotCaughtAndGoToJail(const GotCaughtAndGoToJail&);
  GotCaughtAndGoToJail& operator=(const GotCaughtAndGoToJail&);

public:

  //this is a singleton
  static GotCaughtAndGoToJail* Instance();

  virtual void Enter(Robber* robber);

  virtual void Execute(Robber* robber);

  virtual void Exit(Robber* robber);

  virtual bool OnMessage(Robber* agent, const Telegram& msg);
};

#endif /* ROBBEROWNEDSTATES_H_ */
