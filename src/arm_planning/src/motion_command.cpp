#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/robot_model/robot_model.h> 
#include <moveit/robot_state/robot_state.h> 
#include <moveit/kinematic_constraints/utils.h> 
#include <moveit/trajectory_processing/iterative_time_parameterization.h>

void scale_trajectory_speed(moveit::planning_interface::MoveGroupInterface::Plan &plan, double scale_factor) {
    // 实现函数逻辑
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "cartesian_path_demo", ros::init_options::AnonymousName);
 
    // 创建一个异步的自旋线程（spinning thread）
    ros::AsyncSpinner spinner(1);
    spinner.start();
 
    moveit::planning_interface::MoveGroupInterface move_group("arm");
 
    // 设置一个目标位置（路点）
    geometry_msgs::Pose target_pose;
    target_pose.orientation.w = 0.8129126437415342;
    target_pose.orientation.x = 0.23297924420790708;
    target_pose.orientation.y = 0.509018876993605;
    target_pose.orientation.z = 0.16060351265657682;
    target_pose.position.x = 0.4607054862676324;
    target_pose.position.y = 0.13631097298751307;
    target_pose.position.z = 0.4230179971879574;
    std::vector<geometry_msgs::Pose> waypoints;
    waypoints.push_back(target_pose);
 
    // 笛卡尔空间下的路径规划
    moveit_msgs::RobotTrajectory trajectory;
    const double jump_threshold = 0.0;
    const double eef_step = 0.01;
    double fraction = move_group.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
   
    // 生成机械臂的运动规划数据
    moveit::planning_interface::MoveGroupInterface::Plan plan;
    plan.trajectory_ = trajectory;
 
    scale_trajectory_speed(plan,0.3);
 
    // 执行运动
    move_group.execute(plan);
 
    ros::shutdown(); 
    return 0;
}
