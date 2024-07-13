#!/bin/bash

# Prompt user for directory name
echo "Enter directory name:"
read directory_name

# Check if directory already exists
if [ ! -d "$directory_name" ]; then
    # Directory doesn't exist, create it
    mkdir "$directory_name"
    echo "Directory '$directory_name' created successfully."
else
    # Directory already exists
    echo "Directory '$directory_name' already exists."
fi


