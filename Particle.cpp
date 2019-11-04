#include "Particle.h"
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

Particle::Particle():m_x(0),m_y(0)
{
    m_direction = (2.0 * M_PI * rand())/RAND_MAX;
    m_speed = (0.00005 * rand())/RAND_MAX;
}
Particle::~Particle()
{

}
void Particle::update(int interval)
{
    double xspeed = m_speed * cos(m_direction) * interval;
    double yspeed = m_speed * sin(m_direction) * interval;
    m_x += xspeed;
    m_y += yspeed;

}
