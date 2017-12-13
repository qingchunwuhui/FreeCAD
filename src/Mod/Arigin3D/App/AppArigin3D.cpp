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
#include <Base/Interpreter.h>

#include <CXX/Extensions.hxx>
#include <CXX/Objects.hxx>

#include "CXJPoint.h"


namespace Arigin3D {
class Module : public Py::ExtensionModule<Module>
{
public:
    Module() : Py::ExtensionModule<Module>("Arigin3D")
    {
        initialize("This module is the Arigin3D module."); // register with Python
    }

    virtual ~Module() {}

private:
};
} // namespace Arigin3D


/* Python entry */
PyMODINIT_FUNC initArigin3D() {

    // ADD YOUR CODE HERE
    //
    //
	//load dependent module
	try
	{
		Base::Interpreter().runString("import Part");
	}
	catch (const Base::Exception& e)
	{
		PyErr_SetString(PyExc_ImportError, e.what());
		return;
	}

	Base::Console().Log("Module::Arigin");
    new Arigin3D::Module();

	Arigin3D::CXJPoint::init();


    Base::Console().Log("Loading Arigin3D module... done\n");
}
