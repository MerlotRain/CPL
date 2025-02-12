/**
 * CPL - Common Portability Library
 *
 * Copyright (C) 2024 Merlot.Rain
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "cpl_version.h"

#include "cpl_stringhelp.h"

#include "cpl_atomic.h"
#include "cpl_byteendian.h"
#include "cpl_datetime.h"
#include "cpl_delegate.h"
#include "cpl_flags.h"

#include "cpl_mathhelp.h"
#include "cpl_memorymanager.h"
#include "cpl_object.h"

#include "cpl_any.h"

#include <algorithm>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>