|logo| Documents and Views in Pythonwin
=======================================

.. |logo|
   image:: pythonwin.gif
   :alt: Pythonwin logo

.. admonition:: Existing document
   
   :file:`\\Pythonwin\\doc\\docview.html`

.. contents::
   :depth: 1
   :local:

.. todo::
   see also samples index and add links inline below where referenced

   Replace code roles with link to apidocs.

   Replace file roles with links to file on github?

Introduction
------------

This document describes the document/view architecture of |Pythonwin|. It is assumed you have read the |Pythonwin| architecture documentation and are somewhat familiar with the standard MFC architecture.

Wherever possible, |Pythonwin| and the samples have followed the same architecture as MFC. This has advantages and disadvantages. Often the MFC architecture does not seem to fit with small, short GUI utilities, due to the reliance on "document" based applications. On the positive, |Pythonwin| can leverage off the full MFC functionality. This means minimal code to get full-blown application support.

Document and View - Control Flow
--------------------------------

.. warning::
   This needs lots more work. There where 2 flow-charts, which were semi-useless!

The creation of the frame and views are typically done via the :code:`PyCWnd.LoadFrame` method. During this call, the windows are created, and virtual functions pass control back to Python. The LoadFrame flow is shown in the separate diagram.

Object Oriented Documents
-------------------------

Sam Rushing once asked me "there needs to be a way to create 'object-oriented' documents, by that I mean a document with an object associated with it rather than a string. Currently the only way to open a document forces you to use a string (or :code:`None`)."

The most obvious path to take would seem to override :code:`OpenDocumentFile` or some such, and pass an object rather than a file name. The document could then load itself from the object, and all would be happy. Unfortunately, the tight integration with MFC means this can not work, and led to Sam's frustration above.

On the other hand, the :code:`OpenDocumentFile` method is provided for integration with a standard MDI interface, and the Windows explorer. Obviously, it is not possible to select "File/Open", and load an object based document.

However, I didn't have an easy answer for him.

MFC's OLE Implementation
~~~~~~~~~~~~~~~~~~~~~~~~

The closest example to the "right" way to do it seemed to be the MFC OLE implementation. When you have an object embedded in another document, and the user wants to edit the object, MFC must load the object without a simple "file name" parameter. MFC's approach is this:

* A normal blank document is created (via :code:`OnNewDocument`)
* COLEServerDoc's OLE :code:`XPersistStorage::Load()`` method is called, with an "object" (the OLE storage pointer)
* The Documents :code:`OnOpenEmbedding()` method is called.
   * :code:`OnOpenDocument` is called, with a :code:`NULL` file name parameter.
   * :code:`Serialize` is called.

Instead of changing the meaning of the existing functions, MFC adds new definitions for derived classes, such as :code:`OnOpenEmbedding`.

Back to our example
~~~~~~~~~~~~~~~~~~~

The cleanest thing seems to be to duplicate the functionality of :code:`OpenDocumentFile` - such as :code:`OpenObject`. You would do this by:

* Check to see if there is already a document representing the document open. If so, switch to it and :kbd:`return`.
* Create a new document object.
* Create a frame for the document
* Call :code:`OnNewDocument` to initialise the document.
* Set the document's title
* Call :code:`InitialUpdateFrame` for the initial display.

:file:`objdoc.py`
~~~~~~~~~~~~~~~~~

In the |Pythonwin| demos directory, there is a file :file:`objdoc.py`.

This module defines a template, which has an :code:`OpenObject` method, and takes any Python object as an argument. If window with the object is already open, it is switched to. If not, a edit window is created, and the object's :code:`__repr__` is written to the window.

Standard virtual function specification
---------------------------------------

.. note::
   I'm not sure where to stick this!

In general, the C++ virtual function handlers follow the same general logic. If no handler is defined, the base class is called. If a Python handler is defined, the base C++ class is not called. In the latter case, it is up to the Python programmer to ensure the base class is called if necessary. This is normally done by calling the method in the underlying :code:`_obj_`.