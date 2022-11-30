|logo|

.. |logo|
   image:: image/pycom_blowing.gif
   :alt: Python and COM, Blowing the rest away

==========================
ADSI, Exchange, and Python
==========================

.. admonition:: Existing document
   
   :file:`\\com\\help\\adsi.html`

.. contents::
   :depth: 1
   :local:

.. sectionauthor:: John Nielsen <jn@who.net>

Python's adsi access works really well with Exchange (late or early binding since you can read microsoft's type library). To get started, you will need to download adsi from microsoft: `Microsoft ADSI`_. Microsoft has documentation for using languages other than python in the sdk.

Introduction
============

Before doing anything else you need to go through the next two steps:

TABLE FORMATTING

Acquiring ADSI object

Task Description

Create Global Providers Object adsi = win32com.client.Dispatch('ADsNameSpaces')

Create LDAP Provider Object ldap = adsi.getobject("","LDAP:")

Now you have to decide how you want to access the exchange server. I have chosen to authenticate, in which case you need to use OpenDSObject().

TABLE FORMATTING

Method of access

Task Description

Specify Login and Domain logon_ex='cn=wilma, dc=bedrock'

Specify password password='dino'

Login to Server myDSObject = ldap.OpenDSObject(ex_path,logon_ex,password,0)

Note - the fourth argument to opendsobject has various options for how to authenticate. For example, if you use 1 instead of zero, it should either use NTLM or Kerberos for authentication. For more information, check out: `OpenDSObject <http://www.microsoft.com/windows/server/Technical/directory/adsilinks.asp>`_

The ex_path in the above example specifies the resource you are trying to access. For example:

TABLE FORMATTING

Types of paths

Task Description

Specific User ex_path="LDAP://server/cn=fredflintsone,cn=Recipients,ou=rubble,o=bedrock"

Mailing List ex_path="LDAP://server/cn=bedrock,cn=Recipients,ou=rubble,o=bedrock"

All Recipients ex_path="LDAP://server/cn=Recipients,ou=rubble,o=bedrock"

User Account Management
=======================

Adding a user to exchange
-------------------------

# Adding a new account to exchange is simple except for one thing. # You need to associate an NT account with an exchange account. # To do so at this point requires some c++ to produce some hex SID # and trustee information that adsi can use. # At this point assume we have C++ magic # # Note we are accessing Recipients directly now ex_path="LDAP://server/cn=Recipients,ou=rubble,o=bedrock" logon_ex='cn=wilma,dc=bedrock' password='dino' myDSObject = ldap.OpenDSObject(ex_path,logon_ex,password,0) newobj = myDSObject.create("OrganizationalPerson", "cn=betty") newobj.put('MailPreferenceOption', 0) # etc . . . add whatever else you want. There are a few required fields. # Now the part to get exchange associated with NT # The Magic is here import win32pipe assoc_nt=win32pipe.popen('getsid bedrock\\fredflint') nt_security=win32pipe.popen('gettrustee bedrock\\fredflint') newobj.put('NT-Security-Descriptor',assoc_nt) newobj.put('NT-Security-Descriptor',nt_security) newobj.SetInfo

Getting/Modify user info
------------------------

ex_path="LDAP://server/cn=fredflint,cn=Recipients,ou=rubble,o=bedrock" myDSObject = ldap.OpenDSObject(ex_path,logon_ex,password,0) myDSObject.Getinfo() # To access a user's data try: attribute = myDSObject.Get('Extension-Attribute-1') print attribute # To modify a user try: myDSObject.Put('Extension-Attribute-1','barney was here') myDSObject.Setinfo()

Comments Note -- To make any changes permanent setinfo is required.

Deleting a user from exchange
-----------------------------

#Here we connect to Recipients and then #delete a user #This is a more complete example. #data is a dictionary that contains info #that may be dynamic like the domain, #admin login, or exchange server #notice I am using a try/except clause here #to catch any exceptions try: #ADSI here # Create the Global Providers object logon_ex='cn='+data['NT_admin']+', dc='+data['NT_domain']+',cn=admin' ex_list_path="LDAP://"+data['EX_site_srv']+"/cn=Recipients,ou="\ +data['ou']+",o="+data['o'] adsi = win32com.client.Dispatch('ADsNameSpaces') # # Now get the LDAP Provider object ldap = adsi.getobject("","LDAP:") dsobj = ldap.OpenDSObject(ex_list_path,logon_ex,data['NT_password'],0); dsobj.Getinfo() dsobj.Delete("OrganizationalPerson", "cn="+login) dsobj.Setinfo() except: print 'Error deleting '+login, sys.exc_type , sys.exc_value

Distribution List
=================

Adding to a distribution list
-----------------------------

# I used putex instead of put because it has more options
# The '3' value means append. The SDK has specific info on it
ex_list_path="LDAP://"+server+"/cn="+list+",cn=Recipients,ou="+ou+",o="+o
dsobj = ldap.OpenDSObject(ex_list_path,logon_ex,password,0);
dsobj.Getinfo()
list_member='cn='+user+',cn=Recipients,ou='+ou+',o='+o
append_list=[list_member]
dsobj.putEx(3,'Member',append_list);
dsobj.SetInfo()

Recursively listing all unique members of a distribution list
-------------------------------------------------------------

.. code-block:: python

   #This function looks for all Organizational persons to add to a dictionary
   #If it gets a groupOfNames, it needs to parse that and call the function again
   #to get the members of the groupOfNames
   def getmembers(path=''):
   user_dict={}
   logon_ex='cn=fred, dc=bedrock'
   password='dino'
   server='flintstone'
   ldap = win32com.client.Dispatch('ADsNameSpaces').getobject("","LDAP:")
   dsobj = ldap.OpenDSObject(path,logon_ex,password,0)
   dsobj.Getinfo()
   if dsobj.Class=='organizationalPerson':
         user_dict[string.capitalize(dsobj.cn)]=dsobj.uid
   elif dsobj.Class=='groupOfNames':
         for i in dsobj.Members():
               if i.Class=='organizationalPerson':
                     user_dict[string.capitalize(i.cn)]=i.uid
               elif type(i.member)==types.TupleType:
                     for j in i.member:
                        newpath='LDAP://'+server+'/'+j
                        getmembers(newpath)
               elif type(i.member)==types.StringType:
                     newpath='LDAP://'+server+'/'+i.member
                     getmembers(newpath)
   elif dsobj.Class=='Remote-Address':
         User_dict[string.capitalize(dsobj.cn)]=dsobj.uid
   elif  dsobj.Class=='Public-Folder':
         pass
   else:
         print 'skipped',dsobj.Class,dsobj.uid
   return user_dict

In Conclusion
=============

Microsoft's ADSI allows one to manage exchange w/out having to resort to the lower-level APIs. Python has no trouble accessing Microsoft's ADSI to help simplify user management.

*Have a great time with programming with python!*

Further Info
============

`Microsoft MSDN references <http://msdn.microsoft.com/>`_

`Microsoft ADSI`_

`Microsoft MSDN ADSI reference <http://msdn.microsoft.com/library/default.asp?URL=/library/psdk/adsi/if_core_3uic.htm>`_

Relevant Python libraries: :code:`win32com.client`

.. _Microsoft ADSI: https://www.microsoft.com/windows/server/Technical/directory/adsilinks.asp