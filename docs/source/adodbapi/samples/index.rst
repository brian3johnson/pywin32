=======
Samples
=======

.. toctree::
   :maxdepth: 4
   :hidden:
   :titlesonly:

   db_table_names
   xls_write
   xls_read
   db_print

.. note::

   The samples :file:`db_print.py` and :file:`db_table_names.py` use the database :file:`\\adodbapi\\examples\\test.mdb`

Several small complete sample programs are included:

.. todo:: 

   * :file:`db_print_simple.py` is not in the examples directory. Should it be?
   * :file:`is64bit.py` is not in the examples directory. Should it be?
   
:file:`db_print_simple.py`
   A simple as possible example. Opens a local :file:`.mdb` (ACCESS) datebase and reads rows from a table.
:doc:`db_table_names`
   Opens the same database & prints out a list of the tables in it.
:file:`is64bit.py`
   A copy of the one in the package, just here for import convenience.

   `is64bit.Python()` → bool

   `is64bit.os()` → bool

:file:`\\adodbapi\\examples\\test.mdb`
   The sample database for the examples. (Also copied into the test environment temporary folder when testing 64-bit Python programs. They cannot build :file:`.mdb` files.)
:doc:`xls_write`
   Creates a simple :program:`Excel` spreadsheet.
:doc:`xls_read`
   Read the above spreadsheet.
:doc:`db_print`
   The only smart program in the folder. By default, this does the same thing as :file:`db_print_simple.py`. However, it also looks for command line arguments. Type :kbd:`help` to see the options.

   If you use :code:`table_name=?` it will print a list of the tables in the :file:`.mdb`.

   :samp:`filename={X}` lets you open a different :file:`.mdb`.