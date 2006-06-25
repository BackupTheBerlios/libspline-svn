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
#include "curve.h"
#include "segment.h"
#include "splinemath.h"

namespace Spline
{
	// -------------------------------------------------------------------------
	Curve::Curve(ControlPoint* controlPoints, unsigned int amount) : mLength(0)
	{
		mAmount = amount;

		mSegments = new Segment*[mAmount-1];

		mSegments[0] = new Segment();
		mSegments[0]->setBegin(&controlPoints[0]);
		mSegments[0]->setEnd(&controlPoints[1]);

		for(unsigned int i = 1; i < mAmount-1; ++i)
		{
			mSegments[i] = new Segment();
			mSegments[i]->setBegin(&controlPoints[i]);
			mSegments[i]->setEnd(&controlPoints[i+1]);
		}
	}

	// -------------------------------------------------------------------------
	Curve::~Curve()
	{
		mAmount -= 2;
		do
		{
			SPLINE_SAFE_DELETE(mSegments[mAmount]);
		}while(mAmount--);

		SPLINE_SAFE_DELETE_ARRAY(mSegments);
	}

	// -------------------------------------------------------------------------
	void Curve::calculateLength(float resolution)
	{
		float positionA[3];
		float positionB[3];

		float stepLength = 1.0f / resolution;

		for(unsigned int i = 0; i < mAmount-1; ++i)
		{
			float segmentLength = 0;

			for(float j = 0; j < 1.0f; j += stepLength)
			{
				if(j > (1.0f - stepLength))
					j = 1.0f - stepLength;

				getPositionOnSegment(positionA, j + stepLength, i);
				getPositionOnSegment(positionB, j, i);
				positionA[0] -= positionB[0];
				positionA[1] -= positionB[1];
				positionA[2] -= positionB[2];

				segmentLength += Math::getLength(positionA);
			}

			mSegments[i]->setLength(segmentLength);
			mSegments[i]->setLengthFromBeginning(mLength);

			mLength += segmentLength;
		}
	}
}
