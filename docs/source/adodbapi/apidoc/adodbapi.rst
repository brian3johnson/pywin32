================
adodbapi package
================

.. todo::
  
  * Create docstrings for remaining module members

.. contents::
   :depth: 1
   :local:

adodbapi
========

.. automodule:: adodbapi
   :members:
   :undoc-members:
   :show-inheritance:

adodbapi.ado_consts
===================

.. automodule:: adodbapi.ado_consts
   :members:
   :undoc-members:
   :show-inheritance:

adodbapi.Connection
===================

.. 
   automodule:: adodbapi.adodbapi
   :members:
   :undoc-members: 
   :show-inheritance:

.. autoclass:: adodbapi.Connection
   :undoc-members: 
   :show-inheritance:
   
   A :class:`.Connection` object holds an ADO connection in its :code:`.connector` attribute.

   A :class:`.Connection` object is usually created using the standard api constructor.

   Internally, it creates an empty :class:`.Connection` object, fills in the attributes needed, and then call its :meth:`.connect()` method (which calls the ADO :code:`Open` method).

Connection methods
------------------

.. automethod:: adodbapi.Connection.close

.. automethod:: adodbapi.Connection.commit

.. automethod:: adodbapi.Connection._rollback

.. automethod:: adodbapi.Connection.cursor

   returns an :class:`adodbapi.adodbapi.Cursor`

Connection methods (non-standard)
---------------------------------

.. automethod:: adodbapi.Connection.__enter__

   The connection is a context manager for transactions.

.. automethod:: adodbapi.Connection.__exit__

   If no errors occurred, :meth:`.commit()`, otherwise :meth:`._rollback()`

.. automethod:: adodbapi.Connection.get_table_names

   Returns a list of table names in your database. (schema)

Connection attributes
---------------------

.. autoproperty:: adodbapi.Connection.dbapi

   references the module defining the connection. (A proposed db-api V3 extension.) This is a way for higher level code to reach module-level attributes.

.. todo:: 

   * autodoc fails to generate .messages, variantConversions, and .timeout
   * These are all *private* attributes. Should they be converted to *properties*?

.. autoattribute:: adodbapi.Connection.errorhandler

   (standard extension. See PEP.) (does not work on remote)
.. 
   autoattribute:: adodbapi.Connection.messages
   
   (standard extension. See PEP)

.. autoattribute:: adodbapi.Connection.connector

   (Internal) the ADO connection object

.. autoattribute:: adodbapi.Connection.paramstyle

   can be altered by the programmer to change the paramstyle in use. The supported values are :code:`'qmark'` (the default), :code:`'format'`, and :code:`'named'`. Values of :code:`'pyformat'`, and :code:`'dynamic'` are also accepted (see below).

   The connection string keyword :code:`paramstyle` will set the default for the class for future connections.

.. autoattribute:: adodbapi.Connection.connection_string

   the complete connection string which was used to start ADO.

.. autoattribute:: adodbapi.Connection.dbms_name

   string identifying the actual database engine from the connection.

.. autoattribute:: adodbapi.Connection.dbms_version

   string identifying the version of the db engine.
.. 
   autoattribute:: adodbapi.Connection.variantConversions

   a map of ado types to the functions used to import them.(not available on remote)

.. autoattribute:: adodbapi.Connection.supportsTransactions

   (bool) this driver is capable of :meth:`.commit()`/:meth:`.rollback()`.
.. 
   autoattribute:: adodbapi.Connection.timeout

   supply a value for :code:`CommandTimeout`.
   
   .. note::
      The :attr:`timeout` connection value is stored in this attribute, and is used as the connection timeout. It is then re-used as the command timeout. The user may overcome this rather goofy "feature" by supplying a different value to this attribute after the connection is made. The value is in seconds, and will be used for all subsequent SQL commands.

adodbapi.Cursor
===============

.. autoclass:: adodbapi.Cursor
   :undoc-members: 
   :show-inheritance:

Attributes
----------

.. note:: 

   .description is created/accessed only via __getattr__. Is a list[tuple]

.. autoattribute:: adodbapi.Cursor._description

   as defined by :pep:`249`, a sequence of 7-item sequences

.. autoattribute:: adodbapi.Cursor.rowcount

   type is / returns int

   :code:`-1` means "not known". Will be ADO :code:`recordset.RecordCount` (if it works), otherwise, the count returned by the last ADO :code:`Execute` operation.

Attributes (standard extensions)
--------------------------------

.. autoattribute:: adodbapi.Cursor.connection

   back-link to the :class:`adodbapi.adodbapi.Connection`

.. autoattribute:: adodbapi.Cursor.errorhandler

   (see :pep:`249` - a function to process exceptions.)

.. autoattribute:: adodbapi.Cursor.messages

   (see :pep:`249`)

.. autoattribute:: adodbapi.Cursor.arraysize

   (=:code:`1`) # the default number of rows to fetch in :code:`fetchmany()`

