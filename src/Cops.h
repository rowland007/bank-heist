/************************************************************************
 Program: bank-heist
 Author: Randall D. Rowland Jr.
 Class: Cops.h
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
 ************************************************************************/

#ifndef COPS_H_
#define COPS_H_

#include <string>

#include "FSM/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "CopsOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "Robber.h"
#include "FSM/StateMachine.h"
#include "misc/Utils.h"



class Cops : public BaseGameEntity
{
private:

  //an instance of the state machine class
  StateMachine<Cops>* m_pStateMachine;

  location_type   m_Location;

  //Are they chasing the robber?
  bool            m_bChasing;


public:

  Cops(int id):m_Location(jail),
                     m_bChasing(false),
                     BaseGameEntity(id)

  {
    //set up the state machine
    m_pStateMachine = new StateMachine<Cops>(this);

    m_pStateMachine->SetCurrentState(CaughtRobber::Instance());

    m_pStateMachine->SetGlobalState(CopsGlobalState::Instance());
  }

  ~Cops(){delete m_pStateMachine;}


  //this must be implemented
  void          Update();

  //so must this
  virtual bool  HandleMessage(const Telegram& msg);

  StateMachine<Cops>* GetFSM()const{return m_pStateMachine;}

  //----------------------------------------------------accessors
  location_type Location()const{return m_Location;}
  void          ChangeLocation(location_type loc){m_Location=loc;}

  bool          ChasingRobber()const{return m_bChasing;}
  void          SetChasingRobber(bool val){m_bChasing = val;}

};

#endif
