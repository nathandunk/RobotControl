#include <RobotModel.hpp>
#include <RobotParams.hpp>

using namespace mahi::util;

RobotModel::RobotModel(){
    zero();
}

void RobotModel::update(double dt){
    
    Matrix3d a = M();
    Vector3d b = m_s.Tau - V() - G() - B() - Fk();
    Vector3d Qdd = a.householderQr().solve(b);

    integrate_state(Qdd,dt);
}

void RobotModel::integrate_state(Vector3d Qdd, double dt){
    // Vector3d Qd = m_s.Qd + dt * 0.5 * (m_s.Qdd + Qdd);
    // m_s.Q = m_s.Q + dt * 0.5 * (m_s.Qd + Qd);
    
    // m_s.Qd  = Qd;
    // m_s.Qdd = Qdd;
    Vector3d Qd  = m_s.Qd + dt * 0.5 * (m_s.Qdd + Qdd);
    Vector3d Q   = m_s.Q  + dt * 0.5 * (m_s.Qd  + Qd);
    m_s.Qdd = Qdd; m_s.Qd = Qd; m_s.Q = Q;
}

Matrix3d RobotModel::M(){
    Matrix3d M = Matrix3d::Zero();

    double q1 = m_s.Q(0); double q2 = m_s.Q(1); double q3 = m_s.Q(2);

    M(0,0) = Ic1xx+Ic2xx*(1.0/2.0)+Ic3xx*(1.0/2.0)+Ic2yy*(1.0/2.0)+Ic3yy*(1.0/2.0)+Ic3xx*cos(q2*2.0+q3*2.0)*(1.0/2.0)-Ic3yy*cos(q2*2.0+q3*2.0)*(1.0/2.0)+Ic3xy*sin(q2*2.0+q3*2.0)+(Pc1x*Pc1x)*m1+(Pc1y*Pc1y)*m1+(Pc2x*Pc2x)*m2*(1.0/2.0)+(Pc2y*Pc2y)*m2*(1.0/2.0)+(Pc3x*Pc3x)*m3*(1.0/2.0)+(Pc2z*Pc2z)*m2+(Pc3y*Pc3y)*m3*(1.0/2.0)+(Pc3z*Pc3z)*m3+(l1*l1)*m3*(1.0/2.0)+Ic2xx*cos(q2*2.0)*(1.0/2.0)-Ic2yy*cos(q2*2.0)*(1.0/2.0)+Ic2xy*sin(q2*2.0)-(Pc2x*Pc2x)*m2*cos(q2*2.0)*(1.0/2.0)+(Pc2y*Pc2y)*m2*cos(q2*2.0)*(1.0/2.0)-(l1*l1)*m3*cos(q2*2.0)*(1.0/2.0)-(Pc3x*Pc3x)*m3*cos(q2*2.0+q3*2.0)*(1.0/2.0)+(Pc3y*Pc3y)*m3*cos(q2*2.0+q3*2.0)*(1.0/2.0)+Pc3x*l1*m3*cos(q3)-Pc3y*l1*m3*sin(q3)-Pc3x*l1*m3*cos(q2*2.0+q3)+Pc3y*l1*m3*sin(q2*2.0+q3)+Pc2x*Pc2y*m2*sin(q2*2.0)+Pc3x*Pc3y*m3*sin(q2*2.0+q3*2.0);
    M(0,1) = -Ic3xz*cos(q2+q3)+Ic3yz*sin(q2+q3)-Ic2xz*cos(q2)+Ic2yz*sin(q2)-Pc3x*Pc3z*m3*cos(q2+q3)+Pc3y*Pc3z*m3*sin(q2+q3)-Pc2x*Pc2z*m2*cos(q2)+Pc2y*Pc2z*m2*sin(q2)-Pc3z*l1*m3*cos(q2);
    M(0,2) = -Ic3xz*cos(q2+q3)+Ic3yz*sin(q2+q3)-Pc3x*Pc3z*m3*cos(q2+q3)+Pc3y*Pc3z*m3*sin(q2+q3);
    M(1,0) = -Ic3xz*cos(q2+q3)+Ic3yz*sin(q2+q3)-Ic2xz*cos(q2)+Ic2yz*sin(q2)-Pc3x*Pc3z*m3*cos(q2+q3)+Pc3y*Pc3z*m3*sin(q2+q3)-Pc2x*Pc2z*m2*cos(q2)+Pc2y*Pc2z*m2*sin(q2)-Pc3z*l1*m3*cos(q2);
    M(1,1) = Ic2xx+Ic3xx+(Pc2x*Pc2x)*m2+(Pc2y*Pc2y)*m2+(Pc3x*Pc3x)*m3+(Pc3y*Pc3y)*m3+(l1*l1)*m3+Pc3x*l1*m3*cos(q3)*2.0-Pc3y*l1*m3*sin(q3)*2.0;
    M(1,2) = Ic3xx+(Pc3x*Pc3x)*m3+(Pc3y*Pc3y)*m3+Pc3x*l1*m3*cos(q3)-Pc3y*l1*m3*sin(q3);
    M(2,0) = -Ic3xz*cos(q2+q3)+Ic3yz*sin(q2+q3)-Pc3x*Pc3z*m3*cos(q2+q3)+Pc3y*Pc3z*m3*sin(q2+q3);
    M(2,1) = Ic3xx+(Pc3x*Pc3x)*m3+(Pc3y*Pc3y)*m3+Pc3x*l1*m3*cos(q3)-Pc3y*l1*m3*sin(q3);
    M(2,2) = Ic3xx+(Pc3x*Pc3x)*m3+(Pc3y*Pc3y)*m3;
    
    return M;
}

