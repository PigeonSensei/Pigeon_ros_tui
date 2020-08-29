/*
  pigeon robot steering.Ver 0.2
  maker PigeonSensei
  Date 2020.08.30
*/

#include <pigeon_tui/pigeon_robot_steering.h>
//#include <curses.h>
int pigeon_robot_steering::keybord_input(void) // 키보드 입력 함수
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
//{
//  int ch;
//  struct termios buf;
//  struct termios save;

//  tcgetattr(0, &save);
//  buf = save;
//  buf.c_lflag &= ~(ICANON|ECHO);
//  buf.c_cc[VMIN] = 1;
//  buf.c_cc[VTIME] = 0;
//  tcsetattr(0, TCSAFLUSH, &buf);
//  ch = getchar();
//  tcsetattr(0, TCSAFLUSH, &save);
//  return ch;
//}

void pigeon_robot_steering::tui() // TUI 함수
{
  std::string reset_position;

  auto style_0 = (cmd_vel_menu_number == 0) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto style_1 = (cmd_vel_menu_number == 1) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto style_2 = (cmd_vel_menu_number == 2) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto style_3 = (cmd_vel_menu_number == 3) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto style_4 = (cmd_vel_menu_number == 4) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto style_5 = (cmd_vel_menu_number == 5) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);

  auto limit_style_0 = (cmd_vel_pub.linear.x >= 1.0) ? (cmd_vel_menu_number == 0) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number == 0) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto limit_style_1 = (cmd_vel_pub.linear.y >= 1.0) ? (cmd_vel_menu_number == 1) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number == 1) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto limit_style_2 = (cmd_vel_pub.linear.z >= 1.0) ? (cmd_vel_menu_number == 2) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number == 2) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto limit_style_3 = (cmd_vel_pub.angular.x >= 1.0) ? (cmd_vel_menu_number == 3) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number == 3) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto limit_style_4 = (cmd_vel_pub.angular.y >= 1.0) ? (cmd_vel_menu_number == 4) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number == 4) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto limit_style_5 = (cmd_vel_pub.angular.z >= 1.0) ? (cmd_vel_menu_number == 5) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number == 5) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);

  auto negative_style_0 = (cmd_vel_menu_number == 0) ? bgcolor(ftxui::Color::Green) : bgcolor(ftxui::Color::GreenLight);
  auto negative_style_1 = (cmd_vel_menu_number == 1) ? bgcolor(ftxui::Color::Green) : bgcolor(ftxui::Color::GreenLight);
  auto negative_style_2 = (cmd_vel_menu_number == 2) ? bgcolor(ftxui::Color::Green) : bgcolor(ftxui::Color::GreenLight);
  auto negative_style_3 = (cmd_vel_menu_number == 3) ? bgcolor(ftxui::Color::Green) : bgcolor(ftxui::Color::GreenLight);
  auto negative_style_4 = (cmd_vel_menu_number == 4) ? bgcolor(ftxui::Color::Green) : bgcolor(ftxui::Color::GreenLight);
  auto negative_style_5 = (cmd_vel_menu_number == 5) ? bgcolor(ftxui::Color::Green) : bgcolor(ftxui::Color::GreenLight);

  auto negative_limit_style_0 = (cmd_vel_pub.linear.x <= -1.0) ? (cmd_vel_menu_number == 0) ? bgcolor(ftxui::Color::Red) | ftxui::dim : bgcolor(ftxui::Color::RedLight) : (cmd_vel_menu_number == 0) ? bgcolor(ftxui::Color::Green) : bgcolor(ftxui::Color::GreenLight);
  auto negative_limit_style_1 = (cmd_vel_pub.linear.y <= -1.0) ? (cmd_vel_menu_number == 1) ? bgcolor(ftxui::Color::Red) | ftxui::dim : bgcolor(ftxui::Color::RedLight) : (cmd_vel_menu_number == 1) ? bgcolor(ftxui::Color::Green) : bgcolor(ftxui::Color::GreenLight);
  auto negative_limit_style_2 = (cmd_vel_pub.linear.z <= -1.0) ? (cmd_vel_menu_number == 2) ? bgcolor(ftxui::Color::Red) | ftxui::dim : bgcolor(ftxui::Color::RedLight) : (cmd_vel_menu_number == 2) ? bgcolor(ftxui::Color::Green) : bgcolor(ftxui::Color::GreenLight);
  auto negative_limit_style_3 = (cmd_vel_pub.angular.x <= -1.0) ? (cmd_vel_menu_number == 3) ? bgcolor(ftxui::Color::Red) | ftxui::dim : bgcolor(ftxui::Color::RedLight) : (cmd_vel_menu_number == 3) ? bgcolor(ftxui::Color::Green) : bgcolor(ftxui::Color::GreenLight);
  auto negative_limit_style_4 = (cmd_vel_pub.angular.y <= -1.0) ? (cmd_vel_menu_number == 4) ? bgcolor(ftxui::Color::Red) | ftxui::dim : bgcolor(ftxui::Color::RedLight) : (cmd_vel_menu_number == 4) ? bgcolor(ftxui::Color::Green) : bgcolor(ftxui::Color::GreenLight);
  auto negative_limit_style_5 = (cmd_vel_pub.angular.z <= -1.0) ? (cmd_vel_menu_number == 5) ? bgcolor(ftxui::Color::Red) | ftxui::dim : bgcolor(ftxui::Color::RedLight) : (cmd_vel_menu_number == 5) ? bgcolor(ftxui::Color::Green) : bgcolor(ftxui::Color::GreenLight);

  ftxui::Element Document =
  ftxui::vbox({
       // -------- Top panel --------------
       ftxui::hbox({
           // -------- Left Menu --------------
           ftxui::hbox({
              ftxui::text(L"Pigeon_robot_steering") | ftxui::bold | ftxui::center, ftxui::separator(),
           }),
           ftxui::text(L"cmd_vel")| color(ftxui::Color::Red) | ftxui::center, ftxui::separator(),
           ftxui::text(L"ver 0.2")| ftxui::bold,
           // -------- Right Menu --------------
       }),
      ftxui::separator(),
      ftxui::hbox({
           ftxui::vbox({
              ftxui::text(L"-"),
              ftxui::text(L"-"),
              ftxui::text(L"-"),
              ftxui::text(L"-"),
              ftxui::text(L"-"),
              ftxui::text(L"-"),
              }) | ftxui::bold,ftxui::separator(),
           ftxui::vbox({
              ftxui::gauge(1- (-1 * cmd_vels.negative_linear_x)) | color(ftxui::Color::Black) | negative_limit_style_0,
              ftxui::gauge(1- (-1 * cmd_vels.negative_linear_y)) | color(ftxui::Color::Black) | negative_limit_style_1,
              ftxui::gauge(1- (-1 * cmd_vels.negative_linear_z)) | color(ftxui::Color::Black) | negative_limit_style_2,
              ftxui::gauge(1- (-1 * cmd_vels.negative_angular_x)) | color(ftxui::Color::Black) | negative_limit_style_3,
              ftxui::gauge(1- (-1 * cmd_vels.negative_angular_y)) | color(ftxui::Color::Black) | negative_limit_style_4,
              ftxui::gauge(1- (-1 * cmd_vels.negative_angular_z)) | color(ftxui::Color::Black) | negative_limit_style_5,
              }) | ftxui::flex, ftxui::separator(),
           ftxui::vbox({
              ftxui::text(L"liner.x") | style_0 | ftxui::center,
              ftxui::text(L"liner.y") | style_1 | ftxui::center,
              ftxui::text(L"liner.z") | style_2 | ftxui::center,
              ftxui::text(L"angular.x") | style_3 | ftxui::center,
              ftxui::text(L"angular.y") | style_4 | ftxui::center,
              ftxui::text(L"angular.z") | style_5 | ftxui::center,
               }) | ftxui::bold,ftxui::separator(),
           ftxui::vbox({
              ftxui::gauge(cmd_vels.linear_x) | limit_style_0,
              ftxui::gauge(cmd_vels.linear_y) | limit_style_1,
              ftxui::gauge(cmd_vels.linear_z) | limit_style_2,
              ftxui::gauge(cmd_vels.angular_x) | limit_style_3,
              ftxui::gauge(cmd_vels.angular_y) | limit_style_4,
              ftxui::gauge(cmd_vels.angular_z) | limit_style_5,
              }) | ftxui::flex, ftxui::separator(),
           ftxui::vbox({
              ftxui::text(L"+"),
              ftxui::text(L"+"),
              ftxui::text(L"+"),
              ftxui::text(L"+"),
              ftxui::text(L"+"),
              ftxui::text(L"+"),
              }),
          }) | ftxui::flex, ftxui::separator(),
      // -------- Bottom panel --------------
      ftxui::vbox({
          ftxui::hbox({
              ftxui::text(L"liner.x   : "),
              ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_pub.linear.x) + " m/s")),
          }),
          ftxui::hbox({
              ftxui::text(L"liner.y   : "),
              ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_pub.linear.y) + " m/s")),
          }),
          ftxui::hbox({
              ftxui::text(L"liner.z   : "),
              ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_pub.linear.z) + " m/s")),
          }),
          ftxui::hbox({
              ftxui::text(L"angular.x : "),
              ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_pub.angular.x) + " rad/s")),
          }),
          ftxui::hbox({
              ftxui::text(L"angular.y : "),
              ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_pub.angular.y) + " rad/s")),
          }),
          ftxui::hbox({
              ftxui::text(L"angular.z : "),
              ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_pub.angular.z) + " rad/s")),
              }),
          }) | ftxui::flex,
  });
  Document = border(Document);
  auto screen = ftxui::Screen::Create(
  ftxui::Dimension::Full(),       // Width
  ftxui::Dimension::Fit(Document) // Height
  );

  Render(screen, Document);

