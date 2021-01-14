#ifndef PIGEON_ROBOT_STEERING_H
#define PIGEON_ROBOT_STEERING_H
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#include <termios.h>

#include "ftxui/component/container.hpp"
#include "ftxui/screen/string.hpp"
#include "ftxui/screen/color.hpp"
#include <pigeon_terminal/pigeon_terminal.h>

struct CmdVels
{
  double linear_x = 0;
  double negative_linear_x = 0;

  double linear_y = 0;
  double negative_linear_y = 0;

  double linear_z = 0;
  double negative_linear_z = 0;

  double angular_x = 0;
  double negative_angular_x = 0;

  double angular_y = 0;
  double negative_angular_y = 0;

  double angular_z = 0;
  double negative_angular_z = 0;

};

class Pigeon_robot_steering
{
public:
    Pigeon_robot_steering(ros::NodeHandle &n)
           : pub_(n.advertise<geometry_msgs::Twist>("cmd_vel",10))
       {
          // open run
          ROS_INFO("PIGEON_TUI_ROBOT_STEERING_NODE OPNE");
       }
       ~Pigeon_robot_steering()
       {
          // close run
          ROS_INFO("PIGEON_TUI_ROBOT_STEERING_NODE CLOSE");
       }

    void DrawTUI();

    int SetKey();

    void InputCmdVelData(int cmd_vel_menu_number, int key_input);

    void InputCmdVels(int cmd_vel_menu_number, double cmd_vel);

    void ResetAtCmdVel(int cmd_vel_menu_number);

    void ResetAllCmdVel();

    void UpdateTopic();

    void Spin();

    void Exit();

    int key_value_;

private:
    ros::Publisher pub_;
    geometry_msgs::Twist cmd_vel_pub_;
    CmdVels cmd_vels_;
    int cmd_vel_menu_number_ = 0;
    Pigeon_terminal pigeon_terminal_;

};
#endif // PIGEON_ROBOT_STEERING_H
