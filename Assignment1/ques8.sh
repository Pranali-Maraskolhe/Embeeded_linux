#Create a script to find and display all files modified in the last 24 hours in a specified directory.

echo "Enter the path of directory: "
read dir

if [ -d "$dir" ]; then
	#display the file which is update in 24hour
	find "$dir" -type f -mtime -1 -ls 
else
	echo "No file update in 24 hours"
fi

