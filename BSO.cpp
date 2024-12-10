#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm> // std::sort

using namespace std;

const int POP_SIZE = 30; 
const int MAX_ITER = 1000; 
const double LOWER_BOUND = -10.0; 
const double UPPER_BOUND = 10.0; 
const int NUM_ELITES = 5; 
const double PERTURBATION = 0.1; 


double objectiveFunction(double x) {
    return x * x - 4 * x + 4; // Ví d?: hàm b?c 2 f(x) = x^2 - 4x + 4
}


double randInRange(double low, double high) {
    return low + (rand() / (RAND_MAX + 1.0)) * (high - low);
}


double perturb(double center, double range) {
    return center + randInRange(-range, range);
}


struct Particle {
    double position; 
    double value;   

    
    Particle(double pos) : position(pos), value(objectiveFunction(pos)) {}

    
    bool operator<(const Particle& other) const {
        return value < other.value;
    }
};

int main() {
    srand(time(0)); 

   
    vector<Particle> swarm;
    for (int i = 0; i < POP_SIZE; i++) {
        swarm.emplace_back(randInRange(LOWER_BOUND, UPPER_BOUND));
    }

   
    for (int iter = 0; iter < MAX_ITER; iter++) {
       
        sort(swarm.begin(), swarm.end());

        
        vector<Particle> elites(swarm.begin(), swarm.begin() + NUM_ELITES);

        
        vector<Particle> newParticles;
        for (int i = 0; i < POP_SIZE - NUM_ELITES; i++) {
            
            const Particle& elite1 = elites[rand() % NUM_ELITES];
            const Particle& elite2 = elites[rand() % NUM_ELITES];

           
            double newPosition = (elite1.position + elite2.position) / 2.0;
            newPosition = perturb(newPosition, PERTURBATION);
            
           
            newPosition = max(LOWER_BOUND, min(UPPER_BOUND, newPosition));
            newParticles.emplace_back(newPosition);
        }

        
        swarm = elites;
        swarm.insert(swarm.end(), newParticles.begin(), newParticles.end());

        
        if (iter % 100 == 0) {
            cout << "Vong lap " << iter << ": Vi tri tot nhat = " 
                 << swarm[0].position << ", Gia tri = " << swarm[0].value << endl;
        }
    }

   
    cout << "Giai phap tot nhat tim thay: Vi trí = " 
         << swarm[0].position << ", Gia tri = " << swarm[0].value << endl;

    return 0;
}


