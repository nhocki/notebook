// Returns the shortest distance on the surface of a sphere with
// radius R from point A to point B.
// Both points are described as a pair of latitude and longitude
// angles, in degrees.
// 
// -90 (South Pole) <= latitude <= +90 (North Pole)
// -180 (West of meridian) <= longitude <= +180 (East of meridian)
//
double greatCircle(double laa, double loa,
                   double lab, double lob,
                   double R = 6378.0){
    const double PI = acos(-1.0);
    // Convert to radians
    laa *= PI / 180.0; loa *= PI / 180.0;
    lab *= PI / 180.0; lob *= PI / 180.0;
    
    double u[3] = { cos(laa) * sin(loa), cos(laa) * cos(loa),
                    sin(laa) };
    double v[3] = { cos(lab) * sin(lob), cos(lab) * cos(lob),
                    sin(lab) };
    double dot = u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
    bool flip = false;
    if (dot < 0.0){
        flip = true;
        for (int i = 0; i < 3; i++) v[i] = -v[i];
    }
    double cr[3] = { u[1] * v[2] - u[2] * v[1],
                     u[2] * v[0] - u[0] * v[2],
                     u[0] * v[1] - u[1] * v[0] };
    double theta = asin(sqrt(cr[0] * cr[0] + 
                             cr[1] * cr[1] + 
                             cr[2] * cr[2]));
    double len = theta * R;
    if (flip) len = PI * R - len;
    return len;
}