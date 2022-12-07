|logo|

.. |logo|
   image:: image/pycom_blowing.gif
   :alt: Python and COM, Blowing the rest away

=========================================
Quick Start to Client side COM and Python
=========================================

.. admonition:: Existing document
   
   :file:`\\com\\win32com\\html\\QuickStartClientCom.html`

.. contents::
   :depth: 2
   :local:

Introduction
============

This documents how to quickly start using |com| from Python. It is not a thorough discussion of the |com| system, or of the concepts introduced by |com|.

Other good information on |com| can be found in various conference tutorials. Please see the collection of `Mark's conference tutorials <http://starship.python.net/crew/mhammond/conferences>`_ 💀🔗.

For information on implementing |com| objects using Python, please see a :doc:`QuickStartServerCom`.

Quick Start
===========

To use a COM object from Python
-------------------------------

.. code-blocK:: python

   import win32com.client
   o = win32com.client.Dispatch("Object.Name")
   o.Method()
   o.property = "New Value"
   print o.property

Example:

.. code-blocK:: python
   
   o = win32com.client.Dispatch("Excel.Application")
   o.Visible = 1
   o.Workbooks.Add() # for office 97 – 95 a bit different!
   o.Cells(1,1).Value = "Hello"

And we will see the word "Hello" appear in the top cell.

How do I know which methods and properties are available?
---------------------------------------------------------

Good question. This is hard! You need to use the documentation with the products, or possibly a |com| browser. Note however that |com| browsers typically rely on these objects registering themselves in certain ways, and many objects to not do this. You are just expected to know.

The Python COM browser
----------------------

PythonCOM comes with a basic |com| browser that may show you the information you need. Note that this package requires :doc:`/Pythonwin/index` (i.e., the MFC GUI environment) to be installed for this to work.

There are far better |com| browsers available. I tend to use the one that comes with MSVC, or this one!

To run the browser, simply select it from the :program:`Pythonwin` :menuselection:`Tools` menu, or :kbd:`double-click` on the file :file:`win32com\client\combrowse.py`

Static Dispatch (or Type Safe) objects
======================================

In the above examples, if we printed the :code:`repr(o)` object above, it would have resulted in:

.. code-block:: python

   <COMObject Excel.Application>

This reflects that the object is a generic |com| object that Python has no special knowledge of (other than the name you used to create it!). This is known as a *dynamic dispatch* object, as all knowledge is built dynamically. The :code:`win32com` package also has the concept of *static dispatch* objects, which gives Python up-front knowledge about the objects that it is working with (including arguments, argument types, etc.).

In a nutshell, Static Dispatch involves the generation of a :file:`.py` file that contains support for the specific object. For more overview information, please see the documentation references above.

The generation and management of the :file:`.py` files is somewhat automatic, and involves one of two steps:

* Using :file:`makepy.py` to select a |com| library. This process is very similar to :program:`Visual Basic`, where you select from a list of all objects installed on your system, and once selected the objects are magically useable.

or

* Use explicit code to check for, and possibly generate, support at run-time. This is very powerful, as it allows the developer to avoid ensuring the user has selected the appropriate type library. This option is extremely powerful for OCX users, as it allows Python code to sub-class an OCX control, but the actual sub-class can be generated at run-time. Use :file:`makepy.py` with a ``-i`` option to see how to include this support in your Python code.

.. todo::

   Add an option directive for and option role to the -i command line option above.

The :code:`win32com.client.gencache` module manages these generated files. This module has some :doc:`documentation <GeneratedSupport>` of its own, but you probably don't need to know the gory details!

How do I get at the generated module?
-------------------------------------

You will notice that the generated file name is long and cryptic - obviously not designed for humans to work with! So how do you get at the module object for the generated code?

Hopefully, the answer is *you shouldn't need to*. All generated file support is generally available directly via :code:`win32com.client.Dispatch` and :code:`win32com.client.constants`. But should you ever really need the Python module object, the :code:`win32com.client.gencache` module has functions specifically for this. The functions :code:`GetModuleForCLSID` and :code:`GetModuleForProgID` both return Python module objects that you can use in your code. See the docstrings in the gencache code for more details.

To generate Python Sources supporting a COM object
--------------------------------------------------

Example using Microsoft Office 97
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Either:

* Run :file:`win32com\client\makepy.py` (e.g., run it from the command window, or double-click on it) and a list will be presented. Select the Type Library ':file:`Microsoft Word 8.0 Object Library`'
* From a command prompt, run the command :program:`makepy.py "Microsoft Word 8.0 Object Library"` (include the double quotes). This simply avoids the selection process.
* If you desire, you can also use explicit code to generate it just before you need to use it at runtime. Run :program:`makepy.py -i "Microsoft Word 8.0 Object Library"` (include the double quotes) to see how to do this.

And that is it! Nothing more needed. No special import statements needed! Now, you simply need say:

.. code-block:: python
   
   >>> import win32com.client
   >>> w=win32com.client.Dispatch("Word.Application")
   >>> w.Visible=1
   >>> w
   <win32com.gen_py.Microsoft Word 8.0 Object Library._Application>

Note that now Python knows the explicit type of the object.

Using COM Constants
-------------------

Makepy automatically installs all generated constants from a type library in an object called :code:`win32com.clients.constants`. You do not need to do anything special to make these constants work, other than create the object itself (i.e., in the example above, the constants relating to :program:`Word` would automatically be available after the :code:`w=win32com.client.Dispatch("Word.Application")` statement).

For example, immediately after executing the code above, you could execute the following:

.. code-block:: python

   >>> w.WindowState = win32com.client.constants.wdWindowStateMinimize

and :program:`Word` will Minimize.