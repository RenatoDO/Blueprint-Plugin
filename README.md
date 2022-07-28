# Blueprint-Plugin

The primary goals of this assignment are:
Create a UE4 Plugin.
Extend the Blueprint system.
Create and use a blue noise point distribution

Create a new Blueprint node and data type in a UE4 plugin. In this case, we'll create a new Blueprint type to hold data about a blue noise point distribution generated using Mitchell's best candidate algorithm. You'll also create a Blueprint node to provide a random number seed to an object of this new type, and one to return a point location from it, and a simple Blueprint script to place some objects using this blue noise point distribution.

Objects distributed using true random numbers will tend to be clumpy because each position is independent of all of the ones before, so has no memory that another object has been placed nearby or that there is an unfilled gap. A blue noise distribution spaces has correlation between the point placements to make them more even in density, To summarize Mitchell's algorithm (https://blog.demofox.org/2017/10/20/generating-blue-noise-sample-points-with-mitchells-best-candidate-algorithm/), you first place one point at a random x/y location. At each step, select several candidate points and keep the one furthest from any already placed points. You should use distance calculations that wrap around from left to right and top to bottom so the distribution will tile and to avoid preference for point locations along the edges.

The linked page suggests choosing a set of candidate points at each iteration proportional to the number of points placed so far. If you naively loop through all of the already placed points to find the distances for each candidate, the resulting algorithm to generate N points will run in O(N3) time

In order to see the diference between random generated seeds and blue noise seeds look at the images back to back of each corresponding seed numnber and counter number
like Random_Seed5_Count10 .png with BlueNoise_Seed5_Count10 .png.

I'll describe how my algorithm works which is in the function MakeRandomPointInRange in 
BlueNoiseBPLibrary.cpp

Line 38 is just a simple check
Lines 40 and 41. I created an array that will contain the candidates as locations and then
I initialized the array with five times generated point number and FVector. Thus, the candidate
array would contain five times the number of generated point times FVector.
I mean (5*Generated Point Number) times FVector.

The lines 44-46. The function will return the BestCandidate's location. Therefore, I 
created these 2 variables to contain MaxDistance(farthest distance) and the Location 
which will satisfy the MaxDistance. The loop which is located under these definitions 
will change these variables according to candidates which are processed by loop until 
that time.

Line 48. This line will create random candidate locations. Above I just created an array
and fill it by FVector, not random FVector. These lines will provide us with random candidate
locations.

The lines 50-54. I created a variable called MinDistance to store the closest distance between
the candidates and all generated points and I set it by using the distance between the candidate
and the first generated point. The loop located under the definition will iter to find the closes
distance. At the end of the loop, we will have found the closest distance be a particular candidate
and all generated points. We can use this data to compare this candidate with others.

The lines 56-60. if this statement is true, it means we have found a candidate whose shortest
distance is longer than the previous longest distance. In this case, we can update MaxDistance
to MinDistance and BestCandidate to the candidate.
