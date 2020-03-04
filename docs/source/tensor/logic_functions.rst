Logic functions
===============

.. note::

    Section in progress

    Read this: https://github.com/deephealthproject/eddl/blob/master/eddl_progress_tensor.md


Truth value testing
---------------------------


all
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::all

Test whether all elements evaluate to True.

.. code-block:: c++

    static bool all(Tensor *A);
    

any
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::any

Test whether any element evaluates to True

.. code-block:: c++

    static bool any(Tensor *A);


Array contents
-----------------



isfinite
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::isfinite

Test element-wise for finiteness (not infinity or not Not a Number).

  Parameters:

  - ``*A``: Tensor to test.
  - ``B``: Tensor to store the results of the test as booleans.

.. code-block:: c++

    static void isfinite(Tensor *A, Tensor* B);
    

isinf
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::isinf

Test element-wise for positive or negative infinity.

  Parameters:

  - ``*A``: Tensor to test.
  - ``B``: Tensor to store the results of the test as booleans.

.. code-block:: c++

    static void isinf(Tensor *A, Tensor* B);
    

isnan
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::isnan

Test element-wise for NaN.

  Parameters:

  - ``*A``: Tensor to test.
  - ``B``: Tensor to store the results of the test as booleans.

.. code-block:: c++

    static void isnan(Tensor *A, Tensor* B);
    

isneginf
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::isneginf

Test element-wise for negative infinity.
  
  Parameters:

  - ``*A``: Tensor to test.
  - ``B``: Tensor to store the results of the test as booleans.

.. code-block:: c++

    static void isneginf(Tensor *A, Tensor* B);
    

isposinf
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::isposinf

Test element-wise for positive infinity.

  Parameters:

  - ``*A``: Tensor to test.
  - ``B``: Tensor to store the results of the test as booleans.

.. code-block:: c++

    static void isposinf(Tensor *A, Tensor* B);



Logical operations
---------------------------


logical_and
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::logical_and

Compute the truth value of ``A and B`` element-wise.

  Parameters:

  - ``A``: Tensor.
  - ``B``: Tensor.
  - ``C``: Tensor to store the results of the operation.


.. code-block:: c++

    static void logical_and(Tensor *A, Tensor *B, Tensor *C);
        

logical_or
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::logical_or

Compute the truth value of ``A or B`` element-wise.

  Parameters:

  - ``A``: Tensor.
  - ``B``: Tensor.
  - ``C``: Tensor to store the results of the operation.

.. code-block:: c++

    static void logical_or(Tensor *A, Tensor *B, Tensor *C);
        

logical_not
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::logical_not

Compute the truth value of ``not A`` element-wise.

  Parameters:

  - ``A``: Tensor.
  - ``B``: Tensor to store the results of the operation.
 
.. code-block:: c++

    static void logical_not(Tensor *A, Tensor *B);
        

logical_xor
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::logical_xor

Compute the truth value of ``A xor B``, element-wise.

  Parameters:

  - ``A``: Tensor.
  - ``B``: Tensor.
  - ``C``: Tensor to store the results of the operation.
 
.. code-block:: c++

    static void logical_xor(Tensor *A, Tensor *B, Tensor *C);



Comparison
---------------------------


allclose
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::allclose

Returns True if two arrays are element-wise equal within a tolerance.

.. code-block:: c++

    static bool allclose(Tensor *A, Tensor *B, float rtol=1e-05, float atol=1e-08, bool equal_nan=false);  // Returns true or false
    

isclose
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::isclose

Returns a boolean array where two arrays are element-wise equal within a tolerance.

.. code-block:: c++

    static void isclose(Tensor *A, Tensor *B, Tensor *C, float rtol=1e-05, float atol=1e-08, bool equal_nan=false);  // Returns a boolean tensor
        

greater
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::greater

Return the truth value of ``A > B`` element-wise.

  Parameters:

  - ``A``: Tensor.
  - ``B``: Tensor.
  - ``C``: Tensor to store the results of the operation.
 
.. code-block:: c++

    static void greater(Tensor *A, Tensor *B, Tensor *C);


greater_equal
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::greater_equal

Return the truth value of ``A >= B`` element-wise.

  Parameters:

  - ``A``: Tensor.
  - ``B``: Tensor.
  - ``C``: Tensor to store the results of the operation.
 
.. code-block:: c++

    static void greater_equal(Tensor *A, Tensor *B, Tensor *C);


less
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::less

Return the truth value of ``A < B`` element-wise.

  Parameters:

  - ``A``: Tensor.
  - ``B``: Tensor.
  - ``C``: Tensor to store the results of the operation.
 
.. code-block:: c++

    static void less(Tensor *A, Tensor *B, Tensor *C);


less_equal
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::less_equal

Return the truth value of ``A =< B`` element-wise.

  Parameters:

  - ``A``: Tensor.
  - ``B``: Tensor.
  - ``C``: Tensor to store the results of the operation.
 
.. code-block:: c++

    static void less_equal(Tensor *A, Tensor *B, Tensor *C);


equal
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::equal

Return ``A == B`` element-wise.

  Parameters:

  - ``A``: Tensor.
  - ``B``: Tensor.
  - ``C``: Tensor to store the results of the operation.
 
.. code-block:: c++

    static void equal(Tensor *A, Tensor *B, Tensor *C);
        

not_equal
^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::not_equal

Return ``A != B`` element-wise.

  Parameters:

  - ``A``: Tensor.
  - ``B``: Tensor.
  - ``C``: Tensor to store the results of the operation.
 
.. code-block:: c++

    static void not_equal(Tensor *A, Tensor *B, Tensor *C);