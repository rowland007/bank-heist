/************************************************************************
 Program: bank-heist
 Author: Randall D. Rowland Jr.
 Class: Cops.cpp
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

#include "Cops.h"

bool Cops::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}


void Cops::Update()
{
  //set text color to green
  SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

  m_pStateMachine->Update();
}
