# Assignment Objective

Implement and compare three search algorithms (IDDFS, UCS, and A*) to navigate an agent through
a dynamic maze with energy constraints and moving obstacles. The goal is to explore the strengths
and weaknesses of each algorithm in different scenarios.

## Environment Setup

Minimum Grid size should be 5x5 and it should be kept variable and its input should be given by the
user to ensure a generic code environment, the walls and fixed obstacles should be randomly placed.

- Maze: A grid where:
- (A) represents agent position.
- (‘ ’) represents an open space.
- (-) represents a wall.
- (O) represents fix obstacles that deduct 2 energy points.
- (G) represents the goal.
- Agent should start from top left and goal should be placed on bottom right of the grid.
- Agent: Starts in a given position and has a limited amount of energy. E.g. if grid size is 5x5 energy is
25, 6x6 energy is 36.
- The agent loses energy with each movement.
- The agent's movement is restricted to 4 possible directions: up, down, left, right.

### Key Features

1. Energy Constraint:
    - Agent consumes 1 energy point per move.
    - If it passes through an obstacle (not wall) 2 energy points will be consumed.

## Part 1: Environment and State Representation

### State Representation

- A state should include the agent’s position (x, y), current energy level.

### Movement

- The agent should only move into cells that are free (‘ ’) and not blocked by walls (-) or fixed
obstacles (O).

## Part 2: Implementing Search Algorithms

You need to implement the following search algorithms, handling all dynamic obstacles and energy
constraints:

### 1.Iterative Deepening Depth-First Search (IDDFS)

- Search depth-limited layers incrementally.
- Return the shortest path to the goal, if found.

### 2. Uniform Cost Search (UCS)

- Expand nodes based on the least cumulative cost (in this case, the number of moves and energy
consumption).
- Ensure that the agent finds the path that consumes the least energy.
- Track and compare paths based on both time and energy consumption.

### 3. A* Search

- Use a heuristic to guide the search. Choose either Manhattan or Euclidean distance as the
heuristic.
- The heuristic should account for the remaining distance to the goal and also the obstacles to find
the optimum path.
- Compare its efficiency with UCS in terms of time and energy usage.
Also implement an interface that shows the path that the agent takes in each algorithm.

## Part 3: Evaluation and Comparison

For each search algorithm, collect the following metrics:

1. Path length: Number of steps taken to reach the goal.
2. Energy consumed: Total energy used.
3. Time complexity: Number of nodes explored.
4. Space complexity: Memory usage, tracked by the maximum number of nodes stored in memory.

## Part 4: Handling Edge Cases

Make sure your implementation handles the following edge cases:

1. No Solution: The maze has no valid path to the goal (e.g., completely blocked off)

## IMPORTANT POINTS

Make a testing grid that has fixed walls on some places and some fixed obstacles. (Must)
Your testing grid should encompass all kinds of scenarios e.g. in which the Agent has to pass through
an obstacle to reach the goal in a lesser energy consumed. And all other similar cases must be
covered in these testing grids, testing grid should be of size 10x10.
Your path at the end of the program should be clear and if you’re just making a simple output UI
then make the path taken by the algorithm using asterisks (*) else if you’re doing it using some other
UI, draw the path taken by the algorithm explicitly.
Your report should be extensive having screenshots of the output and the comparison should be easy
to read (tabular format preferably).
Your report should also have different parts of codes where the functionality of important code
segments is mentioned and explained.
