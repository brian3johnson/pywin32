====================================
Windows NT Security -- Impersonation
====================================

.. admonition:: Existing document
   
   :file:`\\win32\\help\\security.d`

.. contents::
   :depth: 1
   :local:

Python's win32 access to help to simplify providing privileged access.

There may be times when you want to give specific access to someone with NT. One mechanism to do this is with the win32 calls: LogonUser and ImpersonateLoggedOnUser. LogonUser gives you a handel which ImpersonateLoggedOnUser can then use to "become" the user. To do this the thread calling, LogonUser, needs SE_TCB_NAME, SE_CHANGE_NOTIFY_NAME, and SE_ASSIGNPRIMARYTOKEN_NAME privileges. If you plan to do this with something like IIS and cgi, be careful, the anonymous account IIS uses is already impersonated from the system account. You will need to use the RevertToSelf, api call to first terminate the impersonation. And, the system account, a local account, ultimately limits you, regardless of who you log in as (COM/MTS can provide an alternative security solution).

Example
=======

The c++ api call for Logonasuser looks like:

.. code-block:: cpp

   BOOL LogonUser(
      LPTSTR lpszUsername,    
      LPTSTR lpszDomain,      
      LPTSTR lpszPassword,    
      DWORD dwLogonType,      
      DWORD dwLogonProvider,  
      PHANDLE phToken         
   );

The python documentation says this:

.. code-block:: python

   PyHANDLE = LogonUser( userName, domain , password , logonType , logonProvider )

The api call is very similar in both cases except in python the handel is returned seperately to the caller. The interesting options in this case are logonType and logonProvider. To give values for these, you need to use the constants present in win32con (you can use the browser in pythonwin->tools to list the constants in win32con). Unless you have unusual server requirements, for logonType, win32con.LOGON32_LOGON_INTERACTIVE should be fine. With regards to logonProvider, generally use win32con.LOGON32_PROVIDER_DEFAULT - it's for specifiying the type of logon NT 3.5, 4.0, win2000. Generally, default is fine.

ImpersonateLoggedOnUser is extremely simple and you'll see it's usage in the examples.

Now for some code

.. code-block:: python

   #A raw example looks like this:
   handel=win32security.LogonUser('barney','bedrock','bambam'\
      ,win32con.LOGON32_LOGON_INTERACTIVE,win32con.LOGON32_PROVIDER_DEFAULT)
   win32security.ImpersonateLoggedOnUser(handel)

   #do stuff here
   print win32api.GetUserName() #show you're someone else

   win32security.RevertToSelf() #terminates impersonation
   handel.Close()

   #The impersonate code can be encapsulated in a class, which then makes it even more
   #trivial to use

   import win32security
   import win32con
   import win32api

   class Impersonate:
      def __init__(self,login,password):
         self.domain='bedrock'
         self.login=login
         self.password=password
      def logon(self):
         self.handel=win32security.LogonUser(self.login,self.domain,self.password,\
         win32con.LOGON32_LOGON_INTERACTIVE,win32con.LOGON32_PROVIDER_DEFAULT)
         win32security.ImpersonateLoggedOnUser(self.handel)
      def logoff(self):
         win32security.RevertToSelf() #terminates impersonation
         self.handel.Close() #guarantees cleanup


   a=Impersonate('barney','bambam')

   try:
      a.logon() #become the user
      #do whatever here
      print win32api.GetUserName() #show you're someone else
      a.logoff() #return to normal
   except:
      print sys.exc_type , sys.exc_value

Have a great time with programming with python!

John Nielsen   nielsenjf@my-deja.com