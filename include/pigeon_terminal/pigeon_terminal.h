#ifndef PIGEON_TERMINAL_H
#define PIGEON_TERMINAL_H

#include <termios.h>
#include <stdio.h>
#include <unistd.h>

#define ATTRESET "\33[0m"

/* attributes */

#define ATTBOLD      "\33[1m"
#define ATTUNDERLINE "\33[4m"
#define ATTBLINK     "\33[5m"
#define ATTINVERSE   "\33[7m"
#define ATTINVISIBLE "\33[8m"

/* foreground colors */

#define FGBLACK   "\33[30m"
#define FGRED     "\33[31m"
#define FGGREEN   "\33[32m"
#define FGYELLOW  "\33[33m"
#define FGBLUE    "\33[34m"
#define FGMAGENTA "\33[35m"
#define FGCYAN    "\33[36m"
#define FGWHITE   "\33[37m"

/* background colors */

#define BGBLACK   "\33[40m"
#define BGRED     "\33[41m"
#define BGGREEN   "\33[42m"
#define BGYELLOW  "\33[43m"
#define BGBLUE    "\33[44m"
#define BGMAGENTA "\33[45m"
#define BGCYAN    "\33[46m"
#define BGWHITE   "\33[47m"

/* cursor */

#define CSR_HOME  "\33[H"
#define CSR_UP    "\33[A"
#define CSR_DOWN  "\33[B"
#define CSR_RIGHT "\33[C"
#define CSR_LEFT  "\33[D"

#define CSR_HIDE  "\33[?25l"
#define CSR_SHOW  "\33[?25h"

/* clear screen */

#define CLR_SCREEN  "\33[2J"

class Pigeon_terminal
{
public:
    Pigeon_terminal()
       {
          // open run
       }
       ~Pigeon_terminal()
       {
          // close run
       }

    int ReturnInputKey(); // 키보드 입력 함수

    int StayReturnInputKey(); // 키보드 입력 대기 함수

    int ClearTerminal(); // 터미널 창 클리어

private:

};

#endif // PIGEON_TERMINAL_H

