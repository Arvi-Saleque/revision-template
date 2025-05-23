// sum of from l to r
ll f(ll l, ll r) {
    ll val = (l + r) * (r - l + 1) / 2;
    return val;
}
gcd(a, b) = gcd(a, b - a)
so gcd(a1 + bj, a2 + bj) = gcd(a1 + bj, a2 - a1)

// basic geometry
// be careful! [θ in radians]
Chord Length of a Circle
L = 2r * sin(θ / 2)
Arc Length of a Circle
L = r * θ
Sector Area of a Circle
A = (1/2) * r^2 * θ
Area of Segment = Area of Sector - Area of Triangle
A = (1/2) * r^2 * (θ - sin(θ))
Length of a Common Chord of Two Circles
L = 2 * sqrt( R^2 - ((d^2 + R^2 - r^2) / (2d))^2 )
