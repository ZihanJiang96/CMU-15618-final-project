#include <iostream>
#include <random>
#include "random.h"
#include <stdlib.h> // Make : g++ -O3 -fopenmp smallpt.cpp -o smallpt
#include <stdio.h>
#include <math.h> 
using namespace std;

#define N 1000
#define LEFT -300
#define RIGHT 300

int main() {
    freopen("scene","w",stdout);
    //std::default_random_engine generator;
    //std::uniform_int_distribution<int> distribution(LEFT, RIGHT);
    float x_array[484];
    float y_array[484];
    float z_array[484];
    float r_array[484];
    float g_array[484];
    float b_array[484];
    int method_array[484];
    int count = 0;

    uint32_t seed = 0x6314759;
        for (int a = -11; a < 11; a++)
        {
            for (int b = -11; b < 11; b++)
            {
                float chooseMat = randf(seed);
                float x = (a + 0.8f*randf(seed))*20;
                float y = 6;
                float z = (b + 0.9f*randf(seed))*20;
                float z_squared = (z)*(z);
                float r= ((float)rand())/RAND_MAX;
                float g = ((float)rand())/RAND_MAX;
                float blue =((float)rand())/RAND_MAX;
                float dist = sqrtf(
                    (x-13.0f)*(x-13.0f) +
                    //(y-0.2f)*(y-0.2f) +
                    (z-82.0f)*(z-82.0f)
                    );

                // keep out area near medium spheres
                if ((dist > 10.0f) ||
                    ((z*z - 82*82 > 10.0f) && ((x*x - 13.0f*13.0f) > -10.f)))
                {
                    x_array[count] = x;
                    y_array[count] = y;
                    z_array[count] = z;
                    if (chooseMat < 0.70f)
                    {
                        r_array[count] = r;
                        g_array[count] = g;
                        b_array[count] = b;
                        method_array[count] = 1;
                        //cout << 5 << x << y << z << 0 << 0 << 0 << r << g << blue << 1 << endl;
                        //spheres[idx] = Sphere(5.0f,Vec(x, y, z),   Vec(),Vec(r,g,blue), DIFF); 
                        //geometryList.push_back(new ioSphere(x,y,z, 0.2f));
                    }
                    else if (chooseMat < 0.85f)
                    {
                        r_array[count] = 0.96*0.9;
                        g_array[count] = 0.96*0.9;
                        b_array[count] = 0.96*0.9;
                        method_array[count] = 2;
                        //cout << 5 << x << y << z << 0 << 0 << 0 << 0.96*0.9 << 0.96*0.9 << 0.96*0.9 << 2 << endl;
                        //spheres[idx] = Sphere(5.0f,Vec(x, y, z),   Vec(),Vec(.96,.96,.96)*.9, REFR); 
                    }
                    else if (chooseMat < 0.93f)
                    {
                        r_array[count] = 0.96*0.9;
                        g_array[count] = 0.96*0.9;
                        b_array[count] = 0.96*0.9;
                        method_array[count] = 3;
                        //cout << 5 << x << y << z << 0 << 0 << 0 << 0.96*0.9 << 0.96*0.9 << 0.96*0.9 << 3 << endl;
                        //spheres[idx] = Sphere(5.0f,Vec(x, y, z),   Vec(),Vec(.96,.96,.96)*.9, SPEC); 
                    }
                    else
                    {
                         r_array[count] = r;
                        g_array[count] = g;
                        b_array[count] = b;
                        method_array[count] = 1;
                        //cout << 5 << x << y << z << 0 << 0 << 0 << r << g << blue << 1 << endl;
                        //spheres[idx] = Sphere(5.0f,Vec(x, y, z),   Vec(),Vec(r,g,blue), DIFF); 
                    }
                    count++;
                }
            }
        }



    cout << 500 << " " << count+5 << endl;

    // sun
    cout << 500 << " " << 0 << " "<< 5000 << " " << 6000 << " " << 1*1.2e1*1.56*2 << " " << 0.9*1.2e1*1.56*2 << " " << 0.8*1.2e1*1.56*2 << " " << 0 << " " << 0 << " " << 0 << " " << 1 << endl;

    // ground
    cout << 100000 << " "  << 50 << " " << 100000 << " " << 0  << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0.1 << " " << 0.1 << " " << 0.1 << endl;

    // middle sphere
    cout << 26.5 << " " << 77 << " " << 26.5 << " " << 85 << " " << 0 << " " << 0  << " " << 0  << " " << 0.3 << " " << 0.1 << " " << 0.1 <<  " " << 1 << endl;
    cout << 22 << " " << 35 << " " << 13 <<  " " << 50 << " " << 0 << " " << 0 << " " << 0 << " " << 0.96*0.96 << " " << 0.96*0.96 << " " << 0.96*0.96 << " " << 2 << endl;
    cout << 13 << " " << 25 << " " << 22 << " " << 25 << " " << 0 <<  " " << 0 << " " << 0 << " " << 0.6*0.696 << " " << 0.6*0.696 << " " << 0.6*0.696 <<  " " << 2 << endl;

    for(int i=0; i<count; ++i){
        cout << 5 << " " << x_array[i] << " " << y_array[i] << " " << z_array[i] << " " << 0 <<  " " << 0 <<  " " << 0 <<  " " << r_array[i] <<  " " << g_array[i] << " " <<  b_array[i] << " " << method_array[i] << endl;
    }

    
	return 0;
}
