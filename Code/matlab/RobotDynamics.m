% Nathan Dunkelberger | nathandunkelberger.com | n8dunk@gmail.com
%
% Written 05/31/2020

%% Define Symbolic Symbols
syms tau1 eta1 Jm1 q1 q1d q1dd m1 b1 fk1 ...
     tau2 eta2 Jm2 q2 q2d q2dd m2 b2 fk2 ...
     tau3 eta3 Jm3 q3 q3d q3dd m3 b3 fk3 ...
     Pc1x Pc1y Pc1z Ic1xx Ic1xy Ic1xz Ic1yy Ic1yz Ic1zz ...
     Pc2x Pc2y Pc2z Ic2xx Ic2xy Ic2xz Ic2yy Ic2yz Ic2zz ...
     Pc3x Pc3y Pc3z Ic3xx Ic3xy Ic3xz Ic3yy Ic3yz Ic3zz ...
     g ...
     l1 l2

Tau = [tau1; tau2; tau3];

Eta = [eta1;eta2;eta3];
Jm = [Jm1;Jm2;Jm3];

Q =   [  q1;   q2;   q3];
Qd =  [ q1d;  q2d;  q3d];
Qdd = [q1dd; q2dd; q3dd];

Pc1 = [Pc1x Pc1y Pc1z].';
Pc2 = [Pc2x Pc2y Pc2z].';
Pc3 = [Pc3x Pc3y Pc3z].';

Ic1 = [Ic1xx -Ic1xy -Ic1xz;
      -Ic1xy  Ic1yy -Ic1yz;
      -Ic1xz -Ic1yz  Ic1xx];

Ic2 = [Ic2xx -Ic2xy -Ic2xz;
      -Ic2xy  Ic2yy -Ic2yz;
      -Ic2xz -Ic2yz  Ic2xx];

Ic3 = [Ic3xx -Ic3xy -Ic3xz;
      -Ic3xy  Ic3yy -Ic3yz;
      -Ic3xz -Ic3yz  Ic3xx];

%% Forward Kinematics
           %a %alpha %d  %theta
DH_table = [ 0,    0,  0,      q1;
             0, pi/2,  0, q2+pi/2;
            l1,    0,  0,      q3;
            l2,    0,  0,       0];

[~,T_array] = dh2tf(DH_table);

%% Newton-Euler Dynamics
m = [m1;m2;m3];
Pc = {Pc1 Pc2 Pc3};
Ic = {Ic1 Ic2 Ic3};
g0 = [0; 0; -g];
u_ref = [0,0,0].';
MVG = dynamics_newtonian(m,Pc,Ic,T_array,Qd,Qdd,g0);
% MVG = dynamics_lagrangian(m,Pc,Ic,T_array,Q,Qd,Qdd,g0,0);

MVG = simplify(expand(MVG));

%% Separate MVG into M, V, and G
[M,V,G] = separate_mvg(MVG,Qdd,g);

%% Generate code to copy into cpp file

generate_code(M,'M')
generate_code(V,'V')
generate_code(G,'G')

%% Test dynamics
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

q   = [0.2, .1, -.3];
qd  = [0.34, -.02, 0.04];
qdd  = [0.02, 0.04, -0.06];
tau = [0, 0, 0].';

M_eval = subs(M);
V_eval = subs(V);
G_eval = subs(G);

M_eval = vpa(subs(M_eval,[Q.',Qd.'],[q,qd]),4)
V_eval = vpa(subs(V_eval,[Q.',Qd.'],[q,qd]),4)
G_eval = vpa(subs(G_eval,[Q.',Qd.'],[q,qd]),4)

a = M_eval;
b = tau - V_eval-G_eval;
vpa(a\b)

%% Test with ODE45

% x0 = [0,pi,0,0,0,0].';
% tspan = [0,5];
% [t,xsol] = ode45(@eom,tspan,x0);
% plot(t,xsol(:,1:3));

