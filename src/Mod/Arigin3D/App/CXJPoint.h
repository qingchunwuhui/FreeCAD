

#ifndef XJ_POINT_H
#define XJ_POINT_H

#include <Mod/Part/App/PrimitiveFeature.h>

namespace Arigin3D
{

class Arigin3DAppExport CXJPoint : public Part::Primitive
{
	PROPERTY_HEADER(Arigin3D::CXJPoint);

public:
	CXJPoint();
	~CXJPoint();

	App::PropertyVector m_point;

	/** @name methods override feature */
	//@{
	/// recalculate the Feature
	App::DocumentObjectExecReturn *execute(void);
	short mustExecute() const;
	void onChanged(const App::Property* prop);

	/// returns the type name of the ViewProvider
	const char* getViewProviderName(void) const {
		return "PartGui::ViewProviderPointParametric";
	}

};

}

#endif