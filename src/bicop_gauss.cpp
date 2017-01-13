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

#include "bicop_gauss.hpp"

// constructor
GaussBicop::GaussBicop()
{
    family_ = 1;
    family_name_ = "Gaussian";
    rotation_ = 0;
    association_direction_ = "both";
    parameters_ = VecXd::Zero(1);
    parameters_bounds_ = MatXd::Ones(1, 2);
    parameters_bounds_(0, 0) = -1;
}

GaussBicop::GaussBicop(const VecXd& parameters)
{
    GaussBicop();
    set_parameters(parameters);
}

GaussBicop::GaussBicop(const VecXd& parameters, const int& rotation)
{
    GaussBicop();
    set_parameters(parameters);
    set_rotation(rotation);
}

// PDF
VecXd GaussBicop::pdf_default(const MatXd& u)
{
    double t1, t2, tmp;
    double rho = double(this->parameters_(0));
    VecXd f = VecXd::Zero(u.rows());
    //boost::math::normal dist(0,1);

    for (int j = 0; j < u.rows(); ++j) {
        t1 = gsl_cdf_ugaussian_Pinv(u(j, 0));
        t2 = gsl_cdf_ugaussian_Pinv(u(j, 1));
        tmp = gsl_ran_bivariate_gaussian_pdf(t1, t2, 1.0, 1.0, rho);
        tmp /= gsl_ran_ugaussian_pdf(t1) * gsl_ran_ugaussian_pdf(t2);
        f(j) = tmp;
        //t1 = boost::math::quantile(dist, u1);
        //t2 = boost::math::quantile(dist, u2);
        //f(j) = 1.0/sqrt(1.0-pow(rho,2.0))*exp((pow(t1,2.0)+pow(t2,2.0))/2.0+(2.0*rho*t1*t2-pow(t1,2.0)-pow(t2,2.0))/(2.0*(1.0-pow(rho,2.0))));
    }

    return f;
}


// Normal h-function
VecXd GaussBicop::hfunc1_default(const MatXd& u)
{
    double rho = double(this->parameters_(0));
    int j;
    double u1, u2, t1, t2;
    VecXd h = VecXd::Zero(u.rows());
    //boost::math::normal dist(0,1);

    for (j = 0; j < u.rows(); ++j) {
        u1 = u(j, 0);
        u2 = u(j, 1);

        if ((u1 == 0.0) | (u2 == 0.0)) {
            h(j) = 0;//else if (u2==1) h(j) = u1;
        } else {
            t1 = gsl_cdf_ugaussian_Pinv(u1);
            t2 = gsl_cdf_ugaussian_Pinv(u2);
            //t1 = boost::math::quantile(dist, u1);
            //t2 = boost::math::quantile(dist, u2);
            h(j) = (t2 - rho*t1) / sqrt(1.0 - pow(rho, 2.0));
            if (std::isfinite(h(j)))
                h(j) = gsl_cdf_ugaussian_P(h(j));
                //h(j) = boost::math::cdf(dist, h(j));
            else if ((t2 - rho*t1) < 0)
                h(j) = 0;
            else
                h(j) = 1;
        }
    }

    return h;
}


VecXd GaussBicop::hinv1_default(const MatXd& u)
{
    double rho = double(this->parameters_(0));
    VecXd hinv = VecXd::Zero(u.rows());

    for (int j = 0; j < u.rows(); ++j) {
        hinv(j) = gsl_cdf_ugaussian_P(
            gsl_cdf_ugaussian_Pinv(u(j, 1)) * sqrt(1.0 - pow(rho, 2.0)) +
            rho * gsl_cdf_ugaussian_Pinv(u(j, 0))
        );
    }

    return hinv;
}