%% Test from python
Tau3py = -1.0*Ic3xz*(1.0*q3d*(-1.0*q1d*sin(q2)*cos(q3) - 1.0*q1d*sin(q3)*cos(q2)) + (-1.0*q1d*q2d*sin(q2) + 1.0*q1dd*cos(q2))*cos(q3) + (-1.0*q1d*q2d*cos(q2) - 1.0*q1dd*sin(q2))*sin(q3)) - 1.0*Ic3yz*(-1.0*q3d*(-1.0*q1d*sin(q2)*sin(q3) + 1.0*q1d*cos(q2)*cos(q3)) - (-1.0*q1d*q2d*sin(q2) + 1.0*q1dd*cos(q2))*sin(q3) + (-1.0*q1d*q2d*cos(q2) - 1.0*q1dd*sin(q2))*cos(q3)) + 1.0*Ic3zz*(1.0*q2dd + 1.0*q3dd) + 1.0*Pc3x*m3*(Pc3x*(1.0*q2dd + 1.0*q3dd) - Pc3z*(1.0*q3d*(-1.0*q1d*sin(q2)*cos(q3) - 1.0*q1d*sin(q3)*cos(q2)) + (-1.0*q1d*q2d*sin(q2) + 1.0*q1dd*cos(q2))*cos(q3) + (-1.0*q1d*q2d*cos(q2) - 1.0*q1dd*sin(q2))*sin(q3)) + (1.0*q2d + 1.0*q3d)*(-Pc3y*(1.0*q2d + 1.0*q3d) + Pc3z*(-1.0*q1d*sin(q2)*cos(q3) - 1.0*q1d*sin(q3)*cos(q2))) - (-Pc3x*(-1.0*q1d*sin(q2)*cos(q3) - 1.0*q1d*sin(q3)*cos(q2)) + Pc3y*(-1.0*q1d*sin(q2)*sin(q3) + 1.0*q1d*cos(q2)*cos(q3)))*(-1.0*q1d*sin(q2)*sin(q3) + 1.0*q1d*cos(q2)*cos(q3)) + (-g*sin(q2) - 1.0*l1*q1d^2*sin(q2)*cos(q2) + 1.0*l1*q2dd)*cos(q3) - (g*cos(q2) - 1.0*l1*q1d^2*sin(q2)^2 - 1.0*l1*q2d^2)*sin(q3)) - 1.0*Pc3y*m3*(-Pc3y*(1.0*q2dd + 1.0*q3dd) + Pc3z*(-1.0*q3d*(-1.0*q1d*sin(q2)*sin(q3) + 1.0*q1d*cos(q2)*cos(q3)) - (-1.0*q1d*q2d*sin(q2) + 1.0*q1dd*cos(q2))*sin(q3) + (-1.0*q1d*q2d*cos(q2) - 1.0*q1dd*sin(q2))*cos(q3)) - (1.0*q2d + 1.0*q3d)*(Pc3x*(1.0*q2d + 1.0*q3d) - Pc3z*(-1.0*q1d*sin(q2)*sin(q3) + 1.0*q1d*cos(q2)*cos(q3))) + (-Pc3x*(-1.0*q1d*sin(q2)*cos(q3) - 1.0*q1d*sin(q3)*cos(q2)) + Pc3y*(-1.0*q1d*sin(q2)*sin(q3) + 1.0*q1d*cos(q2)*cos(q3)))*(-1.0*q1d*sin(q2)*cos(q3) - 1.0*q1d*sin(q3)*cos(q2)) + (-g*sin(q2) - 1.0*l1*q1d^2*sin(q2)*cos(q2) + 1.0*l1*q2dd)*sin(q3) + (g*cos(q2) - 1.0*l1*q1d^2*sin(q2)^2 - 1.0*l1*q2d^2)*cos(q3)) + 1.0*(-1.0*q1d*sin(q2)*sin(q3) + 1.0*q1d*cos(q2)*cos(q3))*(-Ic3xy*(-1.0*q1d*sin(q2)*sin(q3) + 1.0*q1d*cos(q2)*cos(q3)) + Ic3yy*(-1.0*q1d*sin(q2)*cos(q3) - 1.0*q1d*sin(q3)*cos(q2)) - Ic3yz*(1.0*q2d + 1.0*q3d)) - 1.0*(-1.0*q1d*sin(q2)*cos(q3) - 1.0*q1d*sin(q3)*cos(q2))*(Ic3xx*(-1.0*q1d*sin(q2)*sin(q3) + 1.0*q1d*cos(q2)*cos(q3)) - Ic3xy*(-1.0*q1d*sin(q2)*cos(q3) - 1.0*q1d*sin(q3)*cos(q2)) - Ic3xz*(1.0*q2d + 1.0*q3d));
vpa(subs(Tau3py,[Q.',Qd.',Qdd.'],[q,qd,qdd]),4)
MVG_subs = subs(MVG)
vpa(subs(MVG_subs(3),[Q.',Qd.',Qdd.'],[q,qd,qdd]),4)