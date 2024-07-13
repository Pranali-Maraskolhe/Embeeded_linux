#Write a script to check if a file exists and if it does, display its contents.

#!/bin/bash

echo "Enter file name: "
read filename

# Check if file already exists

if [ -f "$filename" ]; then
	#Display content of file
	cat "$filename"
else
	echo "'$filename' does not exist"
fi

