# Input a filename from the user and check the modified date of that file. If the modified
# date is greater than 24 hours from the current time, change the modified date to current
# date. Alongwith displaying the output on terminal, maintain a logFile logFile.txt that
# contains the information of the script.

echo "File :"
read file

modified_time=$(stat -c %Y $file)

current_time=$(date +%s)

echo "Modified Time : $modified_time"
echo "Current Time  : $current_time"

if ((($current_time - $modified_time) > 60)) ## 60*60*24 =86400
then
    echo "File is older than 24 hours"
    touch -d "now" $file
    echo "Modified Time : $(stat -c %y $file)"
    echo "File modified"
    echo "File : $file Modified at $(stat -c %y $file)" >> logFile.txt
else
    echo "File is not older than 24 hours (1-min for testing)"
    echo "File : $file Not Modified" >> logFile.txt
fi