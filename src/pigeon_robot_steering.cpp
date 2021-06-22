/*
  pigeon robot steering.Ver 0.4
  maker PigeonSensei
  Date 2021.06.22
*/

#include <pigeon_tui/pigeon_robot_steering.h>

void PigeonRobotSteering::HideEcho(bool value)
{
  if(value == true)
  {
    tcgetattr(STDIN_FILENO, &org_term_);

    new_term_ = org_term_;

    new_term_.c_lflag &= ~(ECHO | ICANON);

    new_term_.c_cc[VMIN] = 0;
    new_term_.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_term_);
  }
  else tcsetattr(STDIN_FILENO, TCSANOW, &org_term_);

  return;
}

void PigeonRobotSteering::ClearTerminal()
{
  printf("\033[2J\033[1;1H");
  return;
}

int PigeonRobotSteering::ReturnInputKey()
{
  char input_key = 0;

  if(read(STDIN_FILENO, &input_key, 1) != 1) input_key = 0;

  else
  {
    char dummy;
    while (read(STDIN_FILENO, &dummy, 1) == 1) ;
  }

  return input_key;
}

void PigeonRobotSteering::DrawTUI()
{
  // -------- style --------------
  auto style_0 = (cmd_vel_menu_number_ == 0) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto style_1 = (cmd_vel_menu_number_ == 1) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto style_2 = (cmd_vel_menu_number_ == 2) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto style_3 = (cmd_vel_menu_number_ == 3) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto style_4 = (cmd_vel_menu_number_ == 4) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto style_5 = (cmd_vel_menu_number_ == 5) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);

  auto limit_style_0 = (cmd_vel_.linear.x >= 1.0) ? (cmd_vel_menu_number_ == 0) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number_ == 0) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto limit_style_1 = (cmd_vel_.linear.y >= 1.0) ? (cmd_vel_menu_number_ == 1) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number_ == 1) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto limit_style_2 = (cmd_vel_.linear.z >= 1.0) ? (cmd_vel_menu_number_ == 2) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number_ == 2) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto limit_style_3 = (cmd_vel_.angular.x >= 1.0) ? (cmd_vel_menu_number_ == 3) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number_ == 3) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto limit_style_4 = (cmd_vel_.angular.y >= 1.0) ? (cmd_vel_menu_number_ == 4) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number_ == 4) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto limit_style_5 = (cmd_vel_.angular.z >= 1.0) ? (cmd_vel_menu_number_ == 5) ? color(ftxui::Color::RedLight) | ftxui::dim : color(ftxui::Color::RedLight) : (cmd_vel_menu_number_ == 5) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);

  auto negative_limit_style_0 = (cmd_vel_.linear.x <= -1.0) ? (cmd_vel_menu_number_ == 0) ? color(ftxui::Color::Red) | ftxui::dim : color(ftxui::Color::Red) : (cmd_vel_menu_number_ == 0) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto negative_limit_style_1 = (cmd_vel_.linear.y <= -1.0) ? (cmd_vel_menu_number_ == 1) ? color(ftxui::Color::Red) | ftxui::dim : color(ftxui::Color::Red) : (cmd_vel_menu_number_ == 1) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto negative_limit_style_2 = (cmd_vel_.linear.z <= -1.0) ? (cmd_vel_menu_number_ == 2) ? color(ftxui::Color::Red) | ftxui::dim : color(ftxui::Color::Red) : (cmd_vel_menu_number_ == 2) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto negative_limit_style_3 = (cmd_vel_.angular.x <= -1.0) ? (cmd_vel_menu_number_ == 3) ? color(ftxui::Color::Red) | ftxui::dim : color(ftxui::Color::Red) : (cmd_vel_menu_number_ == 3) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto negative_limit_style_4 = (cmd_vel_.angular.y <= -1.0) ? (cmd_vel_menu_number_ == 4) ? color(ftxui::Color::Red) | ftxui::dim : color(ftxui::Color::Red) : (cmd_vel_menu_number_ == 4) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);
  auto negative_limit_style_5 = (cmd_vel_.angular.z <= -1.0) ? (cmd_vel_menu_number_ == 5) ? color(ftxui::Color::Red) | ftxui::dim : color(ftxui::Color::Red) : (cmd_vel_menu_number_ == 5) ? color(ftxui::Color::Default) | ftxui::dim : color(ftxui::Color::Default);

  ftxui::Element Document =
  ftxui::vbox
  ({
    // -------- Top panel --------------
    ftxui::hbox
    ({
      ftxui::hbox
      ({
         ftxui::text(L"Pigeon_robot_steering") | ftxui::bold | ftxui::center, ftxui::separator(),
      }),
      ftxui::text(ftxui::to_wstring(cmd_vel_topic_name_))| color(ftxui::Color::Red) | ftxui::center, ftxui::separator(),
      ftxui::text(L"ver 0.4")| ftxui::bold,
      // -------- cmd_vel Menu --------------
    }),
    ftxui::separator(),
    ftxui::hbox
    ({
      ftxui::vbox
      ({
        ftxui::text(L"-"),
        ftxui::text(L"-"),
        ftxui::text(L"-"),
        ftxui::text(L"-"),
        ftxui::text(L"-"),
        ftxui::text(L"-"),
      }) | ftxui::bold, ftxui::separator(),
      ftxui::vbox
      ({
        ftxui::gauge(1- (-1 * back_end_data_.negative_cmd_vel.linear.x)) | ftxui::inverted | negative_limit_style_0,
        ftxui::gauge(1- (-1 * back_end_data_.negative_cmd_vel.linear.y)) | ftxui::inverted | negative_limit_style_1,
        ftxui::gauge(1- (-1 * back_end_data_.negative_cmd_vel.linear.z)) | ftxui::inverted | negative_limit_style_2,
        ftxui::gauge(1- (-1 * back_end_data_.negative_cmd_vel.angular.x)) | ftxui::inverted | negative_limit_style_3,
        ftxui::gauge(1- (-1 * back_end_data_.negative_cmd_vel.angular.y)) | ftxui::inverted | negative_limit_style_4,
        ftxui::gauge(1- (-1 * back_end_data_.negative_cmd_vel.angular.z)) | ftxui::inverted | negative_limit_style_5,
      }) | ftxui::flex, ftxui::separator(),
      ftxui::vbox
      ({
        ftxui::text(L"linear.x") | style_0 | ftxui::center,
        ftxui::text(L"linear.y") | style_1 | ftxui::center,
        ftxui::text(L"linear.z") | style_2 | ftxui::center,
        ftxui::text(L"angular.x") | style_3 | ftxui::center,
        ftxui::text(L"angular.y") | style_4 | ftxui::center,
        ftxui::text(L"angular.z") | style_5 | ftxui::center,
      }) | ftxui::bold,ftxui::separator(),
      ftxui::vbox
      ({
        ftxui::gauge(back_end_data_.positive_cmd_vel.linear.x) | limit_style_0,
        ftxui::gauge(back_end_data_.positive_cmd_vel.linear.y) | limit_style_1,
        ftxui::gauge(back_end_data_.positive_cmd_vel.linear.z) | limit_style_2,
        ftxui::gauge(back_end_data_.positive_cmd_vel.angular.x) | limit_style_3,
        ftxui::gauge(back_end_data_.positive_cmd_vel.angular.y) | limit_style_4,
        ftxui::gauge(back_end_data_.positive_cmd_vel.angular.z) | limit_style_5,
      }) | ftxui::flex, ftxui::separator(),
      ftxui::vbox
      ({
        ftxui::text(L"+"),
        ftxui::text(L"+"),
        ftxui::text(L"+"),
        ftxui::text(L"+"),
        ftxui::text(L"+"),
        ftxui::text(L"+"),
      }),
    }) | ftxui::flex, ftxui::separator(),
    // -------- cmd_vel_info panel --------------
    ftxui::vbox
    ({
      ftxui::hbox
      ({
        ftxui::text(L"linear.x  : "),
        ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_.linear.x) + " m/s")),
      }),
      ftxui::hbox
      ({
        ftxui::text(L"linear.y  : "),
        ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_.linear.y) + " m/s")),
      }),
      ftxui::hbox
      ({
        ftxui::text(L"linear.z  : "),
        ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_.linear.z) + " m/s")),
      }),
      ftxui::hbox
      ({
        ftxui::text(L"angular.x : "),
        ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_.angular.x) + " rad/s")),
      }),
      ftxui::hbox
      ({
        ftxui::text(L"angular.y : "),
        ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_.angular.y) + " rad/s")),
      }),
      ftxui::hbox
      ({
        ftxui::text(L"angular.z : "),
        ftxui::text(ftxui::to_wstring(std::to_string(cmd_vel_.angular.z) + " rad/s")),
      }),
    }) | ftxui::flex,
  });

  Document = border(Document);
  auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(Document));

  Render(screen, Document);
  ClearTerminal();
  screen.Print();
  return;
}

