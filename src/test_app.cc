#include "../include/app.h"
#include <iostream>
#include <cmath>

struct vec3
{
  float x,y,z;
  float norm() const;
};

float vec3::norm() const {
  return sqrt(x*x + y*y + z*z);
}

// struct rot3d{
//   float r[9];
//   rot3d(vec3 dir, float angle);
// };


// rot3d::rot3d(vec3 dir, float angle){
//   // change system of coordinaate such that dir is {0,0,1}
//   /*
//     V =(x,y,z)
//     R = 3x3 mat 
//     V' = (0,0,|v|)

//     0   a b c  x   ax+by+cz
//     0 = b d e  y = bx+dy+ex 
//    |v|  c e f  z   cx+ey+fz
//   */

//   // rotate by angle ( now is a rotaxion in the x-y plane)
//   // change back to the original system 
  

// }

vec3 operator+(const vec3& A,const vec3& B){
  vec3 C = A;
  C.x+=B.x; C.y+=B.y; C.z+=B.z;
  return C;
}
vec3 operator/(const vec3& A,const float& s){
  vec3 C = A;
  C.x/=s; C.y/=s; C.z/=s;
  return C;
}

void operator+=(vec3& A,const vec3& B){
  A.x+=B.x; A.y+=B.y; A.z+=B.z;
}
vec3 operator-(const vec3& A){
  return vec3{-A.x,-A.y,-A.z};
}
vec3 operator-(const vec3& A, const vec3& B){
  return A+ (-B);
}
void operator-=(vec3& A, const vec3&B){
  A += (-B);
}

struct connection{
 int a,b;
};

vec3 get_centroid(std::vector<vec3> vertex){
  vec3 C{0,0,0};
  for(auto& v : vertex){
    C+=v;
  }
  return C/size(vertex);
}


void rotate_three_angle(vec3& point, float thetax, float thetay, float thetaz){
  float rad =0;
  rad = thetax;
  point.y = cos(rad) * point.y - sin(rad) * point.z;
  point.z = sin(rad) * point.y + cos(rad) * point.z;

  rad = thetay;
  point.x = cos(rad)*point.x + sin(rad)*point.z;
  point.z = -sin(rad)*point.x + cos(rad)*point.y;

  rad = thetaz;
  point.x = cos(rad)*point.x - sin(rad)*point.y;
  point.y = sin(rad)*point.x + cos(rad)*point.y;

}

void rotate_axis_angle(vec3& point, const vec3& dir, const float angle){
  float c = cos(angle),s = sin(angle);
  float n = dir.norm();
  float x = dir.x/n, y=dir.y/n, z = dir.z/n;
  vec3 new_p{0,0,0};
  new_p.x = (c+x*x*(1-c)) * point.x + (x*y*(1-c)-z*s)*point.y + (x*z*(1-c)+y*s)*point.z;
  new_p.y = (y*x*(1-c)+z*s)*point.x + (c+y*y*(1-c)) * point.y + (y*z*(1-c)-x*s)*point.z;
  new_p.z = (z*x*(1-c)-y*s)*point.x + (z*y*(1-c)+x*s)*point.y + (c+z*z*(1-c)) * point.z; 
  point = new_p;
}
 
void line(App &app, float x1, float y1, float x2, float y2){
  float dx = x2-x1;
  float dy = y2-y1;
  float d = sqrt(dy*dy +dx*dx);
  float alpha = atan2(dy,dx);
  for(float i=0.0; i<d; i+=0.1){
    app.pixel(x1+cos(alpha)*i, y1 +sin(alpha)*i);
  }
}

int main(){
  App app;

  /*   
       6--------7
      /|       /|
     / |      / |
    2--|-----4  |
    |  3-----|--5 
    | /      | /
    |/       |/
    0--------1  
  */
  std::vector<vec3> vertex{
    {100,100,100},
    {300,100,100},
    {100,400,100},
    {100,100,200},  
    {300,400,100},
    {300,100,200},
    {100,400,200},
    {300,400,200}
  };
  std::vector<connection> sides{{0,1},{0,2},{0,3},{1,4},{1,5},{2,4},{2,6},{3,5},{3,6},{4,7},{5,7},{6,7}};
  
  vec3 c = get_centroid(vertex);

  vec3 O =vec3{app.center().x,app.center().y,100.0};

  std::cout << "screen center: x = "<< O.x << ", y = "<< O.y << std::endl;
  
  c -= O;
  
  // translate the cube to the origin
  for(auto& v : vertex)
    v-=c;

  while(true){
    for(auto& v : vertex){
      v-=O;
      // rotate_three_angle(v,0.,0.,0.20);
      rotate_axis_angle(v,vec3{1,1,1},0.05);
      v+=O;
    } 
    for(auto& s : sides){
      vec3& x = vertex[s.a];
      vec3& y = vertex[s.b]; 
      line(app,x.x,x.y,y.x,y.y);
    }
    // app.center();
    // line(app,0,0,O.x,O.y);
    app.show();
    app.clear();
    app.input();
    SDL_Delay(30);  
  }

  return 0;
}