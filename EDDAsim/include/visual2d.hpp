// ========================================== max. 120 symbols in one line ============================================
/**
 * @par Project
 * EDDA - Evaluative Data-driven Design Application
 *
 * @file    visual2d.hpp
 * @author  Andre Alexander Pieper
 * @version 1.0
 * @date    2019-10-10
 *
 * @brief   Visualization of the test track, vehicle and path.
 *
 * This program part is responsible for the visualization of the test track, vehicle and its path. This includes all
 * information regarding the environment and test subject (e.g. speed, steering angle, distance to optimal path etc.).
 */
// --------------------------------------------------------------------------------------------------------------------

#ifndef HEADER_VISUAL2D_HPP_AP_08092019
#define HEADER_VISUAL2D_HPP_AP_08092019

#include <SFML/Graphics.hpp>


namespace EDDAsim
{
/** @class Visual2D
 *  @brief Visualization for the EDDA project.
 *
 *  This class handles the visual output of the program.
 */
class Visual2D
{
public:
	Visual2D(std::string circuit_file);
	virtual ~Visual2D();				// Virtual Destructor.

	void WindowUpdater();

	/** @var sf::RenderWindow* window
	   *  @brief Object of the open window.
	   *
	   *  This object represents the visual output of the class.
	   */
	sf::RenderWindow* window;

private:
	/** @var sf::Event event
	   *  @brief Object of the event handler.
	   *
	   *  This object represents the user interface to the program.
	   */
	void Init(std::string circuit_file);

	uint32_t screen_height;
	uint32_t screen_width;

	sf::Event event;
	sf::Texture* texture_street;
	sf::Sprite* sprite_street;
};
}

#endif // HEADER_VISUAL2D_HPP_AP_08092019
