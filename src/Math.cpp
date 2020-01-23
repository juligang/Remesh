/*---------------------------------------------------------------------



----------------------------------------------------------------------*/
#include "Math.h"




namespace math
{
	//
	//
	//
	double radToDeg( double rad )
	{
        return rad * 180.0 / M_PIl;
	}

	//
	//
	//
	double degToRad( double degree )
	{
        return degree * M_PIl /180.0;
	}


	/*
	//
	//
	//
    bool rayHitPlaneValues( const Vec3d &planeNormal, const double &planeDistance, Ray &ray, double &hitDistance, Vec3d *hitPoint )
	{
        Vec3d rayOrigin    = ray.getOrigin();
        Vec3d rayDirection = ray.getDirection();//ray.getTarget() - rayOrigin;
        //Vec3d rayOrigin    = Vec3d( 0.0, 10.0, 0.0 );
        //Vec3d rayDirection = Vec3d( 0.0, -1.0, 0.0 );


        double temp = dotProduct( rayDirection, planeNormal );

		// 
        //if( temp >= 0.0 )
		//	return false;

		hitDistance = -(dotProduct( planeNormal, rayOrigin ) + planeDistance) / temp;

		// the point must lie on the raysegment between origin and target to pass the test
        if( (hitDistance > ray.getLength()) || (hitDistance < 0.0) )
			return false;

		if( hitPoint )
			*hitPoint = rayOrigin + hitDistance*rayDirection;

		return true;
	}
	*/

	//
	// computes a intersection between a ray and a plane
	//
	// returns true if an intersection occured, false otherwise
	//
    bool intersectionRayPlane( const Ray3d &ray, const Vec3d &normal, const double &distance, Vec3d &hitPoint )
	{
		// project the ray direction onto the plane normal
        double temp = dotProduct( ray.direction, normal );

		// if result is zero, then the direction is parallel to the plane -> no intersection
		if( !temp )
			return false;

        double hitDistance = -(dotProduct( normal, ray.origin ) + distance) / temp;

		// the point must lie on the raysegment between origin and target to pass the test
        if( (hitDistance >= ray.length) || (hitDistance <= 0.0) )
			return false;

		hitPoint = ray.origin + hitDistance*ray.direction;

		return true;
	}

	//
	// computes a intersection between a ray and another ray
	// algorithm based on Graphics Gems I page 304
	//
	// note: the 2 rays must be coplanar
	//
	// returns true if an intersection occured, false otherwise
	//
    bool intersectionRayRay( const Ray3d &ray1, const Ray3d &ray2, Vec3d &hitPoint )
	{
        math::Vec3d cp = math::crossProduct( ray1.direction, ray2.direction );
        double denom = cp.getSquaredLength();

        if( denom == 0.0 )
			// lines are parallel
			return false;

		// we need to compute s and t to test the line segments

        math::Vec3d c1 = ray2.origin - ray1.origin;

        double t = math::Matrix33d( c1.x, ray2.direction.x, cp.x, c1.y, ray2.direction.y, cp.y, c1.z, ray2.direction.z, cp.z ).getDeterminant() / denom;
        double s = math::Matrix33d( c1.x, ray1.direction.x, cp.x, c1.y, ray1.direction.y, cp.y, c1.z, ray1.direction.z, cp.z ).getDeterminant() / denom;


		// check line segments
        if( (t < 0.0) || (s < 0.0) || (t > ray1.length) || (s > ray2.length) )
			return false;

		// compute intersection point
		hitPoint = ray2.origin + ray2.direction*s;

		// check for coplanarity
		//if( hitPoint != (ray1.origin + ray1.direction*t) )
		//	return false;

		// done
		return true;
	}






	//
	// computes area of an triangle
	//
    double area( const Vec3d &p0, const Vec3d &p1, const Vec3d &p2 )
    {
        double la = (p1 - p0).getLength(); // compute lengths of the triangle sides
        double lb = (p2 - p1).getLength();
        double lc = (p2 - p0).getLength();
        double s = 0.5*( la+lb+lc ); // compute the semiperimeter
        return sqrt( s*(s-la)*(s-lb)*(s-lc) ); // compute the area
    }



