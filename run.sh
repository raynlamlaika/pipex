#!/bin/bash

# Test variables
EXEC="./pipex"
LIMITER="EOF"
OUTPUT_FILE="heredoc_output.txt"

# Cleanup previous test files
rm -f $OUTPUT_FILE

echo "===== Testing Here_doc in Pipex ====="

# Run pipex with here_doc mode
$EXEC here_doc $LIMITER "cat" "wc -l" $OUTPUT_FILE <<EOF
Hello, this is a test.
42 School is great!
Pipex is fun!
EOF
EOF

# Check the output file
echo "===== Output in $OUTPUT_FILE ====="
cat $OUTPUT_FILE

# Expected output: Line count (should be 3)
EXPECTED_OUTPUT="3"
ACTUAL_OUTPUT=$(cat $OUTPUT_FILE)

if [ "$ACTUAL_OUTPUT" = "$EXPECTED_OUTPUT" ]; then
    echo "✅ Here_doc Test Passed!"
else
    echo "❌ Here_doc Test Failed!"
fi
