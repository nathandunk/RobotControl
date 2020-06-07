function [Xd] = eom(t,X)

q1 = X(1);
q2 = X(2);
q3 = X(3);
q1d = X(4);
q2d = X(5);
q3d = X(6);

Ic1xx =  0.00031659; % kg*m^2
Ic1xy = -0.00000032; % kg*m^2
Ic1xz = -0.00000026; % kg*m^2
Ic1yy =  0.00007459; % kg*m^2
Ic1yz = -0.00002138; % kg*m^2
Ic1zz =  0.00028662; % kg*m^2
Pc1x  = -0.00006629; % m
Pc1y  =  0.02685796; % m
Pc1z  =  0.00341708; % m
m1    =  0.23250015; % kg
% Link 2
Ic2xx =  0.00001379; % kg*m^2
Ic2xy =  0.00000000; % kg*m^2
Ic2xz = -0.00000728; % kg*m^2
Ic2yy =  0.00003470; % kg*m^2
Ic2yz =  0.00000000; % kg*m^2
Ic2zz =  0.00002156; % kg*m^2
Pc2x  =  0.06332032; % m
% Pc2y  =  0.00000; % m
Pc2y  =  0.00001183; % m
Pc2z  = -0.01300296; % m
m2     = 0.02350003; % kg
% Link 3
Ic3xx =  0.00000066; % kg*m^2
Ic3xy =  0.00000000; % kg*m^2
Ic3xz = -0.00000001; % kg*m^2
Ic3yy =  0.00001068; % kg*m^2
Ic3yz =  0.00000000; % kg*m^2
Ic3zz =  0.00001043; % kg*m^2
Pc3x  =  0.03091769; % m
Pc3y  =  0.00000000; % m
Pc3z  =  0.00002952; % m
m3    =  0.01100000; % kg
l1    =  0.08800000; % m
l2    =  0.09300000; % m
g     =  9.80665000; % kg*m/s^2

M = [ Ic1xx + Ic2xx/2 + Ic3xx/2 + Ic2yy/2 + Ic3yy/2 + (Ic3xx*cos(2*q2 + 2*q3))/2 - (Ic3yy*cos(2*q2 + 2*q3))/2 + Ic3xy*sin(2*q2 + 2*q3) + Pc1x^2*m1 + Pc1y^2*m1 + (Pc2x^2*m2)/2 + (Pc2y^2*m2)/2 + (Pc3x^2*m3)/2 + Pc2z^2*m2 + (Pc3y^2*m3)/2 + Pc3z^2*m3 + (l1^2*m3)/2 + (Ic2xx*cos(2*q2))/2 - (Ic2yy*cos(2*q2))/2 + Ic2xy*sin(2*q2) - (Pc2x^2*m2*cos(2*q2))/2 + (Pc2y^2*m2*cos(2*q2))/2 - (l1^2*m3*cos(2*q2))/2 - (Pc3x^2*m3*cos(2*q2 + 2*q3))/2 + (Pc3y^2*m3*cos(2*q2 + 2*q3))/2 + Pc3x*l1*m3*cos(q3) - Pc3y*l1*m3*sin(q3) - Pc3x*l1*m3*cos(2*q2 + q3) + Pc3y*l1*m3*sin(2*q2 + q3) + Pc2x*Pc2y*m2*sin(2*q2) + Pc3x*Pc3y*m3*sin(2*q2 + 2*q3), Ic3yz*sin(q2 + q3) - Ic3xz*cos(q2 + q3) - Ic2xz*cos(q2) + Ic2yz*sin(q2) - Pc3x*Pc3z*m3*cos(q2 + q3) + Pc3y*Pc3z*m3*sin(q2 + q3) - Pc2x*Pc2z*m2*cos(q2) + Pc2y*Pc2z*m2*sin(q2) - Pc3z*l1*m3*cos(q2), Ic3yz*sin(q2 + q3) - Ic3xz*cos(q2 + q3) - Pc3x*Pc3z*m3*cos(q2 + q3) + Pc3y*Pc3z*m3*sin(q2 + q3);
                                                                                                                                                                                                                                                                                                                                                                                                                                         Ic3yz*sin(q2 + q3) - Ic3xz*cos(q2 + q3) - Ic2xz*cos(q2) + Ic2yz*sin(q2) - Pc3x*Pc3z*m3*cos(q2 + q3) + Pc3y*Pc3z*m3*sin(q2 + q3) - Pc2x*Pc2z*m2*cos(q2) + Pc2y*Pc2z*m2*sin(q2) - Pc3z*l1*m3*cos(q2),                                                                              m2*Pc2x^2 + m2*Pc2y^2 + m3*Pc3x^2 + 2*m3*cos(q3)*Pc3x*l1 + m3*Pc3y^2 - 2*m3*sin(q3)*Pc3y*l1 + m3*l1^2 + Ic2xx + Ic3xx,                         m3*Pc3x^2 + l1*m3*cos(q3)*Pc3x + m3*Pc3y^2 - l1*m3*sin(q3)*Pc3y + Ic3xx;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            Ic3yz*sin(q2 + q3) - Ic3xz*cos(q2 + q3) - Pc3x*Pc3z*m3*cos(q2 + q3) + Pc3y*Pc3z*m3*sin(q2 + q3),                                                                                                                            m3*Pc3x^2 + l1*m3*cos(q3)*Pc3x + m3*Pc3y^2 - l1*m3*sin(q3)*Pc3y + Ic3xx,                                                                   m3*Pc3x^2 + m3*Pc3y^2 + Ic3xx];