int PigeonRobotSteering::GetInputKey()
{
  int minimum_menu_number = 0;
  int maximum_menu_number = 5;

  int key_value;

  key_value =  ReturnInputKey();

  // INPUT W
  if(key_value == 119 | key_value == 87)
  {
    cmd_vel_menu_number_ = cmd_vel_menu_number_ - 1;
    if(cmd_vel_menu_number_ < 0 ) cmd_vel_menu_number_ = minimum_menu_number;
  }

  // INPUT S
  if(key_value == 115 | key_value == 83)
  {
    cmd_vel_menu_number_ = cmd_vel_menu_number_ + 1;
    if(cmd_vel_menu_number_ > 5 ) cmd_vel_menu_number_ = maximum_menu_number;
  }

  //INPUT D
  if(key_value == 100 | key_value == 68) InputCmdVelBackEndData(cmd_vel_menu_number_, InputCmdVelData(cmd_vel_menu_number_, key_value));

  //INPUT A
  if(key_value == 97 | key_value == 65) InputCmdVelBackEndData(cmd_vel_menu_number_, InputCmdVelData(cmd_vel_menu_number_, key_value));

  //INPUT X
  if(key_value == 120 | key_value == 88) InputCmdVelBackEndData(cmd_vel_menu_number_, ResetCmdVelData(cmd_vel_menu_number_));

  // INPUT Z
  if(key_value == 122 | key_value == 90)
  {
    for(int i=0;i<6;i++)
    {
      InputCmdVelBackEndData(i,ResetCmdVelData(i));
    }
  }

  return 0;
}

