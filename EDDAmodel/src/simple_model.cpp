// ========================================== max. 120 symbols in one line ============================================
/**
 * @par Project
 * EDDA - Evaluative Data-driven Design Application
 *
 * @file    simple_model.cpp
 * @author  Andre Alexander Pieper
 * @version 1.0
 * @date    2020-03-09
 *
 * @brief   CPP file for the simple ODE motion model of the vehicle.
 *
 * This program part is responsible for calculating the motion of the vehicle with respect to 
 * the input.
 */
// --------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <boost/array.hpp>
#include <boost/numeric/odeint.hpp>

#include "simple_model.hpp"


namespace EDDAmodel
{

SimpleModel::SimpleModel()
{
    this->Init();
    SimpleModel::Run();
}

SimpleModel::~SimpleModel()
{

}

void SimpleModel::Init()
{
    std::cout << "Initialization of the Simple Motion Model" << std::endl;

}

void SimpleModel::Run()
{
    std::cout << "Run the Simple Motion Model" << std::endl;

}

}
