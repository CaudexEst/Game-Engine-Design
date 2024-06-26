// MyGameEngine2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <iterator>
using namespace std;

/*
10 slide powerpoint
Objects: sprites, camera, lights, 
Objects have properties of location, rotation, scale

*/


//Triples
class Triples
{
public:
    Triples();
    float x, y, z;
    Triples(float x,float y,float z);
    void operator+=(Triples second);
    float getX() {
        return x;
    }
    float getY() {
        return y;
    }
    float getZ() {
        return z;
    }
    void printTriple() {
        cout << "(" << x << "," << y << "," << z <<")"<< endl;
    }

};
Triples::Triples()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}
Triples::Triples(float x,float y,float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
void Triples::operator+=(Triples second)
{
    this->x += second.x;
    this->y += second.y;
    this->z += second.z;
}





//Objects
class Object
{
public:
    string name;
    Object();
    Triples position, rotation, scale;
    Object(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ);
    void printData() {
        cout << "Position: "; position.printTriple();
        cout << "Rotation: "; rotation.printTriple();
        cout << "Scale: "; scale.printTriple();
    }
    void updatePosition(Triples newPos) {
        this->position = newPos;
    }
    void updateRotation(Triples newRot) {
        this->position = newRot;
    }
    void updateScale(Triples newScale) {
        this->position = newScale;
    }
    void updateName(string name) {
        this->name = name;
    }
    void Update() {
        cout << "What are you updating? 1 for name, 2 for position, 3 for rotation, 4 for scale, 5 to quit." << endl;
        int updateNum;
        std::cin >> updateNum;
        switch (updateNum) {
        case 1: {
              string newName;
              cout << "What is the new name?" << endl;
              std::cin >> newName;
              updateName(newName);
        }
        case 2:
            float x, y, z;
            cout << "What is the new x position?" << endl;
            std::cin >> x;
            cout << "What is the new y position?" << endl;
            std::cin >> y;
            cout << "What is the new z position?" << endl;
            std::cin >> z;
            updatePosition(Triples(x, y, z));
            break;
        case 3:
            cout << "What is the new x rotation?" << endl;
            std::cin >> x;
            cout << "What is the new y rotation?" << endl;
            std::cin >> y;
            cout << "What is the new z rotation?" << endl;
            std::cin >> z;
            updateRotation(Triples(x, y, z));
            break;
        case 4:
            cout << "What is the new x scale?" << endl;
            std::cin >> x;
            cout << "What is the new y scale?" << endl;
            std::cin >> y;
            cout << "What is the new z scale?" << endl;
            std::cin >> z;
            updateScale(Triples(x, y, z));
            break;
        case 5:
            return;
            break;
        default:
            cout << "Command was not accepted. Please input an accepted command." << endl;
            break;
        }
            
    }
    string getName() {
        return name;
    }
    void printAllData() {
        cout << "Name: " << name << endl;
        cout << "Position: "; position.printTriple();
        cout << "Rotation: "; rotation.printTriple();
        cout << "Scale: "; scale.printTriple();
    }

};
Object::Object()
{
    Triples position;
    Triples rotation;
    Triples scale;
}
Object::Object(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ)
{
    this->position.x = posX;
    this->position.y = posY;
    this->position.z = posZ;
    this->rotation.x = rotX;
    this->rotation.y = rotY;
    this->rotation.z = rotZ;
    this->scale.x = scaleX;
    this->scale.y = scaleY;
    this->scale.z = scaleZ;
}

//Sprite Objects
class Sprite : public Object
{
public:
    string Image;
    string name;
    Sprite(string name, string Image);
    Sprite(string name, string Image, Triples pos, Triples rot, Triples scale);
    string getImage() {
        return Image;
    }
    void printAllData() {
        cout << "The current image is: " << Image << endl;
        printData();
    }
    void updateImage(string newImage) {
        this->Image = newImage;
    }
    string getType() {
        return "sprite";
    }
    void Update() {
        cout << "What are you updating? 1 for name, 2 for position, 3 for rotation, 4 for scale, 5 for image, 6 to quit." << endl;
        int updateNum;
        std::cin >> updateNum;
        switch (updateNum) {
        case 1: {
            string newName;
            cout << "What is the new name?" << endl;
            std::cin >> newName;
            updateName(newName);
        }
        case 2:
            float x, y, z;
            cout << "What is the new x position?" << endl;
            std::cin >> x;
            cout << "What is the new y position?" << endl;
            std::cin >> y;
            cout << "What is the new z position?" << endl;
            std::cin >> z;
            updatePosition(Triples(x, y, z));
            break;
        case 3:
            cout << "What is the new x rotation?" << endl;
            std::cin >> x;
            cout << "What is the new y rotation?" << endl;
            std::cin >> y;
            cout << "What is the new z rotation?" << endl;
            std::cin >> z;
            updateRotation(Triples(x, y, z));
            break;
        case 4:
            cout << "What is the new x scale?" << endl;
            std::cin >> x;
            cout << "What is the new y scale?" << endl;
            std::cin >> y;
            cout << "What is the new z scale?" << endl;
            std::cin >> z;
            updateScale(Triples(x, y, z));
            break;
        case 5: {
            string newImage;
            cout << "What is the new Image?" << endl;
            updateImage(newImage);
            break; }
        default:
            cout << "Command was not accepted. Please input an accepted command." << endl;
            break;
        }

    }

};
Sprite::Sprite(string name, string Image)
{
    this->name = name;
    this->Image = Image;
    position = Triples();
    rotation = Triples();
    scale = Triples();
}
Sprite::Sprite(string name,  string Image, Triples pos, Triples rot, Triples scal)
{
    this->name = name;
    this->Image = Image;
    position = pos;
    rotation = rot;
    scale = scal;
}


//Camera objects
class Camera : public Object
{
public:
    Camera();
    Triples pointing;
    Camera(string nam,Triples point);
    Camera(string nam,Triples point, Triples pos, Triples rot, Triples scal);
    void printAllData() {
        cout << "The camera is pointing towards: "; pointing.printTriple();
        printData();
    }
    void updatePointing(Triples newPoint) {
        this->pointing = newPoint;
    }
    string getType() {
        return "camera";
    }
    void Update() {
        cout << "What are you updating? 1 for name, 2 for position, 3 for rotation, 4 for scale, 5 to where its pointing, 6 to quit." << endl;
        int updateNum;
        std::cin >> updateNum;
        switch (updateNum) {
        case 1: {
            string newName;
            cout << "What is the new name?" << endl;
            std::cin >> newName;
            updateName(newName);
        }
        case 2:
            float x, y, z;
            cout << "What is the new x position?" << endl;
            std::cin >> x;
            cout << "What is the new y position?" << endl;
            std::cin >> y;
            cout << "What is the new z position?" << endl;
            std::cin >> z;
            updatePosition(Triples(x, y, z));
            break;
        case 3:
            cout << "What is the new x rotation?" << endl;
            std::cin >> x;
            cout << "What is the new y rotation?" << endl;
            std::cin >> y;
            cout << "What is the new z rotation?" << endl;
            std::cin >> z;
            updateRotation(Triples(x, y, z));
            break;
        case 4:
            cout << "What is the new x scale?" << endl;
            std::cin >> x;
            cout << "What is the new y scale?" << endl;
            std::cin >> y;
            cout << "What is the new z scale?" << endl;
            std::cin >> z;
            updateScale(Triples(x, y, z));
            break;
        case 5: {
            cout << "What x is it pointing at?" << endl;
            std::cin >> x;
            cout << "What y is it pointing at" << endl;
            std::cin >> y;
            cout << "What z is it pointing at" << endl;
            std::cin >> z;
            updatePointing(Triples(x, y, z));
            break; }
        default:
            cout << "Command was not accepted. Please input an accepted command." << endl;
            break;
        }

    }
};
Camera::Camera()
{
    position = Triples();
    rotation = Triples();
    scale = Triples();
    pointing = Triples();
}
Camera::Camera(string nam,Triples point)
{
    this->name = nam;
    this->pointing = point;
    position = Triples();
    rotation = Triples();
    scale = Triples();
}
Camera::Camera(string nam,Triples point, Triples pos, Triples rot, Triples scal)
{
    this->name = nam;
    this->pointing = point;
    this->position = pos;
    this->rotation = rot;
    this->scale = scal;
}

//Light objects
class Light : public Object
{
public:
    Light();
    float intensity;
    Light(string nam, float intens);
    Light(string nam, float intens, Triples pos, Triples rot, Triples scal);
    void printAllData() {
        cout << "The intensity of the light is: " << intensity << endl;
        printData();
    }
    void updateIntensity(float newIntens) {
        this->intensity = newIntens;
    }
    string getType() {
        return "light";
    }
    void Update() {
        cout << "What are you updating? 1 for name, 2 for position, 3 for rotation, 4 for scale, 5 for intensity, 6 to quit." << endl;
        int updateNum;
        std::cin >> updateNum;
        switch (updateNum) {
        case 1: {
            string newName;
            cout << "What is the new name?" << endl;
            std::cin >> newName;
            updateName(newName);
        }
        case 2:
            float x, y, z;
            cout << "What is the new x position?" << endl;
            std::cin >> x;
            cout << "What is the new y position?" << endl;
            std::cin >> y;
            cout << "What is the new z position?" << endl;
            std::cin >> z;
            updatePosition(Triples(x, y, z));
            break;
        case 3:
            cout << "What is the new x rotation?" << endl;
            std::cin >> x;
            cout << "What is the new y rotation?" << endl;
            std::cin >> y;
            cout << "What is the new z rotation?" << endl;
            std::cin >> z;
            updateRotation(Triples(x, y, z));
            break;
        case 4:
            cout << "What is the new x scale?" << endl;
            std::cin >> x;
            cout << "What is the new y scale?" << endl;
            std::cin >> y;
            cout << "What is the new z scale?" << endl;
            std::cin >> z;
            updateScale(Triples(x, y, z));
            break;
        case 5: {
            float intens =0.0;
            cout << "What is the new intensity?" << endl;
            updateIntensity(intens);
            break; }
        default:
            cout << "Command was not accepted. Please input an accepted command." << endl;
            break;
        }

    }

};
Light::Light()
{
    this->intensity = 1.0;
    position = Triples();
    rotation = Triples();
    scale = Triples();
}
Light::Light(string nam, float intens)
{
    this->name = nam;
    this->intensity = intens;
    position = Triples();
    rotation = Triples();
    scale = Triples();
}
Light::Light(string nam, float intens, Triples pos, Triples rot, Triples scal)
{
    this->name = nam;
    this->intensity = intens;
    this->position = pos;
    this->rotation = rot;
    this->scale = scal;
}

void CreateSprite(list<Object> ObjectList) {
    string name, Image;
    float posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ;
    
    cout << "What is the name of the Sprite?"<<endl;
    std::cin >> name;
    cout << "What is the Image?" << endl;
    std::cin >> Image;
    cout << "What is the X position of the Sprite?" << endl;
    std::cin >> posX;
    cout << "What is the Y position of the Sprite?" << endl;
    std::cin >> posY;
    cout << "What is the Z position of the Sprite?" << endl;
    std::cin >> posZ;
    cout << "What is the X rotation of the Sprite?" << endl;
    std::cin >> rotX;
    cout << "What is the Y rotation of the Sprite?" << endl;
    std::cin >> rotY;
    cout << "What is the Z rotation of the Sprite?" << endl;
    std::cin >> rotZ;
    cout << "What is the X scale of the Sprite?" << endl;
    std::cin >> scaleX;
    cout << "What is the Y scale of the Sprite?" << endl;
    std::cin >> scaleY;
    cout << "What is the Z scale of the Sprite?" << endl;
    std::cin >> scaleZ;

    ObjectList.push_back(Sprite(name, Image, Triples(posX, posY, posZ), Triples(rotX, rotY, rotZ), Triples(scaleX, scaleY, scaleZ)));
    return;
}

void CreateCamera(list<Object> ObjectList) {
    string name;
    float posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, pointX,pointY,pointZ;

    cout << "What is the name of the Sprite?" << endl;
    std::cin >> name;
    cout << "What is the Camera pointing for X?" << endl;
    std::cin >> pointX;
    cout << "What is the Camera pointing for Y?" << endl;
    std::cin >> pointY;
    cout << "What is the Camera pointing for Z?" << endl;
    std::cin >> pointZ;
    cout << "What is the X position of the Sprite?" << endl;
    std::cin >> posX;
    cout << "What is the Y position of the Sprite?" << endl;
    std::cin >> posY;
    cout << "What is the Z position of the Sprite?" << endl;
    std::cin >> posZ;
    cout << "What is the X rotation of the Sprite?" << endl;
    std::cin >> rotX;
    cout << "What is the Y rotation of the Sprite?" << endl;
    std::cin >> rotY;
    cout << "What is the Z rotation of the Sprite?" << endl;
    std::cin >> rotZ;
    cout << "What is the X scale of the Sprite?" << endl;
    std::cin >> scaleX;
    cout << "What is the Y scale of the Sprite?" << endl;
    std::cin >> scaleY;
    cout << "What is the Z scale of the Sprite?" << endl;
    std::cin >> scaleZ;

    ObjectList.push_back(Camera(name, Triples(pointX,pointY,pointZ), Triples(posX, posY, posZ), Triples(rotX, rotY, rotZ), Triples(scaleX, scaleY, scaleZ)));
    return;
}

void CreateLight(list<Object> ObjectList) {
    string name;
    float intens;
    float posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ;

    cout << "What is the name of the Sprite?" << endl;
    std::cin >> name;
    cout << "What is the intensity of the Light?" << endl;
    std::cin >> intens;
    cout << "What is the X position of the Sprite?" << endl;
    std::cin >> posX;
    cout << "What is the Y position of the Sprite?" << endl;
    std::cin >> posY;
    cout << "What is the Z position of the Sprite?" << endl;
    std::cin >> posZ;
    cout << "What is the X rotation of the Sprite?" << endl;
    std::cin >> rotX;
    cout << "What is the Y rotation of the Sprite?" << endl;
    std::cin >> rotY;
    cout << "What is the Z rotation of the Sprite?" << endl;
    std::cin >> rotZ;
    cout << "What is the X scale of the Sprite?" << endl;
    std::cin >> scaleX;
    cout << "What is the Y scale of the Sprite?" << endl;
    std::cin >> scaleY;
    cout << "What is the Z scale of the Sprite?" << endl;
    std::cin >> scaleZ;

    ObjectList.push_back(Light(name, intens, Triples(posX, posY, posZ), Triples(rotX, rotY, rotZ), Triples(scaleX, scaleY, scaleZ)));
    return;
}


Object IterateList(list<Object> &ObjectList, string &name) {
    list<Object>::iterator it;
    for (it = ObjectList.begin(); it != ObjectList.end(); ++it) {
        if (it->name == name) {
            (*it).getName();
            return *it;
        }
    }
    //return;
}

void DeleteObject(list<Object> &ObjectList, string &name) {
    list<Object>::iterator it;
    for (it = ObjectList.begin(); it != ObjectList.end(); ++it) {
        if (it->name == name) {
            ObjectList.erase(it);
            return;
        }
    }
    cout << '\n';
}

void PrintObjects(list<Object> &ObjectList) {
    list<Object>::iterator it;
    for (it = ObjectList.begin(); it != ObjectList.end(); ++it) {
        (*it).printAllData();
    }
}
int main() //Has to be at end
{
    cout << "Hello World!\n";
    list<Object> ObjectList;
    string currentName;
    Object currentObject;
    int input = 0;
    int subinput = 0;
    while (input != 10) {
        cout << "What would you like to do? Accepted commands are 1 for create, 2 for modify, 3 for object list, 4 for delete or 10 for quit." << endl;
        std::cin >> input;
        switch (input) {
        case 1:
            //create
            cout << "What object would you like to create? 1 for a Sprite, 2 for a Camera, 3 for a Light, or 10 to quit." << endl;
            std::cin >> subinput;
            switch (subinput) {
            case 1:
                CreateSprite(ObjectList);
                break;
            case 2:
                CreateCamera(ObjectList);
                break;
            case 3:
                CreateLight(ObjectList);
                break;
            case 10:
                cout << "Quitting" << endl;
                break;
            default:
                cout << "Command was not accepted. Please insert an accepted command." << endl;
            }
            break;
        case 2:
            //modify
            cout << "What is the name of the Object you want to modify?" << endl;
            std::cin >> currentName;
            currentObject = IterateList(ObjectList, currentName);
            currentObject.Update();
            break;
        case 3:
            //object list
            cout << "Here are all of the created objects: " << endl;
            PrintObjects(ObjectList);
            break;
        case 4:
            //delete
            cout << "What is the name of the Object you want to delete?" << endl;
            std::cin >> currentName;
            DeleteObject(ObjectList, currentName);
            break;
        
        case 10:
            cout << "Quitting";
            break;
        default:
            cout << "Command was not accepted. Please input an accepted command." << endl;
            break;
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
