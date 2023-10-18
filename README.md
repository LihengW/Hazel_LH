# Swirl

Swirl is a self-made Game Engine project. This project is based on **Hazel of the Cherno** and still on update. The current goal is building a light-weighted 2D game engine and implement a small 3D renderer.

github : [GitHub - LihengW/Swirl: Basic Game Engine under construction](https://github.com/LihengW/Swirl)

## Features

### 2D Renderer Based on OpenGL

#### Vertex Buffer & Vertex Array

I have to say, it's difficult part for new users to understand the complicate relationships between the Vertex Buffer and Vertex Array. So we decided to modify the structure of these confusing concepts. Now the Buffers just have every thing they need !

![ss](docs/VertexBuffer.png)

#### Shader Library

The most important part in Renderer perhaps! We build a wrapped Shader Library. Like most of the engine, the shaders can be editted outside the app, all you need to do is paste the relative route to the Shader receiver. Surely you can create the vertex shader and fragment shader in the same file, but you **HAVE TO** address them like this:

```
#type vertex
#version 330 core


layout ....
in / out ....
void main()
{
    ...
    gl_Position = {};
}

#type fragment
#version 330 core

...
void main()
{
    ...
}
```

#### 2D Texure System

Textures! OpenGL has offered us powerful samplers to deal with 2D texture, so what left to do is delivering the pictures' data to the GPU using OpenGL API. That's what we have implemented in the Swril Texture2D.

Texture Library is also available Now. Common picture files like jpg / png can be directly read into engine by creating Textures with their file path. We use **stb_image** as the image input class, and we give the data pointer to the Texture Class which can pass to GPU.

*follow the tradition of OpenGL, before assign the Texture to specific sampler or mesh data, you need to Bind() them first. The basic usage is like:*

#### Camera

Surely this engine involves cameras, at present, only Orthographical Camera and Perspective Camera are usable, we havn't compeleted the development of Physical Camera yet. Basic elements like field of view and viewport are set correctly. However, there is no much use in 2D system for a camera, so this class is very simple now.



### 3D Renderer Based on OpenGL

coming soon



*As we all know, the renderer is the core of a game engine, but even a basic game engine involve far more than graphics. Following features will be introduced apart from rendering technology and graphics.*



### Events & Inputs

Swirl created an event system to handle all the information passing from the operation system to the game and even more. The basic idea is that when users create a event by making movements in their computers, the event will be dispatched into several classes and handled layer by layer in the layerstack. The structure can be easily explained by following picture:



 In a word, all the game designer need to do is creating the layers. With these layers, the designers can freely code what they want to deal with the event. Also, the order of events' responses can be defined freely by properly organizing the layers. 



### GUI

The whole GUI of Swirl is made of Imgui components. This is a very cool GUI library, it offers great and easily adjustable components of GUI. These dockable and resizable windows are surely useful for the engine. The basic usage can be found in their docs.



## Coming:

- [ ] Perspective Camera in 3D world

- [ ] Texture2D samplers with regular AA

## Examples

*At present, two example projects are offered. One of them is a simple rendered scene, and the other is a pretty little game. The examples will be updated soon with the development of the engine.*

### Regular Sandbox



### Demo Game
