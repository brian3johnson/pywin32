|logo|

.. |logo|
   image:: image/pycom_blowing.gif
   :alt: Python and COM, Blowing the rest away

==================
Python COM support
==================

.. admonition:: Existing document
   
   * :file:`\\com\\win32com\\html\\docindex.html`
   * :file:`\\com\\win32com\\html\\index.html`
   * :file:`\\com\\readme.html`

.. toctree::
   :maxdepth: 2
   :hidden:

   Client-side COM <QuickStartClientCom>
   Server-side COM <QuickStartServerCom>
   Generated COM <GeneratedSupport>
   VARIANT <variant>
   win32com <package>
   Python & COM <PythonCOM>
   Miscellany <misc>
   active_directory
   ADSI & Exchange <adsi>
   asp
   cpp
   mts
   win32com.shell <shell>
   directsound

   samples/index
   apidoc/index

.. contents::
   :depth: 1
   :local:

Python and COM
==============

Introduction
------------

Python has an excellent interface to COM (also known variously as OLE2, ActiveX, etc).

The Python COM package can be used to interface to almost any COM program (such as the MS-Office suite), write servers that can be hosted by any COM client (such as Visual Basic or C++), and has even been used to provide the core ActiveX Scripting Support.

* Note that win32com is now released in the win32all installation package. The <A HREF="../win32all/win32all.exe">installation EXE can be downloaded</A>, or you <A HREF="../win32all/">can jump to the win32all readme</A> for more details.
* Here is the <A HREF="win32com_src.zip">win32com source code</A> in a zip file.

Documentation
-------------

<A HREF="ActiveXScripting.html">Preliminary Active Scripting and Debugging documentation</A> is available.

2 Quick-Start guides have been provided, which also contain other links. See the <A HREF="QuickStartClientCom.html">Quick Start for Client side COM</A> and the <A HREF="QuickStartServerCom.html">Quick Start for Server side COM

Python COM Extensions Readme
============================

This is the readme for win32com. Please check out the win32com documentation index.

The :file:`win32com/test` directory contains some interesting scripts (and a new :file:`readme.txt`). Although these are used for testing, they do show a variety of COM techniques.

VARIANT objects
---------------

win32com.client now has explicit VARIANT objects which can be used in situations where you need more control over the argument types passed when calling COM methods. See the documentation on this object.

Important Currency changes
--------------------------

In all builds prior to 204, a COM currency value was returned as a tuple of integers. Working with 2 integers to represent a currency object was a poor choice, but the alternative was never clear. Now Python ships with the decimal module, the alternative has arrived!

Up until build 212, code could set :code:`pythoncom.__future_currency__ = True` to force use of the decimal module, with a warning issued otherwise. In builds 213 and later, the decimal module is unconditionally used when pythoncon returns you a currency value.

Recent Changes
--------------

Lots of internal changes on the road to py3k
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

win32com.axcontrol and win2con.internet
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Many more interfaces for hosting AX controls and the interfaces used by Internet Explorer.

win32com.shell
~~~~~~~~~~~~~~

The shell interfaces have undergone a number of enhancements and changes. A couple of methods have changed signature between the first build with shell support (200) and later builds. SHGetFileInfo was broken in its result handling, so had to be changed - this is the only function used by the samples that changed, but others not used by the samples also have changed. These shell interfaces are now generally stable.

New win32com.taskscheduler module
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Roger Upole has contributed an interface to the Windows task scheduler. This is actually very neat, and it allows Python to edit the task list as shown by Windows Control Panel. Property page suppport may even appear later, now that the win32 library has the new win32rcparser module.

ActiveX Scripting
~~~~~~~~~~~~~~~~~

Python only supports "trusted" execution hosts - thus, it will no longer work as an engine inside IE (Python itself no longer has a restricted execution environment). Python continues to work fine as an Active Scripting Engine in all other applications, including Windows Scripting Host, and ASP.

There is also support for Python as an ActiveX Scripting Host.

Active Debugging seems to be fully functional.

Older stuff
~~~~~~~~~~~

* Unexpected exceptions in Python COM objects will generally now dump the exception and traceback to stdout. This is useful for debugging and testing - it means that in some cases there will be no need to register an object with --debug to see these tracebacks.  Note that COM objects used by server processes (such as ASP) generally have no valid stdout, so will still need to use --debug as usual.
* universal gateway support has been improved - we can now work as an Outlook Addin.