//  screen.Clear();
//  std::cout << std::endl << std::endl;
//  system("clear");


  reset();
  std::cout << reset_position << screen.ToString() << std::flush;
  reset_position = screen.ResetPosition();
//  reset();
//  ros::Duration(0.08).sleep();



//  std::this_thread::sleep_for(0.01s);
  return;
}

int pigeon_robot_steering::set_key() // 키 입력 함수
{
  key_input =  keybord_input();
  if(key_input == 119 | key_input == 87){ // INPUT W
    cmd_vel_menu_number = cmd_vel_menu_number - 1;
    if(cmd_vel_menu_number < 0 ) cmd_vel_menu_number = 0;
  }
  if(key_input == 115 | key_input == 83){ // INPUT S
    cmd_vel_menu_number = cmd_vel_menu_number + 1;
    if(cmd_vel_menu_number > 5 ) cmd_vel_menu_number = 5;
  }
  if(key_input == 100 | key_input == 68) intput_cmd_vel_data(cmd_vel_menu_number, key_input); //INPUT D
  if(key_input == 97 | key_input == 65) intput_cmd_vel_data(cmd_vel_menu_number, key_input); //INPUT A

  if(key_input == 122 | key_input == 90) all_reset_cmd_vel(); // INPUT Z
  if(key_input == 120 | key_input == 88) at_reset_cmd_vel(cmd_vel_menu_number); //INPUT X
  return 0;
}

