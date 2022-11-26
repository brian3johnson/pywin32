|logo| Pythonwin Debugger Documentation
=======================================

.. |logo|
   image:: ../pythonwin.gif
   :alt: Pythonwin logo

.. admonition:: Existing document
   
   :file:`\\Pythonwin\\doc\\debugger\\general.html`

This documents the Win32 Debugger, and much of its functionality. 

You may also wish to view the debugger overview, the debugger tutorial, or the known problems with the debugger. 

.. contents:: This document contains the following topics 
   :depth: 1
   :local:
   
pywin.debugger package
----------------------

The debugger is a sub-package of |Pythonwin|, named pywin.debugger.

Debugger Interface
------------------

The debugger is based on the standard Python debugging modules. It is suggested you read the documentation on the "pdb" and "bdb" modules. This documentation can be located in the standard Python documentation: 

The package exports the following functions: 

GetDebugger() 

Returns a debugger object. If there is already a debugger, then this function returns it (re-creating its window, if necessary). If there is no current debugger, a debugger is created. 

The following functions operate almost identically to those described in the pdb documentation 

set_trace()
brk() # alternative name 

Like a hard-coded break-point, this function creates a debugger if necessary, and stops at the following statement. Note - putting this statement as the last line of a function may cause you to stop at an unexpected place! 

post_mortem(traceback, exception_type = None, exception_value = None) 

Perform post-mortem debugging of the passed traceback. This is useful for analysing the conditions that lead up to an exception. 

run(cmd, globals=None, locals=None) 

Begin debugging the command, in the globals and locals context. 

runeval(expression, globals=None, locals=None) 

Like "run" but treats the string as an expression to be evaluated. 

GUI versus Non-GUI Issues
-------------------------

The |Pythonwin| debugger behaves differently depending on if the application being debugged is |Pythonwin| or not. If the host Python application is |Pythonwin|, then the debugger runs in "GUI" mode - otherwise in "non-GUI" mode. 

If the application is not |Pythonwin|, then the debugger has far less control over the debugging environment. There are 2 main areas where this is most apparent. 

Will we return? 
^^^^^^^^^^^^^^^

In a non-GUI application, each time we leave the debugger (eg, to step through a line of code), we may never re-appear. We may be debugging the last statement of the program, or just may never hit another breakpoint until termination. 

Therefore, the debugger will always prompt for file saves whenever stepping into code. Although the file will be saved, the changes will probably not take affect until the program is restarted. 

Are there any messages for me? 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

When debugging non-GUI applications, there may not be a message loop. As the debugger is a GUI application, it needs a message loop to respond to user interaction, etc. 

There is an option for the debugger to "hide in non-GUI applications", which by default is enabled. This means that each time a statement is executed, the entire debugger environment is hidden! In fact, it may never re-appear (see above). 

If you disable this option, then debugging these applications will be smoother, but the side-effects will depend on your host application. 

If debugging a Python.exe program (or any other console program), the debugger will not be hidden, but will not respond at all to any user input while the host program is executing. In fact, the debugger will appear to have totally hung. The debugger has not hung - it just can not process messages. It will either spring back into life when a breakpoint etc. it hit, or vanish when the host application exits. 

If debugging inside another GUI application (such as Excel, or MS Internet Explorer), then there is a reasonable chance that the debugger will continue to operate totally normally while the host is running (ie, just as it does under |Pythonwin|) 

Let me out of here 
^^^^^^^^^^^^^^^^^^

The other potential area where things may get strange is shutting down the main application frame while debugging. In general, this should shut down normally, but sometimes may not! 

How It Works
------------

For those who care, the debugger uses the standard Python debugger hooks. Whenever interaction with the user is required, the debugger creates a new message loop, right under the code being debugged. 

While this message loop is processing messages, the code is broken, and the user can interact with the debugger. Whenever the debugger is about to return control to Python itself, it breaks out of the message loop, leaving the code to execute as it was.