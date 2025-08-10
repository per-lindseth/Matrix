Initial version:
---------------
This code is almost exact the same as in the you tube video:
"Linear Algebra in C++ - Part 1 - A simple class to handle matrices", QuantitativeBytes
by Michael J. Bennett, PhD.

I plan to gradually change this code, both as an exercise in practicing more 
modern C++ and to make it more robust.

2. version:
-----------
A row and column index are non-negative integers. The same goes for the number of rows 
and the number of columns. That's why I prefer to use size_t instead of int.
This way I don't have to test for negativeness. I'll throw an error instead of returning -1
in Sub2Ind(...) for now, and change the test for illegal indices.
The problem with this is that the call GetElement(-1, 0) will actually go unnoticed as 
GetElement(18446744073709551615, 0). However, this is an index that is too large, so it will be 
taken care of and handled properly.

