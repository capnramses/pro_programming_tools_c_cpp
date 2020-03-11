#!/bin/bash
afl-gcc -g -o test_ppm_fuzz main.c my_ppm_stuff.c -I ./ 
AFL_EXIT_WHEN_DONE=1 AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 AFL_SKIP_CPUFREQ=1 afl-fuzz -i fuzzer_inputs/ -o fuzzer_outputs/ -- ./test_ppm_fuzz @@
