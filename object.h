
#include <string>
#include <vector>

#ifndef OBJECT_H
#define OBJECT_H


struct vec{
    double x;
    double y;
    double z;
    vec(a,b,c){
        x=a
        y=b
        z=c
    }
}





class object
{
public:
    std::string name;
    std::string type;
	struct vec pos;
    struct vec ang;
    struct vec velocity;
    struct vec acceleration;
    long uuid;
    double mass;
private:
	

};

#endif
