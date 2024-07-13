#Create a script that takes a filename as input and checks if it is a regular file, a directory, or something else.

#!/bin/bash

echo "Enter file directory or other: "
read var

#check var is directory
if [ -d "$var" ]; then

	echo "It is directory"

#check var is file
elif [ -f "$var" ]; then

	echo "It is a file"

else
	echo "something else"

fi

