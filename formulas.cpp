// sum of from l to r
ll f(ll l, ll r) {
    ll val = (l + r) * (r - l + 1) / 2;
    return val;
}
gcd(a, b) = gcd(a, b - a)
so gcd(a1 + bj, a2 + bj) = gcd(a1 + bj, a2 - a1)

// basic geometry 
//be carefull ***[θ in radians]***
Chord Length of a Circle
L = 2r sin (θ/2)
Arc Length of a Circle
L = rθ
Sector Area of a Circle
L = 1/2 * r^2 * θ
Area of Segment = Area of Sector - Area of Triangle
A = (1/2) × r2(θ - sinθ)
Length of a Common Chord of Two Circles 
<pre> **Length of Common Chord Between Two Circles:** If two circles of radii \( R \) and \( r \), with centers distance \( d \) apart, intersect, the length \( L \) of their common chord is: \[ L = 2 \sqrt{R^2 - \left( \frac{d^2 + R^2 - r^2}{2d} \right)^2} \] </pre>
