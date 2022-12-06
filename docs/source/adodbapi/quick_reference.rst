===============================
Python ADODBAPI quick reference
===============================

.. admonition:: Existing document

   :file:`\\adodbpi\\quick_reference.md`

.. contents::
   :depth: 1
   :local:


adodbapi is a Python DB-API 2.0 module that makes it easy to use Microsoft |ado| for connecting with databases and other data sources using either CPython or IronPython.

For complete installation instructions, see the README.txt file, which you may also find at https://pypi.python.org/pypi/adodbapi. Quick installation instructions (for users of CPython) are as follows: :code:`pip3 install pywin32`.

About ADO, ODBC, and Connection Strings
=======================================

Microsoft engineers invented ODBC as a standard way of connecting to a tabular data source, such as an SQL database server. It was such a good design that it was adopted almost universally. Therefore, Microsoft thought they should come up with something even better that everyone else did not have.

That was ADO. In truth, ADO does have some features that ODBC does not have. For compatibility, it uses ODBC as its default mode of operation. One powerful anti-feature is: it is proprietary. You have to have Windows to use it.

ODBC connections are made using a string, called a "data set name", abbreviated "dsn". A dsn can be very short. There is a utility program which stores the translations of a dsn to all of the information needed to connect to that data store. There is a more-or-less defined standard of how to pass that additional information using the dsn string for those cases where the dsn is not already known by the system.

ADO uses a completely different way of accomplishing the same goal. To make matters worse, ADO operates, by default, in ODBC mode, so it must be able to process this information in either format. The resulting mass of confusion is called a "connection string". There is an entire web site dedicated to giving examples of connection strings in numerous combinations. See http://www.connectionstrings.com/

and for more explanation:

http://www.asp101.com/articles/john/connstring/default.asp


The software which connects ODBC to an engine is called a "Driver". One which talks in ADO is called a "Provider". Sometimes there will be a Provider for a Driver.

Driver (and Provider) download links
====================================

The current (as of 2019) SQL Server OLE DB provider (which they call a "driver" here) is https://www.microsoft.com/en-us/download/details.aspx?id=56730 which is linked from, and explained `here, in their document <https://docs.microsoft.com/en-us/sql/connect/oledb/oledb-driver-for-sql-server?view=sql-server-2017>`_.

* Jet (ACCESS database) and other file datasets (like .xls and .csv) "ACE" Provider:

  * http://www.microsoft.com/en-us/download/details.aspx?id=13255 a (32 bit) Microsoft.Jet.OLEDB.4.0 Provider, which may be included with Windows. Note that you are not permitted load the 32 bit "ACE" provider if you have any 64-bit Office components installed. Conventional wisdom says that you must use 64 bit Python in this case. However, see the answer in http://stackoverflow.com/questions/12270453/ms-access-db-engine-32-bit-with-office-64-bit. If you decide to try hacking the installers, you may find http://www.pantaray.com/msi_super_orca.html to be a useful alternative to Orca. My experience is that such a `hacked installer (like this one) <http://shares.digvil.info/redis>`_ can also be used on machines where "click to buy" versions of Office have been removed, but are still blocking installation of the redistributable provider.

* To use any ODBC driver from 64 bit Python, you also need the MSDASQL provider. It is shipped with Server 2008 and Vista and later. For Server 2003, You will have to `download it <http://www.microsoft.com/en-us/download/details.aspx?id=20065>`_ from Microsoft.
* MySQL driver http://dev.mysql.com/downloads/connector/odbc/ or MariaDB driver https://downloads.mariadb.org/connector-odbc/ or :code:`choco install mysql.odbc`
* PostgreSQL driver http://www.postgresql.org/ftp/odbc/versions/msi/ (scroll all the way to the bottom) or :code:`choco install psqlodbc`.

PEP-249
=======

This "quick reference" assumes that you are already familiar with Python, SQL, and the general principles of accessing a database using the :pep:`249` api. I may write a book later. Here, I only intend to cover the extensions and special features of adodbapi.

Module level attributes
=======================

The PEP requires several module level attributes. Older versions of adodbapi (which was once all one big file) defined a hundred or two. I hate that, but cannot break old code, so I decided to fix the problem for Python 3. If using Python3 the programmer must take the time to pick up the symbols she needs from :code:`apibase` and :code:`ado_consts`.

Part of the adodbapi package's :file:`__init__.py` looks something like this:

