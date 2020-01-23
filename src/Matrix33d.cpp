/*---------------------------------------------------------------------



----------------------------------------------------------------------*/
#include "Matrix33d.h"

#include "Math.h"


namespace math
{
	//
	//
	//
    Matrix33d::Matrix33d()
	{
		_11=_12=_13=
		_21=_22=_23=
        _31=_32=_33=0.0;
	}

    Matrix33d::Matrix33d( const double &_11, const double &_12, const double &_13,
                          const double &_21, const double &_22, const double &_23,
                          const double &_31, const double &_32, const double &_33)
	{
        this->_11=_11; this->_12=_12; this->_13=_13;
        this->_21=_21; this->_22=_22; this->_23=_23;
		this->_31=_31; this->_32=_32; this->_33=_33;
	}

	//
	//
	//
    Matrix33d::~Matrix33d()
	{
	}

	//
	// returns the zeromatrix
	//
    Matrix33d Matrix33d::Zero( void )
	{
        return Matrix33d( 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0);
	}

	//
	// returns the identitymatrix
	//
    Matrix33d Matrix33d::Identity( void )
	{
        return Matrix33d( 1.0, 0.0, 0.0,
                          0.0, 1.0, 0.0,
                          0.0, 0.0, 1.0);
	}


	//
	// returns a matrix with a transformation that rotates around a certain axis which starts at the origin
	//
	// code from Graphics Gems (Glassner, Academic Press, 1990)
	//
    Matrix33d Matrix33d::RotationMatrix( const Vec3d &axis, const double &angle )
	{
        double c = cos( angle );
        double t = 1.0 - c;
        double s = sin( angle );
        double txy = t*axis.x*axis.y;
        double txz = t*axis.x*axis.z;
        double tyz = t*axis.y*axis.z;
        double sx = s*axis.x;
        double sy = s*axis.y;
        double sz = s*axis.z;
        return Matrix33d( t*axis.x*axis.x+c, txy+sz, txz-sy,
			              txy-sz, t*axis.y*axis.y+c, tyz+sx,
						  txz+sy, tyz-sx, t*axis.z*axis.z+c);
	}


    void Matrix33d::transpose( void )
	{
        Matrix33d temp = *this;

		_11 = temp._11;
		_12 = temp._21;
		_13 = temp._31;

		_21 = temp._12;
		_22 = temp._22;
		_23 = temp._32;

		_31 = temp._13;
		_32 = temp._23;
		_33 = temp._33;
	}


	//
	// computes the determinant of a 2x2 matrix
	//
    inline double Det( double &_11, double &_12,
                      double &_21, double &_22 )
	{
		return _11*_22 - _12*_21;
	}

	//
	// computes and returns the determinant
	//
    double Matrix33d::getDeterminant()
	{
		// rule of sarrus
		return _11*_22*_33 + _21*_32*_13 + _31*_12*_23 - _13*_22*_31 - _23*_32*_11 - _33*_12*_21;
	}



	//
	//
	//
    void Matrix33d::invert( void )
	{
        double det =	_11*Det(_22, _23,
							_32, _33 ) -
					_12*Det(_21, _23,
							_31, _33 ) +
					_13*Det(_21, _22,
							_31, _32 );
		// determinant must be not zero
        if( fabsf( det ) < 0.000000001 )
			// error determinant is zero
			return;

        det = 1.0 / det;

        Matrix33d mMatrix;

		// Row1
		mMatrix._11 = Det( _22, _23,
						   _32, _33 );
		mMatrix._12 = -Det( _12, _13,
						   _32, _33 );
		mMatrix._13 = Det( _12, _13,
						   _22, _23 );
		// Row2
		mMatrix._21 = -Det( _21, _23,
						   _31, _33 );
		mMatrix._22 = Det( _11, _13,
						   _31, _33 );
		mMatrix._23 = -Det( _11, _13,
						   _21, _23 );
		// Row2
		mMatrix._31 = Det( _21, _22,
						   _31, _32 );
		mMatrix._32 = -Det( _11, _12,
						   _31, _32 );
		mMatrix._33 = Det( _11, _12,
						   _21, _22 );

		_11 = det*mMatrix._11;
		_12 = det*mMatrix._12;
		_13 = det*mMatrix._13;

		_21 = det*mMatrix._21;
		_22 = det*mMatrix._22;
		_23 = det*mMatrix._23;

		_31 = det*mMatrix._31;
		_32 = det*mMatrix._32;
		_33 = det*mMatrix._33;
	}

	//
	//
	//
    bool Matrix33d::operator==( const Matrix33d &rhs )
	{
		if( _11==rhs._11 && _12==rhs._12 && _13==rhs._13 &&
			_21==rhs._21 && _22==rhs._22 && _23==rhs._23 &&
			_31==rhs._31 && _32==rhs._32 && _33==rhs._33 )
			return true;
		else
			return false; 
	}

	//
	//
	//
    bool Matrix33d::operator!=( const Matrix33d &rhs )
	{
		return !((*this)==rhs);
	}
	
	//
	//
	//
    bool Matrix33d::operator+=( const Matrix33d &rhs )
	{
		_11+=rhs._11;
		_12+=rhs._12;
		_13+=rhs._13;

		_21+=rhs._21;
		_22+=rhs._22;
		_23+=rhs._23;

		_31+=rhs._31;
		_32+=rhs._32;
		_33+=rhs._33;

		return true;
	}

	//
	//
	//
    bool Matrix33d::operator-=( const Matrix33d &rhs )
	{
		_11-=rhs._11;
		_12-=rhs._12;
		_13-=rhs._13;

		_21-=rhs._21;
		_22-=rhs._22;
		_23-=rhs._23;

		_31-=rhs._31;
		_32-=rhs._32;
		_33-=rhs._33;

		return true;
	}

	//
	//
	//
    bool Matrix33d::operator+=( const double &rhs )
	{
		_11+=rhs;
		_12+=rhs;
		_13+=rhs;

		_21+=rhs;
		_22+=rhs;
		_23+=rhs;

		_31+=rhs;
		_32+=rhs;
		_33+=rhs;
		return true;
	}

	//
	//
	//
    bool Matrix33d::operator-=( const double &rhs )
	{
		_11-=rhs;
		_12-=rhs;
		_13-=rhs;

		_21-=rhs;
		_22-=rhs;
		_23-=rhs;

		_31-=rhs;
		_32-=rhs;
		_33-=rhs;
		return true;
	}

	//
	//
	//
    bool Matrix33d::operator*=( const double &rhs )
	{
		_11*=rhs;
		_12*=rhs;
		_13*=rhs;

		_21*=rhs;
		_22*=rhs;
		_23*=rhs;

		_31*=rhs;
		_32*=rhs;
		_33*=rhs;
		return true;
	}


	//
	//
	//
    bool Matrix33d::operator/=( const double &rhs )
	{
		_11/=rhs;
		_12/=rhs;
		_13/=rhs;

		_21/=rhs;
		_22/=rhs;
		_23/=rhs;

		_31/=rhs;
		_32/=rhs;
		_33/=rhs;
		return true;
	}
}
