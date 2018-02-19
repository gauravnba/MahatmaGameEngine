# Mahatma Game Engine
A Data-driven game engine that I created in my time at Florida Interactive Entertainment Academy. The project was built in Visual Studio 2015, primarily using C++, with a C library to parse XML files (Expat). 
For a **_detailed folder structure_**, please refer to the index.html file in the **_docs/html_** folder, which details all the documentation of the project.

### Overview of Engine Structure:
 - `/source/Library.Shared/Datum` :
 The base datatype for the scripting structure of the engine. Includes support for datatypes of integer, float, vector, matrix, a Scope (similar to object pointer in C++), string, and RTTI (Return Type Type Identification) type (similar to a C++ object in C++)
 - `/source/Library.Shared/Scope` :
 To support encapsulation of datatypes in the scripting structure of the engine.
 - `/source/Library.Shared/Attributed` : 
 To support composition in game objects.
 - `/source/Library.Shared/World` or `Sector` or `Entity` :
 Game object heirarchy designed to support a game world with an organized structure with support for a game loop using the update() method.
 - `/source/Library.Shared/Action` and `Reaction` :
 Action base class describes any action that an Entity can perform in game; an example Action derived class, ActionListIf defined to highlight how an Action derived class should be modelled. Action relies on _ActionCreateAction_, _ActionDestroyAction_ and _ActionListIf_ to create a reliable Action structure.
 Reaction, along with ActionEvent tie in Actions with the Event System.
 - `/source/Library.Shared/Event`, `EventSubscriber`, `EventPublisher` and `EventQueue` :
 This classes create a reliable, asynchronous Event System that can be used by the scripting supported by this engine. 

## The primary objectives of this project
 - To learn how game engines are structured.
 - To learn advanced concepts of C++.
 - To see how compiler structures are made.
 - To learn asynchronous programming.
 - To better understand how the STL library is designed.
 - To implement complete unit testing practices.

### What this project is:
 - An engine (or framework) that provides a generic game world structure with Worlds, Sectors and Entities.
 - A custom library of C++ container classes including singly linked list, vector, hashmap.
 - Provision of an asynchronous event system to be used in game.
 - A world game loop that can run the Update method of each object in the world.
 - A Run-Time Type Identification (RTTI) system that can recognize the type of the object at runtime. If used, this can be used to create new types of game objects that the system can identify at runtime.

### What this project isn't:
 - A graphics engine to create beautiful 2D or 3D environments.
 - A complex physics engine to create dynamic interactions between game objects.
 - An audio mixing engine that can generate contextual audio.
 - A framework to capture game inputs from a user to be used in gameplay.
