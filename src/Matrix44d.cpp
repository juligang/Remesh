/*---------------------------------------------------------------------



----------------------------------------------------------------------*/
#include "Matrix44d.h"

#include "Math.h"


namespace math
{
	//
	//
	//
    Matrix44d::Matrix44d()
	{
		_11=_12=_13=_14=
		_21=_22=_23=_24=
		_31=_32=_33=_34=
        _41=_42=_43=_44=0.0;
	}

    Matrix44d::Matrix44d( const double &_11, const double &_12, const double &_13, const double &_14,
                          const double &_21, const double &_22, const double &_23, const double &_24,
                          const double &_31, const double &_32, const double &_33, const double &_34,
                          const double &_41, const double &_42, const double &_43, const double &_44 )
	{
        this->_11=_11; this->_12=_12; this->_13=_13; this->_14=_14;
        this->_21=_21; this->_22=_22; this->_23=_23; this->_24=_24;
        this->_31=_31; this->_32=_32; this->_33=_33; this->_34=_34;
        this->_41=_41; this->_42=_42; this->_43=_43; this->_44=_44;
	}

	//
	// creates the Matrix from 3 rows
	//
    Matrix44d::Matrix44d( const Vec3d &right, const Vec3d &up, const Vec3d &forward )
	{
        this->_11=right.x; this->_12=up.x; this->_13=forward.x; this->_14=0.0;
        this->_21=right.y; this->_22=up.y; this->_23=forward.y; this->_24=0.0;
        this->_31=right.z; this->_32=up.z; this->_33=forward.z; this->_34=0.0;
        this->_41=0.0; this->_42=0.0; this->_43=0.0; this->_44=1.0;
	}


	//
	//
	//
    Matrix44d::~Matrix44d()
	{
	}

	//
	// returns the zeromatrix
	//
    Matrix44d Matrix44d::Zero( void )
	{
        return Matrix44d( 0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0,
                          0.0, 0.0, 0.0, 0.0);
	}

	//
	// returns the identitymatrix
	//
    Matrix44d Matrix44d::Identity( void )
	{
        return Matrix44d( 1.0, 0.0, 0.0, 0.0,
                          0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0,
                          0.0, 0.0, 0.0, 1.0);
	}

	//
    // returns a matrix which defines a rotation about the x axis with the double-specified amount
	//
    Matrix44d Matrix44d::RotationMatrixX( const double &angle )
	{
        double fSin = sinf( angle );
        double fCos = cosf( angle );

        return Matrix44d( 1.0, 0.0, 0.0, 0.0,
                          0.0, fCos, -fSin, 0.0,
                          0.0, fSin, fCos, 0.0,
                          0.0, 0.0, 0.0, 1.0);
	}

	//
    // returns a matrix which defines a rotation about the y axis with the double-specified amount
	//
    Matrix44d Matrix44d::RotationMatrixY( const double &angle )
	{
        double fSin = sinf( angle );
        double fCos = cosf( angle );

        return Matrix44d( fCos, 0.0, fSin, 0.0,
                          0.0, 1.0, 0.0, 0.0,
                          -fSin, 0.0, fCos, 0.0,
                          0.0, 0.0, 0.0, 1.0);
	}

	//
    // returns a matrix which defines a rotation about the z axis with the double-specified amount
	//
    Matrix44d Matrix44d::RotationMatrixZ( const double &angle )
	{
        double fSin = sinf( angle );
        double fCos = cosf( angle );
        return Matrix44d( fCos, -fSin, 0.0, 0.0,
                          fSin, fCos, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0,
                          0.0, 0.0, 0.0, 1.0);
	}

	//
	// returns a matrix with a transformation that rotates around
	// a certain axis which starts at the origin
	//
    Matrix44d Matrix44d::RotationMatrix( const Vec3d &axis, const double &angle )
	{
		// code from Graphics Gems (Glassner, Academic Press, 1990)
        double c = cos( angle );
        double t = 1.0 - c;
        double s = sin( angle );
        double txy = t*axis.x*axis.y;
        double txz = t*axis.x*axis.z;
        double tyz = t*axis.y*axis.z;
        double sx = s*axis.x;
        double sy = s*axis.y;
        double sz = s*axis.z;
        return Matrix44d( t*axis.x*axis.x+c, txy+sz, txz-sy, 0.0,
                          txy-sz, t*axis.y*axis.y+c, tyz+sx, 0.0,
                          txz+sy, tyz-sx, t*axis.z*axis.z+c, 0.0,
                          0.0, 0.0, 0.0, 1.0);
	}

