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
#ifndef __SPLINE_MATH_H__
#define __SPLINE_MATH_H__

#ifndef _MSC_VER
#include <cmath>
#endif

namespace Spline
{
	namespace Math
	{
		// ---------------------------------------------------------------------
		static inline float sqrtf(float x)
		{
#ifndef _MSC_VER
			return ::sqrt(x);
#else
			__asm
			{
				fld x
				fsqrt
			}
#endif
		}

		// ---------------------------------------------------------------------
		static inline float getLength(const float* v)
		{
			float vec[4] = {v[0], v[1], v[2], 0};

			vec[0] *= vec[0];
			vec[1] *= vec[1];
			vec[2] *= vec[2];

			return sqrtf(vec[0] + vec[1] + vec[2]);
		}

		// ---------------------------------------------------------------------
		static inline unsigned int faculty(unsigned int x)
		{
			if(x == 0)
				return 1;

			unsigned int ans = 1;

			do 
			{
				ans *= x;
			}while(--x);

			return ans;
		}

		// ---------------------------------------------------------------------
		static inline float pow(float x, unsigned int n)
		{
			if(n == 0)
				return 1.0f;
			if(n == 1)
				return x;

			--n;

			float m = x;

			do
			{
				x *= m;
			}while(--n);

			return x;
		}

		// ---------------------------------------------------------------------
		static inline void normalize(float* v)
		{
			float length = getLength(v);

			v[0] /= length;
			v[1] /= length;
			v[2] /= length;
		}
	}
}

#endif
