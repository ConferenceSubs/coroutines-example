#!/bin/bash

wget https://boostorg.jfrog.io/artifactory/main/release/1.72.0/source/boost_1_72_0.tar.gz
tar -xzf boost_1_72_0.tar.gz
make clean
make 
echo
echo "Running simple app with window_size 2"
echo "====================================="
echo
./sample_cor 2
