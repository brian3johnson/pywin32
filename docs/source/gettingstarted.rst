========================
Getting Started Tutorial
========================

.. contents::
   :depth: 1
   :local:

Install pywin32
===============

Install with :program:`pip`:

.. code-block:: console

   pip install pywin32

See :doc:`/installation` if you run into any snags during installation.

Client-side COM
===============

Interface with COM servers such as Microsoft Excel and Word.

.. todo:: 

   Add more explanation about Dispatch and seeing the Excel API docs.

.. literalinclude:: /_static/com_client.py
   :language: python
   :linenos:

And we will see the word "Hello" appear in the top cell.

Refer to :doc:`com/QuickStartClientCom` for more details.

Win32 API
=========

Work with the `Windows API`_ in python. Open an interactive python shell in the terminal.

.. code-block:: console

   ❯ python

Open an application such as Adobe Acrobat Reader.

.. code-block:: python

   >>> import win32api
   >>> win32api.WinExec("C:\Program Files (x86)\Adobe\Acrobat Reader DC\Reader\AcroRd32.exe")

Get the screen size in pixels.

.. todo:: 

   Add more explanation of the code snippets and referring to the Win32 docs for more details.

.. code-block:: python

   >>> import win32con
   >>> win32api.GetSystemMetrics(win32con.SM_CXSCREEN)
   2560

Get the domain name of the current computer.

.. code-block:: python

   >>> win32api.GetDomainName()
   '{DOMAIN_NAME}'

Get the computer name.

.. code-block:: python

   >>> win32api.GetComputerName()
   '{COMPUTER_NAME}'

Refer to :doc:`win32/index` for more details.

Pythonwin
=========

.. todo::

   Add a quick tutorial for the IDE and a Windows GUI.

Next Steps
==========

Explore the :doc:`Win32 <win32/samples/index>`, :doc:`PythonCOM <com/samples/index>`, and Pythonwin code samples, the API reference, and other :doc:`resources`.