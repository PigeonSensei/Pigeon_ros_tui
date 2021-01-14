/*
  pigeon robot steering.Ver 0.3
  maker PigeonSensei
  Date 2021.01.14
*/

#include <pigeon_tui/pigeon_robot_steering.h>

void Pigeon_robot_steering::DrawTUI() // TUI 함수
{
  std::string reset_position;

  // -------- style 조건문 --------------
  auto style_0 = (cmd_vel_menu_number_ == 0) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto style_1 = (cmd_vel_menu_number_ == 1) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto style_2 = (cmd_vel_menu_number_ == 2) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto style_3 = (cmd_vel_menu_number_ == 3) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto style_4 = (cmd_vel_menu_number_ == 4) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto style_5 = (cmd_vel_menu_number_ == 5) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);

  auto limit_style_0 = (cmd_vel_pub_.linear.x >= 1.0) ? (cmd_vel_menu_number_ == 0) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number_ == 0) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto limit_style_1 = (cmd_vel_pub_.linear.y >= 1.0) ? (cmd_vel_menu_number_ == 1) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number_ == 1) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto limit_style_2 = (cmd_vel_pub_.linear.z >= 1.0) ? (cmd_vel_menu_number_ == 2) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number_ == 2) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto limit_style_3 = (cmd_vel_pub_.angular.x >= 1.0) ? (cmd_vel_menu_number_ == 3) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number_ == 3) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto limit_style_4 = (cmd_vel_pub_.angular.y >= 1.0) ? (cmd_vel_menu_number_ == 4) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number_ == 4) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto limit_style_5 = (cmd_vel_pub_.angular.z >= 1.0) ? (cmd_vel_menu_number_ == 5) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number_ == 5) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);

  auto negative_limit_style_0 = (cmd_vel_pub_.linear.x <= -1.0) ? (cmd_vel_menu_number_ == 0) ? color(ftxui::Color::Red) | ftxui::dim : color(ftxui::Color::Red) : (cmd_vel_menu_number_ == 0) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto negative_limit_style_1 = (cmd_vel_pub_.linear.y <= -1.0) ? (cmd_vel_menu_number_ == 1) ? color(ftxui::Color::Red) | ftxui::dim : color(ftxui::Color::Red) : (cmd_vel_menu_number_ == 1) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto negative_limit_style_2 = (cmd_vel_pub_.linear.z <= -1.0) ? (cmd_vel_menu_number_ == 2) ? color(ftxui::Color::Red) | ftxui::dim : color(ftxui::Color::Red) : (cmd_vel_menu_number_ == 2) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto negative_limit_style_3 = (cmd_vel_pub_.angular.x <= -1.0) ? (cmd_vel_menu_number_ == 3) ? color(ftxui::Color::Red) | ftxui::dim : color(ftxui::Color::Red) : (cmd_vel_menu_number_ == 3) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto negative_limit_style_4 = (cmd_vel_pub_.angular.y <= -1.0) ? (cmd_vel_menu_number_ == 4) ? color(ftxui::Color::Red) | ftxui::dim : color(ftxui::Color::Red) : (cmd_vel_menu_number_ == 4) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto negative_limit_style_5 = (cmd_vel_pub_.angular.z <= -1.0) ? (cmd_vel_menu_number_ == 5) ? color(ftxui::Color::Red) | ftxui::dim : color(ftxui::Color::Red) : (cmd_vel_menu_number_ == 5) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);

  ftxui::Element Document =
  ftxui::vbox({
       // -------- Top panel --------------
       ftxui::hbox({
           ftxui::hbox({
              ftxui::text(L"Pigeon_robot_steering") | ftxui::bold | ftxui::center, ftxui::separator(),
           }),
           ftxui::text(L"cmd_vel")| color(ftxui::Color::Red) | ftxui::center, ftxui::separator(),
           ftxui::text(L"ver 0.3")| ftxui::bold,
           // -------- cmd_vel Menu --------------
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
              ftxui::gauge(1- (-1 * cmd_vels_.negative_linear_x)) | ftxui::inverted | negative_limit_style_0,
              ftxui::gauge(1- (-1 * cmd_vels_.negative_linear_y)) | ftxui::inverted | negative_limit_style_1,
              ftxui::gauge(1- (-1 * cmd_vels_.negative_linear_z)) | ftxui::inverted | negative_limit_style_2,
              ftxui::gauge(1- (-1 * cmd_vels_.negative_angular_x)) | ftxui::inverted | negative_limit_style_3,
              ftxui::gauge(1- (-1 * cmd_vels_.negative_angular_y)) | ftxui::inverted | negative_limit_style_4,
              ftxui::gauge(1- (-1 * cmd_vels_.negative_angular_z)) | ftxui::inverted | negative_limit_style_5,
              }) | ftxui::flex, ftxui::separator(),
           ftxui::vbox({
              ftxui::text(L"linear.x") | style_0 | ftxui::center,
              ftxui::text(L"linear.y") | style_1 | ftxui::center,
              ftxui::text(L"linear.z") | style_2 | ftxui::center,
              ftxui::text(L"angular.x") | style_3 | ftxui::center,
              ftxui::text(L"angular.y") | style_4 | ftxui::center,
              ftxui::text(L"angular.z") | style_5 | ftxui::center,
               }) | ftxui::bold,ftxui::separator(),
           ftxui::vbox({
              ftxui::gauge(cmd_vels_.linear_x) | limit_style_0,
              ftxui::gauge(cmd_vels_.linear_y) | limit_style_1,
              ftxui::gauge(cmd_vels_.linear_z) | limit_style_2,
              ftxui::gauge(cmd_vels_.angular_x) | limit_style_3,
              ftxui::gauge(cmd_vels_.angular_y) | limit_style_4,
              ftxui::gauge(cmd_vels_.angular_z) | limit_style_5,
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
      // -------- cmd_vel_info panel --------------
      ftxui::vbox({
          ftxui::hbox({
              ftxui::text(L"linear.x  : "),
              ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_pub_.linear.x) + " m/s")),
          }),
          ftxui::hbox({
              ftxui::text(L"linear.y  : "),
              ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_pub_.linear.y) + " m/s")),
          }),
          ftxui::hbox({
              ftxui::text(L"linear.z  : "),
              ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_pub_.linear.z) + " m/s")),
          }),
          ftxui::hbox({
              ftxui::text(L"angular.x : "),
              ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_pub_.angular.x) + " rad/s")),
          }),
          ftxui::hbox({
              ftxui::text(L"angular.y : "),
              ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_pub_.angular.y) + " rad/s")),
          }),
          ftxui::hbox({
              ftxui::text(L"angular.z : "),
              ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_pub_.angular.z) + " rad/s")),
              }),
          }) | ftxui::flex,
  });
  Document = border(Document);
  auto screen = ftxui::Screen::Create(
  ftxui::Dimension::Full(),       // Width
  ftxui::Dimension::Fit(Document) // Height
  );

  Render(screen, Document);

  pigeon_terminal_.ClearTerminal();
  std::cout << reset_position << screen.ToString() << std::flush;
  reset_position = screen.ResetPosition();

  return;
}

