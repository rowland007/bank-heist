 /************************************************************************
   Program: Bank Heist
   Author: Randall D. Rowland Jr.
   Class: EntityNames
   Instructor: Candi Reid
   Date: 14 October 2014
   Description:	An enumerator that holds the locations
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
 20OCT14	Modified the names from example and added two
 ************************************************************************/

#ifndef NAMES_H
#define NAMES_H

#include <string>

enum 
{
  ent_Robber,
  ent_Cop,
  ent_Teller,
  ent_Bystander
};

inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_Robber:

    return "Robber";

  case ent_Cop:

    return "Cop";
    
  case ent_Teller:

	  return "Teller";

  case ent_Bystander:

	  return "Bystander";

  default:

    return "UNKNOWN!";
  }
}

#endif