V = [ Ic3yz*q2d^2*cos(q2 + q3) + Ic3yz*q3d^2*cos(q2 + q3) + Ic3xz*q2d^2*sin(q2 + q3) + Ic3xz*q3d^2*sin(q2 + q3) + Ic2yz*q2d^2*cos(q2) + Ic2xz*q2d^2*sin(q2) + 2*Ic3yz*q2d*q3d*cos(q2 + q3) + 2*Ic3xz*q2d*q3d*sin(q2 + q3) + 2*Ic2xy*q1d*q2d*cos(2*q2) - Ic2xx*q1d*q2d*sin(2*q2) + Ic2yy*q1d*q2d*sin(2*q2) + 2*Ic3xy*q1d*q2d*cos(2*q2 + 2*q3) + 2*Ic3xy*q1d*q3d*cos(2*q2 + 2*q3) - Ic3xx*q1d*q2d*sin(2*q2 + 2*q3) - Ic3xx*q1d*q3d*sin(2*q2 + 2*q3) + Ic3yy*q1d*q2d*sin(2*q2 + 2*q3) + Ic3yy*q1d*q3d*sin(2*q2 + 2*q3) + Pc2y*Pc2z*m2*q2d^2*cos(q2) + Pc2x*Pc2z*m2*q2d^2*sin(q2) + Pc3z*l1*m3*q2d^2*sin(q2) + Pc2x^2*m2*q1d*q2d*sin(2*q2) - Pc2y^2*m2*q1d*q2d*sin(2*q2) + l1^2*m3*q1d*q2d*sin(2*q2) + Pc3x^2*m3*q1d*q2d*sin(2*q2 + 2*q3) + Pc3x^2*m3*q1d*q3d*sin(2*q2 + 2*q3) - Pc3y^2*m3*q1d*q2d*sin(2*q2 + 2*q3) - Pc3y^2*m3*q1d*q3d*sin(2*q2 + 2*q3) + Pc3y*Pc3z*m3*q2d^2*cos(q2 + q3) + Pc3y*Pc3z*m3*q3d^2*cos(q2 + q3) + Pc3x*Pc3z*m3*q2d^2*sin(q2 + q3) + Pc3x*Pc3z*m3*q3d^2*sin(q2 + q3) + 2*Pc3x*Pc3z*m3*q2d*q3d*sin(q2 + q3) - Pc3y*l1*m3*q1d*q3d*cos(q3) - Pc3x*l1*m3*q1d*q3d*sin(q3) + 2*Pc3y*l1*m3*q1d*q2d*cos(2*q2 + q3) + Pc3y*l1*m3*q1d*q3d*cos(2*q2 + q3) + 2*Pc3x*l1*m3*q1d*q2d*sin(2*q2 + q3) + Pc3x*l1*m3*q1d*q3d*sin(2*q2 + q3) + 2*Pc2x*Pc2y*m2*q1d*q2d*cos(2*q2) + 2*Pc3x*Pc3y*m3*q1d*q2d*cos(2*q2 + 2*q3) + 2*Pc3x*Pc3y*m3*q1d*q3d*cos(2*q2 + 2*q3) + 2*Pc3y*Pc3z*m3*q2d*q3d*cos(q2 + q3);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        (Ic2xx*q1d^2*sin(2*q2))/2 - Ic2xy*q1d^2*cos(2*q2) - (Ic2yy*q1d^2*sin(2*q2))/2 - Ic3xy*q1d^2*cos(2*q2 + 2*q3) + (Ic3xx*q1d^2*sin(2*q2 + 2*q3))/2 - (Ic3yy*q1d^2*sin(2*q2 + 2*q3))/2 - (Pc2x^2*m2*q1d^2*sin(2*q2))/2 + (Pc2y^2*m2*q1d^2*sin(2*q2))/2 - (l1^2*m3*q1d^2*sin(2*q2))/2 - (Pc3x^2*m3*q1d^2*sin(2*q2 + 2*q3))/2 + (Pc3y^2*m3*q1d^2*sin(2*q2 + 2*q3))/2 - Pc3y*l1*m3*q3d^2*cos(q3) - Pc3x*l1*m3*q3d^2*sin(q3) - Pc3y*l1*m3*q1d^2*cos(2*q2 + q3) - Pc3x*l1*m3*q1d^2*sin(2*q2 + q3) - Pc2x*Pc2y*m2*q1d^2*cos(2*q2) - Pc3x*Pc3y*m3*q1d^2*cos(2*q2 + 2*q3) - 2*Pc3y*l1*m3*q2d*q3d*cos(q3) - 2*Pc3x*l1*m3*q2d*q3d*sin(q3);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            (Ic3xx*q1d^2*sin(2*q2 + 2*q3))/2 - Ic3xy*q1d^2*cos(2*q2 + 2*q3) - (Ic3yy*q1d^2*sin(2*q2 + 2*q3))/2 - (Pc3x^2*m3*q1d^2*sin(2*q2 + 2*q3))/2 + (Pc3y^2*m3*q1d^2*sin(2*q2 + 2*q3))/2 + (Pc3y*l1*m3*q1d^2*cos(q3))/2 + Pc3y*l1*m3*q2d^2*cos(q3) + (Pc3x*l1*m3*q1d^2*sin(q3))/2 + Pc3x*l1*m3*q2d^2*sin(q3) - (Pc3y*l1*m3*q1d^2*cos(2*q2 + q3))/2 - (Pc3x*l1*m3*q1d^2*sin(2*q2 + q3))/2 - Pc3x*Pc3y*m3*q1d^2*cos(2*q2 + 2*q3)];

G = [                                                                                                   0;
     -g*(Pc2x*m2*sin(q2) + l1*m3*sin(q2) + Pc3y*m3*cos(q2 + q3) + Pc3x*m3*sin(q2 + q3) + Pc2y*m2*cos(q2));
                                                            -g*m3*(Pc3y*cos(q2 + q3) + Pc3x*sin(q2 + q3))];

Xd(1) = X(4);
Xd(2) = X(5);
Xd(3) = X(6);
Xd(4:6) = M\(-V-G)

Xd = Xd.';
end
