/************************************************************************
 Program: bank-heist
 Author: Randall D. Rowland Jr.
 Class: CopsOwnedStates.h
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

#ifndef COPSOWNEDSTATES_H_
#define COPSOWNEDSTATES_H_

#include "FSM/State.h"

class Cops;



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class CopsGlobalState : public State<Cops>
{
private:

  CopsGlobalState(){}

  //copy ctor and assignment should be private
  CopsGlobalState(const CopsGlobalState&);
  CopsGlobalState& operator=(const CopsGlobalState&);

public:

  //this is a singleton
  static CopsGlobalState* Instance();

  virtual void Enter(Cops* cop){}

  virtual void Execute(Cops* cop);

  virtual void Exit(Cops* cop){}

  virtual bool OnMessage(Cops* cop, const Telegram& msg);
};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class CaughtRobber : public State<Cops>
{
private:

  CaughtRobber(){}

  //copy ctor and assignment should be private
  CaughtRobber(const CaughtRobber&);
  CaughtRobber& operator=(const CaughtRobber&);

public:

  //this is a singleton
  static CaughtRobber* Instance();

  virtual void Enter(Cops* cop);

  virtual void Execute(Cops* cop);

  virtual void Exit(Cops* cop);

  virtual bool OnMessage(Cops* cop, const Telegram& msg);

};

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
class ChaseRobber : public State<Cops>
{
private:

  ChaseRobber(){}

  //copy ctor and assignment should be private
  ChaseRobber(const ChaseRobber&);
  ChaseRobber& operator=(const ChaseRobber&);

public:

  //this is a singleton
  static ChaseRobber* Instance();

  virtual void Enter(Cops* cop);

  virtual void Execute(Cops* cop);

  virtual void Exit(Cops* cop);

  virtual bool OnMessage(Cops* cop, const Telegram& msg);
};


#endif
