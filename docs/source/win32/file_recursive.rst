Recursive directory deletes and special files
=============================================

.. admonition:: Existing document
   
   :file:`\\win32\\help\\file.d` Part 2

.. contents::
   :depth: 1
   :local:

Python's win32 access for file properties to enable deletes

Sometimes you may want to do something like remove entire directory trees. Python has some great utilities to do that, except files with special attributes cannot be typically deleted.

To get around this problem you need to use the win32 call to SetFileAttributes to be a normal file.

The C++ call looks like this:

.. code-block:: cpp

   BOOL SetFileAttributes(  
      LPCTSTR lpFileName,     
      DWORD dwFileAttributes   
   ); 

You provide it 2 arguments the filename and the specific attributes and it returns whether or not it succeeded.

The corresponding python call is:

.. code-block:: python

   int = win32api.SetFileAttributes( pathName, attrs )

The only question is where do you get attrs. It is included in the ever handy win32con module specifically - win32con.FILE_ATTRIBUTE_*. You can set a file to be read only, archive, hidden, etc. We are concerned with setting it back to normal, so we want: win32con.FILE_ATTRIBUTE_NORMAL

The example below can be useful, but, of course, be careful with it, since it deletes a lot of stuff. It is a recursive function  The example also makes use of some handy functions from the os module.

Example
-------

Here is a basic example of how to remove a directory tree:

.. code-block:: python

   import win32con
   import win32api
   import os

   def del_dir(self,path):
      for file in os.listdir(path):
         file_or_dir = os.path.join(path,file)
         if os.path.isdir(file_or_dir) and not os.path.islink(file_or_dir):
            del_dir(file_or_dir) #it's a directory reucursive call to function again
         else:
            try:
               os.remove(file_or_dir) #it's a file, delete it
            except:
               #probably failed because it is not a normal file
               win32api.SetFileAttributes(file_or_dir, win32con.FILE_ATTRIBUTE_NORMAL)
               os.remove(file_or_dir) #it's a file, delete it
         os.rmdir(path) #delete the directory here

Have a great time with programming with python!

John Nielsen   nielsenjf@my-deja.com