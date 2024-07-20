#delete the file and copy
if [ "$#" -ne 1 ]; then
    echo "Usage : $0 <filename>"
    exit 1
fi

trash_dir="trash"

if [ ! -d "$trash_dir" ]; then
    mkdir "$trash_dir"
    chmod +w "$trash_dir"
fi


mv "$1" "$trash_dir/"
echo "File $1 moved to trash."
