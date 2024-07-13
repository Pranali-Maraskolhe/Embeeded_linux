#Create a script that reads a file line by line and prints each line in reverse order.

#!/bin/bash

echo "Enter file name: "
read filename

# Check if file already exists

if [ -f "$filename" ]; then
	#Display content of file in reverse order
	cat "$filename" | rev
else
	echo "'$filename' does not exist"
fi

