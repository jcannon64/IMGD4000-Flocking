# IMGD4000-Flocking

This is an Unreal Engine project that implements a simple version of the Boids algorithm in C++. Besides having the 3 main rules (Cohesion, Separation, Alignment), this version implements a speed limit and a bounding box that encourages boids to stay inside. Also, the speed of the boids are editable and there are bird noises in the background as shown in the gameplay video. For specific values, check the source code.

Once downloaded, you may be prompted to rebuild the project. Simply pick yes and wait for the project to open, or try opening the project again if it takes too long. Then, just play from the editor. To change the speed during runtime, look for FlockingGameModeBase0 in the outliner on the right, where you will see a Speed slider when clicked. This can be dragged or manually typed in, both are done offscreen in the video.

Gameplay Video: https://youtu.be/2BO6uWoZW5Q
