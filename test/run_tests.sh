#!/bin/bash
#
# run_tests.sh - is performing runs some unit tests in auto mode, 
# including memchecking (usually using `valgrind`), and showing results
# in depending of return code of tested application and memcheck app.
#
# Project: https://github.com/ans-hub/test_toolkit
# Version: 0.22
#__________________________________________________________________


# HELPER FUNCTIONS

function get_workdir()
{
  local source \
        dir

  source="${BASH_SOURCE[0]}"

  while [ -h "$source" ]; do
      dir="$( cd -P "$( dirname "$source" )" && pwd )"
      source="$( readlink "$source" )"
      [[ $source != /* ]] && source="$dir/$source"
  done

  dir="$( cd -P "$( dirname "$source" )" && pwd )"
  echo "$dir"
}

function say_hello()
{
  echo "Start testing:"
}

function say_bye()
{
  echo "End testing"
  echo "-"
  echo "Note: if fail occurs then output stored in temp files"
  echo "Note: to see test cases you may run "${testable_fname}" directly"
}

function init_app_vars()
{  
  testable_fname="main.out"
  memcheck_fname="valgrind"

  testable_temp="$(get_workdir)/~"${testable_fname}".tmp"     
  testable_file="$(get_workdir)/"${testable_fname}""

  memcheck_temp="$(get_workdir)/~"${memcheck_fname}".tmp"
  memcheck_cmd="${memcheck_fname} --leak-check=full 
                                  --show-leak-kinds=all 
                                  --track-origins=yes 
                                  --error-exitcode=500 
                                  "${testable_file}" "

  readonly testable_fname
  readonly testable_file
  readonly testable_temp
  
  readonly memcheck_fname
  readonly memcheck_cmd
  readonly memcheck_temp
}

function remove_old_temp()
{
  echo -n "  Remove old temp..."

  [[ ! -n "${testable_temp}" ]] && rm "${testable_temp}"
  [[ ! -n "${memcheck_temp}" ]] && rm "${memcheck_temp}"

  echo "Ok"
}

# MAIN FUNCTIONS

function run_testable_file()
{
  local output
  echo -n "  Run testable_file..."

  output="$("${testable_file}" 2>&1 )"

  if [[ "$?" == 0 ]]; then
    echo "Ok"
  else
    echo "Fail"
    echo "${output}" > "${testable_temp}"
  fi
}

function run_memchecker()
{
  local output
  echo -n "  Run memcheck test..."

  output="$( ${memcheck_cmd} 2>&1 )"
  
  if [[ "$?" == 0 ]]; then
    echo "Ok"
  else
    echo "Fail"
    echo "${output}" > "${memcheck_temp}"
  fi
}

function main()
{
  say_hello
  init_app_vars
  remove_old_temp

  run_testable_file
  run_memchecker

  say_bye
}

main "$@"