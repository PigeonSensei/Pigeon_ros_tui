# Pigeon ROS TUI

### Yotube Video
   https://youtu.be/TM9SyRRZrPo
   
## Dependency package

- [FTXUI](https://github.com/ArthurSonzogni/FTXUI)   
   
## Install

   - Clone the Pigeon ROS TUI & Install
   ```bash
   mkdir -p ~/catkin_ws/src
   cd ~/catkin_ws/src/
   git clone https://github.com/PigeonSensei/Pigeon_ros_tui.git
   catkin_init_workspace
   cd ..
   catkin_make 
   ```

### pigeon_robot_steering

```bash
rosrun pigeon_tui pigeon_robot_steering_node <topic_name>
```
#### args
- **topic name** 

  Publish the name used as an argument as a topic.
  If there is no argument, the topic is published with the cmd_vel name.

![pigeon_robot_steering_demo](./demo/pigeon_robot_steering_node.gif)
#### Input Key
- **select Item** : W,S
- **Change value** : A, S
- **at Reset value** : X
- **all Reset value** : Z


#### Published Topics
- **cmd_vel** ([geometry_msgs/Twist](http://docs.ros.org/en/api/geometry_msgs/html/msg/Twist.html))


The next node is under development ...

   
