#ifndef PIGEON_ROBOT_STEERING_H
#define PIGEON_ROBOT_STEERING_H
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#include <termios.h>
//#include <unistd.h>


//#include <chrono>
//#include <iostream>
//#include <thread>

#include "ftxui/component/container.hpp"
//#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/string.hpp"
#include "ftxui/screen/color.hpp"

struct CMD_VELS
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


class pigeon_robot_steering
{
public:
    pigeon_robot_steering(ros::NodeHandle &n)
           : pub(n.advertise<geometry_msgs::Twist>("cmd_vel",1000))
       {
          // open run
          ROS_INFO("PIGEON_TUI_ROBOT_STEERING_NODE OPNE");
       }
       ~pigeon_robot_steering()
       {
          // close run
          ROS_INFO("PIGEON_TUI_ROBOT_STEERING_NODE CLOSE");
       }

    int keybord_input(void);

    void tui();

    int set_key();

    void intput_cmd_vel_data(int cmd_vel_menu_number, int key_input);

    void intput_cmd_vels(int cmd_vel_menu_number, double cmd_vel);

    void at_reset_cmd_vel(int cmd_vel_menu_number);

    void all_reset_cmd_vel();

    void update_topic();

    void spin();


    int key_input;

private:
    ros::Publisher pub;
    geometry_msgs::Twist cmd_vel_pub;
    CMD_VELS cmd_vels;
    int cmd_vel_menu_number = 0;

};
#endif // PIGEON_ROBOT_STEERING_H
