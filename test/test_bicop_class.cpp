/*
Copyright 2016 Thibault Vatter, Thomas Nagler

This file is part of vinecopulib.

vinecopulib is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

vinecopulib is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with vinecopulib.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "gtest/gtest.h"
#include "include/bicop.hpp"

namespace {
    // Test if the C++ implementation of the par_to_tau and tau_to_par is correct
    TEST(bicop_class, creates_right_copula) {
        BicopPtr bicop;
        bicop = Bicop::create(1, VecXd::Zero(1), 90);
        EXPECT_EQ(bicop->get_family(), 1);
        EXPECT_EQ(bicop->get_rotation(), 90);
        EXPECT_EQ(bicop->get_parameters(), VecXd::Zero(1));
    }
    
    TEST(bicop_class, catches_wrong_parameter_size) {
        BicopPtr bicop;
        EXPECT_ANY_THROW(Bicop::create(0, VecXd::Zero(1), 0));
        EXPECT_ANY_THROW(Bicop::create(1, VecXd::Zero(0), 0));
        EXPECT_ANY_THROW(Bicop::create(2, VecXd::Zero(1), 0));
        EXPECT_ANY_THROW(Bicop::create(3, VecXd::Zero(2), 0));
        EXPECT_ANY_THROW(Bicop::create(4, VecXd::Zero(0), 0));
        EXPECT_ANY_THROW(Bicop::create(5, VecXd::Zero(2), 0));
        EXPECT_ANY_THROW(Bicop::create(6, VecXd::Zero(0), 0));
        EXPECT_ANY_THROW(Bicop::create(1001, VecXd::Zero(1), 0));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
