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

# def	check_died_under_10ms(file_path, time_to_die):
#     died_event = False
#     philo_tid = False

#     last_eating_time = None
#     last_dying_time = None

#     with open(file_path, 'r') as file:
#         for line in file:
#             # Check for "died" event
#             if "died" in line:
#                 died_event = True
#                 last_dying_time = int(re.search(r'\d+', line).group())
#                 philo_tid = int(line.split()[1])
#                 break

#     if not died_event:
#         print("All philos have survived.")
#         return None  # No "died" event found

#     with open(file_path, 'r') as file:
#         for line in reversed(list(file)):
#             if philo_tid in line and "is eating" in line:
#                 last_eating_time = int(re.search(r'\d+', line).group())
#                 break

#     if last_eating_time is None:
#         return None  # No eating event found

#     time_difference = last_dying_time - last_eating_time
#     allowed_limit = time_to_die + 10
#     if time_difference <= allowed_limit:
#         print("\033[32m[OK]\033[0m\n")
#         return None
#     else:
#         print("\033[31m[KO]\033[0m")
#         return None


os.system("./a.out 3 310 102 134 4 | grep eat > test_file.txt")
with open(f"test_file.txt", 'r') as file:
    file_contents = file.read()
numbers = extract_numbers_from_text(file_contents)
print(numbers)
check_last_eat_under_3(numbers)
# os.system("./a.out 3 310 102 134 4 > test_file.txt")
# check_died_under_10ms("test_file.txt", 310)