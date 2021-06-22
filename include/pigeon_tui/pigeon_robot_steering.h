#ifndef PIGEON_ROBOT_STEERING_H
#define PIGEON_ROBOT_STEERING_H
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#include <termios.h>

#include "ftxui/component/container.hpp"
#include "ftxui/screen/string.hpp"
#include "ftxui/screen/color.hpp"

class PigeonRobotSteering
{
public:
    PigeonRobotSteering(ros::NodeHandle &n, std::string cmd_vel_topic_name)
           : publisher_cmd_vel_(n.advertise<geometry_msgs::Twist>(cmd_vel_topic_name,10)),
             cmd_vel_topic_name_(cmd_vel_topic_name)
       {
         HideEcho(true);
         ClearTerminal();
       }
       ~PigeonRobotSteering()
       {
         HideEcho(false);
         for(int i=0;i<6;i++)
         {
           InputCmdVelBackEndData(i,ResetCmdVelData(i));
         }
         DrawTUI();
         UpdateTopic();
         ClearTerminal();
       }

    void HideEcho(bool value);

    void ClearTerminal();

    int ReturnInputKey();

    void DrawTUI();

    int GetInputKey();

    double InputCmdVelData(int cmd_vel_menu_number, int key_input);

    double ResetCmdVelData(int cmd_vel_menu_number);

    void InputCmdVelBackEndData(int cmd_vel_menu_number, double cmd_vel);

    void UpdateTopic();

    void Spin();

private:

    struct BackEndData
    {
      geometry_msgs::Twist positive_cmd_vel;
      geometry_msgs::Twist negative_cmd_vel;
    };

    ros::Publisher publisher_cmd_vel_;
    geometry_msgs::Twist cmd_vel_;
    BackEndData back_end_data_;
    int cmd_vel_menu_number_ = 0;

    std::string cmd_vel_topic_name_;
    struct termios org_term_;
    struct termios new_term_;

};
#endif // PIGEON_ROBOT_STEERING_H
