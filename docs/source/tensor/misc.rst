Miscellaneous
==============

.. note::

    Section in progress

    Read this: https://github.com/deephealthproject/eddl/blob/master/eddl_progress_tensor.md


Functions
------------

toCPU
^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::toCPU

Clone a tensor to the CPU

.. code-block:: c++

    void toCPU(int dev=DEV_CPU);

toGPU
^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::toGPU

Clone a tensor to the GPU

.. code-block:: c++

    void toGPU(int dev=DEV_GPU);


isCPU
^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::isCPU

Check if the tensor is in CPU

.. code-block:: c++

    int isCPU();


isGPU
^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::isGPU

Check if the tensor is in GPU

.. code-block:: c++

    int isGPU();


isFPGA
^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::isFPGA

Check if the tensor is in FPGA

.. code-block:: c++

    int isFPGA();


isSquared
^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::isSquared

Check if all dimensions in the tensors are the same

.. code-block:: c++

    static bool isSquared(Tensor *A);


copy
^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::copy

Copy data from Tensor A to B

.. code-block:: c++

    static void copy(Tensor *A, Tensor *B);


clone
^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::clone

Clone a tensor (same device)

.. code-block:: c++

    Tensor* clone();


info
^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::info

Print shape, device and size information

.. code-block:: c++

    void info();


print
^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::print

Print the tensor values

.. code-block:: c++

    void print(bool asInt=false, bool raw=false);


valid_indices
^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::valid_indices

Check if the given indices are valid for this tensor

.. code-block:: c++

    bool valid_indices(vector<int> indices);


get_address_rowmajor
^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: Tensor::get_address_rowmajor

Translate a set of indices to their corresponding address (row-major)

.. code-block:: c++

    int get_address_rowmajor(vector<int> indices);
