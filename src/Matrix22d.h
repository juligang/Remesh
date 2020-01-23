/*---------------------------------------------------------------------



----------------------------------------------------------------------*/
#pragma once



namespace math
{
	//
	//
	// memory storage is row major (which is native to the c++ arrays)
    //     | 0  1  |
    // M = | 2  3  |
	//
	// index the matrix with matrix.m[row][column] -> _m12 means: first row, second column
	//
	//           m11 m12
	//           m21 m22
	//
	//
    class Matrix22d
	{
	public:
        Matrix22d();
        ~Matrix22d();
        Matrix22d( const double &_11, const double &_12,
                   const double &_21, const double &_22 );

		// convience matrix creation functions
        static Matrix22d                                                                 Zero( void );  // returns the zeromatrix
        static Matrix22d                                                             Identity( void );  // returns the identitymatrix
        static Matrix22d                                         RotationMatrix( const double &angle );  // returns a matrix which defines a rotation with the double-specified amount (in radians)

		// public methods
		void                                                                        transpose( void );
		void                                                                           invert( void );

		// operators
        bool                                                      operator==( const Matrix22d &rhs );
        bool                                                      operator!=( const Matrix22d &rhs );
		
        bool                                                      operator+=( const Matrix22d &rhs );
        bool                                                      operator-=( const Matrix22d &rhs );

        bool                                                          operator+=( const double &rhs );
        bool                                                          operator-=( const double &rhs );
        bool                                                          operator*=( const double &rhs );
        bool                                                          operator/=( const double &rhs );

		union
		{
			struct
			{
                double _11, _12;
                double _21, _22;
			};
            double m[2][2];
            double ma[4];
		};
	};
}
