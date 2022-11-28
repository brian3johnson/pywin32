|logo|

.. |logo|
   image:: image/pycom_blowing.gif
   :alt: Python and COM, Blowing the rest away

Misc stuff I don’t know where to put anywhere else
==================================================

.. admonition:: Existing document
   
   :file:`\\com\\win32com\\html\\misc.html`

.. contents::
   :depth: 1
   :local:


Client Side Dispatch
--------------------

Using win32com.client.Dispatch automatically invokes all the win32com client side "smarts", including automatic usage of generated .py files etc.

If you wish to avoid that, and use truly "dynamic" objects (ie, there is generated .py support available, but you wish to avoid it), you can use win32com.client.dynamic.Dispatch

_print_details_() method
------------------------

If win32com.client.dynamic.Dispatch is used, the objects have a _print_details_() method available, which prints all relevant knowledge about an object (for example, all methods and properties). For objects that do not expose runtime type information, _print_details_ may not list anything.