Attributes (non-standard)
-------------------------

.. note:: 

   autodoc fails to generate .returnValue

.. autoattribute:: adodbapi.Cursor.paramstyle

   can be altered by the user to change paramstyle processing. (default taken from connection.) (see below)

.. autoattribute:: adodbapi.Cursor.rs

   the internal ADO :code:`recordset` (local) or raw unpickled data (remote)

.. autoattribute:: adodbapi.Cursor.converters

   a list of input-conversion functions, one per column. (not available on remote)

.. autoattribute:: adodbapi.Cursor.columnNames

   a dictionary of: (lower-cased) column name : (column number).

.. autoattribute:: adodbapi.Cursor.numberOfColumns

   number of columns in present record set.

.. autoattribute:: adodbapi.Cursor.command

   the last raw SQL command sent to the query (before any reformatting)

.. autoproperty:: adodbapi.Cursor.query

   the text of last operation, as converted by reformatting

.. 
   autoattribute:: adodbapi.Cursor.returnValue

   the result returned by a previous :code:`.callproc()`

Methods (standard)
------------------

.. automethod:: adodbapi.Cursor.callproc

   execute a stored procedure, returning parameter values. A "returned value" (not an "out" parameter) will be in :code:`crsr.returnValue` -> returns the (modified) parameter list

.. automethod:: adodbapi.Cursor.close

   close the cursor, free the recordset

    .. note::
        
       non-standard: in adodbapi, it is NOT an error to re-close a closed cursor

.. automethod:: adodbapi.Cursor.execute

   .. py:attribute:: operation
      :type: str

      the text of the SQL.

   .. py:attribute:: parameters
      :type: list
      :value: None

      parameters for the query or command...

   execute a query or command...

   does not return anything / returns None

.. automethod:: adodbapi.Cursor.executemany

   runs the SQL operation several times, once for each group of parameters in sequence-of-parameters.

.. automethod:: adodbapi.Cursor.fetchone

   returns :class:`adodbapi.apibase.SQLrow`
   get the next row from the result set. Calls ADO :code:`recordset.GetRows(1)`

.. automethod:: adodbapi.Cursor.fetchmany

   returns :class:`adodbapi.apibase.SQLrows`

   get a :code:`size` sequence of rows. Calls ADO :code:`recordset.GetRows(size)`

.. automethod:: adodbapi.Cursor.fetchall

   attempt to retrieve all remaining rows in the result set. Calls ADO :code:`recordset.GetRows()` using a local cursor so may use a great deal of memory if the query set is large.

.. automethod:: adodbapi.Cursor.nextset

   If an operation (such as a stored procedure call) has produced multiple result sets, skip to the next available result set.

.. automethod:: adodbapi.Cursor.setinputsizes

.. automethod:: adodbapi.Cursor.setoutputsize

Methods (extensions)
--------------------

.. automethod:: adodbapi.Cursor.prepare

   initiate an SQL prepared statement.

      This method actually does very little, and the use of it may not speed up your program very much, if at all. It does store the SQL statement you pass (operation) in the cursor's :code:`self.command` attribute, and sends the appropriate flag to ADO. It will cache converted :code:`paramstyle` operation strings. Calling :code:`.execute()` with any other string, or calling :code:`.prepare()` again will invalidate the preparation.

      For example: :code:`cursor.executemany()` is programmed internally like:

      .. code-block:: python

         def executemany(self, operation, sequence_of_parameter_sequences):
             self.prepare(operation)
             for params in sequence_of_parameter_sequences:
                 self.execute(self.command, params)

.. automethod:: adodbapi.Cursor.get_returned_parameters

   some providers will not return the (modified) parameter list, nor the :code:`return_value`, until after the last recordset is closed. This method can be called (_after_ calling :code:`nextset()` until it returns :code:`None`) to get those values.

.. automethod:: adodbapi.Cursor.__next__

   The cursor can be used as an iterator, each iteration does :code:`fetchone()`

.. automethod:: adodbapi.Cursor.__iter__

.. automethod:: adodbapi.Cursor.__enter__

   the cursor is a context manager which will auto-close

.. automethod:: adodbapi.Cursor.__exit__

connect
-------

.. autofunction:: adodbapi.connect

   returns :class:`adodbapi.adodbapi.Connection`

adodbapi.apibase
================

.. automodule:: adodbapi.apibase
   :members:
   :undoc-members: 
   :show-inheritance:

adodbapi.is64bit
================

.. automodule:: adodbapi.is64bit
   :members:
   :undoc-members: 
   :show-inheritance:

adodbapi.process_connect_string
===============================

.. automodule:: adodbapi.process_connect_string
   :members:
   :undoc-members: 
   :show-inheritance:

adodbapi.schema_table
=====================

.. automodule:: adodbapi.schema_table
   :members:
   :undoc-members: 
   :show-inheritance: