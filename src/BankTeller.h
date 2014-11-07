/************************************************************************
 Program: bank-heist
 Author: Randall D. Rowland Jr.
 Class: BankTeller.h
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
 ************************************************************************/

#ifndef BANKTELLER_H_
#define BANKTELLER_H_

#include <string>

#include "FSM/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "BankTellerOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "Robber.h"
#include "FSM/StateMachine.h"
#include "misc/Utils.h"



class BankTeller : public BaseGameEntity
{
private:

  //an instance of the state machine class
  StateMachine<BankTeller>* m_pStateMachine;

  location_type   m_Location;

  //Are you getting robbed?
  bool            m_bRobbing;


public:

  BankTeller(int id):m_Location(bank),
                     m_bRobbing(false),
                     BaseGameEntity(id)

  {
    //set up the state machine
    m_pStateMachine = new StateMachine<BankTeller>(this);

    m_pStateMachine->SetCurrentState(BankTellerDoingBankThings::Instance());

    m_pStateMachine->SetGlobalState(BankTellerGlobalState::Instance());
  }

  ~BankTeller(){delete m_pStateMachine;}


  //this must be implemented
  void          Update();

  //so must this
  virtual bool  HandleMessage(const Telegram& msg);

  StateMachine<BankTeller>* GetFSM()const{return m_pStateMachine;}

  //----------------------------------------------------accessors
  location_type Location()const{return m_Location;}
  void          ChangeLocation(location_type loc){m_Location=loc;}

  bool          GettingRobbed()const{return m_bRobbing;}
  void          SetGettingRobbed(bool val){m_bRobbing = val;}

};

#endif
