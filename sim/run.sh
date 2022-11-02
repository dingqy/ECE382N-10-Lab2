#!/usr/bin/env bash
NUM_NODES=$1
NUM_CYCLE=$2
TEST_START=$3
TEST_END=$4

if [ -z $NUM_NODES ] 
then
    echo "The NUM_NODES var is not set, setting to 32"
    NUM_NODES=32
fi

if [ -z $NUM_CYCLE ] 
then
    echo "The NUM_CYCLE var is not set, setting to 5000"
    NUM_CYCLE=5000
fi

if [ -z $TEST_START ] 
then
    echo "The TEST_START var is not set, setting to 1"
    TEST_START=1
fi

if [ -z $TEST_END ] 
then
    echo "The TEST_END var is not set, setting to 33"
    TEST_END=33
fi

CUR_TEST=$TEST_START
NUM_TESTS=0

while [ $CUR_TEST -le $TEST_END ]
do
    ./sim $NUM_NODES $NUM_CYCLE $CUR_TEST 0
    retVal=$?
    if [ $retVal -eq 1 ]; then
        echo "Error at case" $CUR_TEST
        echo "Total number of test cases" $NUM_TESTS
        exit $retVal
    fi
    ((CUR_TEST++))
    ((NUM_TESTS++))

done

echo "ALL test cases passed"
echo "Total number of test cases" $NUM_TESTS
exit 0