.. code-block:: python

   if sys.version_info < (3,0): # in Python 2, define all symbols, just like before
       from apibase import *  # using this is bad
       from ado_consts import *  # using this is worse
   else:
       # but if the user is running Python 3, then keep the dictionary clean
       from apibase import apilevel, threadsafety, paramstyle
       from apibase import Warning, Error, InterfaceError, DatabaseError, DataError
       from apibase import OperationalError, IntegrityError
       from apibase import InternalError, ProgrammingError, NotSupportedError
       from apibase import NUMBER, STRING, BINARY, DATETIME, ROWID
   
   from adodbapi import connect, Connection, __version__
   version = 'adodbapi v' + __version__

Please, use only those last four symbols from adodbapi. All others should be imported directly from their own sub-modules. My tests and examples all follow that rule.

Connect (Use of the connect constructor)
========================================

As required by the PEP, the simplest way to connect is to use a "data
set name".

.. code-block:: python

   import adodbapi
   myConn = adodbapi.connect('myDataSetName')

Which will work just fine, provided you (or someone) has done all of the hard work by going into :menuselection:`Control Panel --> Administrative Tools --> Data Sources (ODBC)` and set everything up for you under :code:`'myDataSetName'`.

Usually, life is not so simple...

.. code-block:: python

   import adodbapi
   myhost = r".\SQLEXPRESS"
   mydatabase = "Northwind"
   myuser = "guest"
   mypassword = "12345678"
   connStr = """Provider=SQLOLEDB.1; User ID=%s; Password=%s;
   Initial Catalog=%s; Data Source= %s"""
   myConnStr = connStr % (myuser, mypassword, mydatabase, myhost)
   myConn = adodbapi.connect(myConnStr)

The PEP suggests that we should be able to create the connection using positional arguments. For us, that is difficult, because the syntax of an ADO connection string is so varied that we have to tell the module where to insert the arguments. In order to do that, use Python's old-style string formatting operations and label the places where the arguments should be inserted. An argument named :code:`spam` would be located by a :code:`%(spam)s` construct. The second, third, forth, and fifth arguments are defined (by standard) as being :code:`user`, :code:`password`, :code:`host`, and :code:`database`.

.. code-block:: python

   connStr = """Provider=SQLOLEDB.1; User ID=%(user)s;
   Password=%(password)s; Initial Catalog=%(database)s;
   Data Source=%(host)s"""

   myConn=adodbapi.connect(connStr, myuser, mypassword, myhost, mydatabase)

Which will work.

It would be better documented, however, to use keyword, rather than positional arguments:

.. code-block:: python

   myConn = adodbapi.connect(connStr, user=myuser, password=mypassword, host=myhost, database=mydatabase)

In adodbapi, you may also pass keywords using a dictionary structure, which also allows us to pass additional arguments:

.. code-block:: python

   conn_args = {'host' : r".\SQLEXPRESS",
       'database': "Northwind",
       'user': "guest",
       'password': "12345678",
       'timeout': 60}
   
   myConn = adodbapi.connect(connStr, [], **conn_args)

Which works, but is ugly. So let's also put the connection string into the dictionary. As an extension, I allow the first (or second) positional argument to be the keyword dictionary.

.. code-block:: python

   conn_args = {'host': r".\SQLEXPRESS",
       'database': "Northwind",
       'user': "guest",
       'password': "12345678"}
   conn_args['connection_string'] = """Provider=SQLOLEDB.1;
   User ID=%(user)s; Password=%(password)s;
   Initial Catalog=%(database)s; Data Source= %(host)s"""

   myConn = adodbapi.connect(conn_args)

Not pretty, I will admit, but it is about as readable as connection strings get. Arbitrary keywords, are also expanded using the same mechanism. For example, I often use "provider" to allow me to choose between database drivers. There are also built-in keywords which the constructor recognizes when building your connection. For example, :code:`timeout=n`.

**Dictionary Keywords which have meaning inside the connect method:**

