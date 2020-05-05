#include <math.h>   // smallpt, a Path Tracer by Kevin Beason, 2008
#include <stdlib.h> // Make : g++ -O3 -fopenmp smallpt.cpp -o smallpt
#include <stdio.h>  //        Remove "-fopenmp" for g++ version < 4.2
#include "random.h"
struct Vec {        // Usage: time ./smallpt 5000 && xv image.ppm
  double x, y, z;                  // position, also color (r,g,b)
  Vec(double x_=0, double y_=0, double z_=0){ x=x_; y=y_; z=z_; }
  Vec operator+(const Vec &b) const { return Vec(x+b.x,y+b.y,z+b.z); }
  Vec operator-(const Vec &b) const { return Vec(x-b.x,y-b.y,z-b.z); }
  Vec operator*(double b) const { return Vec(x*b,y*b,z*b); }
  Vec mult(const Vec &b) const { return Vec(x*b.x,y*b.y,z*b.z); }
  Vec& norm(){ return *this = *this * (1/sqrt(x*x+y*y+z*z)); }
  double dot(const Vec &b) const { return x*b.x+y*b.y+z*b.z; } // cross:
  Vec operator%(Vec&b){return Vec(y*b.z-z*b.y,z*b.x-x*b.z,x*b.y-y*b.x);}
};
struct Ray { Vec o, d; Ray(Vec o_, Vec d_) : o(o_), d(d_) {} };
enum Refl_t { DIFF, SPEC, REFR };  // material types, used in radiance()
struct Sphere {
  double rad;       // radius
  Vec p, e, c;      // position, emission, color
  Refl_t refl;      // reflection type (DIFFuse, SPECular, REFRactive)
  Sphere(){};
  Sphere(double rad_, Vec p_, Vec e_, Vec c_, Refl_t refl_):
    rad(rad_), p(p_), e(e_), c(c_), refl(refl_) {}
  double intersect(const Ray &r) const { // returns distance, 0 if nohit
    Vec op = p-r.o; // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
    double t, eps=1e-4, b=op.dot(r.d), det=b*b-op.dot(op)+rad*rad;
    if (det<0) return 0; else det=sqrt(det);
    return (t=b-det)>eps ? t : ((t=b+det)>eps ? t : 0);
  }
};
Vec Cen(50,40.8,-860);
Sphere spheres[489];
inline double clamp(double x){ return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x){ return int(pow(clamp(x),1/2.2)*255+.5); }
inline bool intersect(const Ray &r, double &t, int &id){
  double n=sizeof(spheres)/sizeof(Sphere), d, inf=t=1e20;
  for(int i=int(n);i--;) if((d=spheres[i].intersect(r))&&d<t){t=d;id=i;}
  return t<inf;
}
void construct_scene(){
//Scene: radius, position, emission, color, material
   spheres[0] = Sphere(1560, Vec(0,5000,3000), Vec(1,.9,.8)*1.2e1*1.56*2,Vec(), DIFF); // sun
   //Sphere(1560, Vec(1,0,2)*3500,Vec(1,.5,.05)*4.8e1*1.56*2, Vec(),  DIFF), // horizon sun2
//   Sphere(10000,Cen+Vec(0,0,-200), Vec(0.0627, 0.188, 0.569)*6e-2*8, Vec(.7,.7,1)*.25,  DIFF), // sky
   //Sphere(10000,Cen+Vec(0,0,-200), Vec(0.00063842, 0.02001478, 0.28923243)*6e-2*8, Vec(0.01,0.01,0.01),  DIFF), // sky
//Sphere(10000,Cen+Vec(0,0,-20000), Vec(), Vec(100,100,100),  DIFF), // sky
  //spheres[1] = Sphere(100000, Vec(50, -100000, 0),  Vec(),Vec(0.5f,0.5f,0.5f),DIFF); // grnd
  spheres[1] = Sphere(1000, Vec(0, -1000, 0),  Vec(),Vec(0.5f,0.5f,0.5f),DIFF); // grnd
  //Sphere(110000, Vec(50, -110048.5, 0),  Vec(.9,.5,.05)*4,Vec(),DIFF),// horizon brightener
  //Sphere(4e4, Vec(50, -4e4-30, -3000),  Vec(),Vec(.2,.2,.2),DIFF),// mountains
//  Sphere(3.99e4, Vec(50, -3.99e4+20.045, -3000),  Vec(),Vec(.7,.7,.7),DIFF),// mountains snow

   // middle sphere
  //spheres[2] = Sphere(26.5,Vec(22,26.5,42),   Vec(),Vec(1,1,1)*.596, DIFF); // white Mirr
  //spheres[3] = Sphere(13,Vec(75,13,82),   Vec(),Vec(.96,.96,.96)*.96, REFR);// Glas
  //spheres[4] = Sphere(22,Vec(87,22,24),   Vec(),Vec(.6,.6,.6)*.696, REFR);    // Glas2
  spheres[2] = Sphere(1.0f,Vec(0.0f, 1.0f, 0.0),   Vec(),Vec(1,1,1)*.596, DIFF); // white Mirr
  spheres[3] = Sphere(1.0f,Vec(-4.0f, 1.0f, 0.0),   Vec(),Vec(.96,.96,.96)*.96, REFR);// Glas
  spheres[4] = Sphere(1.0f,Vec(4.0f, 1.0f, 0.0),   Vec(),Vec(.6,.6,.6)*.696, REFR);    // Glas2
  int idx= 5;
  // Small Spheres
        uint32_t seed = 0x6314759;
        for (int a = -11; a < 11; a++)
        {
            for (int b = -11; b < 11; b++)
            {
                float chooseMat = randf(seed);
                float x = a + 0.8f*randf(seed);
                float y = 0.2f;
                float z = b + 0.9f*randf(seed);
                float z_squared = (z)*(z);
                float dist = sqrtf(
                    (x-4.0f)*(x-4.0f) +
                    //(y-0.2f)*(y-0.2f) +
                    z_squared
                    );

                // keep out area near medium spheres
                if ((dist > 0.9f) ||
                    ((z_squared > 0.7f) && ((x*x - 16.0f) > -2.f)))
                {
                    if (chooseMat < 0.70f)
                    {
                        spheres[idx] = Sphere(0.2f,Vec(x, y, z),   Vec(),Vec(1,1,1)*.596, DIFF); 
                        //geometryList.push_back(new ioSphere(x,y,z, 0.2f));
                        /*materialList.push_back(new ioLambertianMaterial(
                                                   new ioConstantTexture(make_float3(randf(seed), randf(seed), randf(seed))
                                                       )));*/
                    }
                    else if (chooseMat < 0.85f)
                    {
                        spheres[idx] = Sphere(0.2f,Vec(x, y, z),   Vec(),Vec(1,1,1)*.596, REFR); 
                        /*geometryList.push_back(new ioSphere(x,y,z, 0.2f));
                        materialList.push_back(new ioMetalMaterial(
                                                   new ioConstantTexture(make_float3(0.5f*(1.0f-randf(seed)),
                                                                                     0.5f*(1.0f-randf(seed)),
                                                                                     0.5f*(1.0f-randf(seed)))),
                                                   0.5f*randf(seed)));*/
                    }
                    else if (chooseMat < 0.93f)
                    {
                        spheres[idx] = Sphere(0.2f,Vec(x, y, z),   Vec(),Vec(1,1,1)*.596, DIFF); 
                        //geometryList.push_back(new ioSphere(x,y,z, 0.2f));
                        //materialList.push_back(new ioDielectricMaterial(1.5f));
                    }
                    else
                    {
                        /*geometryList.push_back(new ioSphere(x,y,z, 0.2f));
                        materialList.push_back(new ioDielectricMaterial(1.5f));
                        geometryList.push_back(new ioSphere(x,y,z, -(0.2f-0.007f)));
                        materialList.push_back(new ioDielectricMaterial(1.5f));*/
                        spheres[idx] = Sphere(0.2f,Vec(x, y, z),   Vec(),Vec(1,1,1)*.596, DIFF); 
                    }
                }
                idx++;
            }
        }
}

