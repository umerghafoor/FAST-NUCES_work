% Define the 3 revolute joints using DH parameters (theta, d, a, alpha)

% Link 1: Revolute joint
L(1) = Link([0 0 4 pi/2 0], 'standard');

% Link 2: Revolute joint
L(2) = Link([0 0 1 0 0], 'standard');

% Link 3: Revolute joint
L(3) = Link([0 0 1 0 0], 'standard');

% Create the robot model by combining the links
robot = SerialLink([L(1) L(2) L(3)], 'name', '3-DOF Revolute Robot');

% Define the initial joint angles for the robot
q_init = [0.5, 0.5, 0.5];  % Initial angles for the joints

% Plot the robot with the initial configuration
robot.plot(q_init);

% Interactive GUI to adjust joint angles
robot.teach;
