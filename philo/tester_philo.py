import os
import re
import pandas as pd

def remove_colors(text):
    # Remove ANSI escape codes
    text = re.sub(r'\x1b\[([0-?]*[ -/]*[@-~])', '', text)
    return text

action_counts = {}

def extract_columns_from_file(file_path):
    # Dictionary to store unique actions and their counts

    # Read the file
    with open(file_path, 'r') as f:
        lines = f.readlines()[:-1]

    # Create a list to store the data
    data = []

    # Process each line
    i = 0
    for line in lines:
        # Split the line into words
        words = line.strip().split()
        
        # Extract the required columns
        num1 = int(remove_colors(words[0]))
        num2 = int(remove_colors(words[1]))
        action = words[-1]
        
        # Update action_counts dictionary
        if action not in action_counts:
            action_counts[action] = i
            i += 1
        
        # Add the extracted values to the data list
        data.append([num1, num2, action_counts[action]])

    # Create a DataFrame
    df = pd.DataFrame(data, columns=['timestamp', 'philo', 'Action'])

    return df

def get_last_row_with_condition(df, target_value):
    philo_last_eating = df[df['philo'] == target_value]
    print(philo_last_eating)
    philo_last_eating = philo_last_eating[philo_last_eating['Action'] == 2]
    return philo_last_eating

def get_last_eating_row_before_died(df):
    last_died_row = df.iloc[-1]
    target_value = last_died_row['philo']
    last_eating_row = get_last_row_with_condition(df, target_value)
    return last_eating_row

# Usage
file_path = 'check'
df = extract_columns_from_file(file_path)

print(df.iloc[0]['timestamp'])
if (df.iloc[-1]['Action'] == 5):
    last_eating_row = get_last_eating_row_before_died(df)
    if last_eating_row.empty:
        print("No eating row found before the last died row.")

        print(f"Time without eating: {df.iloc[-1]['timestamp'] - df.iloc[0]['timestamp']}")
    else:
        print(f"Last eating timestamp of [{last_eating_row.iloc[-1]['philo']}]: {last_eating_row.iloc[-1]['timestamp']}")
        print(f"difference: {df.iloc[-1]['timestamp'] - last_eating_row.iloc[-1]['timestamp']}")
elif df.iloc[-1]['Action'] != 5 and not df[df['Action'] == 5].empty:
    print("Philos not correctly joined after the death of a philo!! \U0001f61f")
else:
    print("All philo alive!! \U0001f600")