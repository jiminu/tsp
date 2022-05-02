#pragma once

class Point {
public :
    // member variable
    float x;
    float y;

    // method
    Point();
    Point(const float& x, const float& y);
    ~Point() {};
    
    float distance_to(const Point& p1);
    
    bool operator==(const Point& rhs) const;
};