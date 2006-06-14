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
#ifndef __SPLINE_SEGMENT_H__
#define __SPLINE_SEGMENT_H__

#ifndef NULL
#define NULL 0
#endif

#define SPLINE_SAFE_DELETE(p)       { if(p) { delete (p); (p) = NULL; }}
#define SPLINE_SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p) = NULL; }}

namespace Spline
{
	/*! A control point consists of a position and a tangent which are
	    represented by two structs.
	 * \author Joachim Klahr
	 * \version 0.1
	 * \date 2006 */
	class ControlPoint
	{
	public:
		/*! Position coordinate. */
		struct 
		{
			float x, y, z;
		}position;

		/*! Tangent coordinate. */
		struct 
		{
			float x, y, z;
		}tangent;
	};

	/*! A segment is a part of a Curve. It consist of two ControlPoints. Segments
	    are sharing ControlPoints. A segment is a thin class and does not do anything
		by itself. It got some set function that are used by the class that creates
		the segment. */
	class Segment
	{
	public:
		/*! Initializes the length and its length from the beginning of the curve
		    to 0. */
		inline Segment();

		inline ~Segment();

		/*! Sets a begin ControlPoint.
		 * \param begin Pointer to a ControlPoint. */
		inline void setBegin(ControlPoint* begin);

		/*! Sets an end ControlPoint.
		 * \param end Pointer to a ControlPoint. */
		inline void setEnd(ControlPoint* end);

		/*! Sets a begin tangent.
		 * \param tangent Pointer to an array consisting of three elements (x, y, z). */
		inline void setBeginTangent(float* tangent);

		/*! Sets an end tangent.
		 * \param tangent Pointer to an array consisting of three elements (x, y, z). */
		inline void setEndTangent(float* tangent);

		/*! Sets the total length of the segment.
		 * \param length The length of the segment. */
		inline void setLength(float length);

		/*! Sets the total length from the beginning of the curve to the beginning
		    of the segment.
		 * \param length The length from the beginning of the curve to the beginning of
		          the segment. */
		inline void setLengthFromBeginning(float length);

		/*! Returns a pointer to the segment's begin ControlPoint. */
		inline ControlPoint* getBegin() const;

		/*! Returns a pointer to the segment's end ControlPoint. */
		inline ControlPoint* getEnd() const;

		/*! Returns the total length. */
		inline float getLength() const;

		/*! Returns the total length from the beginning of the curve, to the beginning
		    of the segment. */
		inline float getLengthFromBeginning() const;

	private:
		/*! Pointer to a ControlPoint which represents the begin ControlPoint of the Curve. */
		ControlPoint* mBegin;

		/*! Pointer to a ControlPoint which represents the end ControlPoint of the Curve. */
		ControlPoint* mEnd;

		/*! The total length of the Segment. */
		float mLength;

		/*! The length from the beginning of the Curve to the beginning of the Segment. */
		float mLengthFromBeginning;
	};

	// -------------------------------------------------------------------------
	inline Segment::Segment() : mLength(0), mLengthFromBeginning(0)
	{
	}

	// -------------------------------------------------------------------------
	inline Segment::~Segment()
	{
	}

	// -------------------------------------------------------------------------
	inline void Segment::setBegin(ControlPoint* begin)
	{
		mBegin = begin;
	}

	// -------------------------------------------------------------------------
	inline void Segment::setEnd(ControlPoint* end)
	{
		mEnd = end;
	}

	// -------------------------------------------------------------------------
	inline void Segment::setBeginTangent(float* tangent)
	{
		mBegin->tangent.x = tangent[0];
		mBegin->tangent.y = tangent[1];
		mBegin->tangent.z = tangent[2];
	}

	// -------------------------------------------------------------------------
	inline void Segment::setEndTangent(float* tangent)
	{
		mEnd->tangent.x = tangent[0];
		mEnd->tangent.y = tangent[1];
		mEnd->tangent.z = tangent[2];
	}

	// -------------------------------------------------------------------------
	inline void Segment::setLength(float length)
	{
		mLength = length;
	}

	// -------------------------------------------------------------------------
	inline void Segment::setLengthFromBeginning(float length)
	{
		mLengthFromBeginning = length;
	}

	// -------------------------------------------------------------------------
	inline ControlPoint* Segment::getBegin() const
	{
		return mBegin;
	}

	// -------------------------------------------------------------------------
	inline ControlPoint* Segment::getEnd() const
	{
		return mEnd;
	}

	// -------------------------------------------------------------------------
	inline float Segment::getLength() const
	{
		return mLength;
	}

	// -------------------------------------------------------------------------
	inline float Segment::getLengthFromBeginning() const
	{
		return mLengthFromBeginning;
	}
}

#endif
