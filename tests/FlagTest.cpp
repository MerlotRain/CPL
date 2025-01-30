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

#include <cpl_ports.h>
#include <gtest/gtest.h>

enum TestFlag
{
    FLAG_ONE = 1,
    FLAG_TWO = 2,
    FLAG_THREE = 4,
    FLAG_FOUR = 8,
    FLAG_FIVE = 16,
    FLAG_SIX = 32,
    FLAG_SEVEN = 64,
    FLAG_EIGHT = 128,
    FLAG_NINE = 256,
    FLAG_TEN = 512,
};
CPL_DECLARE_FLAGS(TestFlags, TestFlag)

TEST(Flag, Test1) { TestFlags flags; }