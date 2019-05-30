Efficient Function-Hiding Functional Encryption: From Inner-Products to Orthogonality
=====================================================================================
                      
Author
------

Manuel Barbosa
HASLab INESC TEC and DCC FCUP
mbb@dcc.fc.up.pt

References
----------

Efficient Function-Hiding Functional Encryption: From Inner-Products to Orthogonality
Manuel Barbosa, Dario Catalano, Azam Soleimanian, Bogdan Warinschi
Published in CT-RSA 2019

Dependencies
------------

Requires:
* GNU Multiprecision Arithmetic Library (GMP) available from gmplib.org
* Victor Shoup's NTL: A Library for doing Number Theory available from shoup.net/ntl
* C++ library for Finite Fields and Elliptic Curves available from github.com/scipr-lab/libff

Build Instructions in Ubuntu
------------------

0 - Install necessary packages (see NTL's website for installation instructions)

$ sudo apt-get install build-essential git libboost-all-dev cmake libgmp3-dev libssl-dev libprocps3-dev pkg-config

1 - Initialize libff submodule: 

$ git submodule init

2 - Update libff submodule: 

$ git submodule update

3 - Build libff library

$ cd libff

$ git submodule init

$ git submodule update

$ mkdir build && cd build && cmake ..

$ make

4 - Build from source

$ cd ../../src/test

$ make

5 - Run the test applications

$ ./test_ssfe_ggm 

$ ./test_ssfe_sm

