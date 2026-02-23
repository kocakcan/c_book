#!/bin/bash

tests=(
  "3 5 +|8"
  "3 5 + 2 *|16"
  "10 2 /|5"
  "10 3 %|1"
  "-5 3 +|-2"
  "3.5 2.5 +|6"
  "15 7 1 1 + - / 3 * 2 1 1 + + -|5"
)

echo "=== Running Calculator Tests ==="
passed=0
failed=0

for test in "${tests[@]}"; do
  input="${test%|*}"
  expected="${test#*|}"

  result=$(echo "$input" | ./calc | tail -1 | awk '{print $1}')

  if [ "$result" = "$expected" ]; then
    echo "✓ PASS: $input = $result"
    ((passed++))
  else
    echo "✗ FAIL: $input (expected $expected, got $result)"
    ((failed++))
  fi
done

echo
echo "=== Results ==="
echo "Passed: $passed"
echo "Failed: $failed"
