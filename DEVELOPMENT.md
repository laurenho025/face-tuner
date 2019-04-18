# Development Documentation

## Week 1
Most of this week's work was focused on coming up with an idea, finding the applicable libraries, and getting openFrameworks to build and work successfully. I had some difficulty getting the libraries' example projects to build, partly because of ofxFacialBlendShape's lack of documentation and figuring out aubio's dependencies. Eventually, I figured out openFrameworks and was able to set up the XCode project and add my libraries.

## Week 2
During week 2, I mostly worked on the GUI template for my application and setting up the libraries in my project. I had more difficulties with getting the project to build with aubio, so I decided to switch to the ofxAudioAnalyzer add-on instead, which also has a pitch analyzer algorithm. Going forward, I have to figure out how to integrate the two libraries together, and what things I can unit test. 
