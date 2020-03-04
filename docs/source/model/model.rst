Model
=====


Constructor
------------


.. doxygenfunction:: eddl::Model

Example:

.. code-block:: c++
   :linenos:

    model Model(vlayer in, vlayer out);


Build
----------


.. doxygenfunction:: eddl::build(model, optimizer, CompServ *, bool)

.. doxygenfunction:: eddl::build(model, optimizer, const vector<string>&, const vector<string>&, CompServ *, bool)


Example:

.. code-block:: c++
   :linenos:

    void build(model net, optimizer o, const vector<string> &lo, const vector<string> &me, CompServ *cs=nullptr, bool init_weights=true);
    //e.g.: build(mymodel, sgd(0.01f), {"cross_entropy"}, {"accuracy"}, CS_GPU({1, 0}), true);


Summary
----------

.. doxygenfunction:: eddl::summary

Example:

.. code-block:: c++
   :linenos:

    void summary(model m);


Result:

.. code-block:: text

    Generating Random Table
    ---------------------------------------------
    input1                        |  (784)     =>      (784)
    dense1                        |  (784)     =>      (1024)
    leaky_relu1                   |  (1024)    =>      (1024)
    dense2                        |  (1024)    =>      (1024)
    leaky_relu2                   |  (1024)    =>      (1024)
    dense3                        |  (1024)    =>      (1024)
    leaky_relu3                   |  (1024)    =>      (1024)
    dense4                        |  (1024)    =>      (10)
    softmax4                      |  (10)      =>      (10)
    ---------------------------------------------


Plot
-----------------


.. doxygenfunction:: eddl::plot

Example:

.. code-block:: c++
   :linenos:

    void plot(model m, string fname, string mode="LR");

Result:

.. image:: /_static/images/models/mlp.svg



Load
--------------


.. doxygenfunction:: eddl::load(model, string&, string)

Example:

.. code-block:: c++
   :linenos:

    void load(model m, const string& fname, string format="bin");



Save
--------------------


.. doxygenfunction:: eddl::save(model, string&, string)

Example:

.. code-block:: c++
   :linenos:

    void save(model m, const string& fname, string format="bin");



Learning rate (on the fly)
--------------------------


.. doxygenfunction:: eddl::setlr(model, vector<float>)

Example:

.. code-block:: c++
   :linenos:

    void setlr(model net,vector<float>p);




Logging
--------


.. doxygenfunction:: eddl::setlogfile(model, string)

Example:

.. code-block:: c++
   :linenos:

    void setlogfile(model net, string fname);




Move to device
---------------

Move the model to a specific device

.. doxygenfunction:: eddl::toCPU

.. doxygenfunction:: eddl::toGPU(model, vector<int>, int, string)

Example:

.. code-block:: c++
   :linenos:

    void toCPU(model net, int t=std::thread::hardware_concurrency()); // num. threads, memory consumption
    void toGPU(model net, vector<int> g, int lsb, string mem); // mode, list of gpus (on=1/off=0), sync number, memory consumption

