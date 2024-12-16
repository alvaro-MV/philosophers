#!/bin/bash

find_last_eating_before_died() {
    local last_number=
    
    while IFS= read -r line; do
        if [[ $line == *'died'* ]]; then
            # If we've reached the 'died' line, print the last eating number
            echo "$last_number"
            return
        fi
        
        if [[ $line =~ \[([0-9]+)\] is eating ]]; then
            last_number=${BASH_REMATCH[1]}
        fi
    done
    
    # If we reach here, there was no 'died' line
    echo "None"
}

# Read file contents into a variable
file_contents=$(cat "$1")

# Call the main function with the file contents
find_last_eating_before_died <<< "$file_contents"

# Example usage:
# ./script.sh input_file.txt
