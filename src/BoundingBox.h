/*---------------------------------------------------------------------

The BoundingBox class is a very simple utility class for working with
axis aligned bounding boxes

----------------------------------------------------------------------*/
#pragma once


#include "Math.h"




namespace math
{
	///
	/// \brief The BoundingBox class is a very simple utility class for working
	/// with axis aligned bounding boxes
	///
	struct BoundingBox
	{
		BoundingBox();                                                          ///< constructor
        BoundingBox( math::Vec3d _minPoint, math::Vec3d _maxPoint );            ///< constructor

        math::Vec3d                                        size( void ) const;  ///< returns a vector which represents the dimension in each axis
        void                           extend( const math::Vec3d &nextPoint );  ///< adobts the bounding borders if neccessary so that the given point lies within the bounding box
        math::Vec3d                                   getCenter( void ) const;  ///< returns the geometrical center of the box
        bool                       encloses( const math::Vec3d &point ) const;  ///< this utility function checks wether the given point is within the volume descripted by the bounding box
        bool encloses( const math::Vec3d &min, const math::Vec3d &max ) const;  ///< this utility function checks wether the given box is within the volume descripted by the bounding box

        math::Vec3d                                                  minPoint;  ///< the position of all lowends for each axis
        math::Vec3d                                                  maxPoint;  ///< the position of all highends for each axis
	};
}
