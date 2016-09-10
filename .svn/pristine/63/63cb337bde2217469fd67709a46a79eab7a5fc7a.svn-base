# Automatically download library dependencies

wget 'http://downloads.sourceforge.net/project/chibios/ChibiOS_RT%20stable/Version%202.6.1/ChibiOS_2.6.1.zip'
unzip ChibiOS_2.6.1.zip
mv ChibiOS_2.6.1 chibios

svn co http://libfixmath.googlecode.com/svn/trunk/libfixmath

git clone git://github.com/PetteriAimonen/Baselibc.git baselibc
make -C baselibc PLATFORM=cortex-m3

git clone https://bitbucket.org/Tectu/ugfx ugfx

