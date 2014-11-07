#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_ThisIsAStickUp,
  Msg_StopPolice,
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_ThisIsAStickUp:

    return "Give me all your money! This is a stick up!";

  case Msg_StopPolice:

    return "Freeze! Police! You're busted!";

  default:

    return "Not recognized!";
  }
}

#endif
