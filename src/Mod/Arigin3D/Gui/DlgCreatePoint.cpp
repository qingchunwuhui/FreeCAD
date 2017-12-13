/***************************************************************************
*   Copyright (c) 2007 Werner Mayer <wmayer[at]users.sourceforge.net>     *
*                                                                         *
*   This file is part of the FreeCAD CAx development system.              *
*                                                                         *
*   This library is free software; you can redistribute it and/or         *
*   modify it under the terms of the GNU Library General Public           *
*   License as published by the Free Software Foundation; either          *
*   version 2 of the License, or (at your option) any later version.      *
*                                                                         *
*   This library  is distributed in the hope that it will be useful,      *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU Library General Public License for more details.                  *
*                                                                         *
*   You should have received a copy of the GNU Library General Public     *
*   License along with this library; see the file COPYING.LIB. If not,    *
*   write to the Free Software Foundation, Inc., 59 Temple Place,         *
*   Suite 330, Boston, MA  02111-1307, USA                                *
*                                                                         *
***************************************************************************/

#include "PreCompiled.h"
#ifndef _PreComp_
#include <gp_Ax1.hxx>
#include <gp_Ax3.hxx>
#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <Geom_Circle.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#endif

#include <CXX/WrapPython.h>
#include <Base/Interpreter.h>
#include <Base/Rotation.h>
#include <Base/Tools.h>
#include <Base/Console.h>
#include <App/Application.h>
#include <App/Document.h>
#include <Gui/Application.h>
#include <Gui/Document.h>
#include <Gui/Command.h>
#include <Gui/View3DInventor.h>
#include <Gui/View3DInventorViewer.h>
#include <Gui/SoFCUnifiedSelection.h>
#include <Gui/TaskView/TaskView.h>

#include <QtGui/QMessageBox>

#include "DlgCreatePoint.h"

using namespace Arigin3DGui;

namespace Arigin3DGui{

const char* gce_ErrorStatusText(gce_ErrorType et)
{
	switch (et)
	{
	case gce_Done:
		return "Construction was successful";
	case gce_ConfusedPoints:
		return "Two points are coincident";
	case gce_NegativeRadius:
		return "Radius value is negative";
	case gce_ColinearPoints:
		return "Three points are collinear";
	case gce_IntersectionError:
		return "Intersection cannot be computed";
	case gce_NullAxis:
		return "Axis is undefined";
	case gce_NullAngle:
		return "Angle value is invalid (usually null)";
	case gce_NullRadius:
		return "Radius is null";
	case gce_InvertAxis:
		return "Axis value is invalid";
	case gce_BadAngle:
		return "Angle value is invalid";
	case gce_InvertRadius:
		return "Radius value is incorrect (usually with respect to another radius)";
	case gce_NullFocusLength:
		return "Focal distance is null";
	case gce_NullVector:
		return "Vector is null";
	case gce_BadEquation:
		return "Coefficients are incorrect (applies to the equation of a geometric object)";
	default:
		return "Creation of geometry failed";
	}
}

}


/* TRANSLATOR Arigin3DGui::DlgCreatePoint */
DlgCreatePoint::DlgCreatePoint(QWidget* parent /*= 0*/)
	:QWidget(parent)
{
	ui.setupUi(this);

	//set limits
	ui.vertexX->setMaximum(INT_MAX);
	ui.vertexY->setMaximum(INT_MAX);
	ui.vertexZ->setMaximum(INT_MAX);

}

DlgCreatePoint::~DlgCreatePoint()
{

}

void DlgCreatePoint::createPoint()
{
	try{
		QString cmd; 
		QString name;
		App::Document* doc = App::GetApplication().getActiveDocument();
		if (!doc){
			QMessageBox::warning(this, tr("Create %1")
				.arg(ui.comboBox_CreatePoint->currentText()), tr("No active document"));
			return;
		}

		if (ui.comboBox_CreatePoint->currentIndex() == 0)
		{
			name = QString::fromLatin1(doc->getUniqueObjectName("Line").c_str());
			cmd = QString::fromLatin1(
				"App.ActiveDocument.addObject(\"Arigin3D::CXJPoint\", \"%1\")\n")
				.arg(name);
		}

		

		Base::TimeInfo timecount;

		// Execute the Python block
		QString prim = tr("Create Point by %1").arg(ui.comboBox_CreatePoint->currentText());
		Gui::Application::Instance->activeDocument()->openCommand(prim.toUtf8());
		//Gui::Command::doCommand(Gui::Command::Doc, (const char*)cmd.toUtf8());
		//Gui::Application::Instance->activeDocument()->commitCommand();
		//Gui::Command::doCommand(Gui::Command::Doc, "App.ActiveDocument.recompute()");

		short delta = timecount.getMiliseconds();

		Base::Console().Error("we need %f to create point: \n", Base::TimeInfo::diffTimeF(timecount, Base::TimeInfo()));
		
		Gui::Command::doCommand(Gui::Command::Gui, "Gui.SendMsgToActiveView(\"ViewFit\")");
	}
	catch (const Base::PyException& e) {
		QMessageBox::warning(this, tr("Create %1")
		.arg(ui.comboBox_CreatePoint->currentText()), QString::fromLatin1(e.what()));
		}

}

// ----------------------------------------------

/* TRANSLATOR Arigin3DGui::TaskeCreatePoint */
TaskCreatePoint::TaskCreatePoint()
{
	Gui::TaskView::TaskBox* taskbox;
	widget = new DlgCreatePoint();
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, 0);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);
}

TaskCreatePoint::~TaskCreatePoint()
{
	// automatically deleted in the sub-class
}


QDialogButtonBox::StandardButtons TaskCreatePoint::getStandardButtons(void) const
{
	return QDialogButtonBox::Close |
		QDialogButtonBox::Ok;
}


void TaskCreatePoint::modifyStandardButtons(QDialogButtonBox* box)
{
	/*QPushButton* btn = box->button(QDialogButtonBox::Ok);
	btn->setText(QApplication::translate("Arigin3DGui::DlgCreatePoint", "&Create"));*/
}

bool TaskCreatePoint::accept()
{
	if (widget)
		widget->createPoint();

	return false;
}

bool TaskCreatePoint::reject()
{
	return true;
}

#include "moc_DlgCreatePoint.cpp"
