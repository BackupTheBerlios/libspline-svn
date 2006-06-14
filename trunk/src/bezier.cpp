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
#include "bezier.h"
#include "splinemath.h"

namespace Spline
{
	// -------------------------------------------------------------------------
	Bezier::Bezier(ControlPoint* controlPoints, unsigned int amount) : Curve(controlPoints, amount)
	{
		calculateLength(1000.0f);
	}

	// -------------------------------------------------------------------------
	void Bezier::getWorldPosition(float* position, float distance)
	{
		getPositionOnSegment(position, distance / mLength, 0);
	}

	// -------------------------------------------------------------------------
	void Bezier::getPositionOnSegment(float* position, float distance, unsigned int segment)
	{
		position[0] = 0;
		position[1] = 0;
		position[2] = 0;

		float b;

		for(unsigned int i = 0; i < mAmount-1; ++i)
		{
			b = getBernsteinValue(distance, i);
			position[0] += mSegments[i]->getBegin()->position.x * b;
			position[1] += mSegments[i]->getBegin()->position.y * b;
			position[2] += mSegments[i]->getBegin()->position.z * b;
		}

		b = getBernsteinValue(distance, mAmount-1);
		position[0] += mSegments[mAmount-2]->getEnd()->position.x * b;
		position[1] += mSegments[mAmount-2]->getEnd()->position.y * b;
		position[2] += mSegments[mAmount-2]->getEnd()->position.z * b;
	}

	// -------------------------------------------------------------------------
	float Bezier::getBernsteinValue(float t, unsigned int i)
	{
		return (Math::faculty(mAmount-1) * Math::pow(t, i) * Math::pow(1.0f-t, mAmount-1-i)) /
			   (Math::faculty(i) * Math::faculty(mAmount-1-i));
	}
}
