#Write a script to search for a given pattern in all files in a directory and its subdirectories.

echo "Enter pattern: "
read pattern

#check the type of pattern file and display it
find -type f | ls -l [$pattern]*


