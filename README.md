# EV Charging Station Simulation 

## Description:  This project is a TypeRacer-inspired typing game using an RGB LED and buttons. The LED indicates game status, a button adjusts difficulty, and the serial monitor displays words for players to type. Correct and incorrect inputs are reflected by LED color, and the game score is shown at the end of each round.


##  🛠️ Components: 
### Breadboard
### 3x 100-ohm Resistors
### 1x RGB LED (represents the station status)
### 2x Buttons (for start and stop/reset controls)
### 2x 10K-ohm Resistors (for button debouncing)
### Jumper Wires (for connections)


##  📖 Project Functionality 
### Idle (RGB LED White): The RGB LED starts in white, indicating the game is idle and awaiting input.

### Difficulty Selection: Pressing the difficulty button cycles through Easy, Medium, and Hard modes. Each difficulty setting adjusts the time allowed per word, displayed in the serial monitor.

### Countdown (RGB LED Blue): When the start button is pressed, the RGB LED blinks blue three times, displaying a countdown of 3, 2, 1 in the serial monitor.

### Game Start (RGB LED Green): The RGB LED turns green, and the first word appears in the serial monitor for the player to type. Each correct entry generates a new word, while an incorrect entry turns the LED red.

### Timeout: If a word isn’t typed within the allowed time, a new word automatically appears, with the LED resetting to green.

### Game End: After 30 seconds or if the stop button is pressed, the game ends. The RGB LED returns to white, and the serial monitor displays the player’s score (total correct words).



##  ⚙️ Circuit Schematic 

### ![Mighty Albar-Allis](https://github.com/user-attachments/assets/1875ac73-274c-4668-a2b5-c3a4c4345c85)

### This schematic shows the connections between the components on the breadboard, ensuring correct functionality.


##  🎬 Media 


##  🖼️ Simulation Picture: 

### ![P_20241104_215248](https://github.com/user-attachments/assets/67e25a2a-fa4f-4da9-9277-fd73abf0455e)


##  📹 Demo Video: 

###  https://github.com/user-attachments/assets/5862ee3e-f255-4869-aa1e-e5b0bc33cda6






