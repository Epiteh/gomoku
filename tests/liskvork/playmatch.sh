#!/bin/bash

CONFIG_DIR="./confs/"

LISKVORK_EXEC="./bin/liskvork"

if [ $# -eq 0 ]; then
  echo "Usage: $0 [all|self|MinMaxAB|MinMaxTree|unknown|random] [number_of_games]"
  exit 1
fi

if [ $# -eq 2 ]; then
  if ! [[ "$2" =~ ^[0-9]+$ ]]; then
    echo "Error: number of game(s) must be a valid number"
    exit 1
  fi
  NUMBER_OF_GAMES=$2
else
  NUMBER_OF_GAMES=1
fi

if [ "$1" == "all" ]; then
  echo "Running $NUMBER_OF_GAMES game(s) against all test-purpose AIs"
elif [ "$1" == "self" ]; then
  echo "Running $NUMBER_OF_GAMES game(s) against itself"
  CONFIG_DIR+="/self"
elif [ "$1" == "MinMaxAB_py" ]; then
  echo "Running $NUMBER_OF_GAMES game(s) against MinMaxAB ai"
  CONFIG_DIR+="/MinMaxAB_py"
elif [ "$1" == "unknown" ]; then
  echo "Running $NUMBER_OF_GAMES game(s) against unknown ai"
  CONFIG_DIR+="/unknown"
elif [ "$1" == "random" ]; then
  OPTIONS=("self" "MinMaxAB" "MinMaxTree" "unknown")
  RANDOM_OPTION=${OPTIONS[$RANDOM % ${#OPTIONS[@]}]}
  echo "Randomly selected option: $RANDOM_OPTION"
  CONFIG_DIR+="/$RANDOM_OPTION/"
else
  echo "Error: invalid argument $1"
  exit 1
fi

if [ ! -d "$CONFIG_DIR" ]; then
  echo "Error: configuration directory not found at $CONFIG_DIR"
  exit 1
fi

for config_file in "$CONFIG_DIR"*; do
  echo "Running test for: $config_file"
  if [ -f "$config_file"/config.ini ]; then
    for ((i=1; i<=NUMBER_OF_GAMES; i++)); do
      "$LISKVORK_EXEC" "$config_file/config.ini"
      echo "Test $i completed for: $config_file"
      echo "-----------------------------"
    done
  fi
done

echo "All tests completed."