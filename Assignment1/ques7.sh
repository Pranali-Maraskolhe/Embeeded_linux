#Write a script that checks if a given string is a palindrome.

#!/bin/bash

echo "Enter a number: "
read num
reverse=0

num1=$num

#loop untill num become 0
while [ $num -gt 0 ];
do
	rem=$((num % 10))
	reverse=$((reverse * 10 + rem))
	num=$((num / 10))
done


#compared reverse number with original number and check number is palindrome or not
if [ $num1 == $reverse ]; then
	echo "'$num1' is palindrome"
else
	echo "Not palindrome"
fi

