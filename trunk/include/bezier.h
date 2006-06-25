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
#ifndef __SPLINE_BEZIER_H__
#define __SPLINE_BEZIER_H__

#include "curve.h"

namespace Spline
{
	/*! Bezier spline.
	* \author Joachim Klahr
	* \version 0.1
	* \date 2006 */
	class Bezier : public Curve
	{
	public:
		Bezier(ControlPoint* controlPoints, unsigned int amount);

		inline ~Bezier();

		virtual void getWorldPosition(float* position, float distance);

		virtual void getTangent(float* tangent, float distance);

	private:
		virtual void getPositionOnSegment(float* position,
										  float distance,
										  unsigned int segment);

		virtual void getTangentOnSegment(float* tangent,
										 float distance,
										 unsigned int segment);

		/*! Bernstein polynomial. */
		float getBernsteinValue(float t, unsigned int i);
	};

	// -------------------------------------------------------------------------
	inline Bezier::~Bezier()
	{
	}
}

#endif
