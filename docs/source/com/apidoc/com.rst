===========
com package
===========

.. contents::
   :depth: 1
   :local:

win32com.client
===============

.. py:module:: win32com.client
   :platform: Windows
   :synopsis: This module exists to create the "best" dispatch object for a given object.

   This module exists to create the "best" dispatch object for a given object. If "makepy" support for a given object is detected, it is used, otherwise a dynamic dispatch object.
   
   Note that if the unknown dispatch object then returns a known dispatch object, the known class will be used. This contrasts with dynamic.Dispatch behaviour, where dynamic objects are always used.

.. py:function:: win32com.client.Dispatch(dispatch, userName=None, resultCLSID=None, typeinfo=None, UnicodeToString=None, clsctx=pythoncom.CLSCTX_SERVER)

   :param str dispatch: A dispatch object
   :param userName: User name
   :type userName: str, optional
   :param resultCLSID: Class ID
   :type resultCLSID: str, optional
   :param typeinfo: Type information param
   :type typeinfo: str, optional
   :param UnicodeToString:

      .. deprecated:: 305
         Use None or leave blank.

   :type UnicodeToString: bool, optional
   :param clsctx: Execution contexts in which a class object is to be run, defaults to ``pythoncom.CLSCTX_SERVER``
   :type clsctx: int
   :return: :func:`__WrapDispatch`
   :rtype: Callable

   Creates a Dispatch-based COM object.

   >>> import win32com.client
   >>> xl_app = win32com.client.Dispatch("Excel.Application")

   win32com.client.__WrapDispatch is a helper function that returns a `makepy`-generated class for a CLSID if it exists, otherwise cope by using CDispatch.

   .. seealso::

      `CLSCTX enumeration (wtypesbase.h)`__
      
   .. __: https://learn.microsoft.com/en-us/windows/win32/api/wtypesbase/ne-wtypesbase-clsctx

win32com.client.build
=====================

win32com.clientCLSIDToClass
===========================

win32com.client.combrowse
=========================

win32com.client.connect
=======================

win32com.client.dynamic
=======================

.. py:module:: win32com.client.dynamic
   :platform: Windows
   :synopsis: Support for dynamic COM client support.

   Dynamic COM client support is the ability to use a COM server without prior knowledge of the server. This can be used to talk to almost all COM servers, including much of Microsoft Office.

   In general, you should **not** use this module directly.

   Example::

      >>> import win32com.client
      >>> xl_app = win32com.client.Dispatch("Excel.Application")
      >>> xl_app.Visible = 1 # The Excel window becomes visible.
   
   The line above invokes the functionality of this class. Now we can use :code:`xl_app` to talk to :program:`Excel`.

.. py:function:: win32com.client.Dispatch(dispatch, \
      userName=None, \
      createClass=None, \
      typeinfo=None, \
      UnicodeToString=None, \
      clsctx=pythoncom.CLSCTX_SERVER)

   :param str dispatch: A dispatch object
   :param userName: User name
   :type userName: str, optional
   :param createClass: Class ID?
   :type resultCLSID: str, optional
   :param typeinfo: Type information param
   :type typeinfo: str, optional
   :param UnicodeToString:

      .. deprecated:: 305
         Use None or leave blank.

   :type UnicodeToString: bool, optional
   :param clsctx: Class context, defaults to ``pythoncom.CLSCTX_SERVER``
   :type clsctx: int
   :return: :func:`createClass`
   :rtype: Callable

   Creates a dynamic Dispatch-based COM object.

   .. seealso::

      `CLSCTX enumeration (wtypesbase.h)`__
      
   .. __: https://learn.microsoft.com/en-us/windows/win32/api/wtypesbase/ne-wtypesbase-clsctx

win32com.client.gencache
========================