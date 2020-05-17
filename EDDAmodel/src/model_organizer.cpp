// ========================================== max. 120 symbols in one line ============================================
/**
 * @par Project
 * EDDA - Evaluative Data-driven Design Application
 *
 * @file    model_organizer.cpp
 * @author  Andre Alexander Pieper
 * @version 1.0
 * @date    2020-03-09
 *
 * @brief   CPP file for the oranization of the models.
 *
 * This program part is responsible for the organization of the models.
 */
// --------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include "model_organizer.hpp"


namespace EDDAmodel
{

ModelOrganizer::ModelOrganizer(std::string model_name)
{
    this->_model_name = model_name;

    this->Init();

    simple_ode_model = new EDDAmodel::SimpleModel();
}

ModelOrganizer::~ModelOrganizer()
{
    delete simple_ode_model;
}

void ModelOrganizer::Init()
{
    std::cout << "Initialization of the Model Organizer" << std::endl;

    if (this->_model_name.compare("simple") == 0)
    {
        std::cout << "Using the simple model." << std::endl;
        // TODO Template Function?
        EDDAmodel::SimpleModel ode_model();

        // TODO
        // Load parameter.
    }
    else if (this->_model_name.compare("seven_state") == 0)
    {
        std::cout << "Using the seven state model." << std::endl;
        EDDAmodel::SevenStateModel ode_model();
        // TODO
        // Load parameter.
    }
    else
    {
        std::cout << "No model with the name " << _model_name << ". Using instead the simple model." << std::endl;
        EDDAmodel::SimpleModel ode_model();
        // TODO
        // Load parameter.
    }
}

}