int Pigeon_robot_steering::SetKey() // 키 입력 함수
{
  key_value_ =  pigeon_terminal_.ReturnInputKey();
  if(key_value_ == 119 | key_value_ == 87){ // INPUT W
    cmd_vel_menu_number_ = cmd_vel_menu_number_ - 1;
    if(cmd_vel_menu_number_ < 0 ) cmd_vel_menu_number_ = 0;
  }
  if(key_value_ == 115 | key_value_ == 83){ // INPUT S
    cmd_vel_menu_number_ = cmd_vel_menu_number_ + 1;
    if(cmd_vel_menu_number_ > 5 ) cmd_vel_menu_number_ = 5;
  }
  if(key_value_ == 100 | key_value_ == 68) InputCmdVelData(cmd_vel_menu_number_, key_value_); //INPUT D
  if(key_value_ == 97 | key_value_ == 65) InputCmdVelData(cmd_vel_menu_number_, key_value_); //INPUT A

  if(key_value_ == 122 | key_value_ == 90) ResetAllCmdVel(); // INPUT Z
  if(key_value_ == 120 | key_value_ == 88) ResetAtCmdVel(cmd_vel_menu_number_); //INPUT X
  return 0;
}

void Pigeon_robot_steering::InputCmdVelData(int cmd_vel_menu_number, int key_value) // 키 입력에 따른 cmd_vel 대입 함수
{
//----------------- linear_x -----------------//
  if(cmd_vel_menu_number == 0)
  {
    if(key_value == 100 | key_value == 68){
      cmd_vel_pub_.linear.x = cmd_vel_pub_.linear.x + 0.010000;
      if(cmd_vel_pub_.linear.x > 0.997){
        cmd_vel_pub_.linear.x = 1.0;
      }
    }
     if(key_value == 97 | key_value == 65 ){
      cmd_vel_pub_.linear.x = cmd_vel_pub_.linear.x - 0.010000;
      if(cmd_vel_pub_.linear.x < -0.997){
        cmd_vel_pub_.linear.x = -1.0;
      }
    }
     if(cmd_vel_pub_.linear.x < 0.002 & cmd_vel_pub_.linear.x > -0.002)
     {
       cmd_vel_pub_.linear.x = 0.0;
     }

    InputCmdVels(cmd_vel_menu_number,cmd_vel_pub_.linear.x);
    }

//----------------- linear_y -----------------//
  if(cmd_vel_menu_number == 1)
  {
    if(key_value == 100 | key_value == 68){
      cmd_vel_pub_.linear.y = cmd_vel_pub_.linear.y + 0.010000;
      if(cmd_vel_pub_.linear.y > 0.997){
        cmd_vel_pub_.linear.y = 1.0;
      }
    }
      if(key_value == 97 | key_value == 65){
      cmd_vel_pub_.linear.y = cmd_vel_pub_.linear.y - 0.010000;
      if(cmd_vel_pub_.linear.y < -0.997){
        cmd_vel_pub_.linear.y = -1.0;
      }
    }
      if(cmd_vel_pub_.linear.y < 0.002 & cmd_vel_pub_.linear.y > -0.002)
      {
        cmd_vel_pub_.linear.y = 0.0;
      }

  InputCmdVels(cmd_vel_menu_number,cmd_vel_pub_.linear.y);
  }

//----------------- linear_z -----------------//
  if(cmd_vel_menu_number == 2)
  {
    if(key_value == 100 | key_value == 68){
      cmd_vel_pub_.linear.z = cmd_vel_pub_.linear.z + 0.010000;
      if(cmd_vel_pub_.linear.z > 0.997){
        cmd_vel_pub_.linear.z = 1.0;
      }
    }
      if(key_value == 97 | key_value == 65){

        cmd_vel_pub_.linear.z = cmd_vel_pub_.linear.z - 0.010000;
        if(cmd_vel_pub_.linear.z < -0.997){
          cmd_vel_pub_.linear.z = -1.0;
        }
    }
      if(cmd_vel_pub_.linear.z < 0.002 & cmd_vel_pub_.linear.z > -0.002)
      {
        cmd_vel_pub_.linear.z = 0.0;
      }

  InputCmdVels(cmd_vel_menu_number,cmd_vel_pub_.linear.z);
  }

//----------------- angular_x -----------------//
  if(cmd_vel_menu_number == 3)
  {
    if(key_value == 100 | key_value == 68){
      cmd_vel_pub_.angular.x = cmd_vel_pub_.angular.x + 0.010000;
      if(cmd_vel_pub_.angular.x > 0.997){
        cmd_vel_pub_.angular.x = 1.0;
      }
    }
      if(key_value == 97 | key_value == 65){
      cmd_vel_pub_.angular.x = cmd_vel_pub_.angular.x - 0.010000;
      if(cmd_vel_pub_.angular.x < -0.997){
        cmd_vel_pub_.angular.x = -1.0;
      }
    }
      if(cmd_vel_pub_.angular.x < 0.002 & cmd_vel_pub_.angular.x > -0.002)
      {
        cmd_vel_pub_.angular.x = 0.0;
      }
  InputCmdVels(cmd_vel_menu_number,cmd_vel_pub_.angular.x);
  }

//----------------- angular_y -----------------//
  if(cmd_vel_menu_number == 4)
  {
    if(key_value == 100 | key_value == 68){
      cmd_vel_pub_.angular.y = cmd_vel_pub_.angular.y + 0.010000;
      if(cmd_vel_pub_.angular.y > 0.997){
        cmd_vel_pub_.angular.y = 1.0;
      }
    }
      if(key_value == 97 | key_value == 65){
      cmd_vel_pub_.angular.y = cmd_vel_pub_.angular.y - 0.010000;
      if(cmd_vel_pub_.angular.y < -0.997){
        cmd_vel_pub_.angular.y = -1.0;
      }
    }
      if(cmd_vel_pub_.angular.y < 0.002 & cmd_vel_pub_.angular.y > -0.002)
      {
        cmd_vel_pub_.angular.y = 0.0;
      }

  InputCmdVels(cmd_vel_menu_number,cmd_vel_pub_.angular.y);
  }

//----------------- angular_z -----------------//
  if(cmd_vel_menu_number == 5)
  {
    if(key_value == 100 | key_value == 68){
      cmd_vel_pub_.angular.z = cmd_vel_pub_.angular.z + 0.010000;
      if(cmd_vel_pub_.angular.z > 0.997){
        cmd_vel_pub_.angular.z = 1.0;
      }
    }
      if(key_value == 97 | key_value == 65){
      cmd_vel_pub_.angular.z = cmd_vel_pub_.angular.z - 0.010000;
      if(cmd_vel_pub_.angular.z < -0.997){
        cmd_vel_pub_.angular.z = -1.0;
      }
    }
      if(cmd_vel_pub_.angular.z < 0.002 & cmd_vel_pub_.angular.z > -0.002)
      {
        cmd_vel_pub_.angular.z = 0.0;
      }

  InputCmdVels(cmd_vel_menu_number,cmd_vel_pub_.angular.z);
  }

  return;

}

