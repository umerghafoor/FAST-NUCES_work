# 2. Create a file output_2.txt and add the content of all the files in the current directory to
# dummy. But copy the content in such a way that if files in current directory = {f1, f2, f3,
# f4,.....,fn} Then copy first N lines of files at even location {f2,f4,...} and last N lines of files
# at odd location {f1,f3,...}. Value of N will be provided by the user.
echo "Enter number Lines :"
read N

index=0
for file in files/*
do
    echo $file
    if (($index%2 == 0))
    then
        cat $file | head -n $N >> output_2.txt
    else
        cat $file | tail -n $N >> output_2.txt
    fi
    index=$(($index + 1))
done

# touch f1.txt
# touch f2.txt
# touch f3.txt
# touch f4.txt
# touch f5.txt
# touch f6.txt
# touch f7.txt
# touch f8.txt
# touch f9.txt
