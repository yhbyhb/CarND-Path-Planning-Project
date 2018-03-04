#include <functional>
#include <iostream>
#include <vector>
#include "cmath"
#include "cost.h"


using namespace std;

float goal_distance_cost(int goal_lane, int intended_lane, int final_lane, float distance_to_goal) {
    /*
    The cost increases with both the distance of intended lane from the goal
    and the distance of the final lane from the goal. The cost of being out of the 
    goal lane also becomes larger as vehicle approaches the goal.
    */

    float cost = 0;

    float delta_d = (goal_lane - final_lane) + (goal_lane - intended_lane);
    float delta_s = distance_to_goal;

    cost = 1 - exp(fabs(delta_d) / delta_s);
    
    return cost;
}

float inefficiency_cost(int target_speed, int intended_lane, int final_lane, std::vector<double> lane_speeds) {
    /*
    Cost becomes higher for trajectories with intended lane and final lane that have traffic slower than target_speed.
    */

    float cost = 0;

    float delta = (target_speed - lane_speeds[intended_lane])
                 + (target_speed - lane_speeds[final_lane]);
    //cost = 1 - exp(-(delta));
    cost = delta / target_speed; //solution

    return cost;
}