#ifndef PARTICLE_H_
#define PARTICLE_H_

class Particle
{
public:
    double m_x, m_y;
    double m_speed;
    double m_direction;
    Particle();
    virtual ~Particle();
    void update(int interval);
};
#endif