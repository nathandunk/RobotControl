#include "RobotLib/Control/Filter.hpp"

// //Low pass butterworth filter order=2 alpha1=0.2 
// class  FilterBuLp2
// {
//   public:
//     FilterBuLp2()
//     {
//       v[0]=0.0;
//       v[1]=0.0;
//     }
//   private:
//     float v[3];
//   public:
//     float step(float x) //class II 
//     {
//       v[0] = v[1];
//       v[1] = v[2];
//       v[2] = (3.621681514928615665e-3 * x)
//          + (-0.83718165125602272969 * v[0])
//          + (1.82269492519630826877 * v[1]);
//       return 
//          (v[0] + v[2])
//         +2 * v[1];
//     }
// };

FilterBuLp2::FilterBuLp2()
{
  v[0]=0.0;
  v[1]=0.0;
}

float FilterBuLp2::step(float x) //class II 
		{
			v[0] = v[1];
			v[1] = v[2];
			v[2] = (1.000000000000000000e+0 * x)
				 + (-1.00000000000000000000 * v[0])
				 + (-2.00000000000000000000 * v[1]);
			return 
				 (v[0] + v[2])
				+2 * v[1];
		}
