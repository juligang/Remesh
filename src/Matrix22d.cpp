/*---------------------------------------------------------------------



----------------------------------------------------------------------*/
#include "Matrix22d.h"
#include "Math.h"


namespace math
{
	//
	//
	//
    Matrix22d::Matrix22d()
	{
		_11=_12=
        _21=_22=0.0;
	}

    Matrix22d::Matrix22d( const double &_11, const double &_12,
                          const double &_21, const double &_22 )
	{
        this->_11=_11; this->_12=_12;
        this->_21=_21; this->_22=_22;
	}

	//
	//
	//
    Matrix22d::~Matrix22d()
	{
	}

	//
	// returns the zeromatrix
	//
    Matrix22d Matrix22d::Zero( void )
	{
        return Matrix22d( 0.0, 0.0,
                          0.0, 0.0);
	}

	//
	// returns the identitymatrix
	//
    Matrix22d Matrix22d::Identity( void )
	{
        return Matrix22d( 1.0, 0.0,
                          0.0, 1.0);
	}

	//
    // returns a matrix which defines a rotation with the double-specified amount (in radians)
	//
    Matrix22d Matrix22d::RotationMatrix( const double &angle )
	{
        double fSin = sinf( angle );
        double fCos = cosf( angle );
        return Matrix22d( fCos, -fSin,
			              fSin, fCos );
	}

	//
	//
	//
    void Matrix22d::transpose( void )
	{
        Matrix22d temp = *this;

		_11 = temp._11;
		_12 = temp._21;

		_21 = temp._12;
		_22 = temp._22;
	}


    void Matrix22d::invert( void )
	{
		// a b
		// c d
		//Then the inverse is 1/(ad-cb) * d -b-c a
        //double c = 1.0/( _11*_22 - _21*_12 );
        //*this = Matrix22d( c*_22, -c*_12, -c*_21, c*_11 );
	}

	//
	//
	//
    bool Matrix22d::operator==( const Matrix22d &rhs )
	{
		if( _11==rhs._11 && _12==rhs._12 &&
			_21==rhs._21 && _22==rhs._22 )
			return true;
		else
			return false; 
	}

	//
	//
	//
    bool Matrix22d::operator!=( const Matrix22d &rhs )
	{
		return !((*this)==rhs);
	}
	
	//
	//
	//
    bool Matrix22d::operator+=( const Matrix22d &rhs )
	{
		_11+=rhs._11;
		_12+=rhs._12;


		_21+=rhs._21;
		_22+=rhs._22;

		return true;
	}

	//
	//
	//
    bool Matrix22d::operator-=( const Matrix22d &rhs )
	{
		_11-=rhs._11;
		_12-=rhs._12;


		_21-=rhs._21;
		_22-=rhs._22;

		return true;
	}

	//
	//
	//
    bool Matrix22d::operator+=( const double &rhs )
	{
		_11+=rhs;
		_12+=rhs;


		_21+=rhs;
		_22+=rhs;

		return true;
	}

	//
	//
	//
    bool Matrix22d::operator-=( const double &rhs )
	{
		_11-=rhs;
		_12-=rhs;

		_21-=rhs;
		_22-=rhs;

		return true;
	}

	//
	//
	//
    bool Matrix22d::operator*=( const double &rhs )
	{
		_11*=rhs;
		_12*=rhs;

		_21*=rhs;
		_22*=rhs;

		return true;
	}


	//
	//
	//
    bool Matrix22d::operator/=( const double &rhs )
	{
		_11/=rhs;
		_12/=rhs;

		_21/=rhs;
		_22/=rhs;

		return true;
	}
}