void Pigeon_robot_steering::InputCmdVels(int cmd_vel_menu_number, double cmd_vel) // DrawTUI에 사용할 cmd_vel 대입 함수
{
//----------------- linear_x -----------------//
  if(cmd_vel_menu_number == 0.0)
  {
    if(cmd_vel > 0.0){
    cmd_vels_.linear_x = cmd_vel;
    cmd_vels_.negative_linear_x = 0.0;
    }
    if(cmd_vel < 0.0){
    cmd_vels_.linear_x = 0.0;
    cmd_vels_.negative_linear_x = cmd_vel;
    }
    if(cmd_vel == 0.0){
    cmd_vels_.linear_x = 0.0;
    cmd_vels_.negative_linear_x = 0.0;
    }
    cmd_vel_pub_.linear.x = cmd_vel;
  }

//----------------- linear_y -----------------//
  if(cmd_vel_menu_number == 1)
  {
    if(cmd_vel > 0.0){
    cmd_vels_.linear_y = cmd_vel;
    cmd_vels_.negative_linear_y = 0.0;
    }
    if(cmd_vel < 0.0){
    cmd_vels_.linear_y = 0.0;
    cmd_vels_.negative_linear_y = cmd_vel;
    }
    if(cmd_vel == 0.0){
    cmd_vels_.linear_y = 0.0;
    cmd_vels_.negative_linear_y = 0.0;
    }
    cmd_vel_pub_.linear.y = cmd_vel;
  }

//----------------- linear_z -----------------//
  if(cmd_vel_menu_number == 2)
  {
    if(cmd_vel > 0.0){
    cmd_vels_.linear_z = cmd_vel;
    cmd_vels_.negative_linear_z = 0.0;
    }
    if(cmd_vel < 0.0){
    cmd_vels_.linear_z = 0.0;
    cmd_vels_.negative_linear_z = cmd_vel;
    }
    if(cmd_vel == 0.0){
    cmd_vels_.linear_z = 0.0;
    cmd_vels_.negative_linear_z = 0.0;
    }
    cmd_vel_pub_.linear.z = cmd_vel;
  }

//----------------- angular_x -----------------//
  if(cmd_vel_menu_number == 3)
  {
    if(cmd_vel > 0.0){
    cmd_vels_.angular_x = cmd_vel;
    cmd_vels_.negative_angular_x = 0.0;
    }
    if(cmd_vel < 0.0){
    cmd_vels_.angular_x = 0.0;
    cmd_vels_.negative_angular_x = cmd_vel;
    }
    if(cmd_vel == 0.0){
    cmd_vels_.angular_x = 0.0;
    cmd_vels_.negative_angular_x = 0.0;
    }
    cmd_vel_pub_.angular.x = cmd_vel;
  }

//----------------- angular_y -----------------//
  if(cmd_vel_menu_number == 4)
  {
    if(cmd_vel > 0.0){
    cmd_vels_.angular_y = cmd_vel;
    cmd_vels_.negative_angular_y = 0.0;
    }
    if(cmd_vel < 0.0){
    cmd_vels_.angular_y = 0.0;
    cmd_vels_.negative_angular_y = cmd_vel;
    }
    if(cmd_vel == 0.0){
    cmd_vels_.angular_y = 0.0;
    cmd_vels_.negative_angular_y = 0.0;
    }
    cmd_vel_pub_.angular.y = cmd_vel;
  }

//----------------- angular_z -----------------//
  if(cmd_vel_menu_number == 5)
  {
    if(cmd_vel > 0.0){
    cmd_vels_.angular_z = cmd_vel;
    cmd_vels_.negative_angular_z = 0.0;
    }
    if(cmd_vel < 0.0){
    cmd_vels_.angular_z = 0.0;
    cmd_vels_.negative_angular_z = cmd_vel;
    }
    if(cmd_vel == 0.0){
    cmd_vels_.angular_z = 0.0;
    cmd_vels_.negative_angular_z = 0.0;
    }
    cmd_vel_pub_.angular.z = cmd_vel;
  }
  return;
}

