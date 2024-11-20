#!/usr/bin/env python3

import os
import subprocess
import time
from tabulate import tabulate
from tqdm import tqdm

GREEN = "\033[92m"
RED = "\033[91m"
RESET = "\033[0m"

single_scenarios = [
    {
        "name": "HORIZONTAL 4",
        "board": [
            "9,10,2",
            "10,10,1",
            "11,10,1",
            "12,10,1"
        ],
        "expected": "13,10"
    },
    {
        "name": "VERTICAL 4",
        "board": [
            "5,4,2",
            "5,5,1",
            "5,6,1",
            "5,7,1",
        ],
        "expected": "5,8"
    },
    {
        "name": "SPLIT HORIZONTAL 4",
        "board": [
            "7,7,2",
            "8,7,1",
            "9,7,1",
            "11,7,1"
        ],
        "expected": "10,7"
    },
    {
        "name": "SPLIT VERTICAL 4",
        "board": [
            "5,5,2",
            "5,6,1",
            "5,7,1",
            "5,9,1"
        ],
        "expected": "5,8"
    },
    {
        "name": "SPLIT DIAGONAL 4",
        "board": [
            "8,8,2",
            "9,9,1",
            "11,11,1",
            "12,12,1"
        ],
        "expected": "10,10"
    },
    {
        "name": "HORIZONTAL 5 WIN",
        "board": [
            "9,10,2",
            "10,10,1",
            "11,10,1",
            "12,10,1",
            "13,10,1"
        ],
        "expected": "14,10"
    },
    {
        "name": "DIAGONAL 5 WIN",
        "board": [
            "9,9,2",
            "10,10,1",
            "11,11,1",
            "12,12,1",
            "13,13,1"
        ],
        "expected": "14,14"
    },
    {
        "name": "VERTICAL 5 WIN",
        "board": [
            "5,4,2",
            "5,5,1",
            "5,6,1",
            "5,7,1",
            "5,8,1"
        ],
        "expected": "5,9"
    },
    {
        "name": "SPLIT HORIZONTAL 5 WIN",
        "board": [
            "7,7,2",
            "8,7,1",
            "9,7,1",
            "11,7,1",
            "12,7,1"
        ],
        "expected": "10,7"
    },
    {
        "name": "SPLIT VERTICAL 5 WIN",
        "board": [
            "5,5,2",
            "5,6,1",
            "5,7,1",
            "5,9,1",
            "5,10,1"
        ],
        "expected": "5,8"
    },
    {
        "name": "SPLIT DIAGONAL 5 WIN",
        "board": [
            "8,8,2",
            "9,9,1",
            "11,11,1",
            "12,12,1",
            "13,13,1"
        ],
        "expected": "10,10"
    },
    {
        "name": "HORIZONTAL 2 DEFENSE",
        "board": [
            "10,10,1",
            "11,10,2",
            "12,10,2"
        ],
        "expected": "13,10"
    },
    {
        "name": "DIAGONAL 2 DEFENSE",
        "board": [
            "8,8,1",
            "9,9,2",
            "10,10,2"
        ],
        "expected": "11,11"
    },
    {
        "name": "VERTICAL 2 DEFENSE",
        "board": [
            "5,5,1",
            "5,6,2",
            "5,7,2"
        ],
        "expected": "5,8"
    },
    {
        "name": "HORIZONTAL 3 DEFENSE",
        "board": [
            "10,10,1",
            "11,10,2",
            "12,10,2",
            "13,10,2"
        ],
        "expected": "14,10"
    },
    {
        "name": "DIAGONAL 3 DEFENSE",
        "board": [
            "10,10,1",
            "11,11,2",
            "12,12,2",
            "13,13,2"
        ],
        "expected": "14,14"
    },
    {
        "name": "VERTICAL 3 DEFENSE",
        "board": [
            "5,6,1",
            "5,7,2",
            "5,8,2",
            "5,9,2"
        ],
        "expected": "5,10"
    },
    {
        "name": "HORIZONTAL 4 DEFENSE",
        "board": [
            "10,10,1",
            "11,10,2",
            "12,10,2",
            "13,10,2",
            "14,10,2"
        ],
        "expected": "15,10"
    },
    {
        "name": "DIAGONAL 4 DEFENSE",
        "board": [
            "6,6,1",
            "5,5,2",
            "4,4,2",
            "3,3,2",
            "2,2,2"
        ],
        "expected": "1,1"
    },
    {
        "name": "VERTICAL 4 DEFENSE",
        "board": [
            "5,6,1",
            "5,7,2",
            "5,8,2",
            "5,9,2",
            "5,10,2"
        ],
        "expected": "5,11"
    },
    {
        "name": "SPLIT DIAGONAL 4 DEFENSE",
        "board": [
            "9,9,1",
            "12,12,2",
            "13,13,2",
            "15,15,2",
            "16,16,2"
        ],
        "expected": "14,14"
    },
    {
        "name": "SPLIT HORIZONTAL 4 DEFENSE",
        "board": [
            "7,7,1",
            "8,7,2",
            "9,7,2",
            "11,7,2",
            "12,7,2"
        ],
        "expected": "10,7"
    },
    {
        "name": "SPLIT VERTICAL 4 DEFENSE",
        "board": [
            "5,5,1",
            "5,8,2",
            "5,9,2",
            "5,11,2",
            "5,12,2"
        ],
        "expected": "5,10"
    },
    {
        "name": "CHAOS DEFENSE",
        "board": [
            "0,0,1",
            "1,0,1",
            "2,0,1",
            "17,0,1",
            "17,0,1",
            "19,0,1",
            "0,1,1",
            "3,1,2",
            "19,2,1",
            "3,3,2",
            "4,3,2",
            "5,3,2",
            "3,4,2",
            "4,4,2",
            "5,4,1",
            "1,5,2",
            "4,5,1",
            "1,6,2",
            "3,6,1",
            "0,7,2",
            "1,7,2",
            "1,8,1",
            "8,8,1",
            "1,9,2",
            "7,9,1",
            "8,9,2",
            "9,9,2",
            "10,9,2",
            "12,9,1",
            "1,10,1",
            "10,10,1",
            "1,11,2",
            "1,12,1",
            "1,13,2",
            "6,13,2",
            "1,14,1",
            "5,14,1",
            "4,15,1",
            "0,16,2",
            "0,16,2",
            "2,16,2",
            "3,16,1",
            "0,17,1",
            "2,17,1",
            "19,17,1",
            "0,18,1",
            "19,18,1",
            "0,19,1",
            "1,19,1",
            "2,19,1",
            "17,19,1",
            "18,19,1",
            "19,19,1"
        ],
        "expected": "2,7"
    }
]

