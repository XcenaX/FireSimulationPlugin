# FireSimulationPlugin
A plaugin for Unreal Engine 4. Plugin allows you to simulate Fire and Smoke propagation.
## How to use
1) Create FireGridManager, FireManagerActor and FogManagerActor on scene.
2) Create GridActor and give it wanted size. This is Fire Grid. Simulation will be only inside this actor.
3) Add FireSimulationComponent to Actors that you want to take place in Fire Simulation and input Mass, IsWall, IsBurning for every actor
  IsWall - The walls can't burn completely.
  IsBurning - Is actor is starting point of fire spread (Fire starts at this actor)
  Mass - mass of actor in KG
4) Place RoomMarker's on scene. RoomMarker is a room boundaries. Smoke will generate in thoose boundaries.
5) Add DoorComponent to all doors you have and set them up. You must specify which rooms the door connects using component parameters: ConnectedRoom1 and ConnectedRoom2. You also can specify is door open or not (IsOpen)
6) When you places all actors you can go to Tab Window->FireSimulation in Unreal Engine. In modal window you need to input Fire Grid Size (how many cells in 1 dimenstion. Example: 3 means there are 27 cells in grid), amount of threads using for calculating simulation, pick Fire Particle System. Now you can click Draw Grid to see how your grid looks in scene and Clear Grid to hide. Fill Grid with actors button searches actors with FireSimulationComponent in it and initializes Grid for fire simulation.
img 1. FireSimulation tab
<img width="204" alt="image" src="https://github.com/XcenaX/FireSimulationPlugin/assets/40425017/a84d17e1-06b8-4e0d-a5d1-bf8a41e97420">

img 2. Example of scene
<img width="1067" alt="image" src="https://github.com/XcenaX/FireSimulationPlugin/assets/40425017/e6a49cdf-c6b0-4633-aec6-19c7f9ebd0f2">

img 3. Draw Grid
<img width="1106" alt="image" src="https://github.com/XcenaX/FireSimulationPlugin/assets/40425017/b4b00d21-40c7-4790-af71-35aa599f64bc">

8) Now you can test your programm.
