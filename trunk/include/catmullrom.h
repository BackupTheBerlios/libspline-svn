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
#ifndef __SPLINE_CATMULLROM_H__
#define __SPLINE_CATMULLROM_H__

#include "cardinal.h"

namespace Spline
{
	/*! A CatmullRom spline works as Cardinal splines with the difference that
	 * you don't got the control of the tangent strength.
	 * \author Joachim Klahr
	 * \version 0.1
	 * \date 2006 */
	class CatmullRom : public Cardinal
	{
	public:
		/*! Invokes the Cardinal contructor with 0.5f as tangentStrength value. */
		inline CatmullRom(ControlPoint* controlPoints, unsigned int amount);

		inline virtual ~CatmullRom();
	};

	// -------------------------------------------------------------------------
	inline CatmullRom::CatmullRom(ControlPoint* controlPoints, unsigned int amount)
		: Cardinal(controlPoints, amount, 0.5f)
	{
	}

	// -------------------------------------------------------------------------
	inline CatmullRom::~CatmullRom()
	{
	}
}

#endif