void pigeon_robot_steering::intput_cmd_vel_data(int cmd_vel_menu_number, int key_input) // 키 입력에 따른 오돔 대입 함수
{
//----------------- linear_x -----------------//
  if(cmd_vel_menu_number == 0)
  {
    if(key_input == 100 | key_input == 68){
      cmd_vel_pub.linear.x = cmd_vel_pub.linear.x + 0.100000;
      if(cmd_vel_pub.linear.x > 0.97){
        cmd_vel_pub.linear.x = 1.0;
      }
    }
     if(key_input == 97 | key_input == 65 ){
      cmd_vel_pub.linear.x = cmd_vel_pub.linear.x - 0.100000;
      if(cmd_vel_pub.linear.x < -0.97){
        cmd_vel_pub.linear.x = -1.0;
      }
    }
     if(cmd_vel_pub.linear.x < 0.02 & cmd_vel_pub.linear.x > -0.02)
     {
       cmd_vel_pub.linear.x = 0.0;
     }

    intput_cmd_vels(cmd_vel_menu_number,cmd_vel_pub.linear.x);
    }

//----------------- linear_y -----------------//
  if(cmd_vel_menu_number == 1)
  {
    if(key_input == 100 | key_input == 68){
      cmd_vel_pub.linear.y = cmd_vel_pub.linear.y + 0.100000;
      if(cmd_vel_pub.linear.y > 0.97){
        cmd_vel_pub.linear.y = 1.0;
      }
    }
      if(key_input == 97 | key_input == 65){
      cmd_vel_pub.linear.y = cmd_vel_pub.linear.y - 0.100000;
      if(cmd_vel_pub.linear.y < -0.97){
        cmd_vel_pub.linear.y = -1.0;
      }
    }
      if(cmd_vel_pub.linear.y < 0.02 & cmd_vel_pub.linear.y > -0.02)
      {
        cmd_vel_pub.linear.y = 0.0;
      }

  intput_cmd_vels(cmd_vel_menu_number,cmd_vel_pub.linear.y);
  }

//----------------- linear_z -----------------//
  if(cmd_vel_menu_number == 2)
  {
    if(key_input == 100 | key_input == 68){
      cmd_vel_pub.linear.z = cmd_vel_pub.linear.z + 0.100000;
      if(cmd_vel_pub.linear.z > 0.97){
        cmd_vel_pub.linear.z = 1.0;
      }
    }
      if(key_input == 97 | key_input == 65){

        cmd_vel_pub.linear.z = cmd_vel_pub.linear.z - 0.100000;
        if(cmd_vel_pub.linear.z < -0.97){
          cmd_vel_pub.linear.z = -1.0;
        }
    }
      if(cmd_vel_pub.linear.z < 0.02 & cmd_vel_pub.linear.z > -0.02)
      {
        cmd_vel_pub.linear.z = 0.0;
      }

  intput_cmd_vels(cmd_vel_menu_number,cmd_vel_pub.linear.z);
  }

//----------------- angular_x -----------------//
  if(cmd_vel_menu_number == 3)
  {
    if(key_input == 100 | key_input == 68){
      cmd_vel_pub.angular.x = cmd_vel_pub.angular.x + 0.100000;
      if(cmd_vel_pub.angular.x > 0.97){
        cmd_vel_pub.angular.x = 1.0;
      }
    }
      if(key_input == 97 | key_input == 65){
      cmd_vel_pub.angular.x = cmd_vel_pub.angular.x - 0.100000;
      if(cmd_vel_pub.angular.x < -0.97){
        cmd_vel_pub.angular.x = -1.0;
      }
    }
      if(cmd_vel_pub.angular.x < 0.02 & cmd_vel_pub.angular.x > -0.02)
      {
        cmd_vel_pub.angular.x = 0.0;
      }
  intput_cmd_vels(cmd_vel_menu_number,cmd_vel_pub.angular.x);
  }

//----------------- angular_y -----------------//
  if(cmd_vel_menu_number == 4)
  {
    if(key_input == 100 | key_input == 68){
      cmd_vel_pub.angular.y = cmd_vel_pub.angular.y + 0.100000;
      if(cmd_vel_pub.angular.y > 0.97){
        cmd_vel_pub.angular.y = 1.0;
      }
    }
      if(key_input == 97 | key_input == 65){
      cmd_vel_pub.angular.y = cmd_vel_pub.angular.y - 0.100000;
      if(cmd_vel_pub.angular.y < -0.97){
        cmd_vel_pub.angular.y = -1.0;
      }
    }
      if(cmd_vel_pub.angular.y < 0.02 & cmd_vel_pub.angular.y > -0.02)
      {
        cmd_vel_pub.angular.y = 0.0;
      }

  intput_cmd_vels(cmd_vel_menu_number,cmd_vel_pub.angular.y);
  }

//----------------- angular_z -----------------//
  if(cmd_vel_menu_number == 5)
  {
    if(key_input == 100 | key_input == 68){
      cmd_vel_pub.angular.z = cmd_vel_pub.angular.z + 0.100000;
      if(cmd_vel_pub.angular.z > 0.97){
        cmd_vel_pub.angular.z = 1.0;
      }
    }
      if(key_input == 97 | key_input == 65){
      cmd_vel_pub.angular.z = cmd_vel_pub.angular.z - 0.100000;
      if(cmd_vel_pub.angular.z < -0.97){
        cmd_vel_pub.angular.z = -1.0;
      }
    }
      if(cmd_vel_pub.angular.z < 0.02 & cmd_vel_pub.angular.z > -0.02)
      {
        cmd_vel_pub.angular.z = 0.0;
      }

  intput_cmd_vels(cmd_vel_menu_number,cmd_vel_pub.angular.z);
  }

  return;

}

