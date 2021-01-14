/*
  pigeon_terminal
  maker PigeonSensei
  Date 2021.01.11
*/

#include "pigeon_terminal/pigeon_terminal.h"

int Pigeon_terminal::ReturnInputKey()
{
  struct termios org_term;

  char input_key = 0;

  tcgetattr(STDIN_FILENO, &org_term);

  struct termios new_term = org_term;

  new_term.c_lflag &= ~(ECHO | ICANON);

  new_term.c_cc[VMIN] = 0;
  new_term.c_cc[VTIME] = 0;

  tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

  read(STDIN_FILENO, &input_key, 1);

  tcsetattr(STDIN_FILENO, TCSANOW, &org_term);

  return input_key;
}

int Pigeon_terminal::StayReturnInputKey()
{
  int ch;
  struct termios buf;
  struct termios save;

  tcgetattr(0, &save);
  buf = save;
  buf.c_lflag &= ~(ICANON|ECHO);
  buf.c_cc[VMIN] = 1;
  buf.c_cc[VTIME] = 0;
  tcsetattr(0, TCSAFLUSH, &buf);
  ch = getchar();
  tcsetattr(0, TCSAFLUSH, &save);
  return ch;
}

int Pigeon_terminal::ClearTerminal()
{
  printf("\033[2J\033[1;1H");
  return 0;
}

