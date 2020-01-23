/*---------------------------------------------------------------------



----------------------------------------------------------------------*/
#pragma once

#include "Vec3d.h"



namespace math
{
	/// \brief matrix class which is specialiced in the usage as transform matrix
	///
	/// Layout of base vectors within matrices
    ///     | Ix  Iy  Iz  0 |
    /// M = | Jx  Jy  Jz  0 |
    ///     | Kx  Ky  Kz  0 |
    ///     | Tx  Ty  Tz  1  |
    /// where I,J and K are the base vectors of |R^3
	///
	/// memory storage is row major (which is native to the c++ arrays)
    ///     | 0  1  2  3 |
    /// M = | 4  5  6  7 |
    ///     | 8  9  10 11 |
    ///     | 12 13 14 15 |
	///
	/// index the matrix with matrix.m[row][column] -> _m12 means: first row, second column
	///
	///              m11 m12 m13 m14
	/// (x y z 1)    m21 m22 m23 m24
	///              m31 m32 m33 m34
	///              m41 m42 m43 m44
	///
	/// matrix multiplication with a vector assumes row vectors which are multiplied on the left side like vector*matrix
	/// this is from how we have layed out our base vectors
	///
	/// In terms of computergraphics the matrix is layed out in the spirit of direct x in terms of vector-multiplication
	/// and basevectors and in terms of memory layout.
	/// Since opengl has layed out its base vectors in a transposed fashion but in addition assumes column-major memory
	/// layout, this matrix can be used for opengl as well.
	///
	///
    class Matrix44d
	{
	public:
        Matrix44d();
        ~Matrix44d();
        Matrix44d( const double &_11, const double &_12, const double &_13, const double &_14,
                   const double &_21, const double &_22, const double &_23, const double &_24,
                   const double &_31, const double &_32, const double &_33, const double &_34,
                   const double &_41, const double &_42, const double &_43, const double &_44 );
        Matrix44d( const Vec3d &right, const Vec3d &up, const Vec3d &forward );

		// convience matrix creation functions
        static Matrix44d                                                                 Zero( void );  ///< returns the zeromatrix
        static Matrix44d                                                             Identity( void );  ///< returns the identitymatrix
        static Matrix44d                                        RotationMatrixX( const double &angle );  ///< returns a matrix which defines a rotation around the x axis with the double-specified amount
        static Matrix44d                                        RotationMatrixY( const double &angle );  ///< returns a matrix which defines a rotation around the y axis with the double-specified amount
        static Matrix44d                                        RotationMatrixZ( const double &angle );  ///< returns a matrix which defines a rotation around the z axis with the double-specified amount
        static Matrix44d                      RotationMatrix( const Vec3d &axis, const double &angle );  ///< returns a matrix with a transformation that rotates around a certain axis which starts at the origin
        static Matrix44d                                TranslationMatrix( const Vec3d &translation );  ///< returns a matrix which defines a translation of the specified translation vector
        static Matrix44d          TranslationMatrix( const double &x, const double &y, const double &z );  ///< returns a matrix which defines a translation of the specified translation vector
        static Matrix44d                                     ScaleMatrix( const double &uniformScale );  ///< returns a matrix which defines a uniform scale
        static Matrix44d                ScaleMatrix( const double &x, const double &y, const double &z );  ///< returns a matrix which defines a non-uniform scale

		// public methods
		void                                                                        transpose( void );
		void                                                                           invert( void );

        Vec3d                                                 getRight( const bool &normalized=true );
        Vec3d                                                    getUp( const bool &normalized=true );
        Vec3d                                                   getDir( const bool &normalized=true );
        Vec3d                                                                  getTranslation( void );

        Matrix44d                                                              getOrientation( void );
        Matrix44d	                                                 getNormalizedOrientation( void );
        Matrix44d                                                               getTransposed( void );

		// convinience functions for low level matrix manipulation
        void                                                           setRight( const Vec3d &right );
        void                                                                 setUp( const Vec3d &up );
        void                                                               setDir( const Vec3d &dir );
        void                                               setTranslation( const Vec3d &translation );

		// convience functions for higher level matrix manipulations
        void                                                            rotateX( const double &angle ); ///< rotates the current transform around the x-axis (angle in radians)
        void                                                            rotateY( const double &angle ); ///< rotates the current transform around the y-axis (angle in radians)
        void                                                            rotateZ( const double &angle ); ///< rotates the current transform around the z-axis (angle in radians)
        void                                                    translate( const Vec3d &translation ); ///< translates the current transform
        void                              translate( const double &x, const double &y, const double &z ); ///< translates the current transform
        void                                                       scale( const double &uniformScale ); ///< scales the current transform uniformly
        void                                  scale( const double &x, const double &y, const double &z ); ///< scales the current transform non-uniformly
        //void rotate( const Vec3d &origin, const Vec3d &axis, const double &angle ); // will multiply the matrix with a transformation that rotates around a certain axis anywhere in space
        //void                      rotate( const Vec3d &axis, const double &angle ); // will multiply the matrix with a transformation that rotates around a certain axis which starts at the origin

		// operators
        bool                                                      operator==( const Matrix44d &rhs );
        bool                                                      operator!=( const Matrix44d &rhs );
		
        bool                                                      operator+=( const Matrix44d &rhs );
        bool                                                      operator-=( const Matrix44d &rhs );

        bool                                                          operator+=( const double &rhs );
        bool                                                          operator-=( const double &rhs );
        bool                                                          operator*=( const double &rhs );
        bool                                                          operator/=( const double &rhs );

		union
		{
			struct
			{
                double _11, _12, _13, _14;
                double _21, _22, _23, _24;
                double _31, _32, _33, _34;
                double _41, _42, _43, _44;
			};
            double m[4][4];
            double ma[16];
		};
	};
}
