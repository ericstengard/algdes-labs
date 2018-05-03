#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <math.h>
#include <utility>
#include <cmath>
#include <random>
#include <chrono>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <stdio.h>
#include <set>
#include <unordered_set>
#include <cstddef>
#include <map>
#include <unordered_map>
#include <float.h>
#include <stdlib.h>

#define __DBL_MAX std::numeric_limits<double>::max()

struct Point
{
    double x, y;

    double dist(const Point &b) const
    {
        return sqrt((x - b.x)*(x - b.x) +
                    (y - b.y)*(y - b.y));
    }
};

typedef std::vector<Point> Points;

double closestDist(const Points &v, double min = __DBL_MAX)
{
    for (auto it1 = v.begin(); it1 != v.end(); ++it1)
        for (auto it2 = it1 + 1; it2 != v.end() && abs(it2->y - it1->y) < min; ++it2)
            min = std::min(it1->dist(*it2), min);

    return min;
}

double closestDivAndConq(const Points &v)
{
    if (v.size() <= 3)
        return closestDist(v);

    size_t mid = v.size() / 2;

    Points Pl(v.begin(), v.begin() + mid);
    Points Pr(v.begin() + mid, v.end());

    double dl = closestDivAndConq(Pl);
    double dr = closestDivAndConq(Pr);

    double d = std::min(dl, dr);

    Points strip;

    const Point &midPoint = v[mid];

    for (auto p : v)
        if (abs(midPoint.x - p.x) < d)
            strip.push_back(p);

    std::sort(strip.begin(), strip.end(), [](const Point &a, const Point &b) { return (a.y == b.y) ? (a.x < b.x) : (a.y < b.y); });

    return std::min(d, closestDist(strip, d));
}

double closest(Points &v)
{
    std::sort(v.begin(), v.end(), [](const Point &a, const Point &b) { return (a.x == b.x) ? (a.y < b.y) : (a.x < b.x); });

    return closestDivAndConq(v);
}

bool is_digits(const std::string &str)
{
    // %O%F%
    std::size_t found = str.find_first_not_of("0123456789 -.,eE+\v\r\t\n\f");
    //return str.find_first_not_of("0123456789 -.,eE+") == std::string::npos;
    return found == std::string::npos;
}

int main(int argc, char * argv[])
{

    std::vector<Point> points;

    std::ifstream ifs (argv[1], std::ifstream::binary);

    // get pointer to associated buffer object
    std::filebuf* pbuf = ifs.rdbuf();

    // get file size using buffer's members
    std::size_t size = pbuf->pubseekoff (0,ifs.end,ifs.in);
    pbuf->pubseekpos (0,ifs.in);

    // allocate memory to contain file data
    char* buffer= new char[size];

    // get file data
    pbuf->sgetn (buffer,size);

    ifs.close();

    std::string text = buffer;

    std::istringstream iss(text);
    std::string line;
    int N = 0;
    double hane;
    //double X;
    //double Y;
    std::string temp;

    while (std::getline(iss, line)) {
        if(line.compare("EOF") == 0){
            break;
        }
        if (is_digits(line)) {
            std::stringstream iss(line);
            double X;
            double Y;
            iss >> hane;
            iss >> X;
            iss >> Y;
            if(iss.fail()){
                continue;
            }
            N++;
            Point p;
            p.x = X;
            p.y = Y;
            points.push_back(p);
            temp = line;
        }
    }
    /*
    for(auto p : points){
        std::cout << p.x << " " << p.y << '\n';
    }
     */

    double ret = closest(points);
    if (ret == __DBL_MAX)
        return -1;

    std::cout << argv[1] << ": "<< points.size()  << " " << std::setprecision(std::numeric_limits<double>::digits10) << ret << '\n';

    return 0;
}