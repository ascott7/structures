#include "vp-tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdint.h>
#include <string>
#include <string.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>



// #include "rapidjson/document.h"

#define DIM 200
#define NUM 32000

// void QueryPerformanceCounter( uint64_t* val )
// {
//     timeval tv;
//     struct timezone tz = {0, 0};
//     gettimeofday( &tv, &tz );
//     *val = tv.tv_sec * 1000000 + tv.tv_usec;
// }

// struct Point {
//     std::string city;
//     double latitude;
//     double longitude;
// };

// double distance( const Point& p1, const Point& p2 )
// {
//     double a = (p1.latitude-p2.latitude);
//     double b = (p1.longitude-p2.longitude);
//     return sqrt(a*a+b*b);
// }

struct Pair {
    std::string name;
    int64_t hash;
};

double distance( const Pair& card1, const Pair& card2)
{
    int64_t diff = card1.hash ^ card2.hash;
    return double(__builtin_popcount(diff));
}

struct HeapItem {
    HeapItem( int index, double dist) :
        index(index), dist(dist) {}
    int index;
    double dist;
    bool operator<( const HeapItem& o ) const {
        return dist < o.dist;   
    }
};

// void linear_search( const std::vector<Point>& items, const Point& target, int k, std::vector<Point>* results, 
//     std::vector<double>* distances) 
// {
//     std::priority_queue<HeapItem> heap;
//     for ( int i = 0; i < items.size(); i++ ) {
//         double dist = distance( target, items[i] );
//         if ( heap.size() < k || dist < heap.top().dist ) {
//             if (heap.size() == k) heap.pop();
//             heap.push( HeapItem( i, dist ) );
//         }
//     }

//     results->clear();
//     distances->clear();
//     while( !heap.empty() ) {
//         results->push_back( items[heap.top().index] );
//         distances->push_back( heap.top().dist );
//         heap.pop();
//     }

//     std::reverse( results->begin(), results->end() );
//     std::reverse( distances->begin(), distances->end() );
// }

// std::vector<int> findLocations(std::string sample, char findIt)
// {
//     std::vector<int> characterLocations;
//     for(int i =0; i < sample.size(); i++)
//         if(sample[i] == findIt)
//             characterLocations.push_back(i);

//     return characterLocations;
// }

std::vector<int> findColons(std::string sample)
{
    std::vector<int> colonLocations;
    bool quoteOpened = false;
    bool escaped = false;
    for(int i =0; i < sample.size(); i++) {
        if (sample[i] == '\"' && !escaped) {
            quoteOpened = !quoteOpened;
        }
        if(sample[i] == ':' && !quoteOpened)
            colonLocations.push_back(i);
        if (sample[i] == '\\') {
            escaped = true;
        } else {
            escaped = false;
        }
    }
    return colonLocations;
}

std::vector<int> findCommas(std::string sample)
{
    std::vector<int> commaLocations;
    bool quoteOpened = false;
    bool escaped = false;
    for(int i =0; i < sample.size(); i++) {
        if (sample[i] == '\"' && !escaped) {
            quoteOpened = !quoteOpened;
        }
        if(sample[i] == ',' && !quoteOpened)
            commaLocations.push_back(i);
        if (sample[i] == '\\') {
            escaped = true;
        } else {
            escaped = false;
        }
    }
    return commaLocations;
}

int main( int argc, char* argv[] ) {
    std::vector<Pair> pairs;
    printf("Reading card database...\n");
    std::ifstream infile("hashesTCDB.json");
    std::string line;
    std::getline(infile, line);
    std::vector<int> colonLocations;
    std::vector<int> commaLocations;
    colonLocations = findColons(line);
    commaLocations = findCommas(line);
    for (int i = 0; i < colonLocations.size(); i++) {
        // if (i % 2 == 1) {
        Pair newPair;
        if (i == 0) {
            newPair.name = line.substr(2, colonLocations[i] - 2);
        } else {
            newPair.name = line.substr(commaLocations[i - 1], colonLocations[i] - commaLocations[i - 1]);
        }
        // newPair.name = line.substr(colonLocations[i - 1], colonLocations[i] - colonLocations[i - 1]);
        // std::cout << newPair.name << i << "\n";
        newPair.hash = std::strtoul(line.substr(colonLocations[i] + 2, commaLocations[i] - colonLocations[i] + 2).c_str(), NULL, 0);
        pairs.push_back(newPair);
        std::cout << newPair.hash << std::endl;
        // std::cout << line.substr(colonLocations[i] + 2, commaLocations[i] - colonLocations[i] + 2).c_str() << std::endl;
        // }
    }
    // FILE* file = fopen("cities.txt", "rt");
    // for(;;) {
    //     char buffer[1000];
    //     Pair point;
    //     if ( !fgets(buffer, 1000, file ) ) {
    //         fclose( file );
    //         break;
    //     }
    //     point.city = buffer;
    //     size_t comma = point.city.rfind(",");
    //     sscanf(buffer + comma + 1, "%lg", &point.longitude);
    //     comma = point.city.rfind(",", comma-1);
    //     sscanf(buffer + comma + 1, "%lg", &point.latitude);
    //     //printf("%lg, %lg\n", point.latitude, point.longitude);
    //     points.push_back(point);
    //     //if(points.size()>50000)break;
    // }
    std::cout << "creating tree" << std::endl;
    VpTree<Pair, distance> tree;
    // uint64_t start, end;
    // QueryPerformanceCounter( &start );

    tree.create( pairs );
    // QueryPerformanceCounter( &end );
    // printf("Create took %d\n", (int)(end-start));

    Pair test;
    test.name = "test";
    test.hash = 15089378856224868691ul;
    // Point point;
    // point.latitude = 43.466438;
    // point.longitude = -80.519185;
    std::vector<Pair> results;
    std::vector<double> distances;

    // QueryPerformanceCounter( &start );
    tree.search( test, 8, &results, &distances );
    // QueryPerformanceCounter( &end );
    // printf("Search took %d\n", (int)(end-start));

    std::cout << "RESULTS" << std::endl;
    for( int i = 0; i < results.size(); i++ ) {
        // printf("%s %lg\n", results[i].name, distances[i]);
        std::cout << results[i].name << ' ' << distances[i] << std::endl;
    }

    Pair test2;
    test2.name = "test2";
    test2.hash = 15089378856224868690ul;
    std::cout << "distance test" << distance(test, test2) << std::endl;

    // printf("---\n");
    // QueryPerformanceCounter( &start );
    // linear_search( points, point, 8, &results, &distances );
    // QueryPerformanceCounter( &end );
    // printf("Linear search took %d\n", (int)(end-start));

    // for( int i = 0; i < results.size(); i++ ) {
    //     printf("%s %lg\n", results[i].city.c_str(), distances[i]);
    // }


    return 0;
}