Vec radiance(const Ray &r, int depth, unsigned short *Xi){
  double t;                               // distance to intersection
  int id=0;                               // id of intersected object
  if (!intersect(r, t, id)) return Vec(); // if miss, return black
  const Sphere &obj = spheres[id];        // the hit object
  Vec x=r.o+r.d*t, n=(x-obj.p).norm(), nl=n.dot(r.d)<0?n:n*-1, f=obj.c;
  double p = f.x>f.y && f.x>f.z ? f.x : f.y>f.z ? f.y : f.z; // max refl
  if (++depth>5) if (erand48(Xi)<p) f=f*(1/p); else return obj.e; //R.R.
  if (obj.refl == DIFF){                  // Ideal DIFFUSE reflection
    double r1=2*M_PI*erand48(Xi), r2=erand48(Xi), r2s=sqrt(r2);
    Vec w=nl, u=((fabs(w.x)>.1?Vec(0,1):Vec(1))%w).norm(), v=w%u;
    Vec d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).norm();
    return obj.e + f.mult(radiance(Ray(x,d),depth,Xi));
  } else if (obj.refl == SPEC)            // Ideal SPECULAR reflection
    return obj.e + f.mult(radiance(Ray(x,r.d-n*2*n.dot(r.d)),depth,Xi));
  Ray reflRay(x, r.d-n*2*n.dot(r.d));     // Ideal dielectric REFRACTION
  bool into = n.dot(nl)>0;                // Ray from outside going in?
  double nc=1, nt=1.5, nnt=into?nc/nt:nt/nc, ddn=r.d.dot(nl), cos2t;
  if ((cos2t=1-nnt*nnt*(1-ddn*ddn))<0)    // Total internal reflection
    return obj.e + f.mult(radiance(reflRay,depth,Xi));
  Vec tdir = (r.d*nnt - n*((into?1:-1)*(ddn*nnt+sqrt(cos2t)))).norm();
  double a=nt-nc, b=nt+nc, R0=a*a/(b*b), c = 1-(into?-ddn:tdir.dot(n));
  double Re=R0+(1-R0)*c*c*c*c*c,Tr=1-Re,P=.25+.5*Re,RP=Re/P,TP=Tr/(1-P);
  return obj.e + f.mult(depth>2 ? (erand48(Xi)<P ?   // Russian roulette
    radiance(reflRay,depth,Xi)*RP:radiance(Ray(x,tdir),depth,Xi)*TP) :
    radiance(reflRay,depth,Xi)*Re+radiance(Ray(x,tdir),depth,Xi)*Tr);
}
int main(int argc, char *argv[]){
  int w=1024, h=768, samps = argc==2 ? atoi(argv[1])/4 : 1; // # samples
  construct_scene();
  Ray cam(Vec(50,52,295.6), Vec(0,-0.042612,-1).norm()); // cam pos, dir
  Vec cx=Vec(w*.5135/h), cy=(cx%cam.d).norm()*.5135, r, *c=new Vec[w*h];
#pragma omp parallel for schedule(dynamic, 1) private(r)       // OpenMP
  for (int y=0; y<h; y++){                       // Loop over image rows
    fprintf(stderr,"\rRendering (%d spp) %5.2f%%",samps*4,100.*y/(h-1));
    for (unsigned short x=0, Xi[3]={0,0,y*y*y}; x<w; x++)   // Loop cols
      for (int sy=0, i=(h-y-1)*w+x; sy<2; sy++)     // 2x2 subpixel rows
        for (int sx=0; sx<2; sx++, r=Vec()){        // 2x2 subpixel cols
          for (int s=0; s<samps; s++){
            double r1=2*erand48(Xi), dx=r1<1 ? sqrt(r1)-1: 1-sqrt(2-r1);
            double r2=2*erand48(Xi), dy=r2<1 ? sqrt(r2)-1: 1-sqrt(2-r2);
            Vec d = cx*( ( (sx+.5 + dx)/2 + x)/w - .5) +
                    cy*( ( (sy+.5 + dy)/2 + y)/h - .5) + cam.d;
            r = r + radiance(Ray(cam.o+d*140,d.norm()),0,Xi)*(1./samps);
          } // Camera rays are pushed ^^^^^ forward to start in interior
          c[i] = c[i] + Vec(clamp(r.x),clamp(r.y),clamp(r.z))*.25;
        }
  }
  FILE *f = fopen("image.ppm", "w");         // Write image to PPM file.
  fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
  for (int i=0; i<w*h; i++)
    fprintf(f,"%d %d %d ", toInt(c[i].x), toInt(c[i].y), toInt(c[i].z));
}
