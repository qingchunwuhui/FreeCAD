/***************************************************************************
 *   Copyright (c) YEAR YOUR NAME         <Your e-mail address>            *
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
#endif

#include <Base/Console.h>
#include <App/Document.h>
#include <Gui/Application.h>
#include <Gui/Command.h>
#include <Gui/Control.h>

#include "DlgCreatePoint.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//===========================================================================
// CmdArigin3DTest THIS IS JUST A TEST COMMAND
//===========================================================================
DEF_STD_CMD(CmdArigin3DTest);

CmdArigin3DTest::CmdArigin3DTest()
  :Command("Arigin3D_Test")
{
    sAppModule    = "Arigin3D";
    sGroup        = QT_TR_NOOP("Arigin3D");
    sMenuText     = QT_TR_NOOP("Hello");
    sToolTipText  = QT_TR_NOOP("Arigin3D Test function");
    sWhatsThis    = QT_TR_NOOP("Arigin3D Test function");
    sStatusTip    = QT_TR_NOOP("Arigin3D Test function");
    sPixmap       = "Test1";
    sAccel        = "CTRL+H";
}

void CmdArigin3DTest::activated(int iMsg)
{
    Base::Console().Message("Hello, World!\n");
}

//===========================================================================
// cmdArigin3DCreatePoint
//===========================================================================
DEF_STD_CMD_A(CmdArigin3DCreatePoint)

CmdArigin3DCreatePoint::CmdArigin3DCreatePoint()
:Command("Arigin3D_CreatePoint")
{
	sAppModule = "Arigin3D";
	sGroup = QT_TR_NOOP("Arigin3D");
	sMenuText = QT_TR_NOOP("Create Point");
	sToolTipText = QT_TR_NOOP("Create Point");
	sWhatsThis = QT_TR_NOOP("Create Point");
	sStatusTip = QT_TR_NOOP("Click a Point on the part or fill out the coordinate");
	sPixmap = "Part_Point_Parametric";
	sAccel = "CTRL+H";
}

void CmdArigin3DCreatePoint::activated(int)
{
	/*Base::Console().Message("Create a Point!\n");*/
	Arigin3DGui::TaskCreatePoint* dlg = new Arigin3DGui::TaskCreatePoint();
	Gui::Control().showDialog(dlg);
}

bool CmdArigin3DCreatePoint::isActive(void)
{
	if (getActiveGuiDocument())
		return true;
	else
		return false;
}

void CreateArigin3DCommands(void)
{
    Gui::CommandManager &rcCmdMgr = Gui::Application::Instance->commandManager();
    rcCmdMgr.addCommand(new CmdArigin3DTest());
	rcCmdMgr.addCommand(new CmdArigin3DCreatePoint());
}
