This is a C++ implementation of the Straights card game. 

## Overview
This project follows an Object-Oriented design structure, using classes and objects to organize information and maintain an extensible codebase for future upgrades. This design follows the Model-View-Controller design method. 

The project consists of multiple classes, the main ones being StraightsModel, Player, and View. The StraightsModel class is the main hub of functionality for the game, and handles the information regarding players, the game pile, the deck, and is where the main portion of the game is run. The Controller and View classes both interact with this class and serve as the functionality that allows the StraightsModel class to interact with players. The Controller is an abstract base class, with its children implementing specific methods pertaining to how the game should receive input from the user. The View class is also an abstract base class that interacts with the StrightsModel class and updates information to the implemented method desired. Moreover, the View class is an Observer and the StraightsModel class is the subject in an Observer pattern intended to make it easy to add more views to the application in the future, making it more resilient to future change. 

## Design 
This project uses a myriad of Design patterns that help with solving certain design problems and make the code easier to modify in the future. The first main design pattern that this project implement is the Model-View-Controller (MVC) design pattern. Moreover, to implement the ability to add more views, I have implemented the Observer design pattern to keep track of the different views the application has, and the Model class can update them accordingly. Moreover, the Strategy design pattern was also used in the Controller classes in order to make receiving user input from any device is easy. 

The use of multiple classes and Design patterns make this project quite resilient to change and easy to upgrade and extend in the future as the needs of potential players change. A developer can easily add another view to this program by extending from the View class and adding it using the addView method in the Model class. 
