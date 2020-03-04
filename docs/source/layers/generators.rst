Generators
================

Gaussian Generator
------------------

.. doxygenfunction:: GaussGenerator

Generates a gaussian noise output (typically used for GANs)

Example:

.. code-block:: c++
   :linenos:

    layer GaussGenerator(float mean, float stdev, vector<int> size){



Uniform Generator
-----------------

.. doxygenfunction:: UniformGenerator

Generates a uniform noise output (typically used for GANs)

Example:

.. code-block:: c++
   :linenos:

    layer UniformGenerator(float low, float high, vector<int> size);


