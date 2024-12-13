% % Initialize arrays to store end effector positions
% endEffectorPositions = [];

% % Define ranges for joint angles (in degrees)
% theta1_range = linspace(0, 180, 100);  % Joint 1 angles
% theta2_range = linspace(0, 360, 4);  % Joint 2 angles
% theta3_range = linspace(0, 360, 4);  % Joint 3 angles

% % Calculate total iterations for the progress bar
% totalIterations = length(theta1_range) * length(theta2_range) * length(theta3_range);

% % Create a waitbar
% hWaitbar = waitbar(0, 'Calculating End Effector Positions...');

% % Loop through all combinations of joint angles
% iterationCount = 0; % Initialize the iteration count
% for theta1 = theta1_range
%     for theta2 = theta2_range
%         for theta3 = theta3_range
%             % Combine angles into a vector
%             theta = [theta1, theta2, theta3];

%             % Call forward kinematics function to get the transformation matrix
%             T_matrix = forwardKinematics(theta, 'd');  % Use degrees

%             % Extract end effector position
%             position = T_matrix(1:3, 4);  % Get x, y, z position

%             % Store position for plotting
%             endEffectorPositions = [endEffectorPositions; position'];  % Store row-wise

%             % Update the iteration count and waitbar
%             iterationCount = iterationCount + 1; % Increment iteration count
%             waitbar(iterationCount / totalIterations, hWaitbar);  % Update waitbar
%         end
%     end
% end

% % Close the waitbar after calculations are done
% close(hWaitbar);

% % Save end effector positions to a CSV file
% csvwrite('end_effector_positions.csv', endEffectorPositions);

% % Optionally, plot the end effector positions
% figure;
% plot3(endEffectorPositions(:, 1), endEffectorPositions(:, 2), endEffectorPositions(:, 3), 'o');
% xlabel('X Position');
% ylabel('Y Position');
% zlabel('Z Position');
% title('End Effector Positions from Forward Kinematics');
% grid on;
% axis equal;  % Equal axis scaling for better visualization





% % Initialize arrays to store end effector positions
% endEffectorPositions = [];

% % Define ranges for joint angles (in degrees)
% theta1_range = linspace(0, 180, 50);  % Joint 1 angles
% theta2_range = linspace(0, 360, 25);    % Joint 2 angles
% theta3_range = linspace(0, 360, 25);    % Joint 3 angles

% % Calculate total iterations for the progress bar
% totalIterations = length(theta1_range) * length(theta2_range) * length(theta3_range);

% % Create a waitbar
% hWaitbar = waitbar(0, 'Calculating End Effector Positions...');

% % Create a figure for real-time plotting
% figure;
% hold on;  % Keep the plot active
% xlabel('X Position');
% ylabel('Y Position');
% zlabel('Z Position');
% title('End Effector Positions from Forward Kinematics');
% grid on;
% axis equal;  % Equal axis scaling for better visualization

% % Loop through all combinations of joint angles
% iterationCount = 0; % Initialize the iteration count
% for theta1 = theta1_range
%     for theta2 = theta2_range
%         for theta3 = theta3_range
%             % Combine angles into a vector
%             theta = [theta1, theta2, theta3];

%             % Call forward kinematics function to get the transformation matrix
%             T_matrix = forwardKinematics(theta, 'd');  % Use degrees

%             % Extract end effector position
%             position = T_matrix(1:3, 4);  % Get x, y, z position

%             % Store position for plotting
%             endEffectorPositions = [endEffectorPositions; position'];  % Store row-wise

%             % Plot the new position
%             plot3(position(1), position(2), position(3), 'ro');  % Plot current position as a red point
%             drawnow;  % Update the figure window immediately

%             % Update the iteration count and waitbar
%             iterationCount = iterationCount + 1; % Increment iteration count
%             waitbar(iterationCount / totalIterations, hWaitbar);  % Update waitbar
%         end
%     end
% end

% % Close the waitbar after calculations are done
% close(hWaitbar);




% % % Save end effector positions to a CSV file
% % csvwrite('end_effector_positions.csv', endEffectorPositions);
% % Load the data from the CSV file
% data = csvread('end_effector_positions_random.csv');

% % Get the number of rows in the data
% numRows = size(data, 1);

% % Randomly select 50% of the rows
% dropFraction = 0;
% indicesToKeep = randperm(numRows, round(numRows * (1 - dropFraction)));  % Randomly select 50% indices

% % Select the subset of data to plot
% reducedData = data(indicesToKeep, :);

% % Plot the reduced data set
% figure;
% plot3(reducedData(:, 1), reducedData(:, 2), reducedData(:, 3), '.');
% xlabel('X Position');
% ylabel('Y Position');
% zlabel('Z Position');
% title('End Effector Positions with 50% Randomly Dropped Values');
% grid on;
% axis equal;  % Equal axis scaling for better visualization






% % Initialize arrays to store end effector positions
% endEffectorPositions = [];

% % Set the number of points to plot
% numPoints = 5000;

% % Create a waitbar for progress indication
% hWaitbar = waitbar(0, 'Calculating End Effector Positions...');

% % Create a figure for real-time plotting
% figure;
% hold on;  % Keep the plot active
% xlabel('X Position');
% ylabel('Y Position');
% zlabel('Z Position');
% title('End Effector Positions from Forward Kinematics');
% grid on;
% axis equal;  % Equal axis scaling for better visualization

% % Loop through random joint angles
% for i = 1:numPoints
%     % Generate random joint angles for theta1, theta2, theta3
%     theta1 = rand() * 180;  % Random angle between 0 and 180 degrees
%     theta2 = rand() * 360;  % Random angle between 0 and 360 degrees
%     theta3 = rand() * 360;  % Random angle between 0 and 360 degrees
    
%     % Combine angles into a vector
%     theta = [theta1, theta2, theta3];

%     % Call forward kinematics function to get the transformation matrix
%     T_matrix = forwardKinematics(theta, 'd');  % Use degrees

%     % Extract end effector position
%     position = T_matrix(1:3, 4);  % Get x, y, z position

%     % Store position for future use
%     endEffectorPositions = [endEffectorPositions; position'];  % Store row-wise

%     % Plot the new position
%     plot3(position(1), position(2), position(3), 'ro');  % Plot current position as a red point
%     drawnow;  % Update the figure window immediately

%     % Update the waitbar
%     waitbar(i / numPoints, hWaitbar);  % Update waitbar with progress
% end

% % Close the waitbar after calculations are done
% close(hWaitbar);










% % Optionally, save end effector positions to a CSV file
% csvwrite('random_end_effector_positions.csv', endEffectorPositions);



% % Save the reshaped data into a CSV file in one line
% csvwrite('end_effector_positions_random.csv', endEffectorPositions);


% % Select and open the CSV file
% [filename, pathname] = uigetfile('*.csv', 'Select CSV file');
% if isequal(filename, 0)
%     disp('User canceled the file selection');
%     return;
% else
%     filePath = fullfile(pathname, filename);
%     data = readmatrix(filePath); % Read CSV file
% end

% % Assuming the CSV file has three columns: x, y, z
% x = data(:, 1); % First column for x
% y = data(:, 2); % Second column for y
% z = data(:, 3); % Third column for z

% % Plot the 3D points
% figure;
% scatter3(x, y, z, 'filled');
% xlabel('X');
% ylabel('Y');
% zlabel('Z');
% title('3D Plot of XYZ Points');






filePath = 'end_effector_positions_random.csv';

data = readmatrix(filePath);

x = data(:, 1);
y = data(:, 2);
z = data(:, 3);

figure;
scatter3(x, y, z, 'filled');
xlabel('X');
ylabel('Y');
zlabel('Z');
title('3D Plot of XYZ Points');

axis equal;