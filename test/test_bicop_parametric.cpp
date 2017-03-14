// Copyright © 2017 Thomas Nagler and Thibault Vatter
//
// This file is part of the vinecopulib library and licensed under the terms of
// the MIT license. For a copy, see the LICENSE file in the root directory of
// vinecopulib or https://tvatter.github.io/vinecopulib/.

#include "src_test/include/parbicop_test.hpp"
#include "rscript.hpp"

namespace {
    // Test if the C++ implementation of the par_to_tau and tau_to_par is correct
    TYPED_TEST(ParBicopTest, par_to_tau_is_correct) {
        this->setup_parameters();
        std::string command = std::string(RSCRIPT) + "../test/test_bicop_parametric.R";
        command = command + " "  + std::to_string(this->get_n());
        command = command + " "  + std::to_string(this->get_family());
        command = command + " "  + std::to_string(this->get_par());
        command = command + " "  + std::to_string(this->get_par2());
        system(command.c_str());

        if (this->needs_check_) {
            MatXd results = read_matxd("temp");
            VecXd par = this->par_bicop_.get_parameters();
            ASSERT_TRUE(fabs(this->par_bicop_.parameters_to_tau(par) - results(0,0)) < 1e-4);
        }
    }

    // Test if the C++ implementation of the PDF is correct
    TYPED_TEST(ParBicopTest, pdf_is_correct) {
        this->setup_parameters();
        int n = this->get_n();
        if (this->needs_check_) {
            MatXd results = read_matxd("temp");

            // evaluate in C++
            VecXd f = this->par_bicop_.pdf(results.block(0,1,n,2));

            // assert approximate equality
            ASSERT_TRUE(f.isApprox(results.block(0,3,n,1), 1e-4));
        }
    }


    // Test if the C++ implementation of the hfunc1 is correct
    TYPED_TEST(ParBicopTest, hfunc1_is_correct) {
        this->setup_parameters();
        int n = this->get_n();
        if (this->needs_check_) {
            MatXd results = read_matxd("temp");

            // evaluate in C++
            VecXd f = this->par_bicop_.hfunc1(results.block(0,1,n,2));

            // assert approximate equality
            ASSERT_TRUE(f.isApprox(results.block(0,4,n,1), 1e-4));
        }
    }

    // Test if the C++ implementation of the hfunc2 is correct
    TYPED_TEST(ParBicopTest, hfunc2_is_correct) {
        this->setup_parameters();
        int n = this->get_n();
        if (this->needs_check_) {
            MatXd results = read_matxd("temp");

            // evaluate in C++
            VecXd f = this->par_bicop_.hfunc2(results.block(0,1,n,2));

            // assert approximate equality
            ASSERT_TRUE(f.isApprox(results.block(0,5,n,1), 1e-4));
        }
    }

    // Test if the C++ implementation of the hinv1 is correct
    TYPED_TEST(ParBicopTest, hinv1_is_correct) {
        this->setup_parameters();
        int n = this->get_n();
        if (this->needs_check_) {
            MatXd results = read_matxd("temp");

            // evaluate in C++
            VecXd f = this->par_bicop_.hinv1(results.block(0,1,n,2));

            // assert approximate equality
            ASSERT_TRUE(f.isApprox(results.block(0,6,n,1), 1e-4));
        }
    }

    // Test if the C++ implementation of the hinv2 is correct
    TYPED_TEST(ParBicopTest, hinv2_is_correct) {
        this->setup_parameters();
        int n = this->get_n();
        if (this->needs_check_) {
            MatXd results = read_matxd("temp");

            // evaluate in C++
            VecXd f = this->par_bicop_.hinv2(results.block(0,1,n,2));

            // assert approximate equality
            ASSERT_TRUE(f.isApprox(results.block(0,7,n,1), 1e-4));
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
