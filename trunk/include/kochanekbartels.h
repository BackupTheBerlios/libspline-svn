/* -----------------------------------------------------------------------------
libspline - Spline library for realtime applications
Copyright (C) 2006  Joachim Klahr

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
------------------------------------------------------------------------------*/
#ifndef __SPLINE_KOCHANEKBARTELS_H__
#define __SPLINE_KOCHANEKBARTELS_H__

#include "hermite.h"

namespace Spline
{
	/*! Kochanek Bartels spline.
	 * \author Joachim Klahr
	 * \version 0.1
	 * \date 2006 */
	class KochanekBartels : public Hermite
	{
	public:
		/*! Calculates the tangents and the length of the Curve.
		* \param controlPoints See Curve::Curve
		* \param amount See Curve::Curve
		* \param tension Higher tension means harder transition between the ControlPoints.
		* \param continuity Controls the continuity.
		* \param bias Controls the direction of the Curve.
		* \sa Curve */
		KochanekBartels(ControlPoint* controlPoints, unsigned int amount,
			            float tension, float continuity, float bias);

		inline virtual ~KochanekBartels();

	private:
		/*! Calculates the tangents.
		 * \sa KochanekBartels::KochanekBartels */
		void calculateTangents(float tension, float continuity, float bias);
	};

	// -------------------------------------------------------------------------
	inline KochanekBartels::~KochanekBartels()
	{
	}
}

#endif