void Pigeon_robot_steering::ResetAtCmdVel(int cmd_vel_menu_number) // 현재 항목 cmd_vel 리셋 함수
{
//----------------- linear_x -----------------//
  if(cmd_vel_menu_number == 0){
    cmd_vel_pub_.linear.x = 0;
    InputCmdVels(cmd_vel_menu_number,cmd_vel_pub_.linear.x);
  }

//----------------- linear_y -----------------//
  if(cmd_vel_menu_number == 1){
    cmd_vel_pub_.linear.y = 0;
    InputCmdVels(cmd_vel_menu_number,cmd_vel_pub_.linear.y);
  }

//----------------- linear_z -----------------//
  if(cmd_vel_menu_number == 2){
    cmd_vel_pub_.linear.z = 0;
    InputCmdVels(cmd_vel_menu_number,cmd_vel_pub_.linear.z);
  }

//----------------- angular_x -----------------//
  if(cmd_vel_menu_number == 3){
    cmd_vel_pub_.angular.x = 0;
    InputCmdVels(cmd_vel_menu_number,cmd_vel_pub_.angular.x);
  }

//----------------- angular_y -----------------//
  if(cmd_vel_menu_number == 4){
    cmd_vel_pub_.angular.y = 0;
    InputCmdVels(cmd_vel_menu_number,cmd_vel_pub_.angular.y);
  }

//----------------- angular_z -----------------//
  if(cmd_vel_menu_number == 5){
    cmd_vel_pub_.angular.z = 0;
    InputCmdVels(cmd_vel_menu_number,cmd_vel_pub_.angular.z);
  }

  return;

}

void Pigeon_robot_steering::ResetAllCmdVel() // 모든 항목 cmd_vel 리셋 함수
{

  for(int i=0;i<6;i++){
    ResetAtCmdVel(i);
  }

  return;

}

void Pigeon_robot_steering::UpdateTopic() // cmd_vel 토픽 퍼블리시 함수
{
  pub_.publish(cmd_vel_pub_);
  return;
}

void Pigeon_robot_steering::Spin() // 전체 흐름 제어 함수
{
  DrawTUI();
  SetKey();
  UpdateTopic();
  return;
}

void Pigeon_robot_steering::Exit() // 종료시 값 초기화 함수
{
  ResetAllCmdVel();
  DrawTUI();
  UpdateTopic();
  pigeon_terminal_.ClearTerminal();
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "pigeon_robot_steering_node");
  ros::NodeHandle n;
  ros::Rate loop_rate(60);

  Pigeon_robot_steering pigeon_robot_steering(n);

  while (ros::ok())
  {
    pigeon_robot_steering.Spin();
    if(pigeon_robot_steering.key_value_ == 27)
    {
      pigeon_robot_steering.Exit();
      return 0;
    }

    loop_rate.sleep();
    ros::spinOnce();

  }
  return 0;

}
