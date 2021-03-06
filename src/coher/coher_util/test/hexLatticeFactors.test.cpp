
#include "catch.hpp"
#include "coher/coher_util/hexLatticeFactors.h"

void equal4( double a, double b ){
//	std::cout << a << "   " << b << std::endl;
  if (b == 0.0){ 
    REQUIRE( std::abs(b-a) < 1e-6 );
    return;
  }
  REQUIRE ( std::abs( (a-b)/(b) ) < 1e-6 );
}

void equal4_vec( std::vector<double> a, std::vector<double> b ){
  REQUIRE( a.size() == b.size() );
  for ( int i = 0; i < a.size(); ++i ){
    equal4( a[i], b[i] );
  }
}


void equal4Hex( std::tuple<int,int,int,double,double>& a, double& b ){
  equal4( tausq(std::get<0>(a),std::get<1>(a),std::get<2>(a),std::get<3>(a),
               std::get<4>(a) ), b );
}

TEST_CASE( "tausq" ){
  GIVEN( "inputs" ){
    std::vector<std::tuple<int,int,int,double,double>> inputs
      { {0,0,0,2,4}, {1,0,0,2,4}, {0,1,0,2,4}, {0,0,1,2,4}, {1,1,0,2,4}, 
	{1,0,1,2,4}, {0,1,1,2,4}, {1,1,1,2,4}, {1,2,3,4,5}, {5,3,6,4,5},
        {8,7,9,.1,.2} };
    std::vector<double> output { 0, 78.956835, 78.956835, 157.91367041, 
	236.870505, 236.870505, 236.870505, 394.78417604, 2881.924485, 
	14843.885019, 1306.735642 };
    
    for ( auto i = 0; i < output.size(); ++i ){
      equal4Hex( inputs[i], output[i] );
    }
  } // GIVEN
} // TEST CASE




