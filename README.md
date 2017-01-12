# beginners-growth
Procedural plant experiments

Before I begin exploring L-Systems, I want to see if I can mimic plant growth similar to what I might draw by hand.

## Algorithmic/Procedural/Generative

### First Sequence (wiry plants with sparse leaves)

1. Draw a line, with a random length.
2. Subdivide into a random number of randomly distributed segments.
  a. use perlin noise to modulate each point along the way.
  b. Draw in a direction, and at each sampling point, turn in a random direction within a certain angle.
3. Attach an egg shaped leaf at random segments.
    
### Enhancements

One way to make better wiry sticks is to give it a more interesting shape before randomizing it. 
If it is made turbulent, and given a bit of a curve, I would think that the stick would seem less rigid. 
(Not line based, but curve based)

## Handdrawn Version

Here is another idea, if I figure out the openCV linedrawing-to-polyline thing I've been thinking about, I can start playing with interesting ways to make that drawing move. 
This might be better, it's simpler, it does what I want it to (in that it simulates the handdrawn ones I've worked on). 

I would essentially convert the image, get the poly lines, and then gently modulate them horizontally. I might want to start with this, and then 
also work on the other algorithmic version.
