import re, sqlite3
import config

class Signups(object):
	def __init__(self, database_file):
		self.db = sqlite3.connect(database_file)
		self.__init_db()
	
	@property
	def mailing_lists(self):
		c = self.db.cursor()
		c.execute("""
			SELECT list_id, name FROM MailingLists ORDER BY name
		""")
		
		return list(c)
	
	def __init_db(self):
		"""
		Setup the DB if this has not already been done.
		"""
		c = self.db.cursor()
		
		# A table for student details
		c.execute("""
			CREATE TABLE IF NOT EXISTS Students(
				student_id INTEGER PRIMARY KEY,
				name TEXT,
				email TEXT,
				paid BOOLEAN
			)
		""")
		
		# A table containing possible mailing lists
		c.execute("""
			CREATE TABLE IF NOT EXISTS MailingLists(
				list_id INTEGER PRIMARY KEY AUTOINCREMENT,
				name TEXT
			)
		""")
		
		# A table linking members to the mailinglists subscribed
		c.execute("""
			CREATE TABLE IF NOT EXISTS MailingListSubscriptions(
				student_id INTEGER,
				list_id INTEGER
			)
		""")
		self.db.commit()
		
		# If the mailing list table is empty, fill it up
		if len(self.mailing_lists) == 0:
			self.__populate_default_lists()
		
	def __populate_default_lists(self):
		"""
		Populate the MailingLists table with the default lists in the config
		"""
		c = self.db.cursor()
		c.executemany("""
			INSERT INTO MailingLists(name)
			VALUES ( ? )
		""",
			((x,) for x in config.default_mailing_lists)
		)
		self.db.commit()
