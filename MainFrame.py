import wx
import ui

class MainFrame(ui.MainFrame):
	def quit_button_clicked(self, event):
		self.Close()
