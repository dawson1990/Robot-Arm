// robotArm.cpp : Defines the entry point for the console application.
//
/*
	Name: Kevin Dawson
	No.: c00130965
	Description:  to create a robot arm that moves with keyboard input
*/
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
int main()
{
	// Create the main window 
	int width = 1000;
	int height = 720;
	sf::RenderWindow window(sf::VideoMode(width, height, 32), "Use: 'q','w','e','r','a','s','z','x'");
	window.setFramerateLimit(60);
	const int size = 5;
	const int clawSize = 7;
	sf::Vector2f pos(height/2, width/2);
	float rotationSpeed = 1.5;
#pragma region blue arm points and rotation
	sf::VertexArray blueArmLines(sf::LinesStrip, size);
	sf::Vector2f blueArmPoints[size];
	blueArmPoints[0] = sf::Vector2f(0, 0);
	blueArmPoints[1] = sf::Vector2f(0, 10);
	blueArmPoints[2] = sf::Vector2f(160, 10);
	blueArmPoints[3] = sf::Vector2f(160, 0);
	blueArmPoints[4] = blueArmPoints[0];
	// blue rotation
	float blueRotation = 0.0;
#pragma endregion

#pragma region green arm points and rotation
	sf::VertexArray greenArmLines(sf::LinesStrip, size);
	sf::Vector2f greenArmPoints[size];
	greenArmPoints[0] = sf::Vector2f(0, 0);
	greenArmPoints[1] = sf::Vector2f(0, 10);
	greenArmPoints[2] = sf::Vector2f(160, 10);
	greenArmPoints[3] = sf::Vector2f(160, 0);
	greenArmPoints[4] = greenArmPoints[0];
	//green rotation
	float greenRotation = 0.0;
#pragma endregion

#pragma region left claw points and rotation
	sf::VertexArray leftClawLines(sf::LinesStrip, clawSize);
	sf::Vector2f leftClawPoints[clawSize];
	leftClawPoints[0] = sf::Vector2f(0, 0);
	leftClawPoints[1] = sf::Vector2f(120, 0);
	leftClawPoints[2] = sf::Vector2f(120, 120);
	leftClawPoints[3] = sf::Vector2f(115, 110);
	leftClawPoints[4] = sf::Vector2f(110, 10);
	leftClawPoints[5] = sf::Vector2f(0, 10);
	leftClawPoints[6] = leftClawPoints[0];
	// left claw rotation
	float leftClawRotation = 0.0;
#pragma endregion

#pragma region right claw points and rotation
	sf::VertexArray rightClawLines(sf::LinesStrip, clawSize);
	sf::Vector2f rightClawPoints[clawSize];
	rightClawPoints[0] = sf::Vector2f(0, 0);
	rightClawPoints[1] = sf::Vector2f(0, 120);
	rightClawPoints[2] = sf::Vector2f(120, 120);
	rightClawPoints[3] = sf::Vector2f(110, 115);
	rightClawPoints[4] = sf::Vector2f(10, 110);
	rightClawPoints[5] = sf::Vector2f(10, 0);
	rightClawPoints[6] = rightClawPoints[0];
	// rigth claw rotation
	float rightClawRotation = 0.0;
#pragma endregion

#pragma region claw control points and rotation
	sf::VertexArray clawControlLines(sf::LinesStrip, size);
	sf::Vector2f clawControlPoints[size];
	clawControlPoints[0] = sf::Vector2f(10, 0);
	clawControlPoints[1] = sf::Vector2f(0, -10);
	clawControlPoints[2] = sf::Vector2f(-10, 0);
	clawControlPoints[3] = sf::Vector2f(0, 10);
	clawControlPoints[4] = clawControlPoints[0];
	float controlRotation = 0.0;
#pragma endregion
	// Start game loop 
	while (window.isOpen())
	{
#pragma region blue arm
		//blue arm transform
		sf::Transform Tb;
		Tb.translate(pos);
		//blue arm rotation
		sf::Transform Rb;
		Rb.rotate(blueRotation);
		//blue arm matrix
		sf::Transform Mb = Tb * Rb;
		for (int i = 0; i<size; i++) {
			blueArmLines[i].position = Mb.transformPoint(blueArmPoints[i]);
			blueArmLines[i].color = sf::Color::Blue;
		}
#pragma endregion

#pragma region green arm 
		//green arm transform
		sf::Transform Tg;
		Tg.translate(160, 0);
		//green arm rotation
		sf::Transform Rg;
		Rg.rotate(greenRotation);
		//green arm matrix
		sf::Transform Mg = Tb * Rb * Tg * Rg;
		for (int i = 0; i<size; i++) {
			greenArmLines[i].position = Mg.transformPoint(greenArmPoints[i]);
			greenArmLines[i].color = sf::Color::Green;
		}

#pragma endregion
		//translate control square
		sf::Transform Tcontrol;
		Tcontrol.translate(170, 0);
		sf::Transform Rcontrol;
		Rcontrol.rotate(controlRotation);
		//control matrix
		sf::Transform Mcontrol = Tb * Rb * Tg * Rg * Tcontrol * Rcontrol;
		for (int i = 0; i<size; i++) {
			clawControlLines[i].position = Mcontrol.transformPoint(clawControlPoints[i]);
			clawControlLines[i].color = sf::Color::Magenta;
		}

#pragma region left claw
		//left claw transform
		sf::Transform Tlc;
		Tlc.translate(10, 0);
		//left claw rotation
		sf::Transform Rlc;
		Rlc.rotate(leftClawRotation);
		//left claw matrix
		sf::Transform Mlc = Tb * Rb * Tg * Rg  * Tcontrol * Rcontrol* Tlc * Rlc;
		for (int i = 0; i<clawSize; i++) {
			leftClawLines[i].position = Mlc.transformPoint(leftClawPoints[i]);
			leftClawLines[i].color = sf::Color::Red;
		}
#pragma endregion

#pragma region right claw
		//right claw transform
		sf::Transform Trc;
		Trc.translate(10, 0);
		//right claw rotation
		sf::Transform Rrc;
		Rrc.rotate(rightClawRotation);
		//right claw matrix
		sf::Transform Mrc = Tb * Rb * Tg * Rg  * Tcontrol * Rcontrol* Trc * Rrc;
		for (int i = 0; i<clawSize; i++) {
			rightClawLines[i].position = Mrc.transformPoint(rightClawPoints[i]);
			rightClawLines[i].color = sf::Color::Red;
		}
#pragma endregion
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::A))
			{
				if (blueRotation != 90)
				{
					blueRotation += rotationSpeed;
				}
			}
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::S))
			{
				if (blueRotation != -90)
				{
					blueRotation -= rotationSpeed;
				}
			}
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::X))
			{
				if (greenRotation != 90)
				{
					greenRotation += rotationSpeed;
				}
			}
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Z))
			{
				if (greenRotation != -90)
				{
					greenRotation -= rotationSpeed;
				}
			}
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Q))
			{
				if (leftClawRotation != 0)
				{
					leftClawRotation += rotationSpeed;
					rightClawRotation -= rotationSpeed;
				}
			}
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::W))
			{
				if (rightClawRotation != 90)
				{
					leftClawRotation -= rotationSpeed;
					rightClawRotation += rotationSpeed;
				}
			}
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::R))
			{
				if (controlRotation != 90)
				{
					controlRotation += rotationSpeed;
				}
			}
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::E))
			{
				if (controlRotation != -180)
				{
					controlRotation -= rotationSpeed;
				}
			}
		}
		//prepare frame
		window.clear();
		window.draw(blueArmLines);
		window.draw(greenArmLines);
		window.draw(clawControlLines);
		window.draw(leftClawLines);
		window.draw(rightClawLines);
		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}

