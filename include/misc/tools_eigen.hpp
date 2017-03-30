// Copyright © 2017 Thomas Nagler and Thibault Vatter
//
// This file is part of the vinecopulib library and licensed under the terms of
// the MIT license. For a copy, see the LICENSE file in the root directory of
// vinecopulib or https://tvatter.github.io/vinecopulib/.

#pragma once

#include <Eigen/Dense>

//! Tools for working with Eigen types
namespace tools_eigen
{
    //! An `Eigen::Matrix` containing `bool`s (similar to `Eigen::MatrixXd`).
    typedef Eigen::Matrix<bool, Eigen::Dynamic, Eigen::Dynamic> MatrixXb;

    Eigen::Matrix<double, Eigen::Dynamic, 2> swap_cols(
         Eigen::Matrix<double, Eigen::Dynamic, 2> u);
    
    Eigen::VectorXd invert_f(
            const Eigen::VectorXd &x, std::function<Eigen::VectorXd(const Eigen::VectorXd&)> f,
            const double lb = 1e-20,
            const double ub = 1-1e-20,
            int n_iter = 35
    );
    
    Eigen::MatrixXd read_matxd(const char *filename, int max_buffer_size = (int) 1e6);
    Eigen::Matrix<size_t, Eigen::Dynamic, Eigen::Dynamic> read_matxs(
        const char *filename, int max_buffer_size = (int) 1e6);
}