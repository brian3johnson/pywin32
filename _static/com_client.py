import win32com.client

xl_app = win32com.client.Dispatch("Excel.Application")

xl_app.Visible = 1
xl_app.Workbooks.Add()
xl_app.Cells(1, 1).Value = "Hello"
