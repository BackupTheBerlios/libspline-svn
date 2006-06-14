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
#ifndef __SPLINE_CARDINAL_H__
#define __SPLINE_CARDINAL_H__	

#include "hermite.h"

namespace Spline
{
	/*! A Cardinal spline is an instance of the Hermite spline. Using a Cardinal
	    spline, you got the possibility to set the strength of the tangents. If
		you want the tangent to be automatically generated you should use the
		CatmullRom spline instead.
	 * \author Joachim Klahr
	 * \version 0.1
	 * \date 2006 */
	class Cardinal : public Hermite
	{
	public:
		/*! Calculates the tangents and the length of the Curve.
		 * \param controlPoints See Curve::Curve
		 * \param amount See Curve::Curve
		 * \param tangentStrength Determines how much the tangents affects the Curve's shape.
		 * \sa Curve */
		Cardinal(ControlPoint* controlPoints, unsigned int amount, float tangentStrength);

		inline virtual ~Cardinal();

	private:
		/*! Calculates the tangents.
		 * \param strength Value that determines how much the tangents should
		          affect the Curve. */
		void calculateTangents(float strength);
	};

	// -------------------------------------------------------------------------
	inline Cardinal::~Cardinal()
	{
	}
}

#endif
