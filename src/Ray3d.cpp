/*---------------------------------------------------------------------



----------------------------------------------------------------------*/
#include "Math.h"







namespace math
{


	//
	// constructor
	//
	Ray3d::Ray3d()
	{
	}

	//
	// constructor
	//
    Ray3d::Ray3d( const math::Vec3d &origin, const math::Vec3d &direction, const double &length )
	{
		this->origin = origin;
		this->direction = direction;
		this->length = length;
	}

	//
	// constructor
	//
    Ray3d::Ray3d( const math::Vec3d &origin, const math::Vec3d &target )
	{
		this->direction = target - origin;
		this->origin = origin;
		this->length = direction.getLength();
		this->direction.normalize();
	}

	//
	// returns origin+direction*length
	//
    math::Vec3d Ray3d::getTarget()
	{
		return origin + direction*length;
	}

}
