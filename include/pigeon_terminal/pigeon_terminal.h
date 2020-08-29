#ifndef PIGEON_TERMINAL_H
#define PIGEON_TERMINAL_H

#include <termios.h>
#include <ros/ros.h>


class pigeon_terminal
{
public:
    pigeon_terminal()
       {
          // open run
       }
       ~pigeon_terminal()
       {
          // close run
       }

    int keybord_input(); // 키보드 입력 함수

    int stay_keybord_input(); // 키보드 입력 대기 함수

    int terminal_clear(); // 터미널 창 클리어

private:

};

#endif // PIGEON_TERMINAL_H
