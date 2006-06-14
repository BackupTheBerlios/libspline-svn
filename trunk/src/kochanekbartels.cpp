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
#include "kochanekbartels.h"

namespace Spline
{
	// -------------------------------------------------------------------------
	KochanekBartels::KochanekBartels(ControlPoint* controlPoints, unsigned int amount,
		                             float tension, float continuity, float bias) : Hermite(controlPoints, amount)
	{
		calculateTangents(tension, continuity, bias);
		calculateLength(1000.0f);
	}

	// -------------------------------------------------------------------------
	void KochanekBartels::calculateTangents(float tension, float continuity, float bias)
	{
		float positionA[3];
		float positionB[3];
		float a, b;

		positionA[0] = mSegments[0]->getEnd()->position.x - mSegments[0]->getBegin()->position.x;
		positionA[1] = mSegments[0]->getEnd()->position.y - mSegments[0]->getBegin()->position.y;
		positionA[2] = mSegments[0]->getEnd()->position.z - mSegments[0]->getBegin()->position.z;
		mSegments[0]->setBeginTangent(positionA);

		// REWRITTEN WITHOUT TESTED
		for(unsigned int i = 0; i < mAmount-2; ++i)
		{
			positionA[0] = mSegments[i]->getEnd()->position.x - mSegments[i]->getBegin()->position.x;
			positionA[1] = mSegments[i]->getEnd()->position.y - mSegments[i]->getBegin()->position.y;
			positionA[2] = mSegments[i]->getEnd()->position.z - mSegments[i]->getBegin()->position.z;

			positionB[0] = mSegments[i+1]->getEnd()->position.x - mSegments[i+1]->getBegin()->position.x;
			positionB[1] = mSegments[i+1]->getEnd()->position.y - mSegments[i+1]->getBegin()->position.y;
			positionB[2] = mSegments[i+1]->getEnd()->position.z - mSegments[i+1]->getBegin()->position.z;

			a = 0.5f * (1.0f-tension) * (1.0f+continuity) * (1.0f+bias);
			b = 0.5f * (1.0f-tension) * (1.0f-continuity) * (1.0f-bias);

			positionA[0] *= a; positionA[1] *= a; positionA[2] *= a;
			positionB[0] *= b; positionB[1] *= b; positionB[2] *= b;
			positionA[0] += positionB[0]; positionA[1] += positionB[1]; positionA[2] += positionB[2];

			mSegments[i]->setEndTangent(positionA);
		}

		positionA[0] = mSegments[mAmount-2]->getBegin()->tangent.x;
		positionA[1] = mSegments[mAmount-2]->getBegin()->tangent.y;
		positionA[2] = mSegments[mAmount-2]->getBegin()->tangent.z;
		mSegments[mAmount-2]->setEndTangent(positionA);

	}
}
