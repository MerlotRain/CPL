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

using namespace CPL;

TEST(String, Split)
{
    std::string str1 = "Hello,world";
    auto string_list1 = StringHelp::Split(str1.c_str(), ',');
    ASSERT_EQ(string_list1.size(), 2);
    ASSERT_EQ(string_list1[0], "Hello");
    ASSERT_EQ(string_list1[1], "world");

    std::string str2 = "Hello,world,";
    auto string_list2 = StringHelp::Split(str2.c_str(), ',');
    ASSERT_EQ(string_list2.size(), 3);
    ASSERT_EQ(string_list2[0], "Hello");
    ASSERT_EQ(string_list2[1], "world");
    ASSERT_EQ(string_list2[2], "");

    std::string str3 = "";
    auto string_list3 = StringHelp::Split(str3.c_str(), ',');
    ASSERT_EQ(string_list3.size(), 0);
}