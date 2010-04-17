#!/usr/bin/python

import wx
from MainFrame import *
from signups import *

if __name__=="__main__":
	signups = Signups("signups.db")

	app = wx.PySimpleApp(0)
	wx.InitAllImageHandlers()
	
	main_frame = MainFrame(None, -1, "")
	app.SetTopWindow(main_frame)
	main_frame.Show()
	
	app.MainLoop()
