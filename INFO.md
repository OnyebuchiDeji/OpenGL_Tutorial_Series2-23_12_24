#   Date: 23-12-2024



#   Overview

This is an OpenGL series from GetIntoGameDev on Youtube.

He goes more in-depth into OpenGL than the Cherno (or so I thought), and this series is done after the one with The Cherno.

Now, he does these things in VSCode, not MSVSCode.


***Reference: GetIntoGameDev (2023), "OpenGL with C++ Series" ***


#   Objectives:

*   Setup of OpenGL using the libraries and Cmake.
*   Creating Shaders, rendering a Triangle.
*   Adding Textures and Applying transformations
*   Refactoring into Classes, and using the Model-View-Controller system
*   Loading .Obj Models
*   Simple Animation System for Models -- but it's not skeletal animation because skeletal animation uses concepts   that are too advanced.
*   Game Dev: Loading Level Geometry from files.
*   Loading Enemies 
*   Rendering Text -- it involves different shaders and pipelines since there will be a layer for 3D rendering and another fro 2D rendering
*   Lighting
*   Creating a Menu -- prbably using ImGUI


#   Future Directions:

After finishing this tutorial, the next is to look at the Cherno's Game Engine series and SDL and start making 3D games for my project in school, and for personal Game Development projects.
as well as those ideas I have about procedural animation both on Human-like Bipedal, Bird/Dinosaur-like, and Spider-like creatures.
After SDL,


#  Episodes Breakdown

##  Ep1: "OpenGL with C++ 1: Intro and Setup"

This covers the setup of OpenGL in VSCode, with the use of Cmake and it worked


##  Ep1B: "Git Submodule: Setting Up CMake Projects in Windows" 

Exactly like the previous, but it installs glfw with git using this series of code:

```
    git init
    git submodule add https://github.com/glfw/glfw
    git mv glfw _dependencies --    to move the glfw submodule into the _dependencies directory
    
    git submodule update -- to update the glfw git submodule.
```

Then modified the CMake file to add these features:
    This code: cmake_policy(SET CMP0072 NEW)
    Enable C++ version 20.
    Enable the Release Build type
    Addded compile flags if the GNU g++ compiler is used.
    After installing glfw with git, added this code to include it:
        add_subdirectory(_dependencies/glfw      EXCLUDE_FROM_ALL)
        This part required moving the `_dependencies` folder into the `core` folder where
        the project source is located.
    
    Lastly was implementation of code to automatically update the glfw repository anytime the code is built.
    This is done in the CMakeLists.txt file:

    ```
        find_package(Git QUIET)         //--  Describe git
        if (EXISTS "${PROJECT_SOURCE_DIR/.git}")    //--  check if in valid git project
            option(GIT_SUBMODULE "Check submodules during build!" ON)   //--  set this option
            if (GIT_SUBMODULE)                      //--  If the project is valid
                message(STATUS "Submodule update")  //--  Update the submodule
                execute_process(COMMAND ${git_executable} submodule update --init --recursive
                                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                                RESULT_VARIABLE GIT_SUBMOD_RESULT)
                                 //--  Loop through registered submodules and fetch to update them
                if (NOT GIT_SUBMOD_RESULT EQUAL "0")
                    message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodule.")
                endif()
            endif()
        endif()

    ```
    With this even if glfw is deleted, one can download the updated version of it into the right directory.

    
##  Ep1C: "OpenGL with C++: Setting up the Envrionment in Visual Studio 

I already know how to do this. But I chose to learn how to do these things here in Visual Studio Code.

But I will explain the stuff here:

*   Open Visual Studio and create a new project.
*   Add the main.cpp and config.h files
*   Downloaded the glfw3 precompiled binaries and glad files.
*   In glfw3, consider the libs especially lib-vc2022 or higher according to your visual studio version.
*   Create the `dependencies` folder.
*   Create a folder `GLFW` in the `dependencies` folder and place the glfw3.lib in a folder named `lib` there.
    likewise place the include folder into the `GLFW` folder
*   Do the same for GLAD, adding the `glad.c` in the src folder, and the `glad.h`and `KHR` folder
    in a folder named `GLAD` in the `dependencies` folder.
