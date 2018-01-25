# Mahatma Game Engine
A Data-driven game engine that I created in my time at Florida Interactive Entertainment Academy. The project was built in Visual Studio 2015, primarily using C++, with a C library to parse XML files (Expat). 
For a **detailed folder structure**, please refer to the index.html file in the **docs/html** folder, which details all the documentation of the project.
## The primary objectives of this project were:
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
