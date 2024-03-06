#!/bin/bash

# Function to check the success or failure of a test
check_result() {
    if grep -q "error" tmp; then
        echo "FAIL"
    else
        echo "PASS"
    fi
}

# Test for command line argument handling

# Test for the correct number of command line arguments
./mazeCode > tmp 2>&1
check_result "Correct number of arguments handled"

./mazeCode arg1 arg2 > tmp 2>&1
check_result "Incorrect number of arguments handled"

# Test for invalid file name
./mazeCode missing_file.txt > tmp 2>&1
check_result "Invalid file name handled"

# Test for characters other than "#"", " ", "S", "E" in the maze file
./mazeCode invalid_characters_maze.txt > tmp 2>&1
check_result "Invalid characters in maze handled"

# Test for maze size boundaries
./mazeCode invalid_size.txt > tmp 2>&1
check_result "Invalid maze size handled"

# Test rows/columns not matching size
./mazeCode mismatched_rows_columns.txt > tmp 2>&1
check_result "Mismatched rows and columns handled"

# Test correct maze
./mazeCode valid_maze.txt > tmp
# Compare the output with the expected output using a tool like 'diff'
if diff -q tmp expected_output.txt; then
    echo "PASS: Valid maze handled correctly"
else
    echo "FAIL: Valid maze not handled correctly"
fi

# Test for movement/gameplay

# Test all other keys for error
./mazeCode valid_maze.txt < invalid_key.txt > tmp 2>&1
check_result "Invalid key handled"

# Test multiple inputs of each actual key
./mazeCode valid_maze.txt < multiple_inputs.txt > tmp 2>&1
check_result "Multiple inputs handled"

# Test no input
./mazeCode valid_maze.txt < no_input.txt > tmp 2>&1
check_result "No input handled"

# Test attempting to move through a wall
./mazeCode valid_maze.txt < move_through_wall.txt > tmp 2>&1
check_result "Move through wall handled"

# Test moving through the edge of the map
./mazeCode valid_maze.txt < move_edge_of_map.txt > tmp 2>&1
check_result "Move through edge of map handled"

# Test key presses (WASD) actually moving the player
# Test 'W' key
echo "W" | ./mazeCode valid_maze.txt < w_key.txt > tmp 2>&1
check_result "Invalid key 'W' handled"

# Test 'A' key
echo "A" | ./mazeCode valid_maze.txt < a_key.txt > tmp 2>&1
check_result "Invalid key 'A' handled"

# Test 'S' key
echo "S" | ./mazeCode valid_maze.txt < s_key.txt > tmp 2>&1
check_result "Invalid key 'S' handled"

# Test 'D' key
echo "D" | ./mazeCode valid_maze.txt < d_key.txt > tmp 2>&1
check_result "Invalid key 'D' handled"

# Test moving onto the endpoint
./mazeCode valid_maze_small.txt < move_to_exit.txt > tmp
check_result "Moving onto the exit handled"

# Test 'M' and 'm' displays the map
./mazeCode valid_maze.txt < map_key.txt > tmp
check_result "Display map handled"

# Test the displayed map is correct
./mazeCode valid_maze.txt > tmp
# Compare the output with the expected output using a tool like 'diff'
if diff -q tmp expected_output.txt; then
    echo "PASS: Displayed map is correct"
else
    echo "FAIL: Displayed map is not correct"
fi

# Clean up temporary files
rm tmp