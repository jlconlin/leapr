
double interpolate( const std::vector<double>& y, const double& delta, 
  const double& x ){
  /* Inputs
   * ------------------------------------------------------------------------
   * y     : evenly spaced vector to be interpolated
   * delta : spacing in y
   * x     : desired value
   * 
   * Operations
   * ------------------------------------------------------------------------
   * * Interpolate
   *
   * Outputs
   * ------------------------------------------------------------------------
   * * interpolated value
   */

  // This is the index just to the left of desired x point
  unsigned int i = x / delta; 
  double x_L = i * delta; 
                     
  // Return 0.0 if out of range (above), else return interpolated value
  return ( i+2 > y.size() ) ? 0.0 : y[i] + (x-x_L) * (y[i+1]-y[i]) / delta;
}



