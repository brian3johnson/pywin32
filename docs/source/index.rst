=============================
Python for Windows Extensions
=============================

.. toctree::
   :maxdepth: 2
   :hidden:
   :titlesonly:

   installation
   gettingstarted
   win32/index
   com/index
   adodbapi/index
   isapi/index
   Pythonwin/index
   SWIG/index
   support
   resources

**Python for Windows Extensions** (|pywin32|) enables developers to work with most of Microsoft's `Windows API`_ and `Component Object Model (COM)`_ interfaces in Python.

Win32 Extensions
================

The :doc:`win32/index` package provides access to the `Windows API`_, including modules for obdc, win32evtlog, win32file, and many others. 

PythonCOM
=========

Use the :doc:`com/index` package to interface with `Component Object Model (COM)`_ programs, such as Microsoft Excel. Write servers that can be hosted by any |com| client, such as Visual Basic or C++. It has even been used to provide the core ActiveX Scripting support.

|adodbapi|
==========

The Python DB-API 2.0-compliant (:pep:`249`) module, :doc:`adodbapi/index`, makes it easy to use `Microsoft ActiveX Data Objects (ADO)`_ for connecting with databases and other data sources using either `CPython <https://www.python.org/>`_ or `IronPython <https://ironpython.net/>`_.

ISAPI
=====

Host Microsoft Internet Server Application Programming Interface (|isapi|) `extensions <isapi_extensions_>`_ and `filters <isapi_filters_>`_ inside `Microsoft Internet Information Services (IIS)`_ with the :doc:`isapi/index` module.

Pythonwin
=========

:doc:`Pythonwin/index` is a Windows-only IDE and GUI framework for Python. It has an integrated debugger and a rich Python editing environment. |pywin32| installs :doc:`Pythonwin/index` in addition to the other packages.

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
