====================================
Windows Network Management: win32net
====================================

.. admonition:: Existing document
   
   :file:`\\win32\\help\\win32net.html`

.. contents::
   :depth: 1
   :local:

.. sectionauthor:: John Nielsen <jn@who.net>

Python's win32 access to Network Management functions are very clean and simple. It exposes to python what normally is available to C++. There are several examples of this:

* NetWkstaUserEnum/NetUserEnum -- Enumerate users on a machine or in a domain
* NetUserGetInfo/NetUserSetInfo -- manage user attributes
* NetShareAdd -- manage shares
* NetServerEnum/NetGetDCName -- list available servers/get Domain Controller info

Introduction
============

The python api for the win32net module closely mirrors the C++ functions documented in the msdn. This makes it convenient to look at the Microsoft MSDN http://msdn.microsoft.com/ for further information if necessary. There is a sister module to win32net called win32netcon that houses all of the constants needed by the win32net modules.

Because of unicode support in python2.0, some of the string handling done w/the examples are no longer necessary. Before one needed to convert PyUnicode to a regular python string, before you could use string functions with it. The examples will work w/both versions of python, the string conversions are not necessary in 2.0.

In the calls which require a server, you need a string that looks like \\servername, a simple way to create that is to use raw strings like: r'\\rubble'.

And finally, python's exception handling makes it convenient to catch win32net errors. I use the following format: try: #win32net calls except win32net.error: print traceback.format_tb(sys.exc_info()[2]),'\n',sys.exc_type,'\n',sys.exc_value The traceback and sys modules are used to extract the error information.

Managing Servers/Workstations
=============================

Listing Logins on a workstation
-------------------------------

If you want to get the logins currently present on a workstation you need to use NetWkstaUserEnum api call. In c++ the call looks like this:

.. code-block:: cpp
   :linenos:

    NET_API_STATUS NetWkstaUserEnum(
      LPWSTR servername,    
      DWORD level,          
      LPBYTE *bufptr,       
      DWORD prefmaxlen,     
      LPDWORD entriesread,  
      LPDWORD totalentries, 
      LPDWORD resumehandle  
    );

The python documentation says this:

.. code-block:: python
   :linenos:

   ([dict, ...], total, resumeHandle) = NetWkstaUserEnum( server, level , resumeHandle , prefLen )

Notice that the api call is split in 2 pieces with python, instead of being all combined in one call. So, how do they relate to each other. In c++, you check the NET_API_STATUS to determine the result of the call and if you have more data. You also have to extract from structures like LPWKSTA_USER_INFO_0 to get the user data keeping track of entriesread and the totalentries. Rather tedious. Thankfully, this is easy in python. With python a list containing a user dictionary is returned which trivial to parse and if resumeHandel is true you make the win32 call again.

Now for some code:

.. code-block:: python
   :linenos:

   def getusers(server):
       res=1 #initially set it to true
       pref=win32netcon.MAX_PREFERRED_LENGTH level=0 #setting it to 1 will provide more detailed info
       total_list=[]
       try:
         while res: #loop until res2 (user_list,total,res2)=win32net.NetWkstaUserEnum(server,level,res,pref)
            for i in user_list:
               total_list.append(i['username'])
               res=res2
               return total_list
      except win32net.error:
         print traceback.format_tb(sys.exc_info()[2]),'\n',sys.exc_type,'\n',sys.exc_value print getusers(r'\\betty')

Listing all user accounts
-------------------------

Sometimes it can be handy to get a list of everyone in your domain. Python exposes NetUserEnum which returns among other things a list of dictionary of users. There are various different accounts you can look for. In this case, we use the constant in win32netcon to look for 'normal' accounts. Another win32net function, NetUserGetInfo described later gets the full_name for the login. def getall_users(server): 'This functions returns a list of id and full_names on an NT server' j=1 res=1 users=[] user_list=[] try: while res: (users,total,res) = win32net.NetUserEnum(server,3,win32netcon.FILTER_NORMAL_ACCOUNT,res,win32netcon.MAX_PREFERRED_LENGTH) for i in users: add=0 login=str(i['name']) info_dict=win32net.NetUserGetInfo(server, login, 3) full_name=str(info_dict['full_name']) j=j+1 user_list.append(login+'\t'+full_name) return user_list except win32net.error: print traceback.format_tb(sys.exc_info()[2]),'\n',sys.exc_type,'\n',sys.exc_value print getall_users(r'\\dino')