Vector3d RobotModel::V(){
    Vector3d V = Vector3d::Zero();
    double q1  = m_s.Q(0);  double q2  = m_s.Q(1);  double q3  = m_s.Q(2);
    double q1d = m_s.Qd(0); double q2d = m_s.Qd(1); double q3d = m_s.Qd(2);

    V[0] = Ic3yz*(q2d*q2d)*cos(q2+q3)+Ic3yz*(q3d*q3d)*cos(q2+q3)+Ic3xz*(q2d*q2d)*sin(q2+q3)+Ic3xz*(q3d*q3d)*sin(q2+q3)+Ic2yz*(q2d*q2d)*cos(q2)+Ic2xz*(q2d*q2d)*sin(q2)+Ic3yz*q2d*q3d*cos(q2+q3)*2.0+Ic3xz*q2d*q3d*sin(q2+q3)*2.0+Ic2xy*q1d*q2d*cos(q2*2.0)*2.0-Ic2xx*q1d*q2d*sin(q2*2.0)+Ic2yy*q1d*q2d*sin(q2*2.0)+Ic3xy*q1d*q2d*cos(q2*2.0+q3*2.0)*2.0+Ic3xy*q1d*q3d*cos(q2*2.0+q3*2.0)*2.0-Ic3xx*q1d*q2d*sin(q2*2.0+q3*2.0)-Ic3xx*q1d*q3d*sin(q2*2.0+q3*2.0)+Ic3yy*q1d*q2d*sin(q2*2.0+q3*2.0)+Ic3yy*q1d*q3d*sin(q2*2.0+q3*2.0)+Pc2y*Pc2z*m2*(q2d*q2d)*cos(q2)+Pc2x*Pc2z*m2*(q2d*q2d)*sin(q2)+Pc3z*l1*m3*(q2d*q2d)*sin(q2)+(Pc2x*Pc2x)*m2*q1d*q2d*sin(q2*2.0)-(Pc2y*Pc2y)*m2*q1d*q2d*sin(q2*2.0)+(l1*l1)*m3*q1d*q2d*sin(q2*2.0)+(Pc3x*Pc3x)*m3*q1d*q2d*sin(q2*2.0+q3*2.0)+(Pc3x*Pc3x)*m3*q1d*q3d*sin(q2*2.0+q3*2.0)-(Pc3y*Pc3y)*m3*q1d*q2d*sin(q2*2.0+q3*2.0)-(Pc3y*Pc3y)*m3*q1d*q3d*sin(q2*2.0+q3*2.0)+Pc3y*Pc3z*m3*(q2d*q2d)*cos(q2+q3)+Pc3y*Pc3z*m3*(q3d*q3d)*cos(q2+q3)+Pc3x*Pc3z*m3*(q2d*q2d)*sin(q2+q3)+Pc3x*Pc3z*m3*(q3d*q3d)*sin(q2+q3)+Pc3x*Pc3z*m3*q2d*q3d*sin(q2+q3)*2.0-Pc3y*l1*m3*q1d*q3d*cos(q3)-Pc3x*l1*m3*q1d*q3d*sin(q3)+Pc3y*l1*m3*q1d*q2d*cos(q2*2.0+q3)*2.0+Pc3y*l1*m3*q1d*q3d*cos(q2*2.0+q3)+Pc3x*l1*m3*q1d*q2d*sin(q2*2.0+q3)*2.0+Pc3x*l1*m3*q1d*q3d*sin(q2*2.0+q3)+Pc2x*Pc2y*m2*q1d*q2d*cos(q2*2.0)*2.0+Pc3x*Pc3y*m3*q1d*q2d*cos(q2*2.0+q3*2.0)*2.0+Pc3x*Pc3y*m3*q1d*q3d*cos(q2*2.0+q3*2.0)*2.0+Pc3y*Pc3z*m3*q2d*q3d*cos(q2+q3)*2.0;
    V[1] = -Ic2xy*(q1d*q1d)*cos(q2*2.0)+Ic2xx*(q1d*q1d)*sin(q2*2.0)*(1.0/2.0)-Ic2yy*(q1d*q1d)*sin(q2*2.0)*(1.0/2.0)-Ic3xy*(q1d*q1d)*cos(q2*2.0+q3*2.0)+Ic3xx*(q1d*q1d)*sin(q2*2.0+q3*2.0)*(1.0/2.0)-Ic3yy*(q1d*q1d)*sin(q2*2.0+q3*2.0)*(1.0/2.0)-(Pc2x*Pc2x)*m2*(q1d*q1d)*sin(q2*2.0)*(1.0/2.0)+(Pc2y*Pc2y)*m2*(q1d*q1d)*sin(q2*2.0)*(1.0/2.0)-(l1*l1)*m3*(q1d*q1d)*sin(q2*2.0)*(1.0/2.0)-(Pc3x*Pc3x)*m3*(q1d*q1d)*sin(q2*2.0+q3*2.0)*(1.0/2.0)+(Pc3y*Pc3y)*m3*(q1d*q1d)*sin(q2*2.0+q3*2.0)*(1.0/2.0)-Pc3y*l1*m3*(q3d*q3d)*cos(q3)-Pc3x*l1*m3*(q3d*q3d)*sin(q3)-Pc3y*l1*m3*(q1d*q1d)*cos(q2*2.0+q3)-Pc3x*l1*m3*(q1d*q1d)*sin(q2*2.0+q3)-Pc2x*Pc2y*m2*(q1d*q1d)*cos(q2*2.0)-Pc3x*Pc3y*m3*(q1d*q1d)*cos(q2*2.0+q3*2.0)-Pc3y*l1*m3*q2d*q3d*cos(q3)*2.0-Pc3x*l1*m3*q2d*q3d*sin(q3)*2.0;
    V[2] = -Ic3xy*(q1d*q1d)*cos(q2*2.0+q3*2.0)+Ic3xx*(q1d*q1d)*sin(q2*2.0+q3*2.0)*(1.0/2.0)-Ic3yy*(q1d*q1d)*sin(q2*2.0+q3*2.0)*(1.0/2.0)-(Pc3x*Pc3x)*m3*(q1d*q1d)*sin(q2*2.0+q3*2.0)*(1.0/2.0)+(Pc3y*Pc3y)*m3*(q1d*q1d)*sin(q2*2.0+q3*2.0)*(1.0/2.0)+Pc3y*l1*m3*(q1d*q1d)*cos(q3)*(1.0/2.0)+Pc3y*l1*m3*(q2d*q2d)*cos(q3)+Pc3x*l1*m3*(q1d*q1d)*sin(q3)*(1.0/2.0)+Pc3x*l1*m3*(q2d*q2d)*sin(q3)-Pc3y*l1*m3*(q1d*q1d)*cos(q2*2.0+q3)*(1.0/2.0)-Pc3x*l1*m3*(q1d*q1d)*sin(q2*2.0+q3)*(1.0/2.0)-Pc3x*Pc3y*m3*(q1d*q1d)*cos(q2*2.0+q3*2.0);
    return V;
}

Vector3d RobotModel::G(){
    Vector3d G = Vector3d::Zero();

    double q1 = m_s.Q(0); double q2 = m_s.Q(1); double q3 = m_s.Q(2);

    G[1] = -g*(Pc2x*m2*sin(q2)+l1*m3*sin(q2)+Pc3y*m3*cos(q2+q3)+Pc3x*m3*sin(q2+q3)+Pc2y*m2*cos(q2));
    G[2] = -g*m3*(Pc3y*cos(q2+q3)+Pc3x*sin(q2+q3));

    return G;
}

Vector3d RobotModel::B(){
    Vector3d B = Vector3d::Zero();

    return B;
}

Vector3d RobotModel::Fk(){
    Vector3d Fk = Vector3d::Zero();

    return Fk;
}

void RobotModel::zero(){
    m_s.Q   = Vector3d(0.0,0.0,0.0);
    m_s.Qd  = Vector3d(0.0,0.0,0.0);
    m_s.Qdd = Vector3d(0.0,0.0,0.0);
    m_s.Tau = Vector3d(0.0,0.0,0.0);
}