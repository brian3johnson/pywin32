===========
db_print.py
===========

------
Sample
------

The only smart program in the folder. By default, this does the same thing as :file:`db_print_simple.py`. However, it also looks for command line arguments. Type :kbd:`help` to see the options.

   If you use :code:`table_name=?` it will print a list of the tables in the :file:`.mdb`.

   :samp:`filename={X}` lets you open a different :file:`.mdb`.

.. note::

   This sample uses the database :file:`\\adodbapi\\examples\\test.mdb`

.. literalinclude:: ../../../../adodbapi/examples/db_print.py
   :linenos: