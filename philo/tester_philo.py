import os
import re

def extract_numbers_from_text(text):
    numbers = []
    for line in text.splitlines():
        match = re.search(r'\[(\d+)\]', line)
        if match:
            try:
                numbers.append(int(match.group(1)))
            except ValueError:
                print(f"Warning: Invalid number '{match.group(1)}' in line: {line}")
    return numbers


def remove_colors(text):
    # Remove ANSI escape codes
    text = re.sub(r'\x1b\[([0-?]*[ -/]*[@-~])', '', text)
    return text


def check_last_eat_under_3(numbers):
    dic_meals = {}
    for i in range(len(numbers)):
        dic_meals[numbers[i]] = 0
    for i in range(len(numbers)):
        print(f"i: {numbers[i]} -- {i}")
        if (i - dic_meals[numbers[i]] > 3):
            print("Starvation: \033[31m[KO]\033[0m")
            print("\twith three philos there can't be more than 2 meals ahead.")
            return None
        dic_meals[numbers[i]] = i
    return print("\033[32m[OK]\033[0m\n")


def find_last_eating_before_died(file_content):
    lines = file_content.split('\n')
    died_index = -1
    last_eating_number = None

    for i, line in enumerate(lines):
        columns = line.split()
        if len(columns) >= 3 and 'died' in columns[2]:
            died_index = i
            break

    if died_index == -1:
        return None

    for j in range(died_index - 1, -1, -1):
        columns = lines[j].split()
        if len(columns) >= 2 and '[0-9]' in columns[1] and 'is eating' in columns[-1]:
            last_eating_number = int(re.search(r'\[(\d+)\]', columns[1]).group(1))
            break

    return last_eating_number


#-----------------------------------

def	check_died_under_10ms(file_path, time_to_die):
    died_event = False
    philo_tid = False

    last_eating_time = None
    last_dying_time = None

    with open(file_path, 'r') as file:
        for line in file:
            # Check for "died" event
            if "died" in line:
                died_event = True
                last_dying_time = int(remove_colors(line.split()[0]))
                philo_tid = str(extract_numbers_from_text(line)[0])
                print(line)
                break

    if not died_event:
        print("All philos have survived.")
        return None  # No "died" event found

    with open(file_path, 'r') as file:
        for line in reversed(list(file)):
            if (philo_tid in line.split()[1]) and "is eating" in line:
                last_eating_time = int(remove_colors(line.split()[0]))
                print(line)
                break
    if last_eating_time is None:
        print("Last eating time is none")
        return None  # No eating event found

    time_difference = last_dying_time - last_eating_time
    print(f"{last_dying_time} - {last_eating_time} = {time_difference}")
    allowed_limit = time_to_die + 10
    if time_difference < allowed_limit:
        print("\033[32m[OK]\033[0m\n")
        return None
    else:
        print(f"> {time_to_die}")
        print("\033[31m[KO]\033[0m")
        return None

#-----------------------------------

# os.system("./philo 3 310 102 102 4 | awk '$4 == \"eating\"' > test_file.txt")
with open(f"check", 'r') as file:
    file_contents = file.read()
# numbers = extract_numbers_from_text(file_contents)
# print(numbers)
# check_last_eat_under_3(numbers)
print(find_last_eating_before_died(file_contents))
print("\n---------------------------------\n")
# os.system("./philo 50 800 200 200 3 > test_file.txt")
# check_died_under_10ms("test_file.txt", 310)