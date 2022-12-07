=================================
Windows NT Eventlog and Threading
=================================

.. admonition:: Existing document
   
   :file:`\\win32\\help\\event.d` Part 2

.. contents::
   :depth: 1
   :local:

Python's threading to manage access access to many Eventlogs

If you need to access the eventlog of many servers, it can take quite some time if you go through a list sequentially -- since you need to wait for each operation to complete. There are a few ways you can do this in python. You can spawn many processes, use python's win32 libraries for win32 style-threading, or use python's native libraries.

In NT spawning a process is slow (though in this case that may not matter) and it can be a little cumbersome to get them to share data. Since python's win32 libraries are thread-safe, you can use python's win32 libraries to do win32-style threading or use python's native threading library to spawn threads. Win32 style threading is available via python's win32process library. It gives you excellent control and ability to do some sophisticated stuff, however raw win32 threaded programming can be tricky. The final option is Python's native high-level threading library which is built on top of a lower level thread library. It turns out that it is easy to use and
cross-platform (well at least to platforms that support threading). It's only disadvantage is that your thread control(synchronization, giving them priorities, suspending them, etc.)  is limited. In many cases, however, that is not important, you just need the ability to _easily_ do a few things at once. Thus, we'll focus on Python's native threading.

One final note, the python interpreter has a global lock for threads forcing them to run serially. Which means only one thread can intrepret python code at any given time. After a certain amount of
python code has been run, then control is switched to another thread. Thus, this means you can't have things like many threads running on many processors. Fortunately, in cases with I/O and extension modules (in which you can manipulate the interpreter lock), this isn't an issue. In our case (accessing the eventlog of many servers) the global lock shouldn't be a bottleneck(i/o will be).

There are a couple of ways to use the threading library. We'll look at the case in which you override the run method of the threading.Thread class. The run method will contain the actual code you want to run many times.

The basic procedure to follow is this. For every server in the list:

#. create a thread class
#. call start method in thread class(which invokes your run method)
#. call join method to force main thread to wait for threads to complete
#. compile data together from all thread classes created.

Since you don't use the return values of the thread, you need to store data with the thread object that you create. Furthermore, you'll notice we use the join method to force the calling thread to wait for the other threads to finish.

Here is the skeleton of that:

.. code-block:: python

   #We are overiding run() method of the threading.Thread class. 
   class thread_it ( threading.Thread ) :
   def __init__ ( self, server) : 
      threading.Thread.__init__(self)
      self.data=[] #store data here to get later
      self.server=server
   # the start() method invokes run
   def run ( self ): #overridden from threading library
      try:
         pass #get event information here and store in data
      except:
         #append any errors to self.data, to get later
         self.data.append('Error for '+self.server+':'+str(traceback.print_exc(sys.exc_info())))

   ######main here
   try:
      l_servers=('fred','barney','wilma','betty')
      for server in l_servers: #make a thread for each server
               thread = thread_it (server) 
               threads.append ( thread ) #append to the a threads list 

      for thread in threads: #now go thru list and start threads running
               thread.start()

      for thread in threads: #make main thread wait for all in list to complete
         thread.join()

      for thread in threads: #print thread results
         for event in thread.data:
      print event 


   except:
      print traceback.print_exc(sys.exc_info())

Looking at the skeleton, all one really needs to do is put the eventlog code in the run function and have it store results in the data variable. The main part is almost boilerplate code.  So you can see multi-threading at work, I've added a 'now' column to the eventlog printout which tells you the current time, and easily shows that the data was gathered simultaneously on the servers.

Filling out the skeleton we get code like this:

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
   import threading
   import traceback

   #We are overiding run() method of the threading.Thread class. 
   class thread_it ( threading.Thread ) :
      def __init__ ( self, server) : 
         threading.Thread.__init__(self)
         self.data=[] #store data here to get later
         self.server=server
   # the start() method invokes run
      def run ( self): #overridden from threading library
         flags = win32evtlog.EVENTLOG_BACKWARDS_READ|\
         win32evtlog.EVENTLOG_SEQUENTIAL_READ
         #This dict converts the event type into a human readable form
         evt_dict={win32con.EVENTLOG_AUDIT_FAILURE:'EVENTLOG_AUDIT_FAILURE',\
         win32con.EVENTLOG_AUDIT_SUCCESS:'EVENTLOG_AUDIT_SUCCESS',\
         win32con.EVENTLOG_INFORMATION_TYPE:'EVENTLOG_INFORMATION_TYPE',\
         win32con.EVENTLOG_WARNING_TYPE:'EVENTLOG_WARNING_TYPE',\
         win32con.EVENTLOG_ERROR_TYPE:'EVENTLOG_ERROR_TYPE'}
         logtype='System'
         begin_sec=time.time()
         begin_time=time.strftime('%H:%M:%S  ',time.localtime(begin_sec))
         try:
            hand=win32evtlog.OpenEventLog(self.server,logtype) #open event log here
            self.data.append('events found in the last 8 hours since:'+begin_time+'for '+self.server)
            events=1
            while events:
               events=win32evtlog.ReadEventLog(hand,flags,0)

               for ev_obj in events:
                  now_sec=time.time()
                  now_time=time.strftime('now=%H:%M:%S  ',time.localtime(now_sec))

                  #check if the event is recent enough 
                  #only want data from last 8hrs
                  the_time=ev_obj.TimeGenerated.Format()
                  seconds=self.date2sec(the_time)
                  if seconds < begin_sec-28800: break 
                  #data is recent enough, so print it out
                  computer=str(ev_obj.ComputerName)
                  cat=str(ev_obj.EventCategory)
                  src=str(ev_obj.SourceName)
                  record=str(ev_obj.RecordNumber)
                  evt_id=str(winerror.HRESULT_CODE(ev_obj.EventID))
                  evt_type=str(evt_dict[ev_obj.EventType])
                  msg = str(win32evtlogutil.SafeFormatMessage(ev_obj, logtype))
                  results=string.join((now_time,the_time,computer,src,cat,record,evt_id,evt_type,msg[0:15]),':')
                  self.data.append(results)
               if seconds < begin_sec-28800: break 
            win32evtlog.CloseEventLog(hand)
         except:
            self.data.append('Error for '+self.server+':'+str(traceback.print_exc(sys.exc_info())))

      def date2sec(self,evt_date):
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
   ######main here
   try:
      threads=[]
      data=[]
      l_servers=['barney','betty','fred','wilma']
      for server in l_servers: #make a thread for each server
            thread = thread_it (server) 
            threads.append ( thread ) #append to the a threads list 

      for thread in threads: #now go thru list and start threads running
            thread.start()

      for thread in threads: #make main thread wait for all in list to complete
         thread.join()

      for thread in threads: #compile all of the threads' data together.
         print '###############'
         for event in thread.data:
            print event 

   except:
      print traceback.print_exc(sys.exc_info())

A very nice addition to this would be to convert it to a web application. HTMLgen is a useful tool in this context.

Have a great time with programming with python!

John Nielsen   nielsenjf@my-deja.com