# -*- coding: utf-8 -*-


class Decor:
	"décor contenu dans une zone"
	
	def __init__(self, _id, x, y):
		self._id = _id
		self.x = x
		self.y = y
	
	def __lt__(self, other):
		return self._id < other._id
	
	def __str__(self):
		return "Décor id %d (x: %d, y: %d)" % (self._id, self.x, self.y)
	
	def to_xml(self):
		return '<decor id="%d" x="%d" y="%d" />' % (self._id, self.x, self.y)
		
