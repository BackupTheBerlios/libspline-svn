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
#ifndef __SPLINE_CURVE_H__
#define __SPLINE_CURVE_H__

#include "segment.h"

namespace Spline
{
	class ControlPoint;
	class Segment;

	/*! This class is an abstract class that only does the basic set up of a curve.
	* \author Joachim Klahr
	* \version 0.1
	* \date 2006 */
	class Curve
	{
	public:
		/*! Creates all segments.
		 * \param controlPoints Pointer to an array with all control points
		          used to construct the curve.
		 * \param amount The number of control points controlPoints are
		          pointing at. */
		Curve(ControlPoint* controlPoints, unsigned int amount);

		/*! Deletes all segments and control points. */
		virtual ~Curve();

		/*! Sets the position parameter to the world position distance units in
		    on the curve.
		 * \param position Is a float[3] where the elements represents a position
		          coordinate.
		 * \param distance The distance from the beginning of the curve.
		 * \remark If the distance parameter is greater the total length of the
			       curve, position will be set to (0, 0, 0). */
		virtual void getWorldPosition(float* position, float distance) = 0;

		/*! Sets the position parameter to the world position on the specified segment.
		    The distance parameter must be a value between 0 and 1.0.
		 * \param position Is a float[3] where the elements represents a position
			      coordinate.
		 * \param distance The distance from the beginning of the curve.
		 * \param segment Which segment to get the position from. */
		virtual void getPositionOnSegment(float* position,
		                                  float distance,
							 			  unsigned int segment) = 0;

		/*! Sets the tangent parameter to the tangent on the curve distance units in
		    on the curve.
		 * \param tangent Is a float[3] where the elements represents a tangent.
		 * \param distance The distance from the beginning of the curve. */
		virtual void getTangent(float* tangent, float distance) = 0;

		/*! Sets the tangent parameter to the normalized tangent on the segment.
		* \param tangent The normalized tangent
		* \param distance The distance in on the curve where to find the tangent.
		* \param segment Which segment to get the tangent from. */
		virtual void getTangentOnSegment(float* tangent,
										 float distance,
										 unsigned int segment) = 0;

		/*! Calculates the total length of the curve.
		 * \param resolution Higher value means smaller step size which increases the
		          precision on the length of the curve. */
		void calculateLength(float resolution);

		/*! \return The total length of the curve. */
		inline float getLength() const;

		/*! \return The amount of control points. */
		inline unsigned int getNumOfControlPoints() const;

		/*! \return The specified segment from the beginning of the curve. */
		inline Segment* getSegment(unsigned int segment) const;

	protected:
		/*! All segments of the curve. */
		Segment** mSegments;

		/*! All control points of the curve. */
		ControlPoint* mControlPoints;

		/*! The total length of the curve. */
		float mLength;

		/*! The total amount of control points the curve is constructed with. */
		unsigned int mAmount;
	};

	// -------------------------------------------------------------------------
	inline float Curve::getLength() const
	{
		return mLength;
	}

	// -------------------------------------------------------------------------
	inline unsigned int Curve::getNumOfControlPoints() const
	{
		return mAmount;
	}

	// -------------------------------------------------------------------------
	inline Segment* Curve::getSegment(unsigned int segment) const
	{
		return mSegments[segment];
	}
}

#endif
