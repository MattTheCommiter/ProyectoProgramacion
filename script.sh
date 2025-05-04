#!/bin/bash


#WARNING: this script works correctly when placed in the project root, where the src directory is located and the executable files are created.

set -euo pipefail

#Definition of variables
RUN_NORMALLY=0
RUN_WITH_VALGRIND=1

#Definition of exit codes
SUCCESS_EXIT_CODE=0
ERROR_EXIT_CODE=1

#Definition of minimum and maximum number of arguments
MIN_ARGUMENTS=1
MAX_ARGUMENTS=2


#We define the functions that will run the code
run_test() {
	echo ">>>>> Running ${1}."
	./${1}
}

run_test_with_valgrind() {
	echo ">>>>> Running ${1} with valgrind."
	valgrind --leak-check=full ./${1}
}

#ERROR CONTROL
#We check that the number of arguments is either one or two
if [[ "$#" -lt "$MIN_ARGUMENTS" || "$#" -gt "$MAX_ARGUMENTS" ]]; then
	echo "ERROR: Invalid ammount of arguments. The script must have one argument ('0' or '1') for the compilation and execution of all tests, or two arguments, with the second one indicating the test that will be compiled and executed."
	exit $ERROR_EXIT_CODE

#We check that the first argument is either '0' or '1'
elif [[ "${1}" -ne "$RUN_NORMALLY" && "${1}" -ne "$RUN_WITH_VALGRIND" ]]; then
	echo "ERROR: First argument not valid. Must be '0' for normal execution and '1' for execution with valgrind."
	exit $ERROR_EXIT_CODE

#We check that, if there is a second argument, it matches the requested format
elif [[ -n "${2:-}" && "${2:-}" != *_test ]]; then
	echo "ERROR: Second argument must be a valid test in C ending in '_test'."
	exit $ERROR_EXIT_CODE
fi

#COMPILATION
#If there is no second argument, we compile each test file individually
if [[ -z "${2:-}" ]]; then
	#We make sure there exists a file that matches the requisites
	if  ! find src/ -type f -name "*_test.c" | grep -q .; then
		echo "ERROR: No test files currenly exist."
		exit $ERROR_EXIT_CODE
	fi
	#We compile each test file individually
	echo ">>>>> Compiling all tests:"
	for test in src/*_test.c; do
		echo ">>>>> Compiling ${test}"
		#basename function allows us to remove the 'src/' directory and the '.c' from the 'test' variable
		test_name=$(basename "${test}" .c)
		make $test_name
		#We check that the make command exited correctly
		make_exit_code=$?
		if [[ "$make_exit_code" -ne "0" ]]; then
			echo "ERROR: Make command exited with code: ${make_exit_code}"
			exit $ERROR_EXIT_CODE
		fi
	done

#If there is a second argument, we only compile that file
else
	if  ! find src/ -type f -name "*${2}.c" | grep -q .; then
		echo "ERROR: No test files match the one entered."
		exit $ERROR_EXIT_CODE
	fi
	echo ">>>>> Compiling ${2}.c"
	make ${2}
	make_exit_code=$?
	if [[ "$make_exit_code" -ne "0" ]]; then
		echo "ERROR: Make command exited with code: ${make_exit_code}"
		exit $ERROR_EXIT_CODE
	fi
fi


#TEST RUNNING
#If there is a second argument, we run that test
if [[ -n "${2:-}" ]]; then
	#We make sure the executable file exists
	if [[ ! -f "${2}" ]]; then
		echo "ERROR: Executable file does not exist."
		exit $ERROR_EXIT_CODE
	fi
	
	#We run the test with the corresponding function
	if [ "${1}" = "${RUN_NORMALLY}" ]; then
		run_test ${2}
	elif [ "${1}" = "${RUN_WITH_VALGRIND}" ]; then
		run_test_with_valgrind ${2}
	fi	
	echo "The test was compiled and executed successfully."
else
	for test_executable in *_test; do 
		if [ "${1}" = "${RUN_NORMALLY}" ]; then
			run_test ${test_executable}
		elif [ "${1}" = "${RUN_WITH_VALGRIND}" ]; then
			run_test_with_valgrind ${test_executable}
		fi	
	done
	echo "All tests were compiled and executed successfully."
fi

exit $SUCCESS_EXIT_CODE