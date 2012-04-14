// Find the intersection of the segment that goes from A to B with the quadric defined by
// ax^2 + by^2 + cz^2 + dxy + exz + fyz + gx + hy + iz + j = 0

Point P, Q; // Initialize to the two endpoints of the segment
long double a, b, c, d, e, f, g, h, i, j; // Initialize to the coefficients of the quadric

long double xd = Q.x - P.x, yd = Q.y - P.y, zd = Q.z - P.z, xo = P.x, yo = P.y, zo = P.z;

double A = a*xd*xd + b*yd*yd + c*zd*zd + d*xd*yd + e*xd*zd + f*yd*zd;
double B = 2*(a*xo*xd + b*yo*yd + c*zo*zd) + d*(xo*yd + yo*xd) + e*(xo*zd + xd*zo) + f*(yo*zd + yd*zo) + g*xd + h*yd + i*zd;
double C = a*xo*xo + b*yo*yo + c*zo*zo + d*xo*yo + e*xo*zo + f*yo*zo + g*xo + h*yo + i*zo + j;

// Now solve the quadratic equation defined by A, B and C. This will give 0, 1, 2 or infinite
//solutions for t, the parameter of the parametric equation of the segment.
// If 0 <= t <= 1, then the intersection lies inside the segment.

// Remember to check these cases:
// if A == B == C == 0: Infinite solutions: The line coincides with the surface of the quadric
// else if A == 0: One solution: t = -C / B
// else if B^2 - 4AC < 0: No solutions.
// else if B^2 - 4AC == 0: One solution: t = -B / 2A
// else: Two solutions: t = (-B +- sqrt(B^2 - 4AC) / 2A