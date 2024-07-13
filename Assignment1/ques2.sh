#Create a script that takes a number as input and prints whether it is even or odd.

#!/bin/bash

echo "Enter number: "
read num

#check number is even and odd
if [ $(($num%2)) -eq 0 ]; then
	echo "'$num' is even"
else
	echo "'$num' is odd"
fi

