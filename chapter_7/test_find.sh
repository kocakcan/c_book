#!/bin/bash

# ============================================
#  Test script for the find pattern program
#  A mini grep straight outta K&R
# ============================================

set -e

BIN="./find"
SRC="find.c"
PASS=0
FAIL=0
TEST_NUM=0

# Colors for output
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[1;33m"
CYAN="\033[0;36m"
RESET="\033[0m"

# ---- Compile ----
echo -e "${CYAN}============================================${RESET}"
echo -e "${CYAN}  Compiling find.c...${RESET}"
echo -e "${CYAN}============================================${RESET}"

gcc -Wall -Wextra -o "$BIN" "$SRC"
if [ $? -ne 0 ]; then
  echo -e "${RED}Compilation failed. Aborting.${RESET}"
  exit 1
fi
echo -e "${GREEN}Compilation successful!${RESET}\n"

# ---- Test runner ----
run_test() {
  local description="$1"
  local expected="$2"
  local actual="$3"

  TEST_NUM=$((TEST_NUM + 1))

  if [ "$expected" = "$actual" ]; then
    echo -e "${GREEN}[PASS]${RESET} Test $TEST_NUM: $description"
    PASS=$((PASS + 1))
  else
    echo -e "${RED}[FAIL]${RESET} Test $TEST_NUM: $description"
    echo -e "  ${YELLOW}Expected:${RESET}"
    echo "$expected" | sed 's/^/    /'
    echo -e "  ${YELLOW}Got:${RESET}"
    echo "$actual" | sed 's/^/    /'
    FAIL=$((FAIL + 1))
  fi
}

echo -e "${CYAN}============================================${RESET}"
echo -e "${CYAN}  Running tests...${RESET}"
echo -e "${CYAN}============================================${RESET}\n"

# ============================================
# TEST 1: Basic pattern match in a single file
# ============================================
expected="test/pirates.txt - Captain Blackbeard sailed the seven seas
test/pirates.txt - Captain Hook feared the crocodile
test/pirates.txt - Captain Sparrow was the luckiest of them all"

actual=$($BIN "Captain" test/pirates.txt)
run_test "Basic pattern match in single file" "$expected" "$actual"

# ============================================
# TEST 2: Pattern match with line numbers (-n)
# ============================================
expected="test/pirates.txt - 1: Captain Blackbeard sailed the seven seas
test/pirates.txt - 5: Captain Hook feared the crocodile
test/pirates.txt - 8: Captain Sparrow was the luckiest of them all"

actual=$($BIN -n "Captain" test/pirates.txt)
run_test "Pattern match with line numbers (-n)" "$expected" "$actual"

# ============================================
# TEST 3: Inverted match (-x)
# ============================================
expected="test/pirates.txt - The crew was loyal and brave
test/pirates.txt - Treasure was hidden on a remote island
test/pirates.txt - The parrot squawked at every sunrise
test/pirates.txt - No pirate ever refused a good rum
test/pirates.txt - The anchor was dropped at midnight
test/pirates.txt - The treasure map was torn and faded
test/pirates.txt - Every pirate needs a sharp cutlass"

actual=$($BIN -x "Captain" test/pirates.txt)
run_test "Inverted match (-x)" "$expected" "$actual"

# ============================================
# TEST 4: Combined flags (-xn)
# ============================================
expected="test/pirates.txt - 2: The crew was loyal and brave
test/pirates.txt - 3: Treasure was hidden on a remote island
test/pirates.txt - 4: The parrot squawked at every sunrise
test/pirates.txt - 6: No pirate ever refused a good rum
test/pirates.txt - 7: The anchor was dropped at midnight
test/pirates.txt - 9: The treasure map was torn and faded
test/pirates.txt - 10: Every pirate needs a sharp cutlass"

actual=$($BIN -xn "Captain" test/pirates.txt)
run_test "Combined flags (-xn)" "$expected" "$actual"

# ============================================
# TEST 5: Search across multiple files
# ============================================
expected="test/pirates.txt - Captain Blackbeard sailed the seven seas
test/pirates.txt - Captain Hook feared the crocodile
test/pirates.txt - Captain Sparrow was the luckiest of them all
test/crew.txt - Edward Teach - Captain
test/ship_log.txt - Day 4: Captain ordered full speed ahead"

actual=$($BIN "Captain" test/pirates.txt test/crew.txt test/ship_log.txt)
run_test "Search across multiple files" "$expected" "$actual"

# ============================================
# TEST 6: Multiple files with line numbers (-n)
# ============================================
expected="test/pirates.txt - 1: Captain Blackbeard sailed the seven seas
test/pirates.txt - 5: Captain Hook feared the crocodile
test/pirates.txt - 8: Captain Sparrow was the luckiest of them all
test/crew.txt - 4: Edward Teach - Captain
test/ship_log.txt - 4: Day 4: Captain ordered full speed ahead"

actual=$($BIN -n "Captain" test/pirates.txt test/crew.txt test/ship_log.txt)
run_test "Multiple files with line numbers (-n)" "$expected" "$actual"

# ============================================
# TEST 7: Reading from stdin (piped input)
# ============================================
expected="Day 5: Storm hit at midnight, lost two barrels of rum"

actual=$(cat test/ship_log.txt | $BIN "rum")
run_test "Reading from stdin (piped input)" "$expected" "$actual"

# ============================================
# TEST 8: No matches found (empty output)
# ============================================
expected=""

actual=$($BIN "ZZZZZ" test/pirates.txt)
run_test "No matches found (empty output)" "$expected" "$actual"

# ============================================
# TEST 9: Pattern that matches every line
# ============================================
expected="test/crew.txt - John Silver - First Mate
test/crew.txt - Anne Bonny - Quartermaster
test/crew.txt - Calico Jack - Navigator
test/crew.txt - Edward Teach - Captain
test/crew.txt - Mary Read - Gunner
test/crew.txt - Henry Morgan - Boatswain
test/crew.txt - Bartholomew Roberts - Lookout
test/crew.txt - Samuel Bellamy - Carpenter
test/crew.txt - Charles Vane - Surgeon
test/crew.txt - Stede Bonnet - Cook"

actual=$($BIN " - " test/crew.txt)
run_test "Pattern matches every line" "$expected" "$actual"

# ============================================
# TEST 10: Case sensitivity check
# ============================================
expected=""

actual=$($BIN "captain" test/pirates.txt)
run_test "Case sensitivity (lowercase 'captain' finds nothing)" "$expected" "$actual"

# ============================================
# TEST 11: Pattern 'mid' across multiple files
# ============================================
expected="test/ship_log.txt - Day 5: Storm hit at midnight, lost two barrels of rum"

actual=$($BIN "mid" test/crew.txt test/ship_log.txt)
run_test "Pattern 'mid' across multiple files" "$expected" "$actual"

# ============================================
# TEST 12: Inverted match with stdin
#   Lines in crew.txt WITHOUT "o":
#     Edward Teach - Captain      (no 'o')
#     Mary Read - Gunner          (no 'o')
#     Samuel Bellamy - Carpenter  (no 'o')
# ============================================
expected="Edward Teach - Captain
Mary Read - Gunner
Samuel Bellamy - Carpenter"

actual=$(cat test/crew.txt | $BIN -x "o")
run_test "Inverted match with stdin" "$expected" "$actual"

# ============================================
#  Results
# ============================================
echo ""
echo -e "${CYAN}============================================${RESET}"
echo -e "${CYAN}  Results${RESET}"
echo -e "${CYAN}============================================${RESET}"
echo -e "  Total:  $TEST_NUM"
echo -e "  ${GREEN}Passed: $PASS${RESET}"
echo -e "  ${RED}Failed: $FAIL${RESET}"
echo -e "${CYAN}============================================${RESET}"

# ---- Cleanup ----
rm -f "$BIN"

if [ $FAIL -ne 0 ]; then
  echo -e "\n${RED}Some tests failed!${RESET}"
  exit 1
else
  echo -e "\n${GREEN}All tests passed! Arrr! 🏴‍☠️${RESET}"
  exit 0
fi