Listing all machines in Domain
------------------------------

If you need to touch every machine in your domain, NetServerEnum can help you out. Based off of the constants defined in win32netcon, you can look for different classes of machines. For example, win32netcon.SV_TYPE_DOMAIN_BAKCTRL, will single out backup domain controllers. Here we use SV_TYPE_ALL to get everything. def getall_boxes(domain='',server=''): res=1 wrk_lst=[] try: while res: #loop until res2 (wrk_list2,total,res2)=win32net.NetServerEnum('',100,win32netcon.SV_TYPE_ALL,server,res,win32netcon.MAX_PREFERRED_LENGTH) wrk_lst.extend(wrk_list2) res=res2 except win32net.error: print traceback.format_tb(sys.exc_info()[2]),'\n',sys.exc_type,'\n',sys.exc_value final_lst=[] for i in wrk_lst: final_lst.append(str(i['name'])) return final_lst print getall_boxes('bedrock',r'\\rubble')

Creating a share
----------------

If we want to add a new share, the help documentation says is that I need a dictionary holding the share data, in the format of PySHARE_INFO_*. Selecting that link will show a number of different PySHARE_INFO structures; lets assume we want to use the PySHARE_INFO_2 structure. So do you create this PySHARE_INFO_2 Object? It is really quite simple: In c++, for example, the SHARE_INFO_2 structure looks like:

.. code-block:: cpp
   :linenos:

    typedef struct _SHARE_INFO_2 { 
    LPWSTR shi2_netname; 
    DWORD shi2_type; 
    LPWSTR shi2_remark; 
    DWORD shi2_permissions; 
    DWORD shi2_max_uses; 
    DWORD shi2_current_uses; 
    LPWSTR shi2_path; 
    LPWSTR shi2_passwd; 
    } SHARE_INFO_2, *PSHARE_INFO_2, *LPSHARE_INFO_2;

What does that mean in python?

You simply make a dictionary with the entries matching the structure above, except you remove the "shi2\_" prefix. In general, not all of the structure items will be required; you will need to consult the Win32 SDK for more information on these structures, and exactly what elements are required for what operation.

The final trick is knowing where to get the constant values for some of these items. For example, the "shi2_type" element is defined as an integer - what values are valid? If we consult the Win32 documentation, we will find valid values include STYPE_DISKTREE, STYPE_PRINTQ and a number of others. In general, you can find these constants in the win32netcon module. The Pythonwin object browser can show you what's available in this module.

Example

Given this knowledge, we could then write the following Python code to add a new share.

.. code-block:: python
   :linenos:

   import win32net import win32netcon shinfo={} shinfo['netname']='python test' shinfo['type']=win32netcon.STYPE_DISKTREE shinfo['remark']='bedrock_rubbel' shinfo['permissions']=0 shinfo['max_uses']=-1 shinfo['current_uses']=0 shinfo['path']='c:\\rubbel_share' shinfo['passwd']='' server='betty_server' try: win32net.NetShareAdd(server,2,shinfo) return "success" except win32net.error: print traceback.format_tb(sys.exc_info()[2]),'\n',sys.exc_type,'\n',sys.exc_value

Manage Users
============

Changing the full name
----------------------

