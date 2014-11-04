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
#include "Robber.h"

bool Robber::HandleMessage(const Telegram& msg)
{
  return m_pStateMachine->HandleMessage(msg);
}


void Robber::Update()
{
  SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);

  m_iThirst += 1;

  m_pStateMachine->Update();
}



void Robber::AddToGoldCarried(const int val)
{
  m_iGoldCarried += val;

  if (m_iGoldCarried < 0) m_iGoldCarried = 0;
}

void Robber::AddToWealth(const int val)
{
  m_iMoneyInBank += val;

  if (m_iMoneyInBank < 0) m_iMoneyInBank = 0;
}

bool Robber::Thirsty()const
{
  if (m_iThirst >= ThirstLevel){return true;}

  return false;
}

bool Robber::Fatigued()const
{
  if (m_iFatigue > TirednessThreshold)
  {
    return true;
  }

  return false;
}
