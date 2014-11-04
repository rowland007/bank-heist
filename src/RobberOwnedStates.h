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
//  In this state the robber will walk to a bank and pick up a nugget
//  of gold. If the robber already has a nugget of gold he'll change state
//  to VisitBankAndDepositgold. If he gets thirsty he'll change state
//  to QuenchThirst
//------------------------------------------------------------------------
class EnterMineAndDigForNugget : public State<Robber>
{
private:

  EnterMineAndDigForNugget(){}

  //copy ctor and assignment should be private
  EnterMineAndDigForNugget(const EnterMineAndDigForNugget&);
  EnterMineAndDigForNugget& operator=(const EnterMineAndDigForNugget&);

public:

  //this is a singleton
  static EnterMineAndDigForNugget* Instance();

  virtual void Enter(Robber* robber);

  virtual void Execute(Robber* robber);

  virtual void Exit(Robber* robber);

  virtual bool OnMessage(Robber* agent, const Telegram& msg);

};

//------------------------------------------------------------------------
//
//  Entity will go to a bank and deposit any bags of money he is carrying. If the
//  robber is subsequently wealthy enough he'll walk home, otherwise he'll
//  keep going to get more
//------------------------------------------------------------------------
class VisitBankAndDepositgold : public State<Robber>
{
private:

  VisitBankAndDepositgold(){}

  //copy ctor and assignment should be private
  VisitBankAndDepositgold(const VisitBankAndDepositgold&);
  VisitBankAndDepositgold& operator=(const VisitBankAndDepositgold&);

public:

  //this is a singleton
  static VisitBankAndDepositgold* Instance();

  virtual void Enter(Robber* robber);

  virtual void Execute(Robber* robber);

  virtual void Exit(Robber* robber);

  virtual bool OnMessage(Robber* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  robber will go home and sleep until his fatigue is decreased
//  sufficiently
//------------------------------------------------------------------------
class GoHomeAndSleepTilRested : public State<Robber>
{
private:

  GoHomeAndSleepTilRested(){}

  //copy ctor and assignment should be private
  GoHomeAndSleepTilRested(const GoHomeAndSleepTilRested&);
  GoHomeAndSleepTilRested& operator=(const GoHomeAndSleepTilRested&);

public:

  //this is a singleton
  static GoHomeAndSleepTilRested* Instance();

  virtual void Enter(Robber* robber);

  virtual void Execute(Robber* robber);

  virtual void Exit(Robber* robber);

  virtual bool OnMessage(Robber* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  robber changes location to the saloon and keeps buying Whiskey until
//  his thirst is quenched. When satisfied he returns to the bank
//  and resumes his quest for bags of money.
//------------------------------------------------------------------------
class QuenchThirst : public State<Robber>
{
private:

  QuenchThirst(){}

  //copy ctor and assignment should be private
  QuenchThirst(const QuenchThirst&);
  QuenchThirst& operator=(const QuenchThirst&);

public:

  //this is a singleton
  static QuenchThirst* Instance();

  virtual void Enter(Robber* robber);

  virtual void Execute(Robber* robber);

  virtual void Exit(Robber* robber);

  virtual bool OnMessage(Robber* agent, const Telegram& msg);
};


//------------------------------------------------------------------------
//
//  this is implemented as a state blip. The robber eats the stew, gives
//  Elsa some compliments and then returns to his previous state
//------------------------------------------------------------------------
class EatStew : public State<Robber>
{
private:

  EatStew(){}

  //copy ctor and assignment should be private
  EatStew(const EatStew&);
  EatStew& operator=(const EatStew&);

public:

  //this is a singleton
  static EatStew* Instance();

  virtual void Enter(Robber* robber);

  virtual void Execute(Robber* robber);

  virtual void Exit(Robber* robber);

  virtual bool OnMessage(Robber* agent, const Telegram& msg);
};

#endif /* ROBBEROWNEDSTATES_H_ */