* :code:`timeout=30` # set the ADO connection :code:`timeout` to :samp:`{n}` seconds. (Default = :code:`30`) This value will also be used as the SQL command timeout subsequently. The command :code:`timeout` can be changed via the :code:`timeout` connection attribute.
* :code:`paramstyle='qmark'` # initialize the connection's :code:`paramstyle`, like :code:`'qmark'`, :code:`'format'`, or :code:`'named'`. (Default = :code:`'qmark'`)
* :code:`autocommit=False`` # initialize :code:`autocommit` on the connection. (Default = :code:`False`)

Connection Keyword Macro Language
=================================

It often happens, when building a connection string for a generic connection, that you need to know information about your host computer, such as, "Is it running 32-bit or 64-bit Python?" Keyword macros provide a method of passing that decision on to the server it run time.

A macro is defined by using a keyword which starts with :code:`macro_` followed by the macro name. The value associated with the keyword must be a single string, or a valid Python sequence. The string or sequence is passed to the macro processor. The first :code:`([0])` argument will become the new keyword which the macro will produce. If the macro requires arguments, they will be in subsequent members.

The result of the macro operation will be the value of the new key.

* :code:`macro_is64bit`: Test 64-bit-ed-ness of the proxy server. If the server is running 64-bit Python, return argument :code:`[1]`, otherwise return argument :code:`[2]`. Example:

.. code-block:: python

   conn_keys['macro_is64bit'] = ['provider',
       'Microsoft.ACE.OLEDB.12.0', "Microsoft.Jet.OLEDB.4.0"]

  conn_keys['connection_string'] = "Provider=%(provider)s; ... and ... more ... stuff\"

* :code:`macro_getuser`: Retrieve the proxy server logged-in-user's username. "My systems administrator gave me a test database named after myself. I thought it would be handy to let others do a similar thing." Thus:

.. code-block:: python

   conn_keys['macro_getuser'] = 'database'

   conn_keys['connection_string'] = "...stuff...; Initial Catalog=%(database)s; ..."

* :code:`macro_auto_security`: Build ADO security string automagically. If the username (key :code:`user`) is missing, blank, or None, use Windows login security, otherwise use SQL Server security with :code:`user` and :code:`password`. It runs this code:

.. code-block:: python

  if macro_name == "auto_security":
      if not 'user' in kwargs or not bool(kwargs['user']):
          return new_key, 'Integrated Security=SSPI'
      return new_key, 'User ID=%(user)s; Password=%(password)s'

      # note that %(user) and %(password) are not substituted here,
      # they are put in place to be substituted before being sent to ADO.

.. code-block:: python

  conn_keys['macro_auto_security'] = ['secure']
  conn_keys['user'] = None # username here for Server Security
  conn_keys['password'] = 'xys' # ignored if "user" is blank or undefined
  conn_keys['connection_string'] = "\...stuff...; %(secure)s"

Connection class
================

A :code:`connection` object holds an ADO connection in its :code:`.connector`` attribute.

A :code:`connection` object is usually created using the standard api constructor.

Internally, it creates an empty :code:`connection` object, fills in the attributes needed, and then call its :code:`.connect()` method (which calls the ADO :code:`Open` method).

Connection Methods:

The standard methods are supplied:

* :code:`.close()` # close the connection (does an ADO Close)

* :code:`.commit()` # commits any pending transaction(s) on the connection

* :code:`.rollback()` # rolls back any pending transaction. If the engine attached to the present instance does not support transactions, this method will appear to not be present (an :code:`AttributeError` will be raised), as per the PEP.

* :code:`.cursor()` # returns a new :code:`Cursor` object for the connection.

Connection Methods: (non-standard)

* :code:`.__enter__()` # the connection is a context manager for transactions

* :code:`.__exit__()` # if no errors occurred, :code:`.commit()`, otherwise :code:`.rollback()`

* :code:`.get_table_names()` # returns a list of table names in your database. (schema)

Connection Attributes

* :code:`.errorhandler` # (standard extension. See PEP.) (does not work on remote)

* :code:`.messages[]` # (standard extension. See PEP)

* :code:`.connector` # (Internal) the ADO connection object

* :code:`.paramstyle` # can be altered by the programmer to change the paramstyle in use. The supported values are :code:`'qmark'` (the default), :code:`'format'`, and :code:`'named'`. Values of :code:`'pyformat'`, and :code:`'dynamic'` are also accepted (see below).

   The connection string keyword :code:`paramstyle` will set the default for the class for future connections.

* :code:`.connection_string` # the complete connection string which was used to start ADO.

* :code:`.dbms_name` # string identifying the actual database engine from the connection.

* :code:`.dbms_version` # string identifying the version of the db engine.

* :code:`.variantConversions` # a map of ado types to the functions used to import them.(not available on remote)

* :code:`.supportsTransactions` # (bool) this driver is capable of commit()/rollback().

