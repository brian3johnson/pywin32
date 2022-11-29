===================
Windows NT Eventlog
===================

.. admonition:: Existing document
   
   :file:`\\win32\\help\\event.d` Part 1

.. contents::
   :depth: 1
   :local:

Python's win32 access for the Eventlog

If you need to scan the eventlog of many servers or do specific filtering based off of the event log, python's win32evtlog win32evtlogutil libraries give you an means to do it efficiently.

The library of primary importance is win32evtlog. With it you can connect to a server's eventlog with the call.

Example
=======

Here is the basic call:

.. code-block:: python

   logtype='System'
   hand=win32evtlog.OpenEventLog(server,logtype)

This returns a handle from which you can make calls such as one that will give you the total number of events or another examine the details for each event. The logtype variable is set to the type of log you want to look at. The default ones are: Application, Security, and System.

After you have the handle you can get ask for things such as the number of records, or the specific event records:

.. code-block:: python

   total=win32evtlog.GetNumberOfEventLogRecords(hand)
   flags = win32evtlog.EVENTLOG_BACKWARDS_READ|win32evtlog.EVENTLOG_SEQUENTIAL_READ
   events=win32evtlog.ReadEventLog(hand,flags,0)

ReadEventLog returns a number of event objects which may not be all of them. You need to continously check in a loop until there are no more events returned by ReadEventLog. You may notice that ReadEventLog has a flags argument. The flags (which are convinently available with the win32evtlog library) specify how to read the event log.

Here is a simple loop getting the data from the events that ReadEventLog returned:

.. code-block:: python

   for ev_obj in events:
      the_time=ev_obj.TimeGenerated.Format() #'12/23/99 15:54:09'
      evt_id=str(winerror.HRESULT_CODE(ev_obj.EventID))
      computer=str(ev_obj.ComputerName)
      cat=ev_obj.EventCategory
         seconds=date2sec(the_time)
         record=ev_obj.RecordNumber
      msg=str(win32evtlogutil.SafeFormatMessage(ev_obj, logtype))
      source=str(ev_obj.SourceName)

We use the library win32evtlogutil to get the actual text body for the event. To get a easily readable date for the event, you need to specify the 'Format' method for the TimeGenerated part of the event object.

The win32evtlogutil comes in handy to give us the actual text body of the eventlog message.  If you want to do any sorting based of off time, here is a handy function that converts the eventlog's time format into seconds using's python's time and regexp library:

.. code-block:: python

   def date2sec(self,evt_date):
      '''
      converts '12/23/99 15:54:09' to seconds
      print '333333',evt_date
      '''
      regexp=re.compile('(.*)\s(.*)') 
      reg_result=regexp.search(evt_date)
      date=reg_result.group(1)
      the_time=reg_result.group(2)
      (mon,day,yr)=map(lambda x: string.atoi(x),string.split(date,'/'))
      (hr,min,sec)=map(lambda x: string.atoi(x),string.split(the_time,':'))
      tup=[yr,mon,day,hr,min,sec,0,0,0]
      sec=time.mktime(tup)
      return sec

If you want to get the current localtime in seconds, you can make the call:

.. code-block:: python

   begin_sec=time.time().

To convert that to a date use:

.. code-block:: python

   begin_time=str(time.strftime('%H:%M:%S  ',time.localtime( begin_sec )))

Finally here is all the code that puts together an application which looks for all events for a server since a certain time.

Find events:

.. code-block:: python

   import win32evtlog
   import win32evtlogutil
   import win32security
   import win32con
   import winerror
   import time
   import re
   import string
   import sys
   import traceback

   def date2sec(evt_date):
      '''
      This function converts dates with format
      '12/23/99 15:54:09' to seconds since 1970.
      '''
      regexp=re.compile('(.*)\s(.*)') #store result in site
      reg_result=regexp.search(evt_date)
      date=reg_result.group(1)
      the_time=reg_result.group(2)
      (mon,day,yr)=map(lambda x: string.atoi(x),string.split(date,'/'))
      (hr,min,sec)=map(lambda x: string.atoi(x),string.split(the_time,':'))
      tup=[yr,mon,day,hr,min,sec,0,0,0]

      sec=time.mktime(tup)

      return sec

   ####Main program
   #initialize variables
   flags = win32evtlog.EVENTLOG_BACKWARDS_READ|\
      win32evtlog.EVENTLOG_SEQUENTIAL_READ

   #This dict converts the event type into a human readable form
   evt_dict={win32con.EVENTLOG_AUDIT_FAILURE:'EVENTLOG_AUDIT_FAILURE',\
         win32con.EVENTLOG_AUDIT_SUCCESS:'EVENTLOG_AUDIT_SUCCESS',\
         win32con.EVENTLOG_INFORMATION_TYPE:'EVENTLOG_INFORMATION_TYPE',\
         win32con.EVENTLOG_WARNING_TYPE:'EVENTLOG_WARNING_TYPE',\
         win32con.EVENTLOG_ERROR_TYPE:'EVENTLOG_ERROR_TYPE'}
   computer='bedrock'
   logtype='System'
   begin_sec=time.time()
   begin_time=time.strftime('%H:%M:%S  ',time.localtime(begin_sec))

   #open event log 
   hand=win32evtlog.OpenEventLog(computer,logtype)
   print logtype,' events found in the last 8 hours since:',begin_time

   try:
   events=1
   while events:
      events=win32evtlog.ReadEventLog(hand,flags,0)
         for ev_obj in events:
         #check if the event is recent enough 
         #only want data from last 8hrs
         the_time=ev_obj.TimeGenerated.Format() 
         seconds=date2sec(the_time)
         if seconds < begin_sec-28800: break 

         #data is recent enough, so print it out
         computer=str(ev_obj.ComputerName)
         cat=str(ev_obj.EventCategory)
         src=str(ev_obj.SourceName)
         record=str(ev_obj.RecordNumber)
         evt_id=str(winerror.HRESULT_CODE(ev_obj.EventID))
         evt_type=str(evt_dict[ev_obj.EventType])
         msg = str(win32evtlogutil.SafeFormatMessage(ev_obj, logtype))
         print string.join((the_time,computer,src,cat,record,evt_id,evt_type,msg[0:15]),':')

      if seconds < begin_sec-28800: break #get out of while loop as well
   win32evtlog.CloseEventLog(hand)
   except:
      print traceback.print_exc(sys.exc_info())


Some useful additions to this would be to make it multi-threaded and deploy it as a web application, to look at many servers.

Have a great time with programming with python!

John Nielsen   nielsenjf@my-deja.com