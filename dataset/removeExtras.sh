#!/bin/bash

for i in {107..5000}
do
    rm -f "${i}.cpp"
done


echo "removed: $(ls *.cpp | wc -l)"
