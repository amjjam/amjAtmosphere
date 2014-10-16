#!/bin/bash

../src/testAtmosphere -n 1000000 -dt 0.1 -t 3 -o ~/tmp/testAtmosphere/dat/test111.dat
../src/testAtmosphere -n 1000000 -dt 0.3 -t 3 -o ~/tmp/testAtmosphere/dat/test121.dat
../src/testAtmosphere -n 1000000 -dt 1 -t 3 -o ~/tmp/testAtmosphere/dat/test131.dat

../src/testAtmosphere -n 1000000 -dt 0.1 -t 10 -o ~/tmp/testAtmosphere/dat/test112.dat
../src/testAtmosphere -n 1000000 -dt 0.3 -t 10 -o ~/tmp/testAtmosphere/dat/test122.dat
../src/testAtmosphere -n 1000000 -dt 1 -t 10 -o ~/tmp/testAtmosphere/dat/test132.dat

../src/testAtmosphere -n 1000000 -dt 0.1 -t 30 -o ~/tmp/testAtmosphere/dat/test113.dat
../src/testAtmosphere -n 1000000 -dt 0.3 -t 30 -o ~/tmp/testAtmosphere/dat/test123.dat
../src/testAtmosphere -n 1000000 -dt 1 -t 30 -o ~/tmp/testAtmosphere/dat/test133.dat


../src/testAtmosphere -n 3000000 -dt 0.1 -t 3 -o ~/tmp/testAtmosphere/dat/test211.dat
../src/testAtmosphere -n 3000000 -dt 0.3 -t 3 -o ~/tmp/testAtmosphere/dat/test221.dat
../src/testAtmosphere -n 3000000 -dt 1 -t 3 -o ~/tmp/testAtmosphere/dat/test231.dat

../src/testAtmosphere -n 3000000 -dt 0.1 -t 10 -o ~/tmp/testAtmosphere/dat/test212.dat
../src/testAtmosphere -n 3000000 -dt 0.3 -t 10 -o ~/tmp/testAtmosphere/dat/test222.dat
../src/testAtmosphere -n 3000000 -dt 1 -t 10 -o ~/tmp/testAtmosphere/dat/test232.dat

../src/testAtmosphere -n 3000000 -dt 0.1 -t 30 -o ~/tmp/testAtmosphere/dat/test213.dat
../src/testAtmosphere -n 3000000 -dt 0.3 -t 30 -o ~/tmp/testAtmosphere/dat/test223.dat
../src/testAtmosphere -n 3000000 -dt 1 -t 30 -o ~/tmp/testAtmosphere/dat/test233.dat

