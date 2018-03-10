# **Project: Path Planning Project**
[![Udacity - Self-Driving Car Engineer NanoDegree Program](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)


## Overview
This repository contains all the codes and reflection that required for completing project. The goal of this project is to safely navigate around a virtual highway with other traffic.

Build instruction and dependency of this project is identical to [upstream repository](https://github.com/udacity/CarND-Path-Planning-Project) which is the starter code repository of udacity.

## Project rubric

I followed criteria of [project rubric](https://review.udacity.com/#!/rubrics/1020/view).

### Compilation

#### The code compiles correctly.
I added `spline.h` for smooth acceleration of vehicle but it doesn't not require to added to `CMakeLists.txt`. The compilation has no error.

### Valid Trajectories
[//]: # (Image References)

[result]: ./img/term3_p1_30min_driving.png "30 mins driving"

![alt text][result]

While driving about 30 minutes, the car kept all of the following rubrics.

- The car is able to drive at least 4.32 miles without incident.
- The car drives according to the speed limit.
- Max Acceleration and Jerk are not Exceeded.
- Car does not have collisions.
- The car stays in its lane, except for the time between changing lanes.
- The car is able to change lanes

Here is the [youtube link](https://www.youtube.com/watch?v=zbTH357hVIY) of 30 minutes driving.

### Reflection
All of my code for generating paths is in `line 236 ~ 598` of `main.cpp`. It is based on [Project Walkthrough and Q&A](https://classroom.udacity.com/nanodegrees/nd013/parts/6047fe34-d93c-4f50-8336-b70ef10cb4b2/modules/27800789-bc8e-4adc-afe0-ec781e82ceae/lessons/23add5c6-7004-47ad-b169-49a5d7b1c1cb/concepts/3bdfeb8c-8dd6-49a7-9d08-beff6703792d) of lecture.

This project is very specific case of path planning. expressway driving. There is no traffic light, pedestrian or bikes. So I decided to simplify model for generating paths. So I don't use searching path algorithm such as hybrid a star. Also, I didn't make cost function for behavior planning. I just decided whether increasing or decreasing speed and change lanes or keep lane.

The code model for generating paths is consisted of three parts, prediction, behavior planning and trajectory generation as following.

#### Prediction
`Line 236 ~ 405` in `main.cpp` is the prediction part. With sensor fusion data and previous_path_x size, future positions (s position, lane) and speed of each car are calculated. Following criteria are important for behavior planning.

* What lane is the car exist? same lane of my car, left or right?
* Is that car ahead or behind?

With above criteria, 6 near positions are generated(ahead left, ahead center, ahead right, behind left, behind center and behind right).

`Line 407 ~ 429` of `main.cpp` shows each near car's id, distance and speed.

During the prediction, there were weired sensor fusion data. Sometimes `d` position comes with `0.0` which represents centerline of the road and `d` can't be 0 with this simulator. So I calculated `s` and `d` position with `getFrenet()` with `x` and `y` position of sensor fusion data as written in `line 92 ~ 138`, use them when `0` comes with sensor fusion data.

#### Behavior planning
Planning behavior of car is located on `line 431 ~ 487` of `main.cpp`. Our goal is just moving forward, and there is no goal lane or goal distance. Simple behavior model is used.

* Is there a car ahead?
* Is it possible to change the lane?
* Is it safe to increase speed?

Additional behavior is added for the first or last lane driving. Since leftmost and rightmost lane driving can change only one direction, So, If car can change the lane, change the lane toward to middle lane.

#### Trajectory generation
As I mentioned above, this code based [Project Walkthrough and Q&A](https://classroom.udacity.com/nanodegrees/nd013/parts/6047fe34-d93c-4f50-8336-b70ef10cb4b2/modules/27800789-bc8e-4adc-afe0-ec781e82ceae/lessons/23add5c6-7004-47ad-b169-49a5d7b1c1cb/concepts/3bdfeb8c-8dd6-49a7-9d08-beff6703792d). This part is almost same of the lecture video. `Line 489 ~ 598` in `main.cpp` is the code of this part.

The trajectory is generated with previous path points, lane and speed from behavior planning part. Firstly, last two path position of previous trajectory are used for making spline. Far three position (30, 60, 90m) are also used for generating spline curve. Before the generating spline, the coordinate of the points mentioned right before is transformed into my car coordination for the simplifying calculation.  `spline.h` is used for smooth acceleration and changing lane. Detailed comments are in codes.

Previous path are used for continuity of trajectory. Rest of the points are generated with spline and by transforming the coordinate from car's to global x, y position. Output points is 50 points.






