// ========================================== max. 120 symbols in one line ============================================
/**
 * @par Project
 * EDDA - Evaluative Data-driven Design Application
 *
 * @file    seven_state_model.cpp
 * @author  Andre Alexander Pieper
 * @version 1.0
 * @date    2020-03-22
 *
 * @brief   CPP file for the ODE motion model of the vehicle with seven states.
 *
 * This program part is responsible for calculating the seven state motion of the vehicle with respect to 
 * the input. This model was inspired by the work of Viktoria Wiedmeyer and Andreas Himmel as part of their
 * study project oTToCAR. The report of their work is attached to the source code in Github:
 * Iarbas/EDDA/EDDAModel/books/oTTocarBericht.pdf
 */
// --------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <boost/array.hpp>
#include <boost/numeric/odeint.hpp>

#include "seven_state_model.hpp"


namespace EDDAmodel
{

SevenStateModel::SevenStateModel()
{
    this->Init();
}

SevenStateModel::~SevenStateModel()
{

}

void SevenStateModel::Init()
{
    std::cout << "Initialization of the Seven State Motion Model" << std::endl;

}

void SevenStateModel::Run()
{
    std::cout << "Run the Seven State Motion Model" << std::endl;

}

}
