
#include "PreCompiled.h"
#ifndef _PreComp_
#include <gp_Pnt.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <Precision.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Vertex.hxx>

#endif

#include "CXJPoint.h"
#include <Base/Console.h>
#include <Base/Exception.h>
#include <Mod/Part/App/PropertyTopoShape.h>

using namespace Arigin3D;

PROPERTY_SOURCE(Arigin3D::CXJPoint, Part::Primitive)

CXJPoint::CXJPoint()
{
	ADD_PROPERTY(m_point, (0.0f, 0.0f, 0.0f));
}


CXJPoint::~CXJPoint()
{

}

App::DocumentObjectExecReturn * CXJPoint::execute(void)
{
	Base::Vector3d val = m_point.getValue();

	gp_Pnt point;
	point.SetX(val.x);
	point.SetY(val.y);
	point.SetZ(val.z);

	BRepBuilderAPI_MakeVertex MakeVertex(point);
	const TopoDS_Vertex& vertex = MakeVertex.Vertex();
	Shape.setValue(vertex);

	return App::DocumentObject::StdReturn;
}

short CXJPoint::mustExecute() const
{
	return Part::Feature::mustExecute();
}

void CXJPoint::onChanged(const App::Property* prop)
{
	if (!isRestoring()) {
		if (prop == &m_point){
			try {
				//App::DocumentObjectExecReturn *ret = recompute();
				//delete ret;
			}
			catch (...) {
			}
		}
	}
	Part::Feature::onChanged(prop);

}
