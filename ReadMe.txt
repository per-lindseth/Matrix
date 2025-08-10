Initial version:
---------------
This code is almost exact the same as in the you tube video:
"Linear Algebra in C++ - Part 1 - A simple class to handle matrices", QuantitativeBytes
by Michael J. Bennett, PhD.

I plan to gradually change this code, both as an exercise in practicing more 
modern C++ and to make it more robust.

2. version: signed and unsigned
-------------------------------
A row and column index are non-negative integers. The same goes for the number of rows 
and the number of columns. That's why I prefer to use size_t instead of int.
This way I don't have to test for negativeness. I'll throw an error instead of returning -1
in Sub2Ind(...) for now, and change the test for illegal indices.
The problem with this is that the call GetElement(-1, 0) will actually go unnoticed as 
GetElement(18446744073709551615, 0). However, this is an index that is too large, so it will be 
taken care of and handled properly.

3. version: test
----------------
Added test project.
Avoid manually check all the test print output.

4. version: initialization
--------------------------
Added const on function argument and on member functions.
Fixed a bug I had in Matrix2(row, colum) and added a test for it.
Improved initialization of member variables and also intialize variables using {}
Replaced replaced 0.0 with {}, or U{}, since the latter works better with all types.
