#!/bin/bash

func_test_output=$(./out/func_tests.exe)
llvm-profdata merge -sparse default.profraw -o default.profdata
llvm_export_output=$(llvm-cov export ./out/func_tests.exe -instr-profile=default.profdata -ignore-filename-regex=".*/(ui_|moc_).*")
llvm_report_output=$(llvm-cov report ./out/func_tests.exe -instr-profile=default.profdata -ignore-filename-regex=".*/(ui_|moc_).*")
percent=$(echo "$llvm_export_output" | jq '.data[].totals.lines.percent')

printf "Coverage: %.2f%%\n\n" "$percent"
echo "LLVM-COV REPORT:"
echo "$llvm_report_output"

echo "FUNC TESTS OUTPUT:"
echo "$func_test_output"
