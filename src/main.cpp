#include <fstream>
#include "Locations.h"
#include "Robber.h"
#include "Cops.h"
#include "BankTeller.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"



std::ofstream os;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //create a robber
  Robber robber(ent_Robber);

  //create cops
  Cops cop(ent_Cop);

  //create bank tellers
  BankTeller teller(ent_Teller);

  //run Bob and Elsa through a few Update calls
  for (int i=0; i<20; ++i)
  { 
    robber.Update();
    cop.Update();
    teller.Update();

    Sleep(800);
  }

  //wait for a keypress before exiting
  PressAnyKeyToContinue();

  return 0;
}