*   Now include the `glad.c` as part of the project.
*   Now open the Project Options:
    +   Click as "All Configurations" and Platform: 64
    +   Now, in VC++ Directories, the "Include Directories", add the directories to the glfw and glad header files:
        "$(ProjectDir)dependencies\GLFW" and "$(ProjectDir)dependencies\GLAD"
    +   Now, add libraries' directories, glfw.lib: in the same Project Options, go to in VC++ Directories, then in "Library Directories", type "$(ProjectDir)dependencies\glfw\lib"
    +   Finally, add the name of the lib file to make the project know its name:
        In "Project Options", go to "Linker" section, in  "Input" -> "Additional Dependencies"/
        Now type the library name, `glfw3.lib`

He talks about the benefits of Visual Studio, how its autocomplete is the best.
Hence I can follow along with Visual Studio but I'll stick with this.


##  Ep2:  "OpenGL with C++ 2: What are Shaders?" ---    Tue-24-Dec-2024

Here he explains modern OpenGL, talking of the CPU and GPU and that they communicate...

Goal:
specifically concerning that here a shader is created and this shader is sent to the GPU.
So basically, the shader code is what renders the triangle -- it does not use vertex data for a triangle.

##  Ep2B:   --- Tue-24-Dec-2024

It was a continuation of Ep2 that was meant to be done in Ep3, but I did it myself here as Ep2B.
Also, my method uses indices for the triangle's faces. His doesn't


##  Ep3: "OpenGL with C++ 3: Vertex Buffers" --- Tue-24-Dec-2024

What is done here is the use of Vertex Buffers to draw the Triangle.
He might have done more than this, but just explained the Vertex Buffer stuff here alone.

After the normal rendering, we did these:
    +   Explored affecting the OpenGL viewport
    +   we explored sending heterogenous data through the Vertex Buffer to the GPU...
        one that sends a color index rather than colors.
        Here, the color index maps to colors defined in the shader code itself in a vec3 array.
        For int-type data, the gl_VertexAttribIPointer() function is used.
        At first, one Vertex Buffer was used to hold all this data.
    +   Then we explored using separate Vertex Buffers to send the data to the GPU, specifying
        each of their VertexAttribPointers differently.
    +   Then we created a quad using more vertices in the vertex buffer, and increasing the number
        of color indices that go with those vertices.
    +   Then created and index or element buffer to reduce redundant vertices and to specify the
        order in which the vertices for a triangle should be drawn using the element/index buffer

All these were done in its 4 version: _EP3[A-D]


#   Ep4: "OpenGL with C++ 4: Textures"

Applying textures to the quad.

these were done:
    +   Creating Textures, binding them an using them
    +   Creating multiple textures, registering them as Texture Units.
        then enabling blending, and using one of the textures as a mask.

#   Ep5: "OpenGL with C++ 5: Transformations"

This covers transformations of several different kinds.
This episodes covers their mathematical background and then demonstrates them.

He first does all of it from scratch before looking at the `glm` library.

