# SDLStickman v0.1.0

Simple Stickman Animation using SDL2

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
git 