void pigeon_robot_steering::intput_cmd_vels(int cmd_vel_menu_number, double cmd_vel) // TUI에 사용할 cmd_vel 대입 함수
{
//----------------- linear_x -----------------//
  if(cmd_vel_menu_number == 0.0)
  {
    if(cmd_vel > 0.0){
    cmd_vels.linear_x = cmd_vel;
    cmd_vels.negative_linear_x = 0.0;
    }
    if(cmd_vel < 0.0){
    cmd_vels.linear_x = 0.0;
    cmd_vels.negative_linear_x = cmd_vel;
    }
    if(cmd_vel == 0.0){
    cmd_vels.linear_x = 0.0;
    cmd_vels.negative_linear_x = 0.0;
    }
    cmd_vel_pub.linear.x = cmd_vel;
  }

//----------------- linear_y -----------------//
  if(cmd_vel_menu_number == 1)
  {
    if(cmd_vel > 0.0){
    cmd_vels.linear_y = cmd_vel;
    cmd_vels.negative_linear_y = 0.0;
    }
    if(cmd_vel < 0.0){
    cmd_vels.linear_y = 0.0;
    cmd_vels.negative_linear_y = cmd_vel;
    }
    if(cmd_vel == 0.0){
    cmd_vels.linear_y = 0.0;
    cmd_vels.negative_linear_y = 0.0;
    }
    cmd_vel_pub.linear.y = cmd_vel;
  }

//----------------- linear_z -----------------//
  if(cmd_vel_menu_number == 2)
  {
    if(cmd_vel > 0.0){
    cmd_vels.linear_z = cmd_vel;
    cmd_vels.negative_linear_z = 0.0;
    }
    if(cmd_vel < 0.0){
    cmd_vels.linear_z = 0.0;
    cmd_vels.negative_linear_z = cmd_vel;
    }
    if(cmd_vel == 0.0){
    cmd_vels.linear_z = 0.0;
    cmd_vels.negative_linear_z = 0.0;
    }
    cmd_vel_pub.linear.z = cmd_vel;
  }

//----------------- angular_x -----------------//
  if(cmd_vel_menu_number == 3)
  {
    if(cmd_vel > 0.0){
    cmd_vels.angular_x = cmd_vel;
    cmd_vels.negative_angular_x = 0.0;
    }
    if(cmd_vel < 0.0){
    cmd_vels.angular_x = 0.0;
    cmd_vels.negative_angular_x = cmd_vel;
    }
    if(cmd_vel == 0.0){
    cmd_vels.angular_x = 0.0;
    cmd_vels.negative_angular_x = 0.0;
    }
    cmd_vel_pub.angular.x = cmd_vel;
  }

//----------------- angular_y -----------------//
  if(cmd_vel_menu_number == 4)
  {
    if(cmd_vel > 0.0){
    cmd_vels.angular_y = cmd_vel;
    cmd_vels.negative_angular_y = 0.0;
    }
    if(cmd_vel < 0.0){
    cmd_vels.angular_y = 0.0;
    cmd_vels.negative_angular_y = cmd_vel;
    }
    if(cmd_vel == 0.0){
    cmd_vels.angular_y = 0.0;
    cmd_vels.negative_angular_y = 0.0;
    }
    cmd_vel_pub.angular.y = cmd_vel;
  }

//----------------- angular_z -----------------//
  if(cmd_vel_menu_number == 5)
  {
    if(cmd_vel > 0.0){
    cmd_vels.angular_z = cmd_vel;
    cmd_vels.negative_angular_z = 0.0;
    }
    if(cmd_vel < 0.0){
    cmd_vels.angular_z = 0.0;
    cmd_vels.negative_angular_z = cmd_vel;
    }
    if(cmd_vel == 0.0){
    cmd_vels.angular_z = 0.0;
    cmd_vels.negative_angular_z = 0.0;
    }
    cmd_vel_pub.angular.z = cmd_vel;
  }
  return;
}

