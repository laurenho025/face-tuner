# Development Documentation

## Week 1
Most of this week's work was focused on coming up with an idea, finding the applicable libraries, and getting openFrameworks to build and work successfully. I had some difficulty getting the libraries' example projects to build, partly because of ofxFacialBlendShape's lack of documentation and figuring out aubio's dependencies. Eventually, I figured out openFrameworks and was able to set up the XCode project and add my libraries.

## Week 2
During week 2, I mostly worked on the GUI template for my application and setting up the libraries in my project. I had more difficulties with getting the project to build with aubio, so I decided to switch to the ofxAudioAnalyzer add-on instead, which also has a pitch analyzer algorithm. This week I figured out the pitch frequency and confidence analyzer. Going forward, I have to implement a class that calculates the note given a frequency in hz, and the absolute difference between the input frequency and the target frequency. After doing this, I can associate the size of this difference with specific emotions, which requires figuring out how to integrate the two libraries together.

## Week 3
This week I worked on integrating the sound analyzer and ofxFacialBlendShape libraries together. However, after working on this with the ofxAudioAnalyzer add-on, I found that its pitch detection was extremely sensitive with my computer's mic. I tried to fix this by calculating the room's ambient sound at each setup and accounting for this, but this still didn't fix the add-on's sensitivity when calculating measured pitch. I ended up switching back to aubio instead, as its pitch detector is much more stable/standardized and measures in MIDI note value rather than hz, which is less sensitive and gave me more accurate pitch numbers. 

Additionally, I made a separate class that does all the note calculations, which includes finding the nearest MIDI note pitch and classifying the MIDI difference as an emotion. To wrap up my project, I have to fix the "weighing" of the emotions, as it isn't displaying a smooth change of emotion weights for certain pitches. Also, I want to fix the dropdown menu issue, which isn't recognizing an empty parameter when the user unselects their choice. 


## Week 4
For this week, I focused on wrapping up the project and improving the emotion weight method. I found that there was something wrong with the math/algorithm when "weighing" the emotions, so I fixed that and got the emotions to be weighed properly. 

Additionally, the "buckets" that I was using to classify the difference as a corresponing emotion were not accurate and did not work when the measured pitch was very close to the target pitch. To fix this, I made the buckets more specific, and had to fix some of the conditional statements to work as expected. 

Lastly, I cleaned up the code and improved on style by adding comments and removing unecessary code. For example, I removed the unecessary functions in the ofApp files. I also added a separate namespace for a lot of the constants I was reusing in my ofApp.cpp file. 