multiple_scenarios = [
    {
        "name": "DIFFICULT SPLIT DEFENSE",
        "board": [
            "11,6,1",
            "12,6,1",
            "13,6,1",
            "7,7,1",
            "8,7,2",
            "9,7,2",
            "11,7,2",
            "9,8,1",
            "11,8,2"
        ],
        "expected": ["10,7", "10,6", "14,6"]
    },
    {
        "name": "DOUBLE CUTTING SITUATION",
        "board": [
            "2,2,1",
            "3,3,2",
            "6,6,2",
            "5,5,2",
            "6,5,2",
            "7,5,1",
            "8,5,1",
            "9,4,1",
            "10,3,1",
            "6,6,2",
            "6,7,1",
            "7,7,2"
        ],
        "expected": ["7,6"]
    }
]

sequential_scenarios = [
    {
        "name": "MULTI-MOVE WINNING CHAIN",
        "board": [
            "6,7,1",
            "7,7,1",
            "8,8,2",
            "7,9,2",
            '9,9,1',
            "6,10,2",
            "9,10,1"
        ],
        "winning_sequence": [
            {"1": "9,7", "2": "5,11"},
            {"1": "4,12", "2": "8,7"},
            {"1": "9,8"}
        ]
    }
]

def run_single_test(scenario):
    board_setup = scenario["board"]
    exp = scenario["expected"]

    command = ['./pbrain-gomoku-ai']
    process = subprocess.Popen(
        command,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True)

    process.stdin.write("START 20\n")
    process.stdin.flush()
    start_response = process.stdout.readline().strip()
    if start_response != "OK":
        return False, f"Expected OK after START but got {start_response}"

    process.stdin.write("BOARD\n")
    process.stdin.write("\n".join(board_setup) + "\nDONE\n")
    process.stdin.flush()

    start_time = time.time()
    output = process.stdout.readline().strip()
    end_time = time.time()
    elapsed = (end_time - start_time) * 1000

    if output == f"{exp}":
        return True, f"Played {exp}", elapsed
    else:
        return False, f"Expected {exp} but got {output}", elapsed

def run_multiple_test(scenario):
    board_setup = scenario["board"]
    exps = scenario["expected"]

    command = ['./pbrain-gomoku-ai']
    process = subprocess.Popen(
        command,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True)

    process.stdin.write("START 20\n")
    process.stdin.flush()
    start_response = process.stdout.readline().strip()
    if start_response != "OK":
        return False, f"Expected OK after START but got {start_response}"

    process.stdin.write("BOARD\n")
    process.stdin.write("\n".join(board_setup) + "\nDONE\n")
    process.stdin.flush()

    start_time = time.time()
    output = process.stdout.readline().strip()
    end_time = time.time()
    eltime = (end_time - start_time) * 1000

    if output in [f"{result}" for result in exps]:
        return True, f"Played {output}", eltime
    else:
        return False, f"Expected one of {exps} but got {output}", eltime

