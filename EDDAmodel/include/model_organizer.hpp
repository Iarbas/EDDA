// ========================================== max. 120 symbols in one line ============================================
/**
 * @par Project
 * EDDA - Evaluative Data-driven Design Application
 *
 * @file    model_organizer.hpp
 * @author  Andre Alexander Pieper
 * @version 1.0
 * @date    2020-03-09
 *
 * @brief   Header file for the oranization of the models.
 *
 * This program part is responsible for the organization of the models.
 */
// --------------------------------------------------------------------------------------------------------------------

#ifndef HEADER_MODEL_ORGANIZER_HPP_AP_09032020
#define HEADER_MODEL_ORGANIZER_HPP_AP_09032020

#include <string>

#include "simple_model.hpp"
#include "seven_state_model.hpp"


namespace EDDAmodel
{
/** @class SimpleModel
 *  @brief Simple ODE motion model of the vehicle.
 *
 *  Class for the simple ODE motion model of the vehicle.
 */
class ModelOrganizer
{
public:
	ModelOrganizer(std::string model_name);
	virtual ~ModelOrganizer();				// Virtual Destructor.

        EDDAmodel::SimpleModel* simple_ode_model;

private:
	void Init();

        std::string _model_name;
};
}

#endif // HEADER_MODEL_ORGANIZER_HPP_AP_09032020
