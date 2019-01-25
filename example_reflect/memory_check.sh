#!/bin/bash
bin=$1
valgrind --log-file=./valgrind_report.log \
         --leak-check=full                \
         --show-reachable=no              \
         --track-origins=yes ./$bin
