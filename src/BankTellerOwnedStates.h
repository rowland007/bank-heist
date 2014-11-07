/************************************************************************
 Program: bank-heist
 Author: Randall D. Rowland Jr.
 Class: BankTellerOwnedStates.h
 Instructor:
 Date: Nov 6, 2014
 Description:
 Input:
 Output:
 Compilation instructions:
 Usage:
 Known bugs/missing features:

 This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 International Public License. To view a tellery of this license, visit
 https://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative
 Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.

 Modifications:
 Date                Comment
 ----    ------------------------------------------------
 ************************************************************************/

#ifndef BANKTELLEROWNEDSTATES_H_
#define BANKTELLEROWNEDSTATES_H_

#include "FSM/State.h"

class BankTeller;



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class BankTellerGlobalState : public State<BankTeller>
{
private:

  BankTellerGlobalState(){}

  //tellery ctor and assignment should be private
  BankTellerGlobalState(const BankTellerGlobalState&);
  BankTellerGlobalState& operator=(const BankTellerGlobalState&);

public:

  //this is a singleton
  static BankTellerGlobalState* Instance();

  virtual void Enter(BankTeller* teller){}

  virtual void Execute(BankTeller* teller);

  virtual void Exit(BankTeller* teller){}

  virtual bool OnMessage(BankTeller* teller, const Telegram& msg);
};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class BankTellerDoingBankThings : public State<BankTeller>
{
private:

  BankTellerDoingBankThings(){}

  //tellery ctor and assignment should be private
  BankTellerDoingBankThings(const BankTellerDoingBankThings&);
  BankTellerDoingBankThings& operator=(const BankTellerDoingBankThings&);

public:

  //this is a singleton
  static BankTellerDoingBankThings* Instance();

  virtual void Enter(BankTeller* teller);

  virtual void Execute(BankTeller* teller);

  virtual void Exit(BankTeller* teller);

  virtual bool OnMessage(BankTeller* teller, const Telegram& msg);

};

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
class GettingRobbed : public State<BankTeller>
{
private:

  GettingRobbed(){}

  //tellery ctor and assignment should be private
  GettingRobbed(const GettingRobbed&);
  GettingRobbed& operator=(const GettingRobbed&);

public:

  //this is a singleton
  static GettingRobbed* Instance();

  virtual void Enter(BankTeller* teller);

  virtual void Execute(BankTeller* teller);

  virtual void Exit(BankTeller* teller);

  virtual bool OnMessage(BankTeller* teller, const Telegram& msg);
};


#endif