	//
	// returns a matrix which defines a translation of the specified translation vector
	//
    Matrix44d Matrix44d::TranslationMatrix( const Vec3d &translation )
	{
        return Matrix44d( 1.0, 0.0, 0.0, 0.0,
                          0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0,
                          translation.x, translation.y, translation.z, 1.0);
	}

	//
	// returns a matrix which defines a translation of the specified translation vector
	//
    Matrix44d Matrix44d::TranslationMatrix( const double &x, const double &y, const double &z )
	{
        return Matrix44d( 1.0, 0.0, 0.0, 0.0,
                          0.0, 1.0, 0.0, 0.0,
                          0.0, 0.0, 1.0, 0.0,
                          x, y, z, 1.0);
	}

	//
	// returns a matrix which defines a uniform scale
	//
    Matrix44d Matrix44d::ScaleMatrix( const double &uniformScale )
	{
        return Matrix44d( uniformScale, 0.0, 0.0, 0.0,
                          0.0, uniformScale, 0.0, 0.0,
                          0.0, 0.0, uniformScale, 0.0,
                          0.0, 0.0, 0.0, 1.0);
	}

	//
	// returns a matrix which defines a non-uniform scale
	//
    Matrix44d Matrix44d::ScaleMatrix( const double &x, const double &y, const double &z )
	{
        return Matrix44d( x, 0.0, 0.0, 0.0,
                          0.0, y, 0.0, 0.0,
                          0.0, 0.0, z, 0.0,
                          0.0, 0.0, 0.0, 1.0);
	}

	//
	//
	//
    void Matrix44d::rotateX( const double &angle )
	{
		//*this = *this * RotationMatrixX( angle );
		*this = RotationMatrixX( angle ) * *this;
	}

	//
	//
	//
    void Matrix44d::rotateY( const double &angle )
	{
		//*this = *this * RotationMatrixY( angle );
		*this = RotationMatrixY( angle ) * *this;
	}

	//
	//
	//
    void Matrix44d::rotateZ( const double &angle )
	{
		//*this = *this * RotationMatrixZ( angle );
		*this = RotationMatrixZ( angle ) * *this;
	}

	//
	//
	//
    void Matrix44d::translate( const Vec3d &translation )
	{
		//*this = *this * TranslationMatrix( translation );
		*this = TranslationMatrix( translation ) * *this;
	}

	//
	//
	//
    void Matrix44d::translate( const double &x, const double &y, const double &z )
	{
		//*this = *this * TranslationMatrix( x, y, z ) ;
		*this = TranslationMatrix( x, y, z ) * *this;
	}

	//
	// scales the current transform
	//
    void Matrix44d::scale( const double &uniformScale )
	{
		*this = ScaleMatrix( uniformScale ) * *this;
	}

	//
	// scales the current transform non-uniformly
	//
    void Matrix44d::scale( const double &x, const double &y, const double &z )
	{
		*this = ScaleMatrix( x, y, z ) * *this;
	}

	//
	//
	//
    void Matrix44d::transpose( void )
	{
        Matrix44d temp = *this;

		_12 = temp._21;
		_13 = temp._31;
		_14 = temp._41;

		_21 = temp._12;
		_23 = temp._32;
		_24 = temp._42;

		_31 = temp._13;
		_32 = temp._23;
		_34 = temp._43;

		_41 = temp._14;
		_42 = temp._24;
		_43 = temp._34;
	}

	//
	// computes the determinant of a 3x3 matrix after the rule of Sarrus
	//
    inline double Det(	double &f_11, double &f_12, double &f_13,
                        double &f_21, double &f_22, double &f_23,
                        double &f_31, double &f_32, double &f_33 )
	{
		return f_11*f_22*f_33 + f_21*f_32*f_13 + f_31*f_12*f_23 - f_13*f_22*f_31 - f_23*f_32*f_11 - f_33*f_12*f_21;
	}


