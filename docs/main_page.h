/*

           d8b
           ?88
            88b
  88bd88b   888888b  d8888b
  88P' ?8b  88P `?8bd8P' `P
d88   88P d88,  d8888b
d88'   88bd88'`?88P'`?888P'

Author: tilu, 22/09/2024,
nbc signature powered by love.

*/

#pragma once

/*! \mainpage Author : Epiteh NBC Signature.
 * ## What's R-Type ?
 * R-Type is a horizontal-scrolling shoot 'em up arcade game produced by Irem in 1987.
 * The player controls a space fighter named the R-9 to defend humanity against a mysterious powerful alien life-form known as the Bydo. \n
 * The game is made up of several levels, each with a boss at the end that must be defeated to progress to the next level.
 *
 * \image html rtype.png "R-Type illustration" width=800 height=400
 *
 * ## The project
 * The project is a remake of the R-Type game, with a client-Nerwork-server architecture.
 * Our project can be played in multiplayer mode, with up to 4 players. \n
 * The game is divided into three parts:
 * The \b client is the graphical interface, the \b server manages the game, and the \b network (protocol) manages the communication between the two. \n 
 *
 * * \b The \b server used an AES encryption to secure the communication between the client and the server. \n
 *                    The main architecture of the server is based on the ECS pattern. \n
 * * \b The \b client is a graphical interface, using SFML, that allows the player to interact with the game.
 * * \b The \b network is the communication part between the client and the server. It's based on the UDP protocol.
 *
 * The entire project is written in C++ and work on Linux and Windows. You can find the Windows and Linus installers just below :
 *
 *  * \b Windows: \link https://we.tl/t-9krHI4wJTp \endlink
 *
 *  * \b Linux: \link https://we.tl/t-3kmMI2wMBd \endlink
 *
 * ## How the architecture look like ?
 *
 * \image html ECS_Diagram.png "R-Type architecture illustration" height=500
 *
 * EntityFactory is the class that creates entities. It is used to create entities with components and systems.<br>
 * component_manager is the class that manages the components. It is used to register components, add components to entities, and get components from entities.<br>
 * ControlTow is the class that manages the game. It is used to create/delete new player, update the background and call the input system that are responsaible for inputs handling.<br>
 * GarbageCollector is the class that manages the entities. It is used to delete entities that are not used anymore.<br>
 * Core is the class that initializes the game. It is used to initialize the components, systems, events, and the stage.<br>
 * IException and its successor classes are used to handle exceptions.<br><br>
 *
 * Systems are the part of the ECS that will allow you to act on the components of your entities. Here is an example of a system :<br>
 * ecs::AI : The AI system is responsible for updating the AI of the game, move the enemy according to a movement pattern.<br>
 * ecs::Collision : The Collision system is responsible for checking the collision between entities.<br>
 * ecs::Input : The Input system is responsible for handling the inputs of the player (chose the direction).<br>
 * ecs::CustomOfficer : The CustomOfficer system is responsible for blocking the user from going out of the screen.<br>
 * ecs::Health : The health system is responsible for updating the health of the entities (Player, Enemy).<br>
 * ecs::Render : The Render system is responsible for sending rendering data to the client.<br>
 * ecs::Position : The Position system is responsible for updating the position of the entities.<br>
 * ecs::Logging : The Logging system is responsible for logging the game data.<br>
 *
 * You can find a more detailed explanation on the use of the architecture in the Related Pages section.
 *
 * ## Dependencies
 * The following dependencies are required to build and run the project:
 * * \b SFML(2.6.1): Simple and Fast Multimedia Library, used for the graphical interface.
 * * \b Boost(1.86.0): Boost is a set of libraries for the C++ programming language that provides support for tasks and structures such as linear algebra, pseudorandom number generation, multithreading, image processing, regular expressions, and unit testing.
 * * \b CMake(3.26.3+): CMake is an open-source, cross-platform family of tools designed to build, test and package software.
 * * \b C++17: The project is written in C++17.
 * * \b GTest: Google Test is a unit testing library for the C++ programming language, based on the xUnit architecture.
 * * \b zlib: zlib is a software library used for data compression.
 *
 * ## How to run the program (Developer Linux)
 *
 * Clone the repository and go to the root of the project.
 * You can compile the program with the following steps:
 * \code{.sh}
 * $> mkdir build
 * \endcode
 * \code {.sh}
 * $> cd build
 * \endcode
 * \code {.sh}
 * $> cmake ..
 * \endcode
 * \code {.sh}
 * $> make
 * \endcode
 *
 * When the program is compiled, you can launch it with the following command:
 * \code {.sh}
 * $> ./rtype_server
 * \endcode
 *
 * \code {.sh}
 * $> ./rtype_client
 * \endcode
 *
 * ## How to run the program (Developer Windows)
 *
 * Clone the repository and go to the root of the project.
 * You can compile the program with the following steps:
 * \code {.powershell}
 * $> mkdir build
 * \endcode
 * \code {.powershell}
 * $> cmake --presets=default
 * \endcode
 * \code {.powershell}
 * $> cmake --build build
 * \endcode
 *
 * When the program is compiled, you can launch it with the following command:
 * \code {.powershell}
 * $> ./build/rtype_server
 * \endcode
 *
 * \code {.powershell}
 * $> ./build/rtype_client
 * \endcode
 */
