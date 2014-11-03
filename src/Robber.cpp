/*
 * Robber.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: rowland007
 */

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
