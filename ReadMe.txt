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

5.version: from T* to vector<T>
-------------------------------
The big advantage of changing the member type m_matrixData from T* to std::vector<T>
is that you can use the rule of zero instead of the rule of five. Therefore, multiple
members are set to default. It also makes the code much cleaner in many places.

Using ranges removes almost all loops, making the code safer and more readable.

The constructor that takes a && vector was added for performance reasons.

The zip template helper function makes the code more compact, and the to_vector template function
implements two variants, one for c++20 and one for c++23 (just for fun).

The MyVec and MyVecConst classes enables the code to use to dimensional indices like m(row, column)
which greatly improves readability. In c++23 the () can be replaced with [].
