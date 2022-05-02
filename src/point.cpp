#include"point.h"
#include<cmath>

Point::Point() {
    this->x = 0;
    this->y = 0;
}

Point::Point(const float& x, const float& y) {
    this->x = x;
    this->y = y;
}

float Point::distance_to(const Point& p1) {
    float distance;

    distance = sqrt(pow(this->x - p1.x, 2) + pow(this->y - p1.y, 2));

    return distance;
}

bool Point::operator==(const Point& rhs) const {
    return (x == rhs.x && y == rhs.y);
}