If you want to get or set attributes about a user in NT you can use NetUserGetInfo and NetUserSetInfo, respectively. Example In c++ the setinfo call looks like this: NET_API_STATUS NetUserSetInfo( LPCWSTR servername, LPCWSTR username, DWORD level, LPBYTE buf, LPDWORD parm_err ); It's reasonably self explanatory except for level. It turns out there are many levels. One of the most useful one is USER_INFO_3 this structure lets you change just about anything you want for a user.Also, not all levels are available for both NetUserSetInfo and NetUserGetInfo. NetUserGetInfo has about 7 available to it. (btw, Microsoft MSDN http://msdn.microsoft.com/ would have more information about this). I'll show an example with NetUserSetInfo using USER_INFO_1008 that has no corresponding NetUserGetInfo. The python call looks like this: NetUserSetInfo( server , username ,level , data ) For it the most interesting parts are server, level, and data. Server is only interesting because the server name has to be prepended with \\. It is not obvious from the python api description, but very important. Luckily, as we'll see later, some functions in python return the server already in the correct format. Level is similar to the C++ level except that you simply use a number. In our case we would use 3. For data the documentation says you need a dictionary holding the user data in the format of PyUSER_INFO_*. If you check out that object you will see many available levels and find the level 3 we are interested in. It is simply a very long python dictionary with all sorts of user attributes. Of these attributes, one can be confusing: flags. If you want to change flags for a user, you need to have all of the appropriate flags bitwise OR'ed together. The second example below will better explain what is happening. Now for some code: In the example below, you will notice a couple of things. First, win32net.NetGetDCName returns the primary domain controller already in the correct format with double backslashes prepended. Also, python exception handling is a very powerful asset. The try block explicitly catches and win32net errors from your system calls. And, we can extract what happened with sys.exc_type and sys.exc_value. import sys import win32net import win32netcon domain="bedrock" login="slate" try: #get the server for the domain -- it has to be a primary dc server=str(win32net.NetGetDCName("",domain)) #info returns a dictionary of information info = win32net.NetUserGetInfo(server, login, 3) print info['full_name'] info['full_name']="Mr. Slate" win32net.NetUserSetInfo(server,login,3,info) info = win32net.NetUserGetInfo(server, login, 3) print info['full_name'] except win32net.error: print traceback.format_tb(sys.exc_info()[2]),'\n',sys.exc_type,'\n',sys.exc_value

Changing password expiration
----------------------------

A trickier 2nd example. The example below deals with the 1008 structure and flags. The python documentation says the structure is a dictionary holding the information in a Win32 USER_INFO_1008 structure. with properties: int flags. What that means is you have something like dict={'flags':int_value}. In our case, each flag represents a bit that is turned off or on. The constants in win32netcon come in very handy here. Make sure you have all of the bits included even if you are only going to change one of the values. For example, if you want to tell NT to not expire a password for a user, you need to use: win32netcon.UF_DONT_EXPIRE_PASSWD. However, if you only use that, then all the remaining bits aren't set. You have 2 options, either bitwise OR the appropriate options together, or do a bitwise OR of the flag with the current user flags To remove a flag use the bitwise compliment ~. This will be more clear in the example below. Here is some code that turns on the UF_DONT_EXPIRE_PASSWD bit for a user. import sys import win32net import win32netcon domain="bedrock" login="slate" try: #get the server for the domain -- it has to be a primary dc server=str(win32net.NetGetDCName("",domain)) #Commented out here is a typical flag setting #flag=win32netcon.UF_NORMAL_ACCOUNT|win32netcon.UF_SCRIPT|win32netcon.UF_DONT_EXPIRE_PASSWD #however, if you want to preserve any non-standard flags then do the following d=win32net.NetUserGetInfo(server,login,3) #get the current flags, note, I didn't use 1008 here! flag=d['flags']| win32netcon.UF_DONT_EXPIRE_PASSWD #this adds the flag # flag=d['flags']& ~win32netcon.UF_DONT_EXPIRE_PASSWD #this removes the flag flag_dict={'flags':flag} win32net.NetUserSetInfo(server,login,1008,flag_dict) except win32net.error: print traceback.format_tb(sys.exc_info()[2]),'\n',sys.exc_type,'\n',sys.exc_value

In Conclusion
=============

Python's win32net library module offers most of the Windows NT Networking API from Python. Several examples are touched upon to show the simple access python gives one to the underlying api.

*Have a great time with programming with python!*

Further Info
============

Microsoft MSDN references http://msdn.microsoft.com/
Relevant Python libraries: win32net and win32netcon