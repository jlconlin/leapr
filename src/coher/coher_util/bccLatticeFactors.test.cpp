#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../../catch.hpp"
#include "formf.h" 
#include "bccLatticeFactors.h"

void equal( double a, double b ){
  if (b == 0.0){ 
    REQUIRE( std::abs(b-a) < 1e-6 );
    return;
  }
  REQUIRE ( std::abs( (a-b)/(b) ) < 1e-6 );
}

void equal_vec( std::vector<double> a, std::vector<double> b ){
  REQUIRE( a.size() == b.size() );
  for ( int i = 0; i < a.size(); ++i ){
    equal( a[i], b[i] );
  }
}

void equalBcc( std::tuple<int,int,int,double>& a, double& b ){
  equal(taubcc(std::get<0>(a),std::get<1>(a),std::get<2>(a),std::get<3>(a)), b);
}


TEST_CASE( "taubcc" ){
  GIVEN( "inputs" ){
    std::vector<std::tuple<int,int,int,double>> inputs
      { {0,0,0,2}, {1,0,0,2}, {0,1,0,2}, {0,0,1,2}, {1,1,0,2},
        {1,0,1,2}, {0,1,1,2}, {1,1,1,2}, {1,2,3,4}, {5,3,6,4},
        {8,7,9,.1} };
    std::vector<double> output { 0, 78.956835, 78.956835, 78.956835, 236.870506,
      236.870506, 236.870506, 473.741011, 3947.84176, 21002.518165, 1519.9191 };
    
    for ( auto i = 0; i < output.size(); ++i ){
      equalBcc( inputs[i], output[i] );
    }
    
  } // GIVEN
} // TEST CASE



TEST_CASE( "Function to Compute BCC Lattice Factors" ){
  double ulim = 9.6e19, wint = 0, t2 = 5.7e-6, 
    a = 2.8e-8, c1 = 1.5e15;
  int ifl = 1, lat = 6;
  std::vector<double> b (60000, 0.0);
  GIVEN( "iron is the desired material" ){
    THEN( "output is correct" ){
      int imax = bccLatticeFactors( ulim, b, ifl, wint, t2, lat, a, c1 );
      REQUIRE( imax == 29789 );

      std::vector<double> b_0_39 { 7.994379E19, 4.473707E-10, 7.644995E19, 
        4.574792E-10, 7.307455E19, 4.679257E-10, 6.981758E19, 4.787156E-10, 
        6.667904E19, 4.898524E-10, 6.365894E19, 5.013375E-10, 6.075728E19, 
        5.131694E-10, 5.797405E19, 5.253432E-10, 5.530926E19, 5.378498E-10, 
        5.276290E19, 5.506753E-10, 5.033498E19, 5.637999E-10, 4.802549E19, 
        5.771970E-10, 4.583444E19, 5.908320E-10, 4.376182E19, 6.046614E-10, 
        4.180764E19, 6.186316E-10, 3.997189E19, 6.326778E-10, 3.825458E19, 
        6.467228E-10, 3.665571E19, 6.606769E-10, 3.517527E19, 6.744368E-10, 
        3.381326E19, 6.878859E-10 };

      for ( auto i = 0; i < 40; ++i ){ equal( b[i], b_0_39[i] ); }

      std::vector<double> b_1000_1039 { 2.877976E19, 7.456179E-10, 
        2.670714E19, 7.740093E-10, 2.475296E19, 8.039820E-10, 2.291722E19, 
        8.355626E-10, 2.119991E19, 8.687463E-10, 1.960103E19, 9.034840E-10, 
        1.812059E19, 9.396665E-10, 1.675858E19, 9.771050E-10, 1.551501E19, 
        1.015509E-9, 1.438988E19, 1.054463E-9, 1.338318E19, 1.093403E-9, 
        1.249491E19, 1.131600E-9, 1.172509E19, 1.168158E-9, 1.107369E19, 
        1.202025E-9, 1.054073E19, 1.232039E-9, 1.012621E19, 1.257003E-9, 
        9.830126E18, 1.275793E-9, 9.652473E18, 1.287480E-9, 9.593255E18, 
        1.291448E-9, 9.652473E18, 1.287480E-9 }; 

      for ( auto i = 0; i < 40; ++i ){ equal( b[1000+i], b_1000_1039[i] ); }

      std::vector<double> b_51000_51039 { 1.166587E19, 1.171119E-9, 
        1.290944E19, 1.113284E-9, 1.427144E19, 1.058829E-9, 1.575188E19, 
        1.007844E-9, 1.735076E19, 9.602861E-10, 1.906807E19, 9.160233E-10, 
        2.090382E19, 8.748772E-10, 2.285800E19, 8.366442E-10, 2.493062E19, 
        8.011123E-10, 2.712167E19, 7.680716E-10, 2.943116E19, 7.373204E-10, 
        3.185908E19, 7.086688E-10, 1.048151E19, 1.235514E-9, 9.534037E18, 
        1.295452E-9, 8.704991E18, 1.355738E-9, 7.994379E18, 1.414710E-9, 
        7.402203E18, 1.470210E-9, 6.928462E18, 1.519642E-9, 6.573156E18, 
        1.560173E-9, 6.336286E18, 1.589068E-9 };

      for ( auto i = 0; i < 40; ++i ){ equal( b[51000+i], b_51000_51039[i] ); }

    } // THEN
  } // GIVEN
} // TEST CASE
