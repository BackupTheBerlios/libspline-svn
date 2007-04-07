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
	void Bezier::getTangent(float* tangent, float distance)
	{
		float resolution = 0.01f;
		float position_a[3];
		float position_b[3];

		getWorldPosition(position_a, distance + resolution);
		getWorldPosition(position_b, distance - resolution);

		position_a[0] -= position_b[0];
		position_a[1] -= position_b[1];
		position_a[2] -= position_b[2];

		Math::normalize(position_a);

		tangent[0] = position_a[0];
		tangent[1] = position_a[1];
		tangent[2] = position_a[2];
	}

	// -------------------------------------------------------------------------
	void Bezier::getPositionOnSegment(float* position, float distance, unsigned int)
	{
		position[0] = 0;
		position[1] = 0;
		position[2] = 0;

		float b;
		unsigned int n = mAmount - 1;

		for(register unsigned int i = 0; i < n; ++i)
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
	void Bezier::getTangentOnSegment(float*, float, unsigned int)
	{
	}

	// -------------------------------------------------------------------------
	float Bezier::getBernsteinValue(float t, unsigned int i)
	{
		unsigned int amount = mAmount - 1;
		return (Math::faculty(amount) * Math::pow(t, i) * Math::pow(1.0f-t, amount-i)) /
			   (Math::faculty(i) * Math::faculty(amount-i));
	}
}
