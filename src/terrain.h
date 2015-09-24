#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class Terrain{
    public:
        vector< vector<float> > points;
        int cols, rows;

        Terrain(int rows, int cols){
            this->rows = rows;
            this->cols = cols;

            //gera valores aleatórios de altura para o terreno
            for(int r = 0; r < rows; r++){
                points.push_back(vector<float>()); //cria uma linha no array
                for(int c = 0; c < cols; c++){
                    // gera um float random de 0 a 1
                    float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

                    points[r].push_back(y);
                }
            }
        }
};
