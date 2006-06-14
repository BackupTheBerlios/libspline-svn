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
#include "cardinal.h"

namespace Spline
{
	// -------------------------------------------------------------------------
	Cardinal::Cardinal(ControlPoint* controlPoints, unsigned int amount, float tangentStrength) : Hermite(controlPoints, amount)
	{
		calculateTangents(tangentStrength);
		calculateLength(1000.0f);
	}

	// -------------------------------------------------------------------------
	void Cardinal::calculateTangents(float strength)
	{
		float tangent[3];
		tangent[0] = mSegments[0]->getEnd()->position.x - mSegments[0]->getBegin()->position.x;
		tangent[1] = mSegments[0]->getEnd()->position.y - mSegments[0]->getBegin()->position.y;
		tangent[2] = mSegments[0]->getEnd()->position.z - mSegments[0]->getBegin()->position.z;
		mSegments[0]->setBeginTangent(tangent);

		for(unsigned int i = 0; i < mAmount-2; ++i)
		{
			tangent[0] = strength * (mSegments[i+1]->getEnd()->position.x - mSegments[i]->getBegin()->position.x);
			tangent[1] = strength * (mSegments[i+1]->getEnd()->position.y - mSegments[i]->getBegin()->position.y);
			tangent[2] = strength * (mSegments[i+1]->getEnd()->position.z - mSegments[i]->getBegin()->position.z);
			mSegments[i]->setEndTangent(tangent);
		}

		tangent[0] = mSegments[mAmount-2]->getBegin()->tangent.x;
		tangent[1] = mSegments[mAmount-2]->getBegin()->tangent.y;
		tangent[2] = mSegments[mAmount-2]->getBegin()->tangent.z;
		mSegments[mAmount-2]->setEndTangent(tangent);
	}
}
