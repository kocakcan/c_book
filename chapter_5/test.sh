#!/bin/bash

echo "=== Test 1: Basic sorting (no options) ==="
echo "----------------------------------------"
cat sort_input.txt | ./sort
echo -e "\n"

echo "=== Test 2: Case-insensitive sorting (-f) ==="
echo "-------------------------------------------"
cat sort_input.txt | ./sort -f
echo -e "\n"

echo "=== Test 3: Directory order sorting (-d) ==="
echo "-----------------------------------------"
cat sort_input.txt | ./sort -d
echo -e "\n"

echo "=== Test 4: Both case-insensitive and directory order (-f -d) ==="
echo "------------------------------------------------------------"
cat sort_input.txt | ./sort -f -d
echo -e "\n"

# Optional: Test different order of options
echo "=== Test 5: Both options in reverse order (-d -f) ==="
echo "------------------------------------------------"
cat sort_input.txt | ./sort -d -f
echo -e "\n"
