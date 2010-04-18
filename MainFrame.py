import wx
import ui

# A wxPython bug -- this event doesn't seem to have been set up
wx.EVT_COMMAND_CHECKLISTBOX_TOGGLED = wx.PyEventBinder(
	wx.wxEVT_COMMAND_CHECKLISTBOX_TOGGLED
)

class MainFrame(ui.MainFrame):
	def __init__(self, signups, *args, **kwargs):
		ui.MainFrame.__init__(self, *args, **kwargs)
		
		# Bind the mailing_lists to an event (extra because wxGlade doesn't do this
		# one particular widget)
		self.Bind(wx.EVT_COMMAND_CHECKLISTBOX_TOGGLED,
		          self.mailing_lists_clicked,
		          self.mailing_lists)
		
		self.signups = signups
		
		self.populate_mailing_lists()
	
	def populate_mailing_lists(self):
		"""
		Setup the mailing_lists box with all available lists
		"""
		self.mailing_lists.Clear()
		for list_id, name in self.signups.mailing_lists:
			self.mailing_lists.Append(item=name, clientData=list_id)
	
	def quit_button_clicked(self, event):
		self.Close()
	
	def mailing_lists_clicked(self, event):
		print "eh"
