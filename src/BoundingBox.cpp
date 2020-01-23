/*---------------------------------------------------------------------

The BoundingBox class is a very simple utility class for working with
axis aligned bounding boxes

----------------------------------------------------------------------*/
#include "BoundingBox.h"
#include <limits>




namespace math
{
	//
	// constructor
	//
	BoundingBox::BoundingBox()
	{
        minPoint = math::Vec3d( std::numeric_limits<double>::max(),
                                std::numeric_limits<double>::max(),
                                std::numeric_limits<double>::max() );
        maxPoint = math::Vec3d( std::numeric_limits<double>::min(),
                                std::numeric_limits<double>::min(),
                                std::numeric_limits<double>::min() );
	}

	//
	// constructor
	//
    BoundingBox::BoundingBox( math::Vec3d _minPoint, math::Vec3d _maxPoint )
	{
		minPoint = _minPoint;
		maxPoint = _maxPoint;
	}

	//
	// returns a vector which represents the dimension in each axis
	//
    math::Vec3d BoundingBox::size( void ) const
	{
        return math::Vec3d( maxPoint - minPoint );
	}

	//
	// adobts the bounding borders if neccessary so that the given point lies within
	// the bounding box
	//
    void BoundingBox::extend( const math::Vec3d &nextPoint )
	{
		if( nextPoint.x > maxPoint.x )
			maxPoint.x = nextPoint.x;
		if( nextPoint.y > maxPoint.y )
			maxPoint.y = nextPoint.y;
		if( nextPoint.z > maxPoint.z )
			maxPoint.z = nextPoint.z;

		if( nextPoint.x < minPoint.x )
			minPoint.x = nextPoint.x;
		if( nextPoint.y < minPoint.y )
			minPoint.y = nextPoint.y;
		if( nextPoint.z < minPoint.z )
			minPoint.z = nextPoint.z;
	}


	//
	// returns the geometrical center of the box
	//
    math::Vec3d BoundingBox::getCenter( void ) const
	{
		return (minPoint + maxPoint)*0.5f;
	}

	//
	// this utility function checks wether the given point
	// is within the volume descripted by the bounding box
	//
    bool BoundingBox::encloses( const math::Vec3d &point ) const
	{
		// check each dimension
		if( (point.x > minPoint.x)&&(point.x < maxPoint.x)&&
			(point.y > minPoint.y)&&(point.y < maxPoint.y)&&
			(point.z > minPoint.z)&&(point.z < maxPoint.z))
			return true;
		else
			return false;
	}

	//
	// this utility function checks wether the given box
	// is within the volume descripted by the bounding box
	//
    bool BoundingBox::encloses( const math::Vec3d &min, const math::Vec3d &max ) const
	{
		// check each dimension for each point
		if( (min.x >= minPoint.x)&&(min.y >= minPoint.y)&&(min.z >= minPoint.z)&&
			(max.x <= maxPoint.x)&&(max.y <= maxPoint.y)&&(max.z <= maxPoint.z))
			return true;
		else
			return false;
	}
}