double PigeonRobotSteering::InputCmdVelData(int cmd_vel_menu_number, int key_value)
{

//----------------- linear_x -----------------//
  if(cmd_vel_menu_number == 0)
  {
    if(key_value == 100 | key_value == 68)
    {
      cmd_vel_.linear.x = cmd_vel_.linear.x + 0.01;
      if(cmd_vel_.linear.x > 1.0) cmd_vel_.linear.x = 1.0;
    }
    if(key_value == 97 | key_value == 65 )
    {
      cmd_vel_.linear.x = cmd_vel_.linear.x - 0.01;
      if(cmd_vel_.linear.x < -1.0) cmd_vel_.linear.x = -1.0;
    }

    cmd_vel_.linear.x = round(cmd_vel_.linear.x * 100) / 100;
    return cmd_vel_.linear.x;
  }

//----------------- linear_y -----------------//
  if(cmd_vel_menu_number == 1)
  {
    if(key_value == 100 | key_value == 68)
    {
      cmd_vel_.linear.y = cmd_vel_.linear.y + 0.01;
      if(cmd_vel_.linear.y > 1.0) cmd_vel_.linear.y = 1.0;
    }
    if(key_value == 97 | key_value == 65)
    {
      cmd_vel_.linear.y = cmd_vel_.linear.y - 0.01;
      if(cmd_vel_.linear.y < -1.0) cmd_vel_.linear.y = -1.0;
    }

    cmd_vel_.linear.y = round(cmd_vel_.linear.y * 100) / 100;
    return cmd_vel_.linear.y;
  }

//----------------- linear_z -----------------//
  if(cmd_vel_menu_number == 2)
  {
    if(key_value == 100 | key_value == 68)
    {
      cmd_vel_.linear.z = cmd_vel_.linear.z + 0.01;
      if(cmd_vel_.linear.z > 1.0) cmd_vel_.linear.z = 1.0;
    }
    if(key_value == 97 | key_value == 65)
    {
      cmd_vel_.linear.z = cmd_vel_.linear.z - 0.01;
      if(cmd_vel_.linear.z < -1.0) cmd_vel_.linear.z = -1.0;
    }

    cmd_vel_.linear.z = round(cmd_vel_.linear.z * 100) / 100;
    return cmd_vel_.linear.z;
  }

//----------------- angular_x -----------------//
  if(cmd_vel_menu_number == 3)
  {
    if(key_value == 100 | key_value == 68)
    {
      cmd_vel_.angular.x = cmd_vel_.angular.x + 0.01;
      if(cmd_vel_.angular.x > 1.0) cmd_vel_.angular.x = 1.0;
    }
    if(key_value == 97 | key_value == 65)
    {
      cmd_vel_.angular.x = cmd_vel_.angular.x - 0.010000;
      if(cmd_vel_.angular.x < -1.0) cmd_vel_.angular.x = -1.0;
    }

    cmd_vel_.angular.x = round(cmd_vel_.angular.x * 100) / 100;
    return cmd_vel_.angular.x;
  }

//----------------- angular_y -----------------//
  if(cmd_vel_menu_number == 4)
  {
    if(key_value == 100 | key_value == 68)
    {
      cmd_vel_.angular.y = cmd_vel_.angular.y + 0.01;
      if(cmd_vel_.angular.y > 1.0) cmd_vel_.angular.y = 1.0;
    }
    if(key_value == 97 | key_value == 65)
    {
      cmd_vel_.angular.y = cmd_vel_.angular.y - 0.01;
      if(cmd_vel_.angular.y < -1.0) cmd_vel_.angular.y = -1.0;
    }

    cmd_vel_.angular.y = round(cmd_vel_.angular.y * 100) / 100;
    return cmd_vel_.angular.y;
  }

//----------------- angular_z -----------------//
  if(cmd_vel_menu_number == 5)
  {
    if(key_value == 100 | key_value == 68)
    {
      cmd_vel_.angular.z = cmd_vel_.angular.z + 0.01;
      if(cmd_vel_.angular.z > 1.0) cmd_vel_.angular.z = 1.0;
    }
    if(key_value == 97 | key_value == 65)
    {
      cmd_vel_.angular.z = cmd_vel_.angular.z - 0.01;
      if(cmd_vel_.angular.z < -1.0) cmd_vel_.angular.z = -1.0;
    }

    cmd_vel_.angular.z = round(cmd_vel_.angular.z * 100) / 100;
    return cmd_vel_.angular.z;

  }

  return 0.0;
}

