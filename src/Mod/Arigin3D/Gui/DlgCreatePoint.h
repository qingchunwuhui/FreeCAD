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

#ifndef ARIGIN3DGUI_DLGCREATRPOINT_H
#define ARIGIN3DGUI_DLGCREATRPOINT_H

#include <QEventLoop>
#include <QPointer>
#include <Gui/TaskView/TaskDialog.h>
#include <mod/Arigin3D/Gui/ui_DlgCreatePoint.h>

namespace App { class Document; }
namespace Gui { class Document; }

namespace Arigin3DGui
{ 

class DlgCreatePoint : public QWidget
{
	Q_OBJECT

public:
	DlgCreatePoint(QWidget* parent = 0);
	~DlgCreatePoint();
	
	void createPoint();

private:
	Ui_CreatePoint ui;

};

class TaskCreatePoint : public Gui::TaskView::TaskDialog
{
	Q_OBJECT

public:
	TaskCreatePoint();
	~TaskCreatePoint();

public:
	bool accept();
	bool reject();

	virtual QDialogButtonBox::StandardButtons getStandardButtons(void) const;
	void modifyStandardButtons(QDialogButtonBox*);

private:
	DlgCreatePoint* widget;
};

} //namespace Arigin3DGui

#endif  //ARIGIN3DGUI_DLGCREATRPOINT_H