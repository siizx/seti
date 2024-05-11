#!/bin/bash

commit_option=" -m "

# Check the number of arguments
if [ $# -eq 0 ]; then
    my_string="general update"
elif [ $# -eq 1 ]; then
    # Use the provided argument as the string
    my_string="\"$1\""
else
    # Print an error message and exit
    echo "Error: Too many arguments. Only one argument allowed." >&2
    exit 1
fi

echo "adding '.' ..."
git add .
echo "committing using the provided string..."
git commit $commit_option "$my_string"
echo "pushing to origin..."
git push origin master
echo "Done!"


