/*---------------------------------------------------------------------



----------------------------------------------------------------------*/
#pragma once

#include "Vec3d.h"

namespace math
{
	//
	//
	// memory storage is row major (which is native to the c++ arrays)
    //     | 0  1  2 |
    // M = | 3  4  5 |
	//     | 6  7  8 |
	//
	// index the matrix with matrix.m[row][column] -> _m12 means: first row, second column
	//
	//           m11 m12 m13
	//           m21 m22 m23
	//           m31 m32 m33
	//
    class Matrix33d
	{
	public:
        Matrix33d();
        ~Matrix33d();
        Matrix33d( const double &_11, const double &_12, const double &_13,
                   const double &_21, const double &_22, const double &_23,
                   const double &_31, const double &_32, const double &_33);

		// convience matrix creation functions
        static Matrix33d                                                                 Zero( void ); // returns the zeromatrix
        static Matrix33d                                                             Identity( void ); // returns the identitymatrix
        static Matrix33d                      RotationMatrix( const Vec3d &axis, const double &angle );  // returns a matrix with a transformation that rotates around a certain axis which starts at the origin

		// public methods
		void                                                                        transpose( void );
		void                                                                           invert( void );

        double                                                                        getDeterminant(); // computes and returns the determinant

		// operators
        bool                                                       operator==( const Matrix33d &rhs );
        bool                                                       operator!=( const Matrix33d &rhs );
		
        bool                                                       operator+=( const Matrix33d &rhs );
        bool                                                       operator-=( const Matrix33d &rhs );

        bool                                                           operator+=( const double &rhs );
        bool                                                           operator-=( const double &rhs );
        bool                                                           operator*=( const double &rhs );
        bool                                                           operator/=( const double &rhs );

		union
		{
			struct
			{
                double _11, _12, _13;
                double _21, _22, _23;
                double _31, _32, _33;
			};
            double m[3][3];
            double ma[9];
		};
	};
}
