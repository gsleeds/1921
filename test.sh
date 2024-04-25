#!/bin/bash

# Function to check the success or failure of a test based on return code
check_result() {
    local expected_code=$1
    local test_description=$2
    local exit_code=$?
    if [ $exit_code -eq $expected_code ]; then
        echo "PASS: $test_description"
    else
        echo "FAIL: $test_description (Expected return code $expected_code, got $exit_code)"
    fi
}

# Test for command line argument handling
./mazeCode > /dev/null 2>&1
check_result 0 "Correct number of arguments handled"

./mazeCode arg1 arg2 > /dev/null 2>&1
check_result 1 "Incorrect number of arguments handled"

# Test for invalid file name
./mazeCode missing_file.txt > /dev/null 2>&1
check_result 2 "Invalid file name handled"

# Test for characters other than "#", " ", "S", "E" in the maze file
./mazeCode invalid_characters_maze.txt > /dev/null 2>&1
check_result 3 "Invalid characters in maze handled"

# Test for maze size boundaries
./mazeCode invalid_size.txt > /dev/null 2>&1
check_result 3 "Invalid maze size handled"

# Test rows/columns not matching size
./mazeCode mismatched_rows_columns.txt > /dev/null 2>&1
check_result 3 "Mismatched rows and columns handled"

# Test correct maze
./mazeCode valid_maze.txt > /dev/null 2>&1
check_result 0 "Valid maze handled correctly"

# Test for movement/gameplay
# Test invalid key
./mazeCode valid_maze.txt < test_input/invalid_key.txt > /dev/null 2>&1
check_result 100 "Invalid key handled"

# Test multiple inputs of each actual key
./mazeCode valid_maze.txt < test_input/multiple_inputs.txt > /dev/null 2>&1
check_result 0 "Multiple inputs handled"

# Test no input
./mazeCode valid_maze.txt < test_input/no_input.txt > /dev/null 2>&1
check_result 0 "No input handled"

# Test attempting to move through a wall
./mazeCode valid_maze.txt < test_input/move_through_wall.txt > /dev/null 2>&1
check_result 0 "Move through wall handled"

# Test moving through the edge of the map
./mazeCode valid_maze.txt < test_input/move_edge_of_map.txt > /dev/null 2>&1
check_result 0 "Move through edge of map handled"

# Test key presses (WASD) actually moving the player
# 'W', 'A', 'S', 'D' should all be successful if they're valid moves
./mazeCode valid_maze.txt < test_input/w_key.txt > /dev/null 2>&1
check_result 0 "Valid key 'W' handled"

./mazeCode valid_maze.txt < test_input/a_key.txt > /dev/null 2>&1
check_result 0 "Valid key 'A' handled"

./mazeCode valid_maze.txt < test_input/s_key.txt > /dev/null 2>&1
check_result 0 "Valid key 'S' handled"

./mazeCode valid_maze.txt < test_input/d_key.txt > /dev/null 2>&1
check_result 0 "Valid key 'D' handled"

# Test moving onto the endpoint
./mazeCode valid_maze_small.txt < test_input/move_to_exit.txt > /dev/null 2>&1
check_result 0 "Moving onto the exit handled"

# Test 'M' and 'm' displays the map
./mazeCode valid_maze.txt < test_input/map_key.txt > /dev/null 2>&1
check_result 0 "Display map handled"