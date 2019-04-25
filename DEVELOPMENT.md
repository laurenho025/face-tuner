# Development Documentation

## Week 1
Most of this week's work was focused on coming up with an idea, finding the applicable libraries, and getting openFrameworks to build and work successfully. I had some difficulty getting the libraries' example projects to build, partly because of ofxFacialBlendShape's lack of documentation and figuring out aubio's dependencies. Eventually, I figured out openFrameworks and was able to set up the XCode project and add my libraries.

## Week 2
During week 2, I mostly worked on the GUI template for my application and setting up the libraries in my project. I had more difficulties with getting the project to build with aubio, so I decided to switch to the ofxAudioAnalyzer add-on instead, which also has a pitch analyzer algorithm. This week I figured out the pitch frequency and confidence analyzer. Going forward, I have to implement a class that calculates the note given a frequency in hz, and the absolute difference between the input frequency and the target frequency. After doing this, I can associate the size of this difference with specific emotions, which requires figuring out how to integrate the two libraries together.

## Week 3
Difficulties: account for the ambient sound in the room, had to switch to aubio which has a much more standardized/stable pitch detection, dropdown not getting empty parameter when user unselects choice
