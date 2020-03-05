// ========================================== max. 120 symbols in one line ============================================
/**
 * @par Project
 * EDDA - Evaluative Data-driven Design Application
 *
 * @file    visual2d.cpp
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

#include <stdio.h>
#include "visual2d.hpp"

namespace EDDAsim
{

/** @fn Visual2D::Visual2D()
 *  @brief Constructor of the class Visual2D.
 *
 *  Initialization of the window object.
 */
Visual2D::Visual2D(std::string circuit_file)
{
	// Get screen resolution.
	sf::VideoMode desktop = sf::VideoMode().getDesktopMode();

	// In an Ubuntu desktop we have the panel at the top and the dock. That we need to take into account.
	Visual2D::screen_height = 0.95f * desktop.height; // 5 percent are missing, because of the panel.
	Visual2D::screen_width = 0.95f * desktop.width;   // 5 percent are missing, because of the Dock.

	Visual2D::window = new sf::RenderWindow(desktop, "EDDAsim");
	Visual2D::texture_street = new sf::Texture;
	Visual2D::sprite_street = new sf::Sprite;

        this->Init(circuit_file);
}

/** @fn Visual2D::~Visual2D()
 *  @brief Destructor of the class Visual2D.
 *
 *  This functions deletes all created objects.
 */
Visual2D::~Visual2D()
{
	delete Visual2D::window;
	delete Visual2D::texture_street;
	delete Visual2D::sprite_street;
}

/** @fn Visual2D::Init()
 *  @brief Initial function of the class Visual2D.
 *
 *  This functions draws the first window.
 */
void Visual2D::Init(std::string circuit_file)
{
    std::string help_string = circuit_file;
    help_string.append("/circuit.png");

    fprintf(stdout,"Opening the circuit in the directory: %s\n", help_string.c_str());
 
    // Load the test ground.
    if (!Visual2D::texture_street->loadFromFile(help_string))
    {
        fprintf(stdout,"Cannot find the image for the test ground. Stopping the program...\n");
        std::exit(0);
    }
    else
    {
        fprintf(stdout,"Opening a window and draw the test ground.\n");
        Visual2D::sprite_street->setTexture(*Visual2D::texture_street);
    }

    // Scale the image to fit the resolution of the screen. To have an equal resize,
    // get the dimension with the smallest pixel.

    float ratio = 1.0;

    int image_width = Visual2D::sprite_street->getTexture()->getSize().x;
    int image_height = Visual2D::sprite_street->getTexture()->getSize().y;

    if (Visual2D::screen_width <= Visual2D::screen_height)
    {
        // Use the ratio of the width.
        ratio = (float) Visual2D::screen_width / (float) image_width;
    }
    else
    {
        // Use the ratio of the height.
        ratio = (float) Visual2D::screen_height / (float) image_height;
    }

    Visual2D::sprite_street->setScale(sf::Vector2f(ratio, ratio)); // absolute scale factor

    Visual2D::window->clear();
    Visual2D::window->draw(*Visual2D::sprite_street);
    Visual2D::window->display();
}

/** @fn Visual2D::WindowUpdater()
 *  @brief Re-draws the window with new input.
 *
 *  This functions draws continuously windows with new input from other EDDA parts.
 */
void Visual2D::WindowUpdater()
{
	if (Visual2D::window->isOpen())
	{
		if (Visual2D::window->pollEvent(Visual2D::event))
		{
			if (Visual2D::event.type == sf::Event::Closed) Visual2D::window->close();
		}
		else
		{
			Visual2D::window->clear();
			Visual2D::window->draw(*Visual2D::sprite_street);
			Visual2D::window->display();
		}
	}
}

}
