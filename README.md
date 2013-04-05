DES (Data Encryption Standard)
------------------------------

My C++ implementation of DES for university crypt course.
It's quite fast (~15mb/sec on i3-370 M).


Dependencies:
-------------

* CMake
* Boost.Program_options

Usage:
------

Encrypt "msg" file with key "0123456789ABCDEF" and write result to "crypted":
./des -e -k 0123456789ABCDEF -i msg -o crypted

Decrypt "crypted" file with key "0123456789ABCDEF" and write result to "res":
./des -d -k 0123456789ABCDEF -i crypted -o res

Resources:
----------

The DES Algorithm Illustrated:

[http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm][1]

[1]: http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm