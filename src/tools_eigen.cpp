// Copyright © 2017 Thomas Nagler and Thibault Vatter
//
// This file is part of the vinecopulib library and licensed under the terms of
// the MIT license. For a copy, see the LICENSE file in the root directory of
// vinecopulib or https://tvatter.github.io/vinecopulib/.

#include <iostream>
#include <fstream>

#include "tools_eigen.hpp"

//! Numerical inversion of a function
//!
//! Computes the inverse \f$f^{-1}\f$ of a function \f$f\f$ by the bisection
//! method.
//!
//! @param x evaluation points.
//! @param f the function to invert.
//! @param lb lower bound.
//! @param ub upper bound.
//! @param n_iter the number of iterations for the bisection (defaults to 35,
//! guaranteeing an accuracy of 0.5^35 ~= 6e-11).
//!
//! @return f^{-1}(x).
VecXd invert_f(const VecXd& x, std::function<VecXd(const VecXd&)> f, const double lb, const double ub, int n_iter)
{
    VecXd xl = VecXd::Constant(x.size(), lb);
    VecXd xh = VecXd::Constant(x.size(), ub);
    VecXd x_tmp = x;
    for (int iter = 0; iter < n_iter; ++iter) {
        x_tmp = (xh + xl) / 2.0;
        VecXd fm = f(x_tmp) - x;
        xl = (fm.array() < 0).select(x_tmp, xl);
        xh = (fm.array() < 0).select(xh, x_tmp);
    }

    return x_tmp;
}

MatXi read_matxi(const char *filename, int max_buffer_size)
{
    MatXd temp = read_matxd(filename, max_buffer_size);
    MatXi output = temp.cast <int> ();
    return output;
}

MatXd read_matxd(const char *filename, int max_buffer_size)
{
    using namespace std;

    int cols = 0, rows = 0;
    double* buff = new double[max_buffer_size];

    // Read numbers from file into buffer.
    ifstream infile;
    infile.open(filename);
    while (! infile.eof())
    {
        string line;
        getline(infile, line);

        int temp_cols = 0;
        stringstream stream(line);
        while(! stream.eof())
            stream >> buff[cols*rows+temp_cols++];

        if (temp_cols == 0)
            continue;

        if (cols == 0)
            cols = temp_cols;

        rows++;
    }

    infile.close();

    rows--;

    // Populate matrix with numbers.
    MatXd result(rows,cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result(i,j) = buff[ cols*i+j ];

    delete [] buff;
    return result;
};