TEST_CASE( "Function to Compute Hex Lattice Factors" ){
  double a = 1e-9, c1 = 1.5e15, c2 = 2.5e15, tsqx = 9.6e17,
    t2 = 3.5e-5, ulim = 9.6e19, c = 3.58e-8, tsq = 0, wint = 0;
  int i = 0, ifl = 1, lat = 3, nw = 60000, imax = 5;
  std::vector<double> b (60000, 0.0);
  int i1m = 1;
/*
  GIVEN( "few iterations" ){
    WHEN( "input constants are large" ){
      THEN( "outputs" ){
        int imax = hexLatticeFactors( a, tsq, c1, c2, lat, nw, tsqx, b, ifl, 
            i, wint, t2, ulim, imax, c, i1m );
        REQUIRE( imax == 41 );
        std::vector<double> bVals { 98696046700994448., 0, 98696046700994448.,
          0, 3.9478418680E17, 3.749690408E-8, 3.947841868E17, 3.749690408E-8, 
          8.882644203E17, 0, 8.882644203E17, 0, 1.579136747E18, 2.964826895E-9, 
          2.467401167E18, 1.493069735E-7, 3.553057681E18, 4.97901242E-8,
          4.836106288E18, 2.051556624E-8, 6.31654698E18, 7.332669318E-8, 
          7.994379782E18, 1.59948166E-8, 9.869604670E18, 2.995272845E-8, 
          1.19422216E19, 6.850673779E-8, 1.421223072E19, 9.96335270E-10,
          1.667963189E19, 5.800790100E-8, 1.93444251E19, 2.141044182E-8, 
          2.220661050E19, 9.61955094E-9, 2.526618795E19, 3.672738109E-8, 
          2.85231574E19, 8.490339719E-9 };

        for ( auto i = 0; i < bVals.size(); ++i ){ equal4( b[i], bVals[i] ); }

      } // THEN
    } // WHEN

    WHEN( "input constants are small" ){
      a = 1e-15; c1 = 1.5e5; c2 = 2.5e5; tsqx = 9.6e7;
      THEN( "outputs" ){
        int imax = hexLatticeFactors( a, tsq, c1, c2, lat, nw, tsqx, b, ifl, 
            i, wint, t2, ulim, imax, c, i1m );
        REQUIRE( imax == 50 );
        std::vector<double> bVals { 9869604.401089, 0, 9869604.401089, 0,
          39478417.60435,  3.7496903E-3, 39478417.604, 3.7496904E-3,
          88826439.609, 0, 88826439.609, 0, 157913670.41, 1.4960564E-4, 
          246740110.02, 0, 355305758.43, 2.4997936E-3, 483610615.65, 0, 
	  631654681.66, 3.674887635E-3, 799437956.48, 0, 986960440.10, 
          1.499876183E-3, 1194222132.531, 0, 1421223033.756, 4.986854883E-5, 
          1667963143.784, 0, 1934442462.613, 1.071340131E-3, 2220660990.245, 0, 
          2526618726.678, 1.83744381799E-3, 2852315671.914, 0 };

        for ( auto i = 0; i < bVals.size(); ++i ){ equal4( b[i], bVals[i] ); }

      } // THEN
    } // WHEN

    WHEN( "the a input is really large" ){
      a = 1e-5; c1 = 1.5e5; c2 = 2.5e5; tsqx = 9.6e7;
      THEN( "many iterations are necessary" ){
        int imax = hexLatticeFactors( a, tsq, c1, c2, lat, nw, tsqx, b, ifl, 
            i, wint, t2, ulim, imax, c, i1m );
        REQUIRE( imax == 672 );
        std::vector<double> bVals { 9869604.401089, 0, 9869604.401089, 0,
          39478417.60435,  3.7496903E-3, 39478417.604, 3.7496904E-3,
          88826439.609, 0, 88826439.609, 0, 157913670.41, 3.90862091E-3,
          246740110.0272, 2.69065335E-2, 355305758.4392, 5.36938034E-3, 
          483610615.6533, 6.16711773E-3, 631654681.6697, 1.67739345E-2, 
          799437956.4882, 2.62611134E-2, 986960440.1089, 1.05068644E-2, 
          1194222132.531, 4.32585375E-2, 1421223033.756, 2.23883343E-2, 
          1667963143.784, 2.07285134E-2, 1934442462.613, 3.49406438E-2, 
          2220660990.245, 2.38701912E-2, 2526618726.678, 3.75143966E-2,
          2852315671.914, 2.59832708E-2 };

        for ( auto i = 0; i < bVals.size(); ++i ){ equal4( b[i], bVals[i] ); }

      } // THEN
    } // WHEN

  } // GIVEN

  */
  i1m = 2;
  GIVEN( "few iterations" ){
    THEN( "outputs" ){
      int imax = hexLatticeFactors( a, tsq, c1, c2, lat, nw, tsqx, b, ifl, 
          i, wint, t2, ulim, imax, c, i1m );
      //REQUIRE( imax == 51 );
      /*
      std::vector<double> bVals { 98696046700994448., 0, 98696046700994448.,
        0, 3.9478418680397779E17, 3.7496904081434691E-8, 3.9478418680397779E17,
	3.7496904081434691E-8, 8.8826442030895002E17, 0, 8.8826442030895002E17,
	0, 1.5791367472159112E18, 3.6992121213998630E-9, 2.4674011675248614E18,
	2.2396046029577356E-7, 3.5530576812358001E18, 6.21862e-8, 
	// The 6.21862e-8 should actually be 1.1097719365713786E-7,, but 
	// because of fortran leapr saying that 
	// 1.500000000001083 < 1.5000000000004342 and my code not doing that,
	// they aren't equal4
	4.8361062883487283E18, 3.0773349369262785E-8, 6.3165469888636447E18,
	1.6410109443981084E-7, 7.9943797827805501E18, 2.3992225035965280E-8,
	9.8696046700994458E18, 6.7160848305905068E-8, 1.1942221650820327E19,
	1.0276010669647593E-7, 1.4212230724943200E19, 2.2363553971699563E-9,
	1.6679631892468062E19, 8.7011851509430656E-8, 1.9344425153394913E19,
	4.8088048636505399E-8, 2.2206610507723751E19, 1.4429326414274293E-8,
	2.5266187955454579E19, 8.2524210602627214E-8, 2.8523157496587395E19,
	1.2735509579295717E-8 };
      */
      REQUIRE( imax == 51 );
      std::vector<double> bVals { 98696046700994448., 0, 98696046700994448., 0,3.9478418680397779E+017, 3.7496904081434691E-008, 3.9478418680397779E+017, 3.7496904081434691E-008, 8.8826442030895002E+017, 0, 8.8826442030895002E+017, 0, 1.5791367472159112E+018, 3.6992121213998630E-009, 2.4674011675248614E+018, 2.2396046029577356E-007, 3.5530576812358001E+018, 1.1097719365713786E-007, 4.8361062883487283E+018, 3.0773349369262785E-008 };
      for ( auto i = 0; i < bVals.size(); ++i ){ equal4( b[i], bVals[i] ); }

    } // THEN
  } // GIVEN



  i1m = 10;
  GIVEN( "few iterations" ){
    THEN( "outputs" ){
      int imax = hexLatticeFactors( a, tsq, c1, c2, lat, nw, tsqx, b, ifl, 
          i, wint, t2, ulim, imax, c, i1m );
      /*
      std::vector<double> bVals { 98696046700994448., 0, 98696046700994448.,
        0, 3.9478418680397779E17, 3.7496904081434691E-8, 3.9478418680397779E17,
	3.7496904081434691E-8, 8.8826442030895002E17, 0, 8.8826442030895002E17,
	0, 1.5791367472159112E18, 3.6992121213998630E-9, 2.4674011675248614E18,
	2.2396046029577356E-7, 3.5530576812358001E18, 6.21862e-8, 
	// The 6.21862e-8 should actually be 1.1097719365713786E-7,, but 
	// because of fortran leapr saying that 
	// 1.500000000001083 < 1.5000000000004342 and my code not doing that,
	// they aren't equal4
	4.8361062883487283E18, 3.0773349369262785E-8, 6.3165469888636447E18,
	1.6410109443981084E-7, 7.9943797827805501E18, 2.3992225035965280E-8,
	9.8696046700994458E18, 6.7160848305905068E-8, 1.1942221650820327E19,
	1.0276010669647593E-7, 1.4212230724943200E19, 2.2363553971699563E-9,
	1.6679631892468062E19, 8.7011851509430656E-8, 1.9344425153394913E19,
	4.8088048636505399E-8, 2.2206610507723751E19, 1.4429326414274293E-8,
	2.5266187955454579E19, 8.2524210602627214E-8, 2.8523157496587395E19,
	1.2735509579295717E-8 };
  */
      REQUIRE( imax == 51 );

      std::vector<double> bVals { 98696046700994448., 0, 98696046700994448., 0,3.9478418680397779E+017, 3.7496904081434691E-008, 3.9478418680397779E+017, 3.7496904081434691E-008, 8.8826442030895002E+017, 0, 8.8826442030895002E+017, 0, 1.5791367472159112E+018, 3.6992121213998630E-009, 2.4674011675248614E+018, 2.2396046029577356E-007, 3.5530576812358001E+018, 1.1097719365713786E-007, 4.8361062883487283E+018, 3.0773349369262785E-008 };
      for ( auto i = 0; i < bVals.size(); ++i ){ equal4( b[i], bVals[i] ); }

    } // THEN
  } // GIVEN
} // TEST CASE

