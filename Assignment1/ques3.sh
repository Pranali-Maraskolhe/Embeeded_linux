#Write a script to calculate the factorial of a given number.

#!/bin/bash


echo "Enter a number"
read num

fact=1

#for((i=2;i<=num;i++))
#{
 # fact=$((fact * i))  #fact = fact * i
#}

#echo $fact

#loop num should be greater than 1 for equal to use -gt option
while [ $num -gt 1 ]
do
	fact=$((fact * num))
	num=$((num - 1))
done

echo $fact










