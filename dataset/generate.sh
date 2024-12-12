#!/bin/bash

for i in {1..5000}
do
    touch "${i}.cpp"
done


echo "created: $(ls *.cpp | wc -l)"