These are done:
    *   Translating the Vertex Data before sending to GPU, using matrices.
        this made the all the vertex data translated according to the specified vector,
        which effectively panned everything.
             The Translation Matrix:
             A = 
             (
                 1 0 0 a
                 0 1 0 b
                 0 0 1 c
                 0 0 0 1
             )

             Here, (a, b, c) are the values by which you want to displace the vector the matrix A
             multiplies.

             A * vec3(x, y, z)
              = (
                     x + a
                     y + b
                     z + c
                 )

    *   Rotation: Specifically around the Z axis.
            For he shows that in OpenGL, the positive Z axis is in front of the screen...
            that is, it's behind the viewer. So into the computer screen, the Z-axis is negative.
            This is how it is for OpenGL.

        It uses the rotation matrix:
            (
                cosa -sina
                sina cosa
            )

    *   Now, here, both rotation and translation are applied.
        This creates a Geometrix Matrix: A Geometric matrix is such that has more than one transforms in them.

        This is brought about by multiplying the Rotate and Translate matrices.
        Where Translation matrix is T and rotations matrix is R...
        the matrix to both translate and rotate is = T * R.

    *   Now, the View Matrix Transform is implemented. So far only transforms on the model itself
        have been done.
        The view matrix transforms the model from World Space to View Space, transforming it
        according to the matrix that define the view/perspective.

        Consider that the view matrix is defined by the Camera.
        If the Camera moves left, the world view/view matrix is defined to move right -- opposite.
        If the camera rolls around the Z-axis anticlockwise, the world rotates around the Z-axis
        clockwide -- opposite.
        Hence, the View of the world is a function that is the negative or "inverse" of the camera's transformations.

        The Camera is a geometric matrix.
        A Geometric matrix is such that has more than one transforms in them.
        A Camera has both a rotation component and a Scale component.
        It has also vectors that specify these:
            +   Forward facing direction or forward vector; It's the image of the Z-axis
            +   Right Vector  -- defines the X-axis of the Camera. It represents
                    the screen's X-axis or is an image of it, when viewing through the camera
            +   Up Vector     -- defines the Y-axis; it's an image of the Y-axis of the screen.
            +   Eye: Camera's position in the World Space.

        Here, a lot of coolade math stuff was done to get the View Matrix.
        Honestly, I think it could have been explained better.
        But I am certain I would understand it very soon.
    
    *   Now, creating the Projection matrix.

        After the View martix transformation, the resulting render showed some of the quad being
        clipped because it was too far away.

        This is fixed with perspective made by the Projection matrix.

        The w component, after all the transformation mappings, should store how far the vertex is
        away from the viewer.
        It brings things further away somewhat closer, fixing it so it's rendered properly.

        The w componenet should store the distance from the viewer.
        After perspective division, visible vertices should be in range [-1..1].

        The derivation was done one my note.

        I'll attach links to the pictures here

        the [rotation matrix derivation part1](/_info_resources/20241228_173259.jpg)
        the [rotation matrix derivation part2](/_info_resources/20241228_173305.jpg)
        the [rotation matrix derivation version 2](/_info_resources/20241228_173324.jpg)
        the [translation matrix derivation full and camera/view matrix derivation part1](/_info_resources/20241228_173335.jpg)
        the [camera/view matrix derivation part2](/_info_resources/20241228_173343.jpg)
        the [camera/view matrix derivation part3](/_info_resources/20241228_173350.jpg)
        the [projection matrix part1](/_info_resources/20241228_173358.jpg)
        the [projection matrix part2](/_info_resources/20241228_173405.jpg)
        the [projection matrix part3](/_info_resources/20241228_173421.jpg)
        the [projection matrix part4](/_info_resources/20241228_173427.jpg)

#   Ep6: 'OpenGL with C++ 6: Design Patterns" --- Date: 29-Dec-2024