	//
	// returns the distance of the given point to the line specified by two points
	//
    double distancePointLine( const math::Vec3d &point, const Vec3d &p1, const Vec3d &p2 )
	{
        math::Vec3d vec = point - p1;
        math::Vec3d direction = math::normalize( p2 - p1 );

		return (vec - dotProduct( vec, direction  ) * direction).getLength();
	}


//	//
//	// computes the distance of a point to a plane
//	//
//    inline double distancePointPlane( const math::Vec3d &point, const Vec3d &normal, const double &distance )
//    {
//        return dotProduct( normal, point ) + distance;
//    }

	//
	// computes the euclidian distance between 2 points in space
	//
    double distance( const Vec3d &p0, const Vec3d &p1 )
	{
		return (p1-p0).getLength();
	}

	//
	// computes the squared euclidian distance between 2 points in space
	//
    inline double squaredDistance( const Vec3d &p0, const Vec3d &p1 )
	{
		return (p1-p0).getSquaredLength();
	}





	//
	// returns the projection of the given point on the normal and distance specified plane
	//
    math::Vec3d projectPointOnPlane( const math::Vec3d &normal, const double &distance, const math::Vec3d &point )
	{
		return point - distancePointPlane( point, normal, distance )*normal;
	}

    math::Vec3d projectPointOnLine( const math::Vec3d &point, const math::Vec3d &p1, const math::Vec3d &p2 )
	{
        math::Vec3d direction = math::normalize( p2 - p1 );

		return p1 + dotProduct( point - p1, direction  ) * direction;
	}

	//
	// creates the matrix which descripes _only_ the orientation which comes from a
	// lookat constrain
	//
	// upVector must be normalized
	//
    Matrix44d createLookAtMatrix( const Vec3d &position, const Vec3d &target, const Vec3d &_up )
	{
        math::Vec3d forward = normalize( target - position );

        math::Vec3d right = crossProduct( _up, forward );

        math::Vec3d up = crossProduct( forward, right );

        return math::Matrix44d( right, up, forward );
	}

	//
	// creates a ViewMatrix from the given polar coordinates
	//
    Matrix44d createMatrixFromPolarCoordinates( const double &azimuth, const double &elevation, const double &distance )
	{
        math::Matrix44d m = math::Matrix44d::Identity();

        m.translate( math::Vec3d( 0.0, 0.0, -distance ) );

		m.rotateX( elevation );
		m.rotateY( azimuth );
		//m.rotateZ( twist );

		return m;


		/*
		m.tr
        vm.Translate( 0.0 , 0.0 , -distance );
		//vm.RotateZ(XMath.Deg2Rad(azimuth)); //TODO
		//vm.RotateX( -XMath.Deg2Rad(elevation) );
		//vm.RotateY( XMath.Deg2Rad(twist) );
		vm.RotateX( XMath.Deg2Rad(elevation) );
		vm.RotateY( XMath.Deg2Rad(twist) );
		vm.RotateZ( XMath.Deg2Rad(azimuth)); //TODO
		vm.Translate( - lx ,- ly , - lz ); 
		*/
		return m;
	}









	//
	//
	//
    double mapValueToRange( const double &sourceRangeMin, const double &sourceRangeMax, const double &targetRangeMin, const double &targetRangeMax, const double &value )
	{
		return (value-sourceRangeMin) / (sourceRangeMax - sourceRangeMin) * (targetRangeMax - targetRangeMin) + targetRangeMin;
	}

	//
	//
	//
    double mapValueTo0_1( const double &sourceRangeMin, const double &sourceRangeMax, const double &value )
	{
		return (value-sourceRangeMin) / (sourceRangeMax - sourceRangeMin);
	}
}
