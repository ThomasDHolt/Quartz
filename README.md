# Quartz

## Overview
Quartz is a 2D game engine which I am developing in my free time, the current goal of Quartz is to have a lightweight game engine that I can extend with features depending on the kind of games I am interested in developing.

Currently Quartz only supports OpenGL, however the engine does have an abstract Renderer class meaning that the engine isn't confined to OpenGL and other graphic APIs such as DirectX or Vulkan can easily be integrated without any added trouble. Levels can quickly be created by populating a .txt file with symbols which represent different textures, in the example below the hash symbol is being used to represent a simple brick wall. These .txt files can then be loaded into the engine's Level Library and then used to draw a level as required.
