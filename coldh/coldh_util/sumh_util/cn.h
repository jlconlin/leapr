#include <vector>

auto helper(int k, bool isA ){
  double s = 0;
  double fact = 1;
  for ( auto i = 0; i < k; ++i ){
    int zi = i + 1;
    s = s + log(zi);
  }
  if ( s > 0.0 ){
    fact = exp(s);
  }
  return isA ? sqrt(fact) : fact;
}

auto cn( int jj, int ll, int nn ){
  /* Calculates Clebsch-Gordon coefficients for cold hydrogen or 
   * deuterium calculation
   */
  int i, kdet, kdel, ka1, ka2, ka3, ka4, kb1, kb2, kb3, kb4, iwign;
  double s, fact, zi, a1, a2, a3, a4, b1, b2, b3, b4, rat, wign;

  // if sum of three inputs is even, continue. Else return 0.0
  if ( (jj + ll + nn )%2 == 0 ){

    a1 = helper(  jj + ll + nn, true );
    a2 = helper(  jj + ll - nn, true );
    a3 = helper(  jj - ll + nn, true );
    a4 = helper( -jj + ll + nn, true );

    b1 = helper( ( jj + ll + nn ) * 0.5, false );
    b2 = helper( ( jj + ll - nn ) * 0.5, false );
    b3 = helper( ( jj - ll + nn ) * 0.5, false );
    b4 = helper( (-jj + ll + nn ) * 0.5, false );

    rat = 2 * nn + 1;
    rat = rat / (jj + ll + nn + 1);
    wign = std::pow(-1,(jj + ll - nn)/2);
    return wign * sqrt(rat) * b1/a1 * a2/b2 * a3/b3 * a4/b4;
  }
  else { return 0.0; }
}

