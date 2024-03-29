# FireSimulationPlugin
```STILL IN DEVELOPMENT```  
This plugin for Unreal Engine 4 enables the simulation of fire and smoke propagation within your scenes. 

## How to Use

Follow these steps to integrate the Fire Simulation Plugin into your Unreal Engine project:

### Setting Up the Environment

1. **Initialize Simulation Managers:** Place the `FireGridManager`, `FireManagerActor`, and `FogManagerActor` in your scene to manage the fire and smoke simulation.
   
2. **Configure the Fire Grid:**
   - Create a `GridActor` in your scene.
   - Assign the desired size to this actor to define the Fire Grid. The simulation will only occur within the bounds of this actor.

### Preparing Actors for Simulation

3. **Enable Fire Simulation for Actors:**
   - Add a `FireSimulationComponent` to each actor you want to include in the fire simulation.
   - Specify the following properties for each actor:
     - `Mass`: The mass of the actor in kilograms.
     - `IsWall`: Indicates whether the actor is a wall, which cannot burn completely.
     - `IsBurning`: If `true`, the actor is a starting point for the fire to spread.

4. **Mark Room Boundaries:**
   - Place `RoomMarker` actors in the scene to define the boundaries of rooms. Smoke will be generated within these boundaries.

5. **Configure Doors:**
   - Add a `DoorComponent` to every door in the scene.
   - Configure the component with `ConnectedRoom1` and `ConnectedRoom2` to specify which rooms the door connects.
   - Optionally, set `IsOpen` to indicate if the door is open or closed. If the door is open, the smoke will come faster into the next room.

### Running the Simulation

6. **Configure and Run the Simulation:**
   - Navigate to the `FireSimulation` tab in the Unreal Engine window.
   - In the modal window, set the `Fire Grid Size` (the number of cells in one dimension; for example, 3 implies a 3x3x3 grid with 27 cells), the number of threads for simulation calculations, and select a Fire Particle System.
   - Use `Draw Grid` to visualize your grid in the scene and `Clear Grid` to hide it.
   - Click `Fill Grid with Actors` to search for actors with `FireSimulationComponent` and initialize the grid for fire simulation.

### Example Images

- **FireSimulation tab:**
  ![FireSimulation tab](https://github.com/XcenaX/FireSimulationPlugin/assets/40425017/a84d17e1-06b8-4e0d-a5d1-bf8a41e97420)

- **Example of Scene:**
  ![Example of Scene](https://github.com/XcenaX/FireSimulationPlugin/assets/40425017/e6a49cdf-c6b0-4633-aec6-19c7f9ebd0f2)

- **Draw Grid Example:**
  ![Draw Grid](https://github.com/XcenaX/FireSimulationPlugin/assets/40425017/b4b00d21-40c7-4790-af71-35aa599f64bc)

7. **Testing the Program:**
   Now you're ready to test your setup and see the fire and smoke simulation in action.
