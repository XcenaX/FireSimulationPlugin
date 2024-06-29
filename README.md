# FireSimulationPlugin
```This is our first UE4 plugin. Plugin can contain bugs. If you found some, please inform. We will be very grateful```  
This plugin for Unreal Engine 4 enables the simulation of fire and smoke propagation within your scenes. 

## How to Use

Follow these steps to integrate the Fire Simulation Plugin into your Unreal Engine project:

### Setting Up the Environment

1. Place the `FireManagerActor` in your scene.
   
2. **Configure the Fire Grid:**
   - Create a `GridActor` in your scene.
   - Assign the desired size to this actor to define the Fire Grid. The simulation will only occur within the bounds of this actor.

3. You also must to place `ExponentialHeightFog` on scene to make smoke work.
### Preparing Actors for Simulation

3. **Enable Fire Simulation for Actors:**
   - Add a `FireSimulationComponent` to each actor you want to include in the fire simulation.
   - Specify the following properties for each actor:
     - `Mass`: The mass of the actor in kilograms.
     - `IsWall`: Walls cannot burn.
     - `IsBurning`: If `true`, the actor is a starting point for the fire to spread. There MUST be only 1 starting point.
     - `Selected material`: The name of a material that has a set of combustion parameters such as Linear flame speed, Lowest Heat Of Combustion, Burning Rate, etc.

4. **Mark Room Boundaries:**
   - Place `RoomMarker` actors in the scene to define the boundaries of rooms. Smoke will be generated within these boundaries.

5. **Configure Doors:**
   - Add a `DoorComponent` to every door in the scene.
   - Configure the component with `ConnectedRoom1` and `ConnectedRoom2` to specify which rooms the door connects.
   - Optionally, set `IsOpen` to indicate if the door is open or closed. If the door is open, the smoke will come faster into the next room.

### Running the Simulation

6. **Configure and Run the Simulation:**
   - Navigate to the `FireSimulation` tab in the Unreal Engine window.
   - In the modal window, set:
   - `Fire Grid element size`. The size of 1 element in grid. Example: 50 means grid will be filled with cubes with size 50x50x50
   - `Number of threads` for simulation calculations
   - `Measure`. The number of Unreal Engine untis that will be equal to 1 meter.
   - `Fire distance`. Visualisation parameter. Distance between fire actors. The greater the distance, the fewer Actors will be required to represent the fire zone and fewer resources will be required.
   - Select a `Fire Particle System`. Visualisation of fire. If you dont have Fire ParticlleSytem you can pick default visualisation located in `Project/Plugins/FireSimulation/Content/P_Fire.uasset`
   - Use `Draw Grid` to visualize your grid in the scene and `Clear Grid` to clear it. Be CAREFULL. If element size is too low this will crash UE.
   - Click `Confirm Changes` to confirm and save plugin settings.

### Example Images

- **FireSimulation tab:**


  ![FireSimulation tab](https://github.com/XcenaX/FireSimulationPlugin/assets/40425017/a84d17e1-06b8-4e0d-a5d1-bf8a41e97420)

- **Example of Scene:**

  
  ![Example of Scene](https://github.com/XcenaX/FireSimulationPlugin/assets/40425017/66ccd0fd-bbc3-4e86-a0ee-847144423674)

- **Draw Grid Example:**

  
  ![Draw Grid](https://github.com/XcenaX/FireSimulationPlugin/assets/40425017/a83eef18-da6c-4835-a63b-7486c9c71cce)


# EXAMPLE OF PLUGINS WORK

## Scene setup
<img width="910" alt="image" src="https://github.com/XcenaX/FireSimulationPlugin/assets/40425017/06dcb48c-58ff-42b8-92e1-7d9d118ee0e4">


## 10 seconds
  ![image](https://github.com/XcenaX/FireSimulationPlugin/assets/40425017/91f50753-e2db-4cde-b79e-d0390bb4e4e9)


## 40 seconds
![image](https://github.com/XcenaX/FireSimulationPlugin/assets/40425017/0d46e556-4eb0-41be-aecb-eaa66170c370)


## 150 seconds
![image](https://github.com/XcenaX/FireSimulationPlugin/assets/40425017/06e7f0df-8622-4790-91df-7190916d284a)


## 185 seconds
![image](https://github.com/XcenaX/FireSimulationPlugin/assets/40425017/a297dde3-7e49-4547-94b4-0fc3e86e1222)


## 240 seconds
![image](https://github.com/XcenaX/FireSimulationPlugin/assets/40425017/b7ea8923-8c18-41db-b14f-ae3ecedaaf77)
