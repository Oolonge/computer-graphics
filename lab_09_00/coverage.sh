#!/bin/bash

# ./out/unit_tests.exe
# /opt/homebrew/Cellar/llvm/18.1.4/bin/llvm-cov show ./out/unit_tests.exe -instr-profile=default.profraw -ignore-filename-regex=".*/(ui_|moc_).*" 

unit_test_output=$(./out/unit_tests.exe)
llvm-profdata merge -sparse default.profraw -o default.profdata
llvm_export_output=$(llvm-cov export ./out/unit_tests.exe -instr-profile=default.profdata -ignore-filename-regex=".*/(ui_|moc_).*")
llvm_report_output=$(llvm-cov report ./out/unit_tests.exe -instr-profile=default.profdata -ignore-filename-regex=".*/(ui_|moc_).*")
percent=$(echo "$llvm_export_output" | jq '.data[].totals.lines.percent')

printf "Coverage: %.2f%%\n\n" "$percent"
echo "LLVM-COV REPORT:"
echo "$llvm_report_output"

echo "UNIT TESTS OUTPUT:"
echo "$unit_test_output"
