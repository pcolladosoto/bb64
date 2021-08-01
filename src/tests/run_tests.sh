#!/bin/bash

# Cd into the tests/ directory to avoid appending it to
    # several paths
cd tests/

# Note the "\x1B[1A" escape sequence moves the cursor one line up,
    # thus, overwriting the output generated by 'make'
echo -e "\x1B[1ARunning Data -> Base64 tests..."
for test in $(ls -1 data_to_b64/*.txt)
do
    echo $(../bb64 $test) | diff -qw - $(echo $test | awk '{split($0, foo, "."); print foo[1] ".target"}') > /dev/null 2>&1
    if [ $? -eq 0 ]
    then
        echo -e "\t\x1B[38;2;0;255;0mPassed\x1B[0m $test"
    else
        echo -e "\t\x1B[38;2;255;0;0mFailed\x1B[0m $test"
    fi
done

# Always tell 'make' everything is okay so that it doesn't complain...
exit 0