* :code:`.dbapi` # references the module defining the connection. (A proposed db-api V3 extension.) This is a way for higher level code to reach module-level attributes.

* :code:`.timeout` # supply a value for :code:`CommandTimeout`. Note: the :code:`timeout` connection value is stored in this attribute, and is used as the connection timeout. It is then re-used as the command timeout. The user may overcome this rather goofy "feature" by supplying a different value to this attribute after the connection is made. The value is in seconds, and will be used for all subsequent SQL commands.

Cursor class
============

Cursor attributes:

* :code:`.description` # as defined by :pep:`249`, a sequence of 7-item sequences:

for each column, defines the column by:

[0] :code:`name``: ADO :code:`field.Name`

[1] :code:`type_code`: ADO :code:`field.Type` - (values defined in
:code:`adodbapi.ado_consts`)

[2] :code:`display_size`: ADO :code:`field.ActualSize` or :code:`None`

[3] :code:`internal_size`: ADO :code:`field.DefinedSize`

[4] :code:`precision`: ADO :code:`field.Precision`

[5] :code:`scale`: ADO :code:`field.NumericScale`

[6] :code:`null_ok``: ADO :code:`field.Attributes` & :code:`adFldMayBeNull`

* :code:`.rowcount` # :code:`-1` means "not known". Will be ADO :code:`recordset.RecordCount` (if it works), otherwise, the count returned by the last ADO :code:`Execute` operation.

Cursor attributes (standard extensions):

* :code:`.connection` # back-link to the connection

* :code:`.errorhandler` # (see :pep:`249` - a function to process exceptions.)

* :code:`.messages[]` # (see :pep:`249`)

* :pep:`249`.arraysize` (=:code:`1`) # the default number of rows to fetch in :code:`fetchmany()`

Cursor attributes (non-standard):

* :code:`.paramstyle` # can be altered by the user to change paramstyle processing. (default taken from connection.) (see below)

* :code:`.rs` # the internal ADO :code:`recordset` (local) or raw unpickled data (remote)

* :code:`.converters[]` # a list of input-conversion functions, one per column. (not available on remote)

* :code:`.columnNames{}` # a dictionary of: (lower-cased) column name : (column number).

* :code:`.numberOfColumns` # number of columns in present record set.

* :code:`.command` # the last raw SQL command sent to the query (before any reformatting)

* :code:`.query` # the text of last operation, as converted by reformatting

* :code:`.return_value` # the result returned by a previous :code:`.callproc()`

Cursor Methods (standard):

* :code:`.callproc()` # execute a stored procedure, returning parameter values. A "returned value" (not an "out" parameter) will be in :code:`crsr.returnValue` -> returns the (modified) parameter list

- :code:`.close()` # close the cursor, free the recordset

    .. note::
        
       non-standard: in adodbapi, it is NOT an error to re-close a closed cursor

* :code:`.execute(operation, parameters)` # execute a query or command...

   - :code:`operation`: the text of the SQL.
   - :code:`parameters`: parameters for the query or command...

      If :code:`paramstyle` is :code:`'qmark'` this must be a sequence.
      
      If :code:`paramstyle` is :code:`'named'` this must be a mapping (dictionary).

      If :code:`paramstyle` is :code:`'dynamic'`, :code:`'format'`, or :code:`'pyformat'` it could be either, but your SQL format must be appropriate for your choice (see below).

      -> :code:`None`. There is no return value, use :code:`.fetchxxx()` to see data.

* :code:`.executemany(operation, sequence-of-parameters)` # runs the SQL operation several times, once for each group of parameters in sequence-of-parameters.

      -> :code:`.rowcount` will be the sum of all :code:`.rowcounts`, unless any was :code:`-1`.

* :code:`.fetchone()` # get the next row from the result set. Calls ADO :code:`recordset.GetRows(1)`
* :code:`.fetchmany(size=cursor.arraysize)` # get a :code:`size` sequence of rows. Calls ADO :code:`recordset.GetRows(size)`
* :code:`.fetchall()` # attempt to retrieve all remaining rows in the result set. Calls ADO :code:`recordset.GetRows()` using a local cursor so may use a great deal of memory if the query set is large.
* :code:`.nextset()` # If an operation (such as a stored procedure call) has produced multiple result sets, skip to the next available result set.

      -> returns :code:`None` if there are no more result sets, otherwise :code:`True`.

* :code:`.setinputsizes()` # pass
* :code:`.setoutputsizes()` # pass

Cursor methods (extensions):

* :code:`.prepare(operation)` # initiate an SQL prepared statement.

   This method actually does very little, and the use of it may not speed up your program very much, if at all. It does store the SQL statement you pass (operation) in the cursor's :code:`self.command` attribute, and sends the appropriate flag to ADO. It will cache converted :code:`paramstyle` operation strings. Calling :code:`.execute()` with any other string, or calling :code:`.prepare()` again will invalidate the preparation.

   For example: :code:`cursor.executemany()` is programmed internally like:

   .. code-block:: python

      def executemany(self, operation, sequence_of_parameter_sequences):
          self.prepare(operation)
          for params in sequence_of_parameter_sequences:
              self.execute(self.command, params)

* :code:`.get_returned_parameters()` # some providers will not return the (modified) parameter list, nor the :code:`return_value`, until after the last recordset is closed. This method can be called (_after_ calling :code:`nextset()` until it returns :code:`None`) to get those values.
* :code:`.next()` # The cursor can be used as an iterator, each iteration does :code:`fetchone()`
* :code:`.__iter__()`
* :code:`.__enter__()` # the cursor is a context manager which will auto-close
* :code:`.__exit__()`

PARAMSTYLEs
===========

What???
=======

.. note::

    A quick explanation of :code:`paramstyle` follows: if you already know this, :ref:`skip this section <guru>`.

Many SQL queries or commands require data as part of their content. For example:

.. code-block::

   `UPDATE cheese SET qtyonhand = 0 WHERE name = 'MUNSTER'`

Chances are, this command will be given many times, but with other values appearing where :code:`0` and :code:`'MUNSTER'` appear in this command. It is convenient (as well as more efficient in some cases) to pass these values as parameters.

Unfortunately, the ISO SQL standard has not defined a method for doing this, so every designer of an SQL engine is free to choose a new way of expressing it. :pep:`249` recognizes several popular methods, and provides a way for the API module writer to communicate to the programmer which method he expects. It is left up to the programmer to adapt to whichever method the engine requires. According to PEP, the module author will place a string in the module attribute named :code:`.paramstyle` telling you which method to use. The defined possibilities are as follows...

:code:`'qmark'` is the default used by ADO. As far as I know, every ADO driver uses it. The above query would be altered by placing a question mark where the parameters should go. The programmer then passes the parameters (as as sequence) in the correct order for each :code:`?`.

.. code-block:: python

   sql = "UPDATE cheese SET qtyonhand = ? WHERE name = ?"
   args = [0, 'MUNSTER']
   crsr.execute(sql, args)

:code:`'format'` is used my many database engines, and blindly expected by django. The format looks like (but is emphatically not) the same as Python :code:`%s` string substitution.

Again, the programmer supplies the parameters (as a sequence) in the correct order.

.. code-block:: python

   sql = "UPDATE cheese SET qtyonhand = %s WHERE name = %s"
   args = [0, 'MUNSTER']
   crsr.execute(sql, args)

:code:`'named'` is used by Oracle, and is superior because it eliminates counting. Rather than keeping track of the parameters by position, the programmer passes the arguments as a mapping (dictionary) where each name is the key to find the correct place to make the substitution. She places names in the SQL string delimited by a leading colon (:code:`:`). Each key calls up the value for that place. In the following simple example, the syntax looks needlessly complex, but in queries which take a dozen or more parameters, it really helps.

.. code-block:: python

   sql = "UPDATE cheese SET qtyonhand = :qty WHERE name = :prodname"
   args = {'qty' : 0, 'prodname' : 'MUNSTER'}
   crsr.execute(sql, args)

:code:`'pyformat'` also takes a dictionary of arguments, but uses a syntax like Python's :code:`%` string operator:

.. code-block:: python

   UPDATE cheese SET qtyonhand = %(qty)s WHERE name =%(prodname)s
   args = {'qty' : 0, 'prodname' : 'MUNSTER'}
   crsr.execute(sql, args)

.. note:: 
   
   In adodbapi, :code:`'format'` and :code:`'pyformat'` both use the same subroutine. It depends on the presence of :code:`%` in your SQL operation string to hint whether to expect a mapping or a sequence. That seems to be the way some other api adapters operate.

The other :code:`paramstyle` possibility mentioned in the PEP is:

:code:`'numeric'`, which takes a sequence. It not implemented in adodbapi. (If you want it, patches will be considered.):

.. code-block::

   UPDATE cheese SET qtyonhand = :1 WHERE name = :2

.. _guru:

*(Gurus: Start reading again here)*

:code:`'dynamic'` [this :code:`paramstyle` is a non-standard extension in adodbapi. It
acts the same as :code:`'qmark'`, unless you pass a mapping (i.e., a dictionary) of parameters to your :code:`.execute()` method -- in which case it will act the same as :code:`'named'`.]

As an extension, adodbapi copies the module's paramstyle attribute to each connection, and then to each cursor. The programmer is allowed to change the paramstyle to the one she prefers to use. When the :code:`.execute()` method runs, it checks which paramstyle is expected, then converts the operation string into :code:`'qmark'`, and then makes the ADO :code:`Execute` call.

Extracting the appropriate SQL table values from Python objects is a complex operation. If your table receives unexpected values, try to simplify the objects you present as parameters. [Set the :code:`.verbose` attribute > :code:`2` to get a debug listing of the parameters.]

You may switch :code:`paramstyle` as often as desired. If you want to use :code:`'named'` for :code:`UPDATE`\s and :code:`'qmark'` for :code:`INSERT`\s, go right ahead. (Restriction: provide a new SQL operation string object after you change :code:`paramstyle`. I don't invalidate the cache.)

Row Class & Rows Class for returned data
========================================

The PEP specifies that :code:`.fetchone()` returns a "single sequence". It does not spell out what kind of a sequence. Originally, adodbapi returned a tuple. It is supposed to be up to the programmer to count columns of the returned data to select the correct thing. In the past, I have often resorted to putting long lists of constants into my Python code to keep track of which column a dutum was in.

The :code:`Row` class in ADODBAPI satisfies the PEP by having :code:`.fetchone()` return a sequence-like :code:`Row` object. It can be indexed and sliced like a list. This is the PEP standard method:

.. code-block:: python

   crsr.execute("SELECT prodname, price, qtyonhand FROM cheese")
   row = crsr.fetchone()
   while row:
       value = row[1] * row[2]
       print('Your {:10s} is worth {:10.2f}'.format(row[0], value))
       row = crsr.fetchone()  # returns None when no data remains

As an extension, a :code:`Row` object can also be indexed by column name:

.. code-block:: python

   crsr.execute("SELECT prodname, price, qtyonhand FROM cheese")
   for row in crsr:  # note extension: using crsr as an iterator
       value = row['price'] * row['qtyonhand']
       print('Your {:10s} is worth {:10.2f}'.format(row['prodname'], value))

But, _really_ lazy programmers, like me, use the column names as attributes:

.. code-block:: python

   crsr.execute("SELECT prodname, price, qtyonhand FROM cheese")
   for row in crsr:
       value = row.price * row.qtyonhand
       print('Your {:10s} is worth {:10.2f}'.format(row.prodname, value))

Now, isn't that easier to read and understand?

The PEP specifies that :code:`.fetchmany()` and :code:`.fetchall()` must return "a sequence of sequences". This as satisfied by returning a :code:`Rows` object, which emits a sequence of :code:`Row` objects. Both :code:`Row` and :code:`Rows` are actually lazy—they do not fetch data from the queryset until the programmer asks for it.

variantConversions for the connection and the cursor
====================================================

Each :code:`Connection` instance has an optional :code:`.variantConversions` attribute. Usually it will not be present. If it is present, it will be used in preference to the module's :code:`variantConversions` attribute. In order to avoid unintentional alterations, when you make an assignment to the attribute, it will be actually copied (by :code:`__setattr__`) rather than merely referenced.

In older versions of adodbapi, the accepted practice for user defined conversions was to modify the module's :code:`VariantConversionMap`. That still works, but please refrain.

A :code:`variantConversionsMap` is a dictionary of ADO variable types (as defined in :code:`adodbapi.ado_consts`) with the function to be used to read each type and convert it into a Python value. As a convenience, the :code:`__setitem__` for this class will accept a sequence, and will enter a mapping for each member of the sequence with the same value. So, to change several data retrieval functions:

.. code-block:: python

   import adodbapi.ado_consts as adc
   import adodbapi.apibase as api
   conn.variantConversions = api.variantConversions  # MAGIC: will make a copy.

   conn.variantConversions[(adc.adTinyInt, adc.adChar)] = myByteFunc

which will be equivalent to:

.. code-block:: python

   conn.variantConversions[adc.adTinyInt] = myByteFunc
   conn.variantConversions[adc.adChar] = myByteFunc

Also, there is a supply of sequences used to initialize to default map, in module :code:`adodbapi.apibase`. For example:

.. code-block:: 

   adoApproximateNumericTypes = (adc.adDouble, adc.adSingle)

If I wish to retrieve all floating point values differently, I might use:

.. code-block:: python

   conn.variantConversions = api.variantConversions
   conn.variantConversions[api.adoApproximateNumericTypes] = myFloatFunc

The cursor builds a list of conversion functions for each new query set, (in other words, each call to :code:`.execute()`, :code:`.callproc()` or :code:`.nextset()`).

You may override the conversion for any column by altering the function for that column:

.. code-block:: python

   crsr.conversions[4] = myFunc # change the reader for the fifth column
   crsr.fetchone()

To do this by column name, use:

.. code-block:: python

   crsr.conversions[crsr.columnNames['mycolumn']] = myFunc

The Examples folder
===================

Several small complete example programs are included:

:file:`db_print_simple.py`
   A simple as possibe example. Opens a local :file:`.mdb` (ACCESS) datebase and reads rows from a table.
:file:`db_table_names.py`
   Opens the same database & prints out a list of the tables in it.
:file:`is64bit.py`
   A copy of the one in the package, just here for import convenience.

   `is64bit.Python()` → bool
   `is64bit.os()` → bool

:file:`test.mdb`
   The sample database for the examples. (Also copied into the test environment temporary folder when testing 64-bit Python programs. They cannot build :file:`.mdb` files.)
:file:`xls_write.py`
   Creates a simple :program:`Excel` spreadsheet.
:file:`xls_read.py`
   Read the above spreadsheet:
:file:`db_print.py`
   The only smart program in the folder. By default, this does the same thing as :file:`db_print_simple.py`. However, it also looks for command line arguments. Type :kbd:`help` to see the options.

   If you use :code:`table_name=?` it will print a list of the tables in the :file:`.mdb`.

   :samp:`filename={X}` lets you open a different :file:`.mdb`.

Running the tests
=================

The test folder contains a set of unittest programs. Setting them up can be a bit complex, because you need several database servers to do a complete test, and each one has a different configuration. Scripts in this folder try to work in Python 2.7 or Python 3.5 and newer.

:file:`dbapi20.py`
   The standard test for API-2.0 compliance. Do not run this, it is imported only.
:file:`test_adodbapi_dbapi20.py`
   Imports the above and runs it on your local machine. You may have to actually install adodbapi in your Python library for it to work exactly right, especially on Python 3.0 to 3.2. It only works correctly against a :program:`Microsoft SQL Server`. :program:`SQLexpress` will do.

   The settings for how to reach your SQL server are in this file. Edit as needed.

:file:`adodbapitest.py`
   This tests the special features and extensions of adodbapi. It is much more complex than the :file:`dbapi20.py` test. You run this program, and it imports :file:`adodbapitestconfig.py`, which is where you put all of your setup information.

   The full operation runs up to 12 series of tests: four different database servers and three date-time formats, in all combinations. If the database servers are distant, this can take a while.

   It does some lightweight command line processing (actually the config does it).

      :code:`--package` tries to build a proper Python package in a temporary location and adds it to sys.path so it can import a test version of the code. It will run 2to3 when it does this, if needed.

      :code:`--all` run as many of the 12 passes as possible.

      :code:`--mysql` run the :program:`MySQL` tests.

      :code:`--postgres` run the :program:`PostgreSQL` tests.

      :code:`--time` run all time tests. (If :program:`mx-DateTime` is not installed it will be skipped.)

      :code:`--verbose=n` gives lots of information.

:file:`adodbapitestconfig.py`
   **E D I T . T H I S . F I L E !**

   You can run this script alone to test your settings quickly. Normally it is imported.

   This sets the configuration for its parent, creates a temporary work directory, reads the command line arguments, etc. You will edit this file—a lot! Many literals are set for my test environment. You must change them to yours.

:file:`runtests.bat`
   Convenient way to run the main and api tests using different Python versions.

:file:`setuptestframework.py`
   If run as a main program, initialize a not-really-temporary directory for the server to use for remote testing. (Otherwise, it is a subroutine for test setup.)