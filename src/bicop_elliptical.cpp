// Copyright © 2017 Thomas Nagler and Thibault Vatter
//
// This file is part of the vinecopulib library and licensed under the terms of
// the MIT license. For a copy, see the LICENSE file in the root directory of
// vinecopulib or https://tvatter.github.io/vinecopulib/.

#include "bicop_elliptical.hpp"
#include <cmath>
#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

namespace vinecopulib
{
    VecXd EllipticalBicop::hfunc2_default(const MatXd& u)
    {
        return hfunc1_default(swap_cols(u));
    }

    VecXd EllipticalBicop::hinv2_default(const MatXd& u)
    {
        return hinv1_default(swap_cols(u));
    }

    double EllipticalBicop::parameters_to_tau(const VecXd& parameters)
    {
        double tau = (2 / M_PI) * asin(parameters(0));
        return tau;
    }

    VecXd EllipticalBicop::tau_to_parameters(const double& tau)
    {
        VecXd parameters = this->parameters_;
        parameters(0) = sin(tau * M_PI / 2);
        return parameters;
    }

    void EllipticalBicop::flip()
    {
        // nothing to do because elliptical copulas are radially syemmetric
    }
}
