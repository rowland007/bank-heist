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

  m_iHeat += 1;

  m_pStateMachine->Update();
}



void Robber::AddToMoneyCarried(const int val)
{
  m_iMoneyCarried += val;

  if (m_iMoneyCarried < 0) m_iMoneyCarried = 0;
}

void Robber::AddToWealth(const int val)
{
  m_iMoneyAtSafehouse += val;

  if (m_iMoneyAtSafehouse < 0) m_iMoneyAtSafehouse = 0;
}

bool Robber::Heat()const
{
  if (m_iHeat >= HeatLevel){return true;}

  return false;
}