This episode shows the differnt design patterns of structuring a Game Engine.
Here, Andrew (the Series' Author), 3 different patterns of structuring the code.
The source code is the episo-de 6 here: [Source](https://github.com/amengede/OpenGL-for-Beginners)

The design patterns:
    1. Object-Oriented (Pure)
    2. Model-View-Controller
    3.  Entity Component System

From 1->3, the "complexity" and the efficiency increase.

All og the above patterns are indeed object-oriented.


1.  The Object-Oriented Design:
    
    It moves each element and their properties and behaviours in its own class.
    For example, the Cube and Player classes will be made.
    Cube's properties and methods: * pos, * eulers, * mesh, * material, + draw(), + update()
    Player's properties and methods: * pos, * eulers, + get_view_transform(), + move(), + spin()

    Then in the main(), everything else.

    _EP6A shows this design.

2.  Model-View-Controller:

    this separates the code structure into these three: Model classes, View classes, and Controller classes.

    Model Classes: * Cube, * Camera (Player), * Scene
        These hold game data of models and the methods to transform the data helf in the view class's Mesh class for a Cube.
        It handles game logic, e.g. to change the Cube's Pos or orientation (euler), and send the updated
    Mesh to the Renderer

        Cube:   * pos, * eulers, + get_world(), + update()
        Camera: * pos, * eulers, + get_view(), + move(), + spin(), + yaw(), + roll()
        Scene: * cubes, * camera (player), + update(), + move_player(), + spin_player(), etc.

    View Classes: * Mesh, * Material, * Renderer
        It is independent of the Game Logic. It does all the operations concerning getting, ordering and keeping information on what to render to the screen

        Mesh: * VAO, * VBO, * Vertex_Count, + draw()
        Material: * Texture, + use(), + delete()
        Renderer: * shaders, * meshes, * materials, + render() 
    
    Controller Classes: * App, * Scene, * Renderer, + handle_keys(), + handle_mouse(), + run()
    It is the bridge between the game logic (Model) and the Renderer (view).
    It also contains a pointer to the Scene (model) and Renderer (view), methods that handle keys and mouse inputs and sends messages to the Game Logic to make it update. Then it gets this updated Model data and sends to the Renderer to update the actual, for example, Cube vertices so what is rendered is updated.
    Finally, it has the run() method to start the app.

3.  Entity Component System:

    The three categories: Entity, Components, System.

    Why is ECS used?
        Reason 1: the MVC structure can have multi-level and multiple inheritance.
        ALthough this is fine from a design standpoint, but in performance, the larger the
        inheritance three is, the worst the program's performance because of indirection lookups
        which slow things down.

        Reason 2: The way ECS is implemented is such that the components that represent an Entity...
        such as the position (x, y), and euler value (for rotation), are defined in a struct and
        placed in an array where the index of these structs is the index that represents a specified
        entity. Now, when the CPU is fetching data from memory, it gets the data in a huge stride so that other adjacent data are also "Cached". Because of this, when the data of a second entity already adjacent to the cache is accessed, the CPU can get this data quickly because it is already in the Cache. This improves performance since the CPU has access to the cache data more easily than the RAM memory space.
        Now, the reason this works is because the components which contain data on an Entity, the data in them are stored in structs; hence it is very compact, hence why the caching advantage works well. 
        This is better than the MVC model because this model mostly creates objects separately; it does not involve storing them in an array-like structure. This results in the data of consecutively-made objects to not be adjacent to each other. So there isn't the advantage of the cache containing the adjacent data of the accessed object, thereby losing the performance boost.

    Entity: Represented by an ID, an unsigned int.

    Components: These are the data: 
        -   Transform Component: * pos vec3, * eulers (rotation) vec3. Basically, holds data for transforms on entities (or objects).
        -   Appearance/Render Component: * materia;s, * mesh
        -   Camera: * up vector, * right vector, * forward vector
        -   Physics: * vel, * euler velocity (for spinning)

    Hence the game engine will have as much arrays/unordered map as there are components -- each entity will have its components, and each of its components will be kept in an array or unordered map, with that entity's components in each component map represented by that entity's id.

    Now, an entity can have some or all available components. E.g.:
        -   Cube Entuty: * Transform, * Apperance, * Physics
        -   Player Component: * Transform, * Camera, * Physics.
        
    System or Controller: These are the set of logic that takes each of the components and operates on them.
        -   Motion System: takes the physics components of each Entity, and that entity's corresponding transform components, and applies the physics to the transfrom component, to update them.
        -   Camera System:  this takes the camera entity and its componenets (specifically the transform components) to read its positions.
        -   Render System:  This takes all the transform data and render components (appearance) to get enough data to render the map to the screen in OpenGL
    

Finished Ep6: Mon-30-Dec-2024


#   Ep7: "OpenGL with C++ 7: Loading Models"

Here, the process of reading .obj files without an external library is demonstrated.

In .obj files, 'v' is for vertex, 'vt' is vertex texture for texture coordinates, 'vn' is vertex normal
and 'f' stands for face. 
The face represents the triangle indices: it holds the position of the position, texture coord, and normal vector -> 1 set.
E.g.:
    `
        <line_no.> f v1/v2/v3
    `
Three of these sets make up a triangle, but there is also a fourth one:
    `
        <line_no.> f v1/v2/v3 v4/v5/v5 v7/v8/v9 v10/v11/v12
    `
Now if in the faces, the one or more of the information is missing, it will be empty, showing just a double slash with nothing
between:
    `
        <line_no.> f v1//v3 v4/v5/v5 v7//v9 v10/v11/v12
    `
Then the material file is also cool:
It even contains the constants for Phong lighting and the like...
and for Lambertian reflection.

Used a cool STl function, std::stof(); it converts a string to a floating point number.

The data labelled by 'f' are called "Edge Tables": they describe a polygon and show the four corners;
They make a quad built from 2 triangles


    
     Reading the face values:
     
     ConsiderPoints: 123456 -- the six points' index of a polygon's points 
    
     then for each triangle:
     123, 135, 145, 156 -- note they are all connected because they share a common point.
     and they cover the above index space, as the Union of them makes up 123456
    
     Note these data labelled by 'f' are the indices that show the order of the vertices that have been gotten...
     for the Position, TextureCoord, and Normal vertices appropriately.
     Hence why in the 'girl.obj' file, an 'f' line is like this:
     v1 -- position vertex index
     v2 -- texture_coord vertex index
     v3 -- normal vertex index.
                 <line_no.> f v1/v2/v3 v4/v5/v5 v7/v8/v9 v10/v11/v12 
     
     The number of triangles for a face is the number of points - 2
    

#   Ep8: "OpenGL with C++ 8: Animating Models" --- Mon-30-Dec-2024 - Tue-31-Dec-2024

This episode demonstrates animating a 3d model.

This is normal animation --- several frames of a 3d .obj model are played to animate it.
It's not procedural --- rather the frames of the animation done with bones in blender are each
captured and exported into .obj files. It is these frames that are being loaded.



#   Ep 9: "OpenGL with C++ 9: Static Geometry" --- Tue-01-Jan-2025

This episode is called "Static Geometry", but it more accurately involves  "Resource Clumping" or "Resource Grouping", or "Batch Rendering".

Elaboration: There is a Mesh Factory that is able to load files. It can listen to input to append multiple files, and it will load these files and throw the data into the same buffer and build the VBO object.
The point is grouping the vertex data of several .obj or like 3d model file into one Vertex Data that is loaded into one large VBO object to render the several objects at once

**Advantages**:
    1.  When rendering Static Geometry, such as Trees, walls, etc... bundling them together in one Vertex Buffer Object and drawing them all in one draw call reduced CPU overhead.
    2.  For rendering animations: The animations as of the last episode is a vector of models.
        So one can load in every single frame from teh separate .obj files into one large Buffer, and then depending only the current frame, draw that region of the buffer.
    
After doing the above, we had to give each of the Objects inside that one Vertex Buffer their own textures.
There are ways to do this:

    1.  Texture Atlas:  Involves stitching bits of different textures unto regions of one big texture. Then in the VBO where the separate models' VBOs are being appended, append a Texture Coordinate appropriate to that model. But this was not implemented here.

    2.  Image Arrays: Instead, this was done. I've done it from The Cherno's tutorial; the separate Textures are sent to the GPU
        as an array, and an index is appended to the Vertex Buffers for each separate static gemoetry, as its being loaded.
        Image Array Layers: A collection of textures in an array. Each are indexed and can be read from.
        Here it uses the Texture Factory and it appends several textures into a single buffer array, and then registers it with OpenGL for use.
        Now, it is different from the one I learnt from The Cherno, in that the U, V, and Layer Index are the three values to be sent to
        the GPU --- it's actually the same with the one from The Cherno
        It is however, done in a way that Batch Binds the texture data.

        Now, there was an issue with this function: glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, 1024, 1024, layers);
        It was not found in the current glad file I was using. So I set to download another.

        The above function reserves memory in the GPU side.
        Then it is followed by:     glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
                                    0, 0, layer, width, height, 1,
                                    GL_RGBA, GL_UNSIGNED_BYTE, data);
        ...which would append the texture data appropriately in the buffer.
        until it is finalized calling the unsigned int TextureFactory::finalize_texture_array()
        function.
        So anytime, glTexStorage3D is called, it reserves a new storage space for consecutive texture data to be appended
        into it.

        The appending was done one by one, hence why this tutorial used the abov two
        That is, for each Static Geometry, in total being 4, a space enough for 4 levels of textures
        was made...
        then glTexSubImage3D would append them appropriately according to its layer.
        Then another space for the Cube and Revy models was reserved.
        then glTexSubImage3D would append the data.
        Sol:
        1.    Could load all the texture data for the Cube and Revy into one spa, not requiring to append it using glTexSubImage3D.
            Instead, would use the normal:
                    glTexImage3D(GL_TEXTURE_2D_ARRAY, layers, GL_RGBA, 1024, 1024, 1, GL_FALSE, GL_RGBA8, GL_UNSIGNED_BYTE, (void*)0);
        2.  Just replaced glad to an updated version that has the function **glTexStorage3D**
            Had to use the one that the author used in the project; replaced glad.c, glad.h, and KHC files


