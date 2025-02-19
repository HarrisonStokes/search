#!/bin/bash

pattern=he
file=(1 2 3 4 5 6 7 8 9 10)

for file_idx in "${file[@]}"
do
	echo "Testing random_words_${file_idx}..."
	./../way $pattern -i dataset/random_words_${file_idx}.txt -Ic -o result/random_words_${file_idx}
	echo
done

