#Task 2 building tets directory
if [ -d "TestData" ]; then
    echo "Directory TestData already exists in curent Folder"
    echo "Deleting existing Directory"
    rm -r TestData
fi

echo -n "Number of files to create : "
read numfiles

mkdir TestData

sample_text_file="sample.txt"

if [ ! -f "$sample_text_file" ]; then
    echo "Error: Sample text file '$sample_text_file' not found"
fi

for ((i=1; i<=$numfiles; i++)); do
    filename="TestData/f$i.txt"
    shuf -n $((RANDOM%10+5)) "$sample_text_file" > "$filename"
    echo "Created $filename"
done

echo "Files created successfully in TestData directory"