#   Ep 10: "OpenGL with C++10: Cubemaps"

This is a way of rendering a SkyBox using a structure called a CubeMap.
Consider a unit length cube: l = w= h = 1 unit, and a vector or ray that shoots from the Cube's origin and hits a surface of the cube --- that surface of the cube is identified by an internal system that assigns a cardinal coordinate to that face, and that particular point on the face has a certain color which is rendered on the screen.

Internally, this is how the device identifies the faces:
    Face 1: x+
    Face 2: x-
    Face 3: y+
    Face 4: y-
    Face 5: z+
    Face 6: z-

Now, the Shader Uniform type for a Cube Map is a SamplerCube.
It is used with the texturel function this way:
    texture(SamplerCube(), dir(or vertex/pixel position));

Now, the Imagine splitting the Cube into its Net shape, and each net face has a unique texture on it (or the same in most cases of Skyboxes) --- note the images must be the same size.

The math is explained written in my note, as well as the explanation of what is done.

Important things to state:
    1.  Multiple shaders are going to be made.
    2.  When making the skybox shader, the Depth Tester is turned off and turned on afterwards.
    3.  Reflections of skybox on objects 'surfaces is done.
    4.  The EBO or IBO will be added


#   Ep 11: "OpenGL with C++: Debugging" --- Wed-08-01-2025

Here, ImGUI is setup to add widgets to the screen.
Next, is Render Doc -- perhaps it doucments performance.

RenderDoc is a tool from `renderdoc.org`

Steps:
    -   Download and open
    -   File->'Launch Application' (Choose the program executable) and then press launch
    -   Then screen shot useing f12 or Windows + Prt Sc
    -   Likewise, you can go to the 'Actions' sub-window. Then choose Queue Capture and select the frame you want to capture, e.g. 30.
    This will automatically capture that frame.
    -   Then from above there are triangles that represent Writes, ReadWrite and Clears events - select them to see the different events under the Event Browser.
    -You can even look at various variable names; it shows the function calls ad the variables there.


#   Ep 12: "OpenGL with C++ 12: Post Processing" --- Wed-08-01-2025

Post Processing? What does it do?

So far, with the use of VBOs, VAOs, EBOs, Texture Buffers -- everything with 3D and textures is combining everything into a texture and putting that texture on the screen.

This can be recreated

**Further Elab**

When everything is rendered, a FrameBuffer, an abstract object and it has various attachments, which are the underlying things we've been manipulating.

A Render or Frame Buffer can have one or more Color Buffer (essentially textures), and has one Depth and Stencil buffer for Depth and Stencil Testing respectively.

### What is Done Here:

    A Frame Buffer, Color Buffer and Depth Buffer are created



    Here, the  colorBuffer or texture that was rendered to off-screen
    is taken and then sampled from and put on the screen.

    So it is an indirect drawing.
    Advantage is that one can modify this separate texture buffer in more
    ways than if one rendered the texture directly to the main Screen Buffer

    For example, one can do Edge Filters, look at points' neighbours...
    and even add black and white.
    One can warp things around and put effects on the screen etc.
    
### The Goal

Here, what is demonstrated is that thing we did when we render a normal quad that is the size of the screen... and on that quad, we can do all those shader and ray-tracing effects.

How he does it is this: In a custom Frame Buffer is done all the rendering of all the Models, the Box with its texture, the Revy model, the Geometry, and the Skybox --- the code remains exactly the same except that it's not rendered directly but on a Frame Buffer.

Then separately, on the actual buffer rendered to the screen, first a quad is rendered --- a quad the same size as the screen. Then that custom buffer is now displayed on that quad as a texture.

This is almost exactly the same as rendering all the objects with their textures directly, since they are all written to a main Frame buffer themselves as a texture --- but this method writes them to a Custom buffer so they can be rendered on another surface, the Quad.
The advantage is that this quad can be transformed, and many shader effects can be applied to it, which affects any texture rendered on it. Hence it affects the Custom Frame Buffer rendered on it. 
One can use this to make them appear on a transformed surface, like adding a CRT TV effect, or, as in this case, a Black and White effect.

