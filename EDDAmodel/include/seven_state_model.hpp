// ========================================== max. 120 symbols in one line ============================================
/**
 * @par Project
 * EDDA - Evaluative Data-driven Design Application
 *
 * @file    seven_state_model.hpp
 * @author  Andre Alexander Pieper
 * @version 1.0
 * @date    2020-03-22
 *
 * @brief   Header file for the ODE motion model of the vehicle with seven states.
 *
 * This program part is responsible for calculating the seven state motion of the vehicle with respect to 
 * the input. This model was inspired by the work of Viktoria Wiedmeyer and Andreas Himmel as part of their
 * study project oTToCAR. The report of their work is attached to the source code in Github:
 * Iarbas/EDDA/EDDAModel/books/oTTocarBericht.pdf
 */
// --------------------------------------------------------------------------------------------------------------------

#ifndef HEADER_SEVEN_STATE_MODEL_HPP_AP_22032020
#define HEADER_SEVEN_STATE_MODEL_HPP_AP_22032020

#include <string>
#include <vector>


namespace EDDAmodel
{
/** @class SevenStateModel
 *  @brief ODE motion model of the vehicle with seven states.
 *
 *  Class for the seven state ODE motion model of the vehicle.
 */
class SevenStateModel
{
public:
	SevenStateModel();
	virtual ~SevenStateModel();			// Virtual Destructor.

	void Run();

private:
	void Init();
};
}

#endif // HEADER_SEVEN_STATE_MODEL_HPP_AP_22032020