void PigeonRobotSteering::InputCmdVelBackEndData(int cmd_vel_menu_number, double cmd_vel)
{

//----------------- linear_x -----------------//
  if(cmd_vel_menu_number == 0)
  {
    if(cmd_vel > 0.0)
    {
      back_end_data_.positive_cmd_vel.linear.x = cmd_vel;
      back_end_data_.negative_cmd_vel.linear.x = 0.0;
    }
    if(cmd_vel < 0.0)
    {
      back_end_data_.positive_cmd_vel.linear.x = 0.0;
      back_end_data_.negative_cmd_vel.linear.x = cmd_vel;
    }
    if(cmd_vel == 0.0)
    {
      back_end_data_.positive_cmd_vel.linear.x = 0.0;
      back_end_data_.negative_cmd_vel.linear.x = 0.0;
    }
  }

//----------------- linear_y -----------------//
  if(cmd_vel_menu_number == 1)
  {
    if(cmd_vel > 0.0)
    {
      back_end_data_.positive_cmd_vel.linear.y = cmd_vel;
      back_end_data_.negative_cmd_vel.linear.y = 0.0;
    }
    if(cmd_vel < 0.0)
    {
      back_end_data_.positive_cmd_vel.linear.y = 0.0;
      back_end_data_.negative_cmd_vel.linear.y = cmd_vel;
    }
    if(cmd_vel == 0.0)
    {
      back_end_data_.positive_cmd_vel.linear.y = 0.0;
      back_end_data_.negative_cmd_vel.linear.y = 0.0;
    }
  }

//----------------- linear_z -----------------//
  if(cmd_vel_menu_number == 2)
  {
    if(cmd_vel > 0.0)
    {
      back_end_data_.positive_cmd_vel.linear.z = cmd_vel;
      back_end_data_.negative_cmd_vel.linear.z = 0.0;
    }
    if(cmd_vel < 0.0)
    {
      back_end_data_.positive_cmd_vel.linear.z = 0.0;
      back_end_data_.negative_cmd_vel.linear.z = cmd_vel;
    }
    if(cmd_vel == 0.0)
    {
      back_end_data_.positive_cmd_vel.linear.z = 0.0;
      back_end_data_.negative_cmd_vel.linear.z = 0.0;
    }
  }

//----------------- angular_x -----------------//
  if(cmd_vel_menu_number == 3)
  {
    if(cmd_vel > 0.0)
    {
      back_end_data_.positive_cmd_vel.angular.x = cmd_vel;
      back_end_data_.negative_cmd_vel.angular.x = 0.0;
    }
    if(cmd_vel < 0.0)
    {
      back_end_data_.positive_cmd_vel.angular.x = 0.0;
      back_end_data_.negative_cmd_vel.angular.x = cmd_vel;
    }
    if(cmd_vel == 0.0)
    {
      back_end_data_.positive_cmd_vel.angular.x = 0.0;
      back_end_data_.negative_cmd_vel.angular.x = 0.0;
    }
  }

//----------------- angular_y -----------------//
  if(cmd_vel_menu_number == 4)
  {
    if(cmd_vel > 0.0)
    {
      back_end_data_.positive_cmd_vel.angular.y = cmd_vel;
      back_end_data_.negative_cmd_vel.angular.y = 0.0;
    }
    if(cmd_vel < 0.0)
    {
      back_end_data_.positive_cmd_vel.angular.y = 0.0;
      back_end_data_.negative_cmd_vel.angular.y = cmd_vel;
    }
    if(cmd_vel == 0.0)
    {
      back_end_data_.positive_cmd_vel.angular.y = 0.0;
      back_end_data_.negative_cmd_vel.angular.y = 0.0;
    }
  }

//----------------- angular_z -----------------//
  if(cmd_vel_menu_number == 5)
  {
    if(cmd_vel > 0.0)
    {
      back_end_data_.positive_cmd_vel.angular.z = cmd_vel;
      back_end_data_.negative_cmd_vel.angular.z = 0.0;
    }
    if(cmd_vel < 0.0)
    {
      back_end_data_.positive_cmd_vel.angular.z = 0.0;
      back_end_data_.negative_cmd_vel.angular.z = cmd_vel;
    }
    if(cmd_vel == 0.0)
    {
      back_end_data_.positive_cmd_vel.angular.z = 0.0;
      back_end_data_.negative_cmd_vel.angular.z = 0.0;
    }
  }
  return;
}

