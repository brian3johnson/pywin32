|logo| Pythonwin's architecture
===============================

.. |logo|
   image:: pythonwin.gif
   :alt: Pythonwin logo

.. admonition:: Existing document
   
   :file:`\\Pythonwin\\doc\\architecture.html`

.. contents::
   :depth: 1
   :local:

.. todo::
   Replace code roles with link to apidocs.

   Replace file roles with links to file on github?

Introduction
------------
This document describes the general architecture of |Pythonwin|. It describes the general design and interface to MFC.

After reading this, you should read the :doc:`document and view architecture documentation <docview>`.

Objects, types, etc.
--------------------
For each MFC object created, there are usually 3 "objects" floating around. Although this may initially seem confusing, it does provide significant flexibility.

In general this complexity is hidden from view. The programmer usually only ever deals with a single object, and this object manages all others. However, an understanding if the implementation will assist in advanced programming techniques.

There is a quick example which shows all this in action.

C++ objects
~~~~~~~~~~~
For every window, toolbar, document etc. that exists in |Pythonwin|, there is a C++ object. In some cases this object may be a standard MFC object, as found in the MFC DLL's. In other cases, the C++ object will be derived from a standard MFC object, and can be found in :file:`win32ui.pyd`.

Often, these C++ objects will not be aware that there is Python support behind them.

win32ui types
~~~~~~~~~~~~~
The win32ui module provides a large number of types, each one usually associated with an MFC C++ object. The naming conventions for these objects is of the form :samp:`Py{MFC_Name}` - e.g., :code:`PyCDocument` provides the functionality of an MFC :code:`CDocument`, :code:`PyCDialog` for a :code:`CDialog`.

There is a form of inheritance used for these objects. Each object provides methods from its derived class. A :code:`PyCDialog` is derived from a :code:`PyCWnd`, and therefore has all :code:`PyCWnd`` methods available. However, this is as far as the inheritance extends, as Python types are more restrictive than Python classes.

Each method that a win32ui type provides is generally just code for extracting Python arguments and making the call to the associated C++ object.

These objects and methods are defined in :file:`Pythonwin.hlp` (available from the |Pythonwin| help menu.)

"Object" base class
~~~~~~~~~~~~~~~~~~~
In :file:`object.py`, there is a base class :code:`Object`. This provides 2 key functions.

.. todo::
   Link to python documentation for __getattr__?

Its constructor (:code:`__init__` method) registers the class with a win32ui type object (see below). This allows all virtual methods (see below) to be handled by a class method.
It allows itself to look exactly like the underlying win32ui type. It does this by storing the win32ui object in :code:`self._obj_`, and providing a :code:`__getattr__` method. See the standard Python documentation for information on :code:`__getattr__` in a Python class.
The end result of this is that a class derived from :code:`Object`` looks just like a win32ui object, and can be used as such. In fact, there is rarely a reason to use the underlying object directly.

Python Classes
~~~~~~~~~~~~~~
If you like you can skip this, and jump straight to the example below. It makes more sense in action!

.. todo::
   Use the dfn role for virtual function?

|Pythonwin| provides support for many "virtual" functions. A "virtual" function is defined as *a virtual C++ MFC function which has deferred its implementation to a Python object*. To explain, I will use the example of a document.

In Python, it is possible to create a :code:`PyCDialog` object by using :code:`win32ui.CreateDialog()`. This will create both a :code:`PyCDialog` object, and a C++ :code:`CDialog` object. For dialogs to be useful to a programmer, it must be possible to define a method to be called when the dialog initialises (i.e., when the C++ :code:`OnInitDialog` virtual method is called). Normally, a programmer would initialise the values of controls etc. at this time. To support this, the C++ :code:`OnInitDialog` implementation calls Python to handle the call. In this example, :code:`OnInitDialog` is a "virtual" function.

Each win32ui type supports being "attached" to a Python class instance. When a virtual function is called, the Python class instance associated with the object is checked to see if it has a method with the same name. If so, the method is called.

More details on this can be found in the :doc:`document and view architecture documentation <docview>`.

Example of this in action
~~~~~~~~~~~~~~~~~~~~~~~~~

>>> import win32ui # import the base win32ui module.
>>> import dialog # import dialog.py
>>> d=dialog.Dialog(win32ui.IDD_SIMPLE_INPUT)
>>> d
<Dialog instance at 886c78>

This creates an instance of class :code:`Dialog`, defined in :file:`dialog.py`. :code:`Dialog` is derived from :code:`Object` (via :code:`Wnd`). To see the underlying win32ui type:

>>> d._obj_
object 'PyCDialog' - assoc is 002F3278, vf=True, ch=0, mh=2, kh=0

This output shows the C++ :code:`CDialog` object is at address :samp:`0x002F3278`, that there is a virtual function handler (i.e., the class instance :code:`d`), that 2 messages have hooks, and no command or keyboard handlers are installed.

Even though the :code:`DoModal()` method is implemented in the underlying win32ui type, the class object can be used just like the win32ui object. Thus:

>>> d.DoModal()
1

To see virtual functions in action:

>>> class MyDialog(dialog.Dialog):
...     def OnInitDialog(self, msg):
...         self.GetDlgItem(win32ui.IDC_PROMPT1).SetWindowText("Hello")
...         return 1
...
>>> d=MyDialog(win32ui.IDD_SIMPLE_INPUT)
>>> d.DoModal()
1

Note the prompt on the dialog box is now "Hello".