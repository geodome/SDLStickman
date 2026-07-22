# SDLStickman v0.4.0

The Swordman navigates the world

![App Demo](https://github.com/geodome/SDLStickman/blob/main/demo/Stickman_Animation_v0.4.0.gif )  

### Improvement over v0.3.0
* Seperated declaration and implementation of the header files
* Introduced a viewport to provide for horizontal scrolling
* Introduced a game map for the Player to traverse
* Refactored State Machine for Swordman Sprite

### Next Phase
* Physics subsystem

### Setup
* Requires C++ 17 and SDL2

## SDLStickman v0.3.0

He yields a sword and strikes fear in his enemy's heart.

![App Demo](https://github.com/geodome/SDLStickman/blob/main/demo/Stickman_Animation_v0.3.0.gif )  

### How to play

His movement is manipulated by pressing the W,A,S,D keys. 

To equip with sword, press Q. To attack with sword, press the space bar.

To exit, press the Escape Key.

### Overall Design

The software architecture is based on the Event-Driven Entity Component System.

System::main_loop() is responsible for triggering the EventEmitter which emits specific event such as:
* system events: system_tick, system_upate, system_render
* input events: key_press_down, key_press_up, mouse_single_click, mouse_double_click, mouse_right_click.

System::render is broken down into 3 phases to support Render Ordering:
* Render handlers triggered by EventEmitter::render_background are executed first,
* Render handlers triggered by EventEmitter::render_midground are executed next,
* Render handlers triggered by EventEmitter::render_foreground are executed last.

An Entity is any game object, which may be the player, villian, NPC or an obstacle such as a wall or ladder.

Each Entity is composed of sub-interfaces that manages different events:
* Position: manages the coordinate, velocity and acceeration
* Sprite: loads and displays a series of images to form an animation
* Shape: objects that are directly created by the programmer without using media or images.
* BoundingBox: To detect and handle collision between entities
* Controller: Updates other components of the Entity in response to user's input.

When programming an Entity, there is no need to access EventEmitter because it is lower tier in the logic hierachy.

### Next Phase

To work on BoundingBox logic and enable new Entities like villian and walls interacting with the Player.


## SDLStickman v0.2.0

Simple Stickman Animation using SDL2

![App Demo](https://github.com/geodome/SDLStickman/blob/main/demo/Stickman_Animation_v0.2.1.gif )  

A stickman running across the Window. 

His movement can be paused by pressing the space bar and his direction is set by the  W,A,S,D keys.

### Overall Design

The overall design is based on an Animation system that interacts with each Game Object, whereby each Stickman is a Game Object.

The interface of a GameObject is segregated into 3 interfaces
- Position which determines the coordinate, velocity and acceleration of the GameObject in 2D space.
- Animation which determines the state of animation.
- Controller which defines the input handlers.

### Next Phase

The nexxt phase will explore tiled maps, placement and interaction between various game objects. e.g. collision.

## SDLStickman v0.1.0

Simple Stickman Animation using SDL2

![App Demo](https://github.com/geodome/SDLStickman/blob/main/demo/Stickman_Animation_v0.1.0.gif )  

4 individual stickman walking at different speeds. Each stickman can be individually suspended by clicking it.

### Overall Design

The overall design is based on an Animation system that interacts with each Game Object, whereby each Stickman is a Game Object.

The interface of the Game Object consists of
- GameObject::add_handler(uint32_t event_type, std::function<void> handler_function)
- GameObject::tick()
- GameObject::update()
- GameObject::render(SDL_Renderer* gRenderer)

GameObject::add_handler() registers a GUI event handler associated with each Game Object. For example, clicking on the stickman toggles the Stickman animation. Animation's main_loop() will process all GUI events and trigger the appropriate handler for each Game Object.

GameObject::tick() allows each Game Object to synchronise its internal rhythm  with the Animation clock. Each Game Object has a default DELAY value. The animation updates itself every DELAY amount of ticks occur.

Animation::main_loop() will call Animation::update() and Animation::render() which in turn calls each Game Object's GameObject::update() and GameObject::render()  method, then finally displays the new screen output.

### Next Phase

Animation will split into a main system and a physics sub-system. The main system is responsible for overall coordiantion between different Game Objects while the Physics sub-system will handle interaction between Game Objects.

To enhance granular control of each Game Object, the interface of Game Object  will be refactored into several sub-interfaces:
- Position sub-interface for controlling movement, velocity and acceleration.
- Animation sub-interface for controlling apperance and other animation related effects.
- Input Handler to handle input events

