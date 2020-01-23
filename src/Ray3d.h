/*---------------------------------------------------------------------



----------------------------------------------------------------------*/
#pragma once
#include "Vec3d.h"




namespace math
{
	///
	/// \brief a class which holds an origin and a target and is used by intersection routines
	///
	class Ray3d
	{
	public:
		Ray3d();                                                                               // constructor
        Ray3d( const math::Vec3d &origin, const math::Vec3d &direction, const double &length ); // constructor
        Ray3d( const math::Vec3d &origin, const math::Vec3d &target );                         // constructor

        math::Vec3d                                                               getTarget(); // returns origin+direction*length

        math::Vec3d                                                                    origin; // point in space where the ray originates from
        math::Vec3d                                                                 direction; // normalized direction of the ray
        double                                                                          length; // length of the ray -> some sort of maximum travel distance
	};

}
