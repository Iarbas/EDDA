// ========================================== max. 120 symbols in one line ============================================
/**
 * @par Project
 * EDDA - Evaluative Data-driven Design Application
 *
 * @file    simple_model.hpp
 * @author  Andre Alexander Pieper
 * @version 1.0
 * @date    2020-02-208
 *
 * @brief   Header file for the simple ODE motion model of the vehicle.
 *
 * This program part is responsible for calculating the motion of the vehicle with respect to 
 * the input.
 */
// --------------------------------------------------------------------------------------------------------------------

#ifndef HEADER_SIMPLE_MODEL_HPP_AP_28022020
#define HEADER_SIMPLE_MODEL_HPP_AP_28022020

#include <string>
#include <vector>


namespace EDDAmodel
{
/** @class SimpleModel
 *  @brief Simple ODE motion model of the vehicle.
 *
 *  Class for the simple ODE motion model of the vehicle.
 */
class SimpleModel
{
public:
	SimpleModel();
	virtual ~SimpleModel();				// Virtual Destructor.

private:
	void Init();
};
}

#endif // HEADER_SIMPLE_MODEL_HPP_AP_28022020
