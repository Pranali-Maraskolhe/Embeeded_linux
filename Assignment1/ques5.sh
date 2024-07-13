#Write a script that takes a directory path as input and recursively counts the number of files and directories inside it.

#!/bin/bash

#Enter the path of directory
echo "Enter directory path: "
read LOCATION

#path=$1 #prints default login shell
filecount=0
dircount=0

DIRS=$(find $LOCATION -type d) #find the directory and store in dirs
FILES=$(find $LOCATION -type f) #find the dicrectory and store in files


#Check number of directrory
for d in $DIRS  
do
   dircount=$[$dircount+1]
done


#check number of files
for f in $FILES
do
	filecount=$[$filecount+1]
done


echo "File count: " $filecount
echo "Directory count: " $dircount


