function robot = sani(theta, unit)
    
    % Default values
    if nargin < 1
        theta = [0, 0.5, 0.5];
    elseif length(theta) ~= 3
        error('theta must be a 3-element vector: [joint angle, prismatic length1, prismatic length2].');
    end

    if nargin < 2
        unit = 'r';
    end
    


    % Define the links
    L(1) = Link([0 4 0 0 0], 'standard');
    L(2) = Link([0 theta(3) 0 -pi/2 1], 'standard');
    L(3) = Link([0 theta(2) 0 0 1], 'standard');

    % Joint limits
    L(1).qlim = [0, pi/2];
    L(2).qlim = [0, 4];
    L(3).qlim = [0, 4];
    
    % Convert angle to radians if needed
    if strcmpi(unit, 'd')
        theta(1) = deg2rad(theta(1));
    elseif ~strcmpi(unit, 'r')
        error('Unit must be either "degrees (d)" or "radians (r)".');
    end
    
    % Create the SerialLink robot
    robot = SerialLink([L(1) L(2) L(3)], 'name', 'RPP Robot');
    
    % Plot and teach the robot in the specified configuration
    robot.plot(theta);
    robot.teach(theta);
end
