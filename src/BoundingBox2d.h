/*---------------------------------------------------------------------

The BoundingBox2d class is a very simple utility class for working with
axis aligned bounding boxes in 2d

----------------------------------------------------------------------*/
#pragma once
#include "Math.h"


namespace math
{
	///
	/// \brief The BoundingBox2d class is a very simple utility class for working
	/// with axis aligned bounding boxes
	///
	struct BoundingBox2d
	{
		BoundingBox2d();                                                        ///< constructor
        BoundingBox2d( math::Vec2d _minPoint, math::Vec2d _maxPoint );          ///< constructor

        math::Vec2d                                        size( void ) const;  ///< returns a vector which represents the dimension in each axis
        void                           extend( const math::Vec2d &nextPoint );  ///< adobts the bounding borders if neccessary so that the given point lies within the bounding box
        math::Vec2d                                   getCenter( void ) const;  ///< returns the geometrical center of the box
        bool                       encloses( const math::Vec2d &point ) const;  ///< this utility function checks wether the given point is within the volume descripted by the bounding box
        bool encloses( const math::Vec2d &min, const math::Vec2d &max ) const;  ///< this utility function checks wether the given box is within the volume descripted by the bounding box

        math::Vec2d                                                  minPoint;  ///< the position of all lowends for each axis
        math::Vec2d                                                  maxPoint;  ///< the position of all highends for each axis
	};
}
