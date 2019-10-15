#!/bin/bash
INPUT_NAME=input
OUTPUT_NAME=output
MY_NAME=my_output
rm -R $MY_NAME* &>/dev/null
for test_file in $INPUT_NAME*
do
    i=$((${#INPUT_NAME}))
    test_case=${test_file:$i}
    if ! `which time` -o time.out -f "(%es)" ./a.out < $INPUT_NAME$test_case > $MY_NAME$test_case; then
        echo [1m[31mSample test \#$test_case: Runtime Error[0m `cat time.out`
        echo ========================================
        echo Sample Input \#$test_case
        cat $INPUT_NAME$test_case
    else
        if diff --brief --ignore-trailing-space $MY_NAME$test_case $OUTPUT_NAME$test_case; then
            echo ========================================
            echo Sample Input \#$test_case
            cat $INPUT_NAME$test_case
            echo ========================================
            echo Sample Output \#$test_case
            cat $OUTPUT_NAME$test_case
            echo ========================================
            echo My Output \#$test_case
            cat $MY_NAME$test_case
            echo ========================================
        fi
    fi
done
