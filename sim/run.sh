#!/usr/bin/env bash
NUM_NODES=$1
NUM_CYCLE=$2
NUM_TESTS=$3
VERBOSE=$3

COUNT=1

while [ $COUNT -le $NUM_TESTS ]
do
    ./sim $NUM_NODES $NUM_CYCLE $COUNT $VERBOSE
    retVal=$?
    if [ $retVal -eq 1 ]; then
        echo "Error at case" $COUNT
        exit $retVal
    fi
    ((COUNT++))

done

echo "ALL test cases passed"
exit 0