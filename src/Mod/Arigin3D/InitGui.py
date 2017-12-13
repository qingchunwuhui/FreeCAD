# Arigin3D gui init module
# (c) 2001 Juergen Riegel LGPL

class Arigin3DWorkbench ( Workbench ):
	"Arigin3D workbench object"
	MenuText = "Arigin3D"
	ToolTip = "Arigin3D workbench"
	def Initialize(self):
		# load the module
		import Arigin3DGui
	def GetClassName(self):
		return "Arigin3DGui::Workbench"

Gui.addWorkbench(Arigin3DWorkbench())
