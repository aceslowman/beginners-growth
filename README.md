# beginners-growth
Procedural plant experiments

Before I begin exploring L-Systems, I want to see if I can mimic plant growth similar to what I might draw by hand.

---

## Sequence

1. First, draw a line from one point, to a random point. The random point is constrained by the random point vector that came before it. (repeat n times)
2. Once one branch is drawn, loop through points along the branch, and create new branches from random points.
3. Once n number of levels have been looped through, change the drawing mode (i.e points to triangle strip)

---

## Parameters

* **Density**
  * *What is the probability of a new branch being drawn off of a particular node?*
* **Length**
  * *What is the maximum length of a segment?*
* **Segments**
  * *How many bends does the branch have?*
* **Depth (levels)**
  * *How deep does the recursion go?*
* **Smoothness / Straightness**
  * *How constrained are the points on the branch to a particular vector?*
* **Leaf Width**
  * *How wide is the leaf?*
  * *What is the theta between the two sides of a leaf?*
* **Leaf Level**
  * *At what point do we begin seeing leaves?*
---

## Methods

This is something I need to put a lot of thought into.

I need to be able to just create a branch, in the main.cpp file. All I pass to that branch is it's parameters, or just the ones necessary.

```
  setup();
  update();
  draw();
```  

Within setup, I need to set all of my defaults. All of these should be normalized, 0 - 1. With that said, a few of these have no maximum, so some sort of limit will need to be implemented, particularly segments and depth.

```
void Growth::setup(){
  this->density      = ofRandomuf();
  this->length       = ofRandomuf();
  this->segments     = ofRandom(10);
  this->depth        = ofRandom(10);
  this->leaf_level   = ofRandom(10);
  this->straightness = ofRandomuf();
}
```

I also want to make sure that the method between leaves and branches stay as similar as possible. All will use an ofMesh class.

This also brings me to the issue of leaves. It seems important to have some separate handling of leaves, but most of the methods will be the same. *Maybe* this means that I shouldn't extend ofMesh, instead have the Growth class own ofMesh objects.

* There is a branch
* The branch has leaves
* LATER: A tree has branches, each of which have leaves.

```
class Growth : public ofMesh {

  public:

    void setup();
    void update();
    void draw();

    float density;
    float length;
    int   segments;
    int   depth;
    int   leaf_level;
    float straightness;

    //other growth factors

    float f_dim; //diminishment factor, size of growth in subsequent levels

    ofMesh branch;
    vector<ofMesh> leaves;
}
```

Essentially, I think if we go beyond a certain number of levels (leaf_level), then we will switch to placing this mesh within a vector, instead of appending it onto the preexisting branch.

## generateBranch()

The generateBranch() method is going to do the bulk of the actual construction. For generateBranch() to work, we need to know a few things.

1. Where did the growth start? The root? The node on a branch before it?
2. What is the initial vector? Which direction was this growth pointing?
3. What level of recursion are we at?

I then need to get a few pieces of information for this specific iteration. Every level deeper we go, some things change.

* Branches become shorter, and consist of less segments. (t_length, t_segments)

These will be dictated by some sort of factor affecting how fast subsequent branches shrink in size.

The factor is f_dim, I want it to be -1 - 1, with the maximum being some hardcoded limit in small or large sizes.

This is going to be implemented with `pow(f_dim,level)`

```
//Diminish parameters
int t_segments = this->segments * pow(f_dim,level);
float t_length = this->length   * pow(f_dim,level);
```

Now, to actual work through the cycle, I need to calculate the point for step 1. t_point is the vector, times the length, plus the previous t_point.

```
t_point = t_point + (t_vec * t_length);
```

After everything else is calculated, at the end of the loop I need to prepare the new semi-random vector. The vector is the previous vector, plus a random direction, -1 to 1, diminished by a degree of smoothness.

```
t_vec = ofVec3f(
  ofClamp(t_vec.x + (ofRandomf() * straightness),0.0,1.0),
  ofClamp(t_vec.y + (ofRandomf() * straightness),0.0,1.0),
  ofClamp(t_vec.z + (ofRandomf() * straightness),0.0,1.0)
);
```

NOTE NOTE NOTE: This is actually a spot where I lose the ability to properly diminish the size. If the vector is always adding or removing some amount from the previous vector, and `t_point = t_point + (t_vec * t_length);`, then I will get unpredictable lengths based on straightness. I need to get random t_length based off of length, which needs to update with every point. T_VEC NEEDS TO BE A UNIT VECTOR

```
t_point = t_point + (t_vec * ( t_length * ofRandomuf() ) );
```

There is an opportunity to create some simple debugging colors here as well. The further along the branch you get, the more the colors turn from 1,0,0 to 0,0,1.

```
t_mesh.addColor(ofFloatColor(i/t_segments,1 - (i/t_segments),0));
```

Also, I need to have the type of drawing mode change, depending on what level we are at.

```
void Growth::generateBranch(ofVec3f origin, ofVec3f initial_vector, int level){
  ofMesh t_mesh;

  if(current_level > leaf_level){
    t_mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
  }else{
    t_mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
  }

  //Diminish parameters
  int t_segments = this->segments * pow(f_dim,level);
  float t_length = this->length   * pow(f_dim,level);

  //Initialize t_point to match initial point
  ofVec3f t_point = origin;

  //begin assembling one cycle of sequence
  for(int i = 0; i < t_segments; i++){

    t_point = t_point + (t_vec * ( t_length * ofRandomuf() ) );

    t_mesh.addVertex(t_point);
    t_mesh.addColor(ofFloatColor(i/t_segments,1 - (i/t_segments),0));

    t_vec = ofVec3f(
      ofClamp(t_vec.x + (ofRandomf() * straightness),0.0,1.0),
      ofClamp(t_vec.y + (ofRandomf() * straightness),0.0,1.0),
      ofClamp(t_vec.z + (ofRandomf() * straightness),0.0,1.0)
    );
  }

  if(current_level > leaf_level){
    leaves.push_back(t_mesh);
  }else{
    branch.append(t_mesh);
  }
}
```

---

  ![Screenshot](../images/basic-sequence.png?raw=true)
