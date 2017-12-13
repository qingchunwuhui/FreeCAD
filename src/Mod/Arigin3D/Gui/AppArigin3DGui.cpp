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
# include <Python.h>
#endif

#include <Base/Console.h>
#include <Gui/Application.h>

#include "Workbench.h"

#include <CXX/Extensions.hxx>
#include <CXX/Objects.hxx>

// use a different name to CreateCommand()
void CreateArigin3DCommands(void);


namespace Arigin3DGui {
class Module : public Py::ExtensionModule<Module>
{
public:
    Module() : Py::ExtensionModule<Module>("Arigin3DGui")
    {
        initialize("This module is the Arigin3DGui module."); // register with Python
    }

    virtual ~Module() {}

private:
};
} // namespace Arigin3DGui


/* Python entry */
PyMODINIT_FUNC initArigin3DGui()
{
    if (!Gui::Application::Instance) {
        PyErr_SetString(PyExc_ImportError, "Cannot load Gui module in console application.");
        return;
    }

    // instanciating the commands
    CreateArigin3DCommands();
    Arigin3DGui::Workbench::init();

    // ADD YOUR CODE HERE
    //
    //
    new Arigin3DGui::Module();
    Base::Console().Log("Loading GUI of Arigin3D module... done\n");
}
