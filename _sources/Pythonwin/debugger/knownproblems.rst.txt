|logo| Pythonwin Debugger Known Problems
========================================

.. |logo|
   image:: ../pythonwin.gif
   :alt: Pythonwin logo

.. admonition:: Existing document
   
   :file:`\\Pythonwin\\doc\\debugger\\probs.html`

This document lists the currently known problems with the pywin.debugger package. 

You may also wish to view the debugger overview, the debugger tutorial, or the general debugger documentation. 

**Exiting the debugger on Windows 95 sometimes causes a crash.**

There is a problem with the "hierlist" control on Windows 95. I don't know what it is. 

**Closing the main debugger application while debugging may cause strange results.**

This is particularly true when debugging non-Pythonwin applications. I have made some efforts in this area, but it is pretty hard and complex. 

Closing the debugger dialog, selecting "End/Close" from one of the property pages, or "Close" from the debugging toolbar should always work as expected. 

**Debugging the bottom call-stack does not work as expected.**

If you are ever debugging a function that is the only function in the call-stack (ie you are at the bottom stack), then the functions "run" "step out" and "step over" may not work as expected - each of these operations may function as a single-step. 

You will need to single-step out of this entire function. 

**Output window does not show function arguments.**
 
This is a restriction in the core Python interpreter, caused by the introduction of keyword arguments. When Python supports it again, so will I.