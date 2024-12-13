% Description: This script is used to calculate the pose of the end-effector of a 3-DOF robot given the joint angles.

% theta = [0.4, 0.4, 0.4];  % Specify the joint angles for the robot
% pose = returnspecificpose(theta);  % Get the pose of the robot's end-effector

% % Display the position and orientation
% disp('End-Effector Position:');
% disp(pose.translation);
% disp('End-Effector Orientation:');
% disp(pose.rotation);



% theta = [0, 0, 0];  % Joint angles in radians
% r = createrobot(theta, 'r');  % Create and visualize the robot


% % theta = [0, 90, 0];  % Joint angles in degrees
% % createrobot(theta, 'd');  % Create and visualize the robot

% theta = [0, 180, 0];  % Joint angles in degrees
% pose = returnspecificpose(theta, 'd');  % Get the pose of the robot's end effector
% disp(pose.position);  % Display the position and orientation
% disp(pose.orientation);

% T = pose.T_matrix;  % Get the transformation matrix
% disp(T);

% joint_angles = r.ikine(T, 'mask', [1 1 1 0 0 0], 'q0', theta);  % Adjust options as necessary
% % agngle = r.ikine(T);  % Calculate the inverse kinematics to find joint angles
% disp(joint_angles);  % Display the joint angles

% theta = [0, 90, 0];  % Example joint angles in degrees
% T_matrix = forwardKinematics(theta, 'd');
% disp(T_matrix);


% % % Link lengths of the robotic arm
% L = [4, 1, 1];  % Example lengths for L1, L2, and L3

% % Desired end effector position
% x = 4;  % X coordinate
% y = 0;  % Y coordinate
% z = 2;  % Z coordinate

% % Calculate the joint angles using the inverse kinematics function
% joint_angles = inverseKinematics(x, y, z, L);

% % Display the results
% disp('Joint Angles (radians):');
% disp(joint_angles);




% % Step 1: Define the robot
% L(1) = Link([0, 0, 4, pi/2, 0], 'standard');  % Link 1
% L(2) = Link([0, 0, 1, 0, 0], 'standard');     % Link 2
% L(3) = Link([0, 0, 1, 0, 0], 'standard');     % Link 3

% r = SerialLink([L(1), L(2), L(3)], 'name', '3-DOF Revolute Robot');

% % Step 2: Specify the target position
% target_position = [0, 0, 5];  % Example target position

% % Step 3: Call the inverse kinematics function
% joint_angles = inverseKinematics(r, target_position);

% % Display the joint angles
% disp('Calculated joint angles (in radians):');
% disp(joint_angles);

% % Optionally, plot the robot in the calculated configuration
% r.plot(joint_angles);


% % Create the robot
% theta = [0, 0, 0];  % Initial joint angles in radians
% r = createrobot(theta, 'r');  % Create and visualize the robot

% % Define the target position and orientation
% target_position = [4, 0, 2];  % Example target position (x, y, z)
% target_orientation = [0, 0, 0];  % Example target orientation (roll, pitch, yaw)

% % Calculate joint angles using inverse kinematics
% joint_angles = inverseKinematics(r, target_position);

% % Display the joint angles
% disp('Calculated Joint Angles:');
% disp(joint_angles);
