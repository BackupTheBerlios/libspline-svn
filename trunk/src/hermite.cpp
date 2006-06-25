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
#include "hermite.h"
#include "segment.h"
#include "splinemath.h"

namespace Spline
{
	// -------------------------------------------------------------------------
	Hermite::Hermite(ControlPoint* controlPoints, unsigned int amount)
		: Curve(controlPoints, amount)
	{
	}

	// -------------------------------------------------------------------------
	void Hermite::getWorldPosition(float* position, float distance)
	{
		unsigned int segment = 0;

		do 
		{
			if(segment > (mAmount - 2))
			{
				getPositionOnSegment(position, mSegments[mAmount-2]->getLengthFromBeginning() / mSegments[mAmount-2]->getLength(), mAmount-2);
				return;
			}

			if((mSegments[segment]->getLengthFromBeginning() + mSegments[segment]->getLength()) >= distance)
				break;
		}while(++segment);

		getPositionOnSegment(position, (distance - mSegments[segment]->getLengthFromBeginning()) / mSegments[segment]->getLength(), segment);
	}

	// -------------------------------------------------------------------------
	void Hermite::getTangent(float* tangent, float distance)
	{
		unsigned int segment = 0;

		do 
		{
			if(segment > (mAmount - 2))
			{
				getTangentOnSegment(tangent, mSegments[mAmount-2]->getLengthFromBeginning() / mSegments[mAmount-2]->getLength(), mAmount-2);
				return;
			}

			if((mSegments[segment]->getLengthFromBeginning() + mSegments[segment]->getLength()) >= distance)
				break;
		}while(++segment);

		getTangentOnSegment(tangent, (distance - mSegments[segment]->getLengthFromBeginning()) / mSegments[segment]->getLength(), segment);	
	}

	// -------------------------------------------------------------------------
	void Hermite::getPositionOnSegment(float* position,	float distance,	unsigned int segment)
	{
		float fH1 = 2.0f * distance*distance*distance - 3.0f * distance*distance + 1.0f;
		float fH2 = distance*distance*distance - 2.0f * distance*distance + distance;
		float fH3 = distance*distance*distance - distance*distance;
		float fH4 = -2.0f * distance*distance*distance + 3.0f * distance*distance;

		ControlPoint* begin = mSegments[segment]->getBegin();
		ControlPoint* end   = mSegments[segment]->getEnd();

		position[0] = begin->position.x * fH1 +
			begin->tangent.x  * fH2 +
			end->tangent.x    * fH3 +
			end->position.x   * fH4;
		position[1] = begin->position.y * fH1 +
			begin->tangent.y  * fH2 +
			end->tangent.y    * fH3 +
			end->position.y   * fH4;
		position[2] = begin->position.z * fH1 +
			begin->tangent.z  * fH2 +
			end->tangent.z    * fH3 +
			end->position.z   * fH4;
	}

	// -------------------------------------------------------------------------
	void Hermite::getTangentOnSegment(float* tangent, float distance, unsigned int segment)
	{
		float fH1 = 6.0f * distance*distance - 6.0f * distance;
		float fH2 = 3.0f * distance*distance - 4.0f * distance + 1.0f;
		float fH3 = 3.0f * distance*distance - 2.0f * distance;
		float fH4 = -6.0f * distance*distance + 6.0f * distance;

		ControlPoint* begin = mSegments[segment]->getBegin();
		ControlPoint* end   = mSegments[segment]->getEnd();

		tangent[0] = begin->position.x * fH1 +
			begin->tangent.x  * fH2 +
			end->tangent.x    * fH3 +
			end->position.x   * fH4;
		tangent[1] = begin->position.y * fH1 +
			begin->tangent.y  * fH2 +
			end->tangent.y    * fH3 +
			end->position.y   * fH4;
		tangent[2] = begin->position.z * fH1 +
			begin->tangent.z  * fH2 +
			end->tangent.z    * fH3 +
			end->position.z   * fH4;

		Math::normalize(tangent);
	}
}