	//
	//
	//
    void Matrix44d::invert( void )
	{
        double fDet =	_11*Det(	_22, _23, _24,
									_32, _33, _34,
									_42, _43, _44 ) -

						_12*Det(	_21, _23, _24,
									_31, _33, _34,
									_41, _43, _44 ) +

						_13*Det(	_21, _22, _24,
									_31, _32, _34,
									_41, _42, _44 ) -

						_14*Det(	_21, _22, _23,
									_31, _32, _33,
									_41, _42, _43 );

		// determinant must be not zero
        if( fabsf( fDet ) < 0.000000001 )
			// error determinant is zero
			return;

        fDet = 1.0 / fDet;

        Matrix44d mMatrix;

		// Row1
		mMatrix._11 =		   Det(	_22, _23, _24,
									_32, _33, _34,
									_42, _43, _44 );

        mMatrix._12 = -1.0 * Det(	_21, _23, _24,
									_31, _33, _34,
									_41, _43, _44 );

		mMatrix._13 =		   Det(	_21, _22, _24,
									_31, _32, _34,
									_41, _42, _44 );

        mMatrix._14 = -1.0 * Det(	_21, _22, _23,
									_31, _32, _33,
									_41, _42, _43 );


		// Row2
        mMatrix._21 = -1.0 * Det(	_12, _13, _14,
									_32, _33, _34,
									_42, _43, _44 );

		mMatrix._22 =		   Det(	_11, _13, _14,
									_31, _33, _34,
									_41, _43, _44 );

        mMatrix._23 = -1.0 * Det(	_11, _12, _14,
									_31, _32, _34,
									_41, _42, _44 );

		mMatrix._24 =		   Det(	_11, _12, _13,
									_31, _32, _33,
									_41, _42, _43 );


		// Row3
		mMatrix._31 =		   Det(	_12, _13, _14,
									_22, _23, _24,
									_42, _43, _44 );

        mMatrix._32 = -1.0 * Det(	_11, _13, _14,
									_21, _23, _24,
									_41, _43, _44 );

		mMatrix._33 =		   Det(	_11, _12, _14,
									_21, _22, _24,
									_41, _42, _44 );

        mMatrix._34 = -1.0 * Det(	_11, _12, _13,
									_21, _22, _23,
									_41, _42, _43 );


		// Row4
        mMatrix._41 = -1.0 * Det(	_12, _13, _14,
									_22, _23, _24,
									_32, _33, _34 );

		mMatrix._42 =		   Det(	_11, _13, _14,
									_21, _23, _24,
									_31, _33, _34 );

        mMatrix._43 = -1.0 * Det(	_11, _12, _14,
									_21, _22, _24,
									_31, _32, _34 );

		mMatrix._44 =		   Det(	_11, _12, _13,
									_21, _22, _23,
									_31, _32, _33 );

		_11 = fDet*mMatrix._11;
		_12 = fDet*mMatrix._21;
		_13 = fDet*mMatrix._31;
		_14 = fDet*mMatrix._41;

		_21 = fDet*mMatrix._12;
		_22 = fDet*mMatrix._22;
		_23 = fDet*mMatrix._32;
		_24 = fDet*mMatrix._42;

		_31 = fDet*mMatrix._13;
		_32 = fDet*mMatrix._23;
		_33 = fDet*mMatrix._33;
		_34 = fDet*mMatrix._43;

		_41 = fDet*mMatrix._14;
		_42 = fDet*mMatrix._24;
		_43 = fDet*mMatrix._34;
		_44 = fDet*mMatrix._44;
	}

	//
	//
	//
    Vec3d Matrix44d::getRight( const bool &normalized )
	{
        Vec3d right( _11, _12, _13 );

		if( normalized )
			right.normalize();

		return right;
	}

	//
	//
	//
    Vec3d Matrix44d::getUp( const bool &normalized )
	{
        Vec3d up( _21, _22, _23 );

		if( normalized )
			up.normalize();

		return up;
	}

	//
	//
	//
    Vec3d Matrix44d::getDir( const bool &normalized )
	{
        Vec3d dir( _31, _32, _33 );

		if( normalized )
			dir.normalize();

		return dir; 
	}

	//
	//
	//
    Vec3d Matrix44d::getTranslation( void )
	{
        return Vec3d( _41, _42, _43 );
	}

	//
	//
	//
    Matrix44d Matrix44d::getOrientation( void )
	{
        return Matrix44d( _11, _12, _13, 0.0,
                          _21, _22, _23, 0.0,
                          _31, _32, _33, 0.0,
                           0.0, 0.0, 0.0, 1.0 );
	}

    Matrix44d Matrix44d::getTransposed( void )
	{
        return Matrix44d( _11, _21, _31, _41,
                          _12, _22, _32, _42,
                          _13, _23, _33, _43,
                          _14, _24, _34, _44 );
	}

	//
	//
	//
    Matrix44d Matrix44d::getNormalizedOrientation( void )
	{
        static Vec3d g_vRight;
        static Vec3d g_vUp;
        static Vec3d g_vDir;

		g_vRight	= getRight();
		g_vUp		= getUp();
		g_vDir		= getDir();

        return Matrix44d(	g_vRight.x, g_vRight.y, g_vRight.z, 0.0,
                            g_vUp.x,	g_vUp.y, g_vUp.z, 0.0,
                            g_vDir.x,	g_vDir.y, g_vDir.z, 0.0,
                            0.0, 0.0, 0.0, 1.0 );
	}

