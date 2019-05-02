# Face Tuner

Face Tuner is an [openFrameworks](https://openframeworks.cc) application that visualizes pitch accuracy through human facial emotions. 

This application currently allows the user to select a target note, takes in audio input from the external microphone, and matches it to a corresponding facial emotion that is then displayed on a 3D facial animation.

See the project [proposal](https://github.com/uiuc-sp19-cs126/final-project-laurenho025/blob/master/PROPOSAL.md) and [documentation](https://github.com/uiuc-sp19-cs126/final-project-laurenho025/blob/master/DEVELOPMENT.md) for more specific details.

## Dependencies:
The only dependencies needed are openFrameworks addons. 
* [ofxGui](https://openframeworks.cc/documentation/ofxGui/) was used to create the display panel in the window. This is automatically installed along with openFrameworks.
* [ofxAubio](https://github.com/aubio/ofxAubio) was used to analyze the input audio. Only the pitch detection method was used, which measures in MIDI number rather than hz. 
* [ofxFacialBlendShape](https://github.com/iwanao731/ofxFacialBlendShape) was used to generate a 3D face model and display facial emotions.
* [ofxDropdown](https://github.com/roymacdonald/ofxDropdown) was used to create a dropdown menu that allows the user to select a target note. 

## Screenshots:
Below are some screenshots of the application's main window.

No target note selected:
![image](https://github.com/uiuc-sp19-cs126/final-project-laurenho025/blob/master/Screenshots/Screen%20Shot%202019-05-01%20at%2010.31.00%20PM.png)

Measured pitch matches target pitch:
![image](https://github.com/uiuc-sp19-cs126/final-project-laurenho025/blob/master/Screenshots/Screen%20Shot%202019-05-01%20at%2010.32.05%20PM.png)

Measured pitch is not accurate:
![image](https://github.com/uiuc-sp19-cs126/final-project-laurenho025/blob/master/Screenshots/Screen%20Shot%202019-05-01%20at%2010.32.32%20PM.png)
