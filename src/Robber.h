 /************************************************************************
   Program: Bank Heist
   Author: Randall D. Rowland Jr.
   Class: Robber
   Instructor:
   Date: 30 October 2014
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
#ifndef ROBBER_H_
#define ROBBER_H_

#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "RobberOwnedStates.h"
#include "FSM/StateMachine.h"

template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;

//the amount of money robber must have before he can go to safehouse
const int ComfortLevel       = 5;
//the amount of money robber can carry
const int MaxMoney         = 3;
//above this value the cops show up
const int HeatLevel        = 10;

class Robber : public BaseGameEntity
{
private:

 //an instance of the state machine class
  StateMachine<Robber>*  m_pStateMachine;

  location_type         m_Location;

  //how many money bags the robber has
  int                   m_iMoneyCarried;

  int                   m_iMoneyAtSafehouse;

  //the higher the value, the more heat on the robber
  int                   m_iHeat;

public:

  Robber(int id):m_Location(safehouse),
                          m_iMoneyCarried(0),
                          m_iMoneyAtSafehouse(0),
                          m_iHeat(0),
                          BaseGameEntity(id)

  {
    //set up state machine
    m_pStateMachine = new StateMachine<Robber>(this);

    m_pStateMachine->SetCurrentState(GoToSafeHouse::Instance());

    /* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
  }

  ~Robber(){delete m_pStateMachine;}

  //this must be implemented
  void Update();

  //so must this
  virtual bool  HandleMessage(const Telegram& msg);


  StateMachine<Robber>* GetFSM()const{return m_pStateMachine;}



  //-------------------------------------------------------------accessors
  location_type Location()const{return m_Location;}
  void          ChangeLocation(location_type loc){m_Location=loc;}
  int           MoneyCarried()const{return m_iMoneyCarried;}
  void          SetMoneyCarried(int val){m_iMoneyCarried = val;}
  void          AddToMoneyCarried(int val);
  bool          PocketsFull()const{return m_iMoneyCarried >= MaxMoney;}

  int           Wealth()const{return m_iMoneyAtSafehouse;}
  void          SetWealth(int val){m_iMoneyAtSafehouse = val;}
  void          AddToWealth(int val);

  bool          Heat()const;
};

#endif /* ROBBER_H_ */