	//
	//
	//
    void Matrix44d::setRight( const Vec3d &right )
	{
		_11 = right.x;
		_12 = right.y;
		_13 = right.z;
	}

	//
	//
	//
    void Matrix44d::setUp( const Vec3d &up )
	{
		_21 = up.x;
		_22 = up.y;
		_23 = up.z;
	}

	//
	//
	//
    void Matrix44d::setDir( const Vec3d &dir )
	{
		_31 = dir.x;
		_32 = dir.y;
		_33 = dir.z;
	}

	//
	//
	//
    void Matrix44d::setTranslation( const Vec3d &translation )
	{
		_41 = translation.x;
		_42 = translation.y;
		_43 = translation.z;
	}

	//
	//
	//
    bool Matrix44d::operator==( const Matrix44d &rhs )
	{
		if( _11==rhs._11 && _12==rhs._12 && _13==rhs._13 && _14==rhs._14 &&
			_21==rhs._21 && _22==rhs._22 && _23==rhs._23 && _24==rhs._24 &&
			_31==rhs._31 && _32==rhs._32 && _33==rhs._33 && _34==rhs._34 &&
			_41==rhs._41 && _42==rhs._42 && _43==rhs._43 && _44==rhs._44 )
			return true;
		else
			return false; 
	}

	//
	//
	//
    bool Matrix44d::operator!=( const Matrix44d &rhs )
	{
		return !((*this)==rhs);
	}
	
	//
	//
	//
    bool Matrix44d::operator+=( const Matrix44d &rhs )
	{
		_11+=rhs._11;
		_12+=rhs._12;
		_13+=rhs._13;
		_14+=rhs._14;

		_21+=rhs._21;
		_22+=rhs._22;
		_23+=rhs._23;
		_24+=rhs._24;

		_31+=rhs._31;
		_32+=rhs._32;
		_33+=rhs._33;
		_34+=rhs._34;

		_41+=rhs._41;
		_42+=rhs._42;
		_43+=rhs._43;
		_44+=rhs._44;

		return true;
	}

	//
	//
	//
    bool Matrix44d::operator-=( const Matrix44d &rhs )
	{
		_11-=rhs._11;
		_12-=rhs._12;
		_13-=rhs._13;
		_14-=rhs._14;

		_21-=rhs._21;
		_22-=rhs._22;
		_23-=rhs._23;
		_24-=rhs._24;

		_31-=rhs._31;
		_32-=rhs._32;
		_33-=rhs._33;
		_34-=rhs._34;

		_41-=rhs._41;
		_42-=rhs._42;
		_43-=rhs._43;
		_44-=rhs._44;

		return true;
	}

	//
	//
	//
    bool Matrix44d::operator+=( const double &rhs )
	{
		_11+=rhs;
		_12+=rhs;
		_13+=rhs;
		_14+=rhs;

		_21+=rhs;
		_22+=rhs;
		_23+=rhs;
		_24+=rhs;

		_31+=rhs;
		_32+=rhs;
		_33+=rhs;
		_34+=rhs;

		_41+=rhs;
		_42+=rhs;
		_43+=rhs;
		_44+=rhs;

		return true;
	}

	//
	//
	//
    bool Matrix44d::operator-=( const double &rhs )
	{
		_11-=rhs;
		_12-=rhs;
		_13-=rhs;
		_14-=rhs;

		_21-=rhs;
		_22-=rhs;
		_23-=rhs;
		_24-=rhs;

		_31-=rhs;
		_32-=rhs;
		_33-=rhs;
		_34-=rhs;

		_41-=rhs;
		_42-=rhs;
		_43-=rhs;
		_44-=rhs;

		return true;
	}

	//
	//
	//
    bool Matrix44d::operator*=( const double &rhs )
	{
		_11*=rhs;
		_12*=rhs;
		_13*=rhs;
		_14*=rhs;

		_21*=rhs;
		_22*=rhs;
		_23*=rhs;
		_24*=rhs;

		_31*=rhs;
		_32*=rhs;
		_33*=rhs;
		_34*=rhs;

		_41*=rhs;
		_42*=rhs;
		_43*=rhs;
		_44*=rhs;

		return true;
	}


	//
	//
	//
    bool Matrix44d::operator/=( const double &rhs )
	{
		_11/=rhs;
		_12/=rhs;
		_13/=rhs;
		_14/=rhs;

		_21/=rhs;
		_22/=rhs;
		_23/=rhs;
		_24/=rhs;

		_31/=rhs;
		_32/=rhs;
		_33/=rhs;
		_34/=rhs;

		_41/=rhs;
		_42/=rhs;
		_43/=rhs;
		_44/=rhs;

		return true;
	}
}