double PigeonRobotSteering::ResetCmdVelData(int cmd_vel_menu_number)
{

  if(cmd_vel_menu_number == 0) cmd_vel_.linear.x = 0;

  if(cmd_vel_menu_number == 1) cmd_vel_.linear.y = 0;

  if(cmd_vel_menu_number == 2) cmd_vel_.linear.z = 0;

  if(cmd_vel_menu_number == 3) cmd_vel_.angular.x = 0;

  if(cmd_vel_menu_number == 4) cmd_vel_.angular.y = 0;

  if(cmd_vel_menu_number == 5) cmd_vel_.angular.z = 0;

  return 0.0;

}

void PigeonRobotSteering::UpdateTopic()
{
  publisher_cmd_vel_.publish(cmd_vel_);
  return;
}

void PigeonRobotSteering::Spin()
{
  DrawTUI();
  GetInputKey();
  UpdateTopic();
  return;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "pigeon_robot_steering_node");
  ros::NodeHandle n;
  ros::Rate loop_rate(60);

  std::string cmd_vel_topic_name;

  if(argc == 1) cmd_vel_topic_name = "cmd_vel";
  else cmd_vel_topic_name = argv[1];

  PigeonRobotSteering pigeon_robot_steering(n,cmd_vel_topic_name);

  while (ros::ok())
  {
    pigeon_robot_steering.Spin();
    loop_rate.sleep();
    ros::spinOnce();
  }

  return 0;

}
