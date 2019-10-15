#!/bin/bash
DBG=""
while getopts ":d" opt; do
  case $opt in
    d)
      echo "-d was selected; compiling in DEBUG mode!" >&2
      DBG=-DDEBUG -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      ;;
  esac
done

if ! g++ -g -std=gnu++14 -Wall -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align  -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector  -O2 $DBG C.cpp; then
    exit
fi
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
            echo [1m[32mSample test \#$test_case: Accepted[0m `cat time.out`
        else
            echo [1m[31mSample test \#$test_case: Wrong Answer[0m `cat time.out`
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