Or one can look at a pixel's neighbours and look at the interactions between those in calculating the final pixel value.

This can be done by looking at the current pixel's corresponding pixel color in the texture made from the custom FrameBuffer in the shader... then looking at its neighbours' colors in the texture, and using them to affect the current pixel's value in one way or the other.


#   Ep 13: "OpenGL with C++ 13: Compute Shaders" --- Wed-08-Jan-2025

This episode follows from the previous, leaving the quad on which's surface things can be drawn.

Now, Compute Shaders need to be at least from OpenGL 4.3...
MAC does not follow OpenGL to the point where Compute Shaders were introduced.

In this case, a Compute Shader is set up and compiled and kjoined to the shader program, and is used to perform ray tracing algorithms to render a sphere.

Now, modern graphic cards parallelise work that is given to it.

The Compute Shader is the logical conclusion of the path of processing data and producing a render result.

Basically, when processes need to be done on Images, which are basically 2D arrays/domain space, the fact that the space is of a higher dimension than 1, it is more ideally done using parallely processes.
This is what the Compute Shader excels at.

Consider these:
    1.  AN array of objects and for each, calculate their model transform, or shift their position by a velocity. Such is a 1D problem domain.
    2.  An image which for every pixel, a custom calculation is needed to work out the pixel's value OR you have a patch of space in Parameter Space or UV Coordinates, and you want to calculate the height of every point there or you want to evaluate a function like the Bezier patch --- such are highly parallelizable problem with a 2D domain space.
    3.  You have a region of space and you want to calculate intersections with Isosurfaces to check for Cube Marching --- this requires a 3D problem space.
    The Compute Shader works well for all these 3 sorts of problems.

One musttake advantage of Work Group Sizes.

Consider an **array** that consists of steps of a problem.
The Compute Shader Can assign a parallel process to each step...
but a better way of managing is partitioning. the work force for a problem set.
Consider that these "steps" are 256 objects in an array that need to be modified with the Compute Shader.
When a Work Group Size of, for example, 64, is specified for the Compute Shader, it specifies that the GPU should invoke 32 of these parallel processes/workers at once to each work on one "Step" or Object each.

This means that for the array of 256 objects, there are 4 reinitializations of new workgroups, that are needed to complete the processing of all objects in the array.

+   For a 1D array of "steps", such as above, the vector representing the workgroup will be:
    ```
        workgroup_count = {4, 1, 1};
    ```
    This means that for all the objects that need to be processed, and a Shader program that specifies the operations to be performed on those objects, to process all those objects through the shader code, 4 batches of the objects and their corresponding processors need to be run through the shader, with each batch consisting of 64 objects, each with their own processor (so also 64 processors), since the work force for a single batch is 64, and each processor works only on one Object --- hence why it's parallel.
    The order of execution should not be relied on.

    here, the 4 represents the no. of workgroup reinitializations in the one dimension (x-dimension).
    If the work space were of higher dimensions, the other vector axes would be populated.
        E.g. 2D: {a, b, 1};
             3D: {a, b, c}

+   For a 2D problem of 256 x 256, a Work Group size of 64 workers, to be distributed evenly in both dimensions, the size would be:
    workgroup_size = {8, 8, 1};
    So to finish the work, the  workgroup_count needed in both dimensions = {256 / 8, 256 / 8, 1} = {32, 32, 1}
    Because, given the work force of 8 on both dimensions, to finish a work amount of 256, 32 batches of the work need to be processed.

+ For a 3D problem of 256x256x256:
    ```
        work_group_size: {4, 4, 4};
        work_group_count: {64, 64, 64};
    ```

    Finally, when working, modify these to see which work group count is best.

Now, issue with Compute Shaders on performance is that they get **memory-bound** rather than **compute-bound**, that is,
they waist more time writing to the Color Buffer rather than processing the numbers diligently. 


##  This Episode 13 marked the official end of this series, though it does continue.
##  These remaining episodes covers techniques that modern game engines use to display really big scenes --- some recount stuff done in previous videos; it is still interesting.


#   Ep 14: "OpenGL with C++ 14: Image Arrays" --- Wed-08-Jan-2025