void pigeon_robot_steering::at_reset_cmd_vel(int cmd_vel_menu_number) // 현재 항목 cmd_vel 리셋 함수
{
//----------------- linear_x -----------------//
  if(cmd_vel_menu_number == 0){
    cmd_vel_pub.linear.x = 0;
    intput_cmd_vels(cmd_vel_menu_number,cmd_vel_pub.linear.x);
  }

//----------------- linear_y -----------------//
  if(cmd_vel_menu_number == 1){
    cmd_vel_pub.linear.y = 0;
    intput_cmd_vels(cmd_vel_menu_number,cmd_vel_pub.linear.y);
  }

//----------------- linear_z -----------------//
  if(cmd_vel_menu_number == 2){
    cmd_vel_pub.linear.z = 0;
    intput_cmd_vels(cmd_vel_menu_number,cmd_vel_pub.linear.z);
  }

//----------------- angular_x -----------------//
  if(cmd_vel_menu_number == 3){
    cmd_vel_pub.angular.x = 0;
    intput_cmd_vels(cmd_vel_menu_number,cmd_vel_pub.angular.x);
  }

//----------------- angular_y -----------------//
  if(cmd_vel_menu_number == 4){
    cmd_vel_pub.angular.y = 0;
    intput_cmd_vels(cmd_vel_menu_number,cmd_vel_pub.angular.y);
  }

//----------------- angular_z -----------------//
  if(cmd_vel_menu_number == 5){
    cmd_vel_pub.angular.z = 0;
    intput_cmd_vels(cmd_vel_menu_number,cmd_vel_pub.angular.z);
  }

  return;

}

void pigeon_robot_steering::all_reset_cmd_vel() // 모든 항목 cmd_vel 리셋 함수
{

  for(int i=0;i<6;i++){
    at_reset_cmd_vel(i);
  }

  return;

}

void pigeon_robot_steering::update_topic() // cmd_vel 토픽 퍼블리시 함수
{
  pub.publish(cmd_vel_pub);
  return;
}

void pigeon_robot_steering::spin() // 전체 흐름 제어 함수
{
  tui();
  set_key();
  update_topic();
  return;
}

void pigeon_robot_steering::exit() // 종료시 값 초기화 함수
{
  all_reset_cmd_vel();
  tui();
  update_topic();
  reset();
}

void pigeon_robot_steering::reset() // 터미널 리셋
{
  printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "pigeon_robot_steering");
  ros::NodeHandle n;
  ros::Rate loop_rate(60);

  pigeon_robot_steering robot_steering(n);

  while (ros::ok())
  {
    robot_steering.spin();
    if(robot_steering.key_input == 27)
    {
      robot_steering.exit();
      return 0;
    }

    loop_rate.sleep();
    ros::spinOnce();



  }
  return 0;

}