def run_sequential_test(scenario):
    board_setup = scenario["board"]
    winning_sequence = scenario["winning_sequence"]

    command = ['./pbrain-gomoku-ai']
    process = subprocess.Popen(
        command,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True)

    process.stdin.write("START 20\n")
    process.stdin.flush()
    start_response = process.stdout.readline().strip()
    if start_response != "OK":
        return False, f"Expected OK after START but got {start_response}"

    process.stdin.write("BOARD\n")
    process.stdin.write("\n".join(board_setup) + "\nDONE\n")
    process.stdin.flush()

    played_moves = []
    start_time = time.time()
    for move in winning_sequence:
        output = process.stdout.readline().strip()

        exp_move = f"{move['1']}"
        if output != exp_move:
            end_time = time.time()
            elapsed = (end_time - start_time) * 1000
            print(f"Expected {exp_move} but got {output}")
            return False, f"Expected {exp_move} but got {output}", elapsed
        played_moves.append(move['1'])

        if '2' in move:
            process.stdin.write(f"TURN {move['2']}\n")
            process.stdin.flush()

    end_time = time.time()
    elapsed = (end_time - start_time) * 1000
    return True, f"Played {played_moves}", elapsed

def generate_board(board_setup, played_moves):
    board = [['.' for _ in range(20)] for _ in range(20)]
    for move in board_setup:
        x, y, player = map(int, move.split(','))
        board[y][x] = 'X' if player == 1 else 'O'
    for move in played_moves:
        x, y = map(int, move.split(','))
        board[y][x] = '*'
    return board

def log_board(board, scenario_name, log_file):
    with open(log_file, 'a') as f:
        f.write(f"Scenario: {scenario_name}\n")
        header = "   " + " ".join(f"{i:2}" if i < 10 else f"{i:1}" for i in range(20))
        f.write(header + "\n")
        for i, row in enumerate(board):
            f.write(f"{i:2}  " + "  ".join(row) + "\n")
        f.write("\n")

def main():
    total_tests = 0
    passed_tests = 0
    results = []
    log_file = "test_boards.log"

    if os.path.exists(log_file):
        os.remove(log_file)

    scenarios = single_scenarios + multiple_scenarios + sequential_scenarios
    total_scenarios = len(scenarios)

    with tqdm(total=total_scenarios, desc="Running tests", ncols=80) as pbar:
        for scenario in single_scenarios:
            total_tests += 1
            success, message, elapsed_time = run_single_test(scenario)
            status = f"{GREEN}Success{RESET}" if success else f"{RED}Failure{RESET}"
            played_moves = [scenario["expected"]]
            board = generate_board(scenario["board"], played_moves)
            results.append([scenario['name'], status, message, f"{elapsed_time:.2f} ms"])
            log_board(board, scenario['name'], log_file)
            if success:
                passed_tests += 1
            pbar.update(1)

        for scenario in multiple_scenarios:
            total_tests += 1
            success, message, elapsed_time = run_multiple_test(scenario)
            status = f"{GREEN}Success{RESET}" if success else f"{RED}Failure{RESET}"
            played_moves = [message.split()[-1]]
            board = generate_board(scenario["board"], played_moves)
            results.append([scenario['name'], status, message, f"{elapsed_time:.2f} ms"])
            log_board(board, scenario['name'], log_file)
            if success:
                passed_tests += 1
            pbar.update(1)

        for scenario in sequential_scenarios:
            total_tests += 1
            success, message, elapsed_time = run_sequential_test(scenario)
            status = f"{GREEN}Success{RESET}" if success else f"{RED}Failure{RESET}"
            played_moves = [message.split()[-1]]
            board = generate_board(scenario["board"], played_moves)
            results.append([scenario['name'], status, message, f"{elapsed_time:.2f} ms"])
            log_board(board, scenario['name'], log_file)
            if success:
                passed_tests += 1
            pbar.update(1)

    print(tabulate(results, headers=["Scenario", "Status", "Message", "Thinking time"], tablefmt="grid"))

    coverage = (passed_tests / total_tests) * 100
    color = GREEN if coverage > 50 else RED
    print(f"\nCoverage: {color}{passed_tests}{RESET}/{total_tests} tests passed ({color}{coverage:.2f}%{RESET})")

if __name__ == "__main__":
    main()
else:
    exit(84)