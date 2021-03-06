//##########################################################################
//#                                                                        #
//#                            CLOUDCOMPARE                                #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#          COPYRIGHT: EDF R&D / TELECOM ParisTech (ENST-TSI)             #
//#                                                                        #
//##########################################################################

#ifndef CC_FACET_HEADER
#define CC_FACET_HEADER

//Local
#include "ccHObject.h"
#include "ccMesh.h"
#include "ccPolyline.h"
#include "ccPointCloud.h"

//CCLib
#include <GenericIndexedCloudPersist.h>


//! Facet
/** Composite object: point cloud + 2D1/2 contour polyline + 2D1/2 surface mesh
**/
#ifdef QCC_DB_USE_AS_DLL
#include "qCC_db_dll.h"
class QCC_DB_DLL_API ccFacet : public ccHObject
#else
class ccFacet : public ccHObject
#endif
{
public:

	//! Default constructor
	/** \param maxEdgeLength max edge length (if possible - ignored if 0)
		\param name name
	**/
	ccFacet(PointCoordinateType maxEdgeLength = 0,
			QString name = QString("Facet"));

	//! Destructor
	virtual ~ccFacet();

	//! Creates a facet from a set of points
	/** The facet boundary can either be the convex hull (maxEdgeLength = 0)
		or the concave hull (maxEdgeLength > 0).
		\param cloud cloud from which to create the facet
		\param maxEdgeLength max edge length (if possible - ignored if 0)
		\param transferOwnership if true and the input cloud is a ccPointCloud, it will be 'kept' as 'origin points'
		\param planeEquation to input a custom plane equation
		\return a facet (or 0 if an error occurred)
	**/
	static ccFacet* Create(	CCLib::GenericIndexedCloudPersist* cloud,
							PointCoordinateType maxEdgeLength = 0,
							bool transferOwnership = false,
							const PointCoordinateType* planeEquation = 0);

    //! Returns class ID
    virtual CC_CLASS_ENUM getClassID() const { return CC_FACET; }
	virtual bool isSerializable() const { return true; }

	//! Sets the facet unique color
	/** \param rgb RGB color
	**/
	void setColor(const colorType rgb[]);

	//! Returns associated RMS
	double getRMS() const { return m_rms; }
	//! Returns associated surface
	double getSurface() const { return m_surface; }
	//! Returns plane equation
	const PointCoordinateType* getPlaneEquation() const { return m_planeEquation; }
	//! Returns normal
	CCVector3 getNormal() const { return CCVector3(m_planeEquation); }
	//! Inverts normal
	void invertNormal();
	//! Returns center
	const CCVector3& getCenter() const { return m_center; }

	//! Returns polygon mesh (if any)
	ccMesh* getPolygon() { return m_polygonMesh; }
	//! Returns contour polyline (if any)
	ccPolyline* getContour() { return m_contourPolyline; }
	//! Returns contour vertices (if any)
	ccPointCloud* getContourVertices() { return m_contourVertices; }
	//! Returns origin points (if any)
	ccPointCloud* getOriginPoints() { return m_originPoints; }

	//! Sets polygon mesh
	void setPolygon(ccMesh* mesh) { m_polygonMesh = mesh; }
	//! Sets contour polyline
	void setContour(ccPolyline* poly) { m_contourPolyline = poly; }
	//! Sets contour vertices
	void setContourVertices(ccPointCloud* cloud) { m_contourVertices = cloud; }
	//! Sets origin points
	void setOriginPoints(ccPointCloud* cloud) { m_originPoints = cloud; }

	//! Show normal vector
	void showNormalVector(bool state) { m_showNormalVector = state; }
	//! Whether normal vector is shown or not
	bool normalVectorIsShown() const { return m_showNormalVector; }

	//! Clones this facet
	ccFacet* clone() const;

protected:

	//inherited from ccDrawable
	void drawMeOnly(CC_DRAW_CONTEXT& context);

	//! Creates internal representation (polygon, polyline, etc.)
	bool createInternalRepresentation(	CCLib::GenericIndexedCloudPersist* points,
										const PointCoordinateType* planeEquation = 0);

	//! Facet 
	ccMesh* m_polygonMesh;
	//! Facet contour
	ccPolyline* m_contourPolyline;
	//! Shared vertices (between polygon and contour)
	ccPointCloud* m_contourVertices;
	//! Origin points
	ccPointCloud* m_originPoints;

	//! Plane equation
	PointCoordinateType m_planeEquation[4];
	
	//! Facet centroid
	CCVector3 m_center;

	//! RMS (relatively to m_associatedPoints)
	double m_rms;

	//! Surface (m_polygon)
	double m_surface;

	//! Max length
	PointCoordinateType m_maxEdgeLength;

	//! Whether the facet normal vector should be displayed or not
	bool m_showNormalVector;

    //inherited from ccHObject
	virtual bool toFile_MeOnly(QFile& out) const;
	virtual bool fromFile_MeOnly(QFile& in, short dataVersion);
};

#endif //CC_FACET_PRIMITIVE_HEADER
