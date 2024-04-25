// MyGameEngine2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <iterator>
#include <ctime>
#include <cmath>
#include <tchar.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define ZERO(memory) ZeroMemory(&memory, sizeof(memory))
using namespace std;

void System(string cmd)
{
    STARTUPINFOA startupInfo;
    PROCESS_INFORMATION processInfo;
    ZERO(startupInfo);
    ZERO(processInfo);

    CreateProcessA(NULL, (LPSTR)cmd.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo);
}


//Triples
class Triples
{
public:
    Triples();
    float x, y, z;
    Triples(float x, float y, float z);
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
        cout << "(" << x << "," << y << "," << z << ")" << endl;
    }
    string getTriple() {
        return to_string(x) + "," + to_string(y) + "," + to_string(z);
    }

};
Triples::Triples()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}
Triples::Triples(float x, float y, float z)
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
    string ObjectData;
    Object();
    Triples position, rotation, scale;
    Object(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ);
    Object(Triples pos, Triples rot, Triples scal);
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
    void Update(Triples pos) {
        cout << "tst";
        stringstream OD(ObjectData);
        string newData = "";
        string objLine;

        while (getline(OD, objLine)) { 
            if (objLine[0] == 'p') { 
                vector<string> Oldvals;
                for(int i =0; i<objLine.size();i++)
                {
                    stringstream OL(objLine);
                    string substr;
                    getline(OL, substr, ',');
                    Oldvals.push_back(substr);
                }

                Triples oldPos = Triples(stof(Oldvals[1]), stof(Oldvals[2]), stof(Oldvals[3])); 
                oldPos += pos; // add move to position
                string newLine = "p," + to_string(oldPos.x) + "," + to_string(oldPos.y) + "," + to_string(oldPos.z) + ",\n"; 
                newData.append(newLine);
            }
            else newData.append(objLine + "\n"); 
        }
        this->ObjectData = newData;
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
Object::Object(Triples pos, Triples rot, Triples scal)
{
    this->position = pos;
    this->rotation = rot;
    this->scale = scal;
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
Sprite::Sprite(string name, string Image, Triples pos, Triples rot, Triples scal)
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
    Triples up;
    Triples right;
    Triples forward;
    float focusPoint;
    Camera(Triples point);
    Camera(Triples point, Triples pos, Triples rot, Triples scal, float focus);
    Camera(Triples point, Triples pos, Triples rot, Triples scal, float focus, Triples u, Triples r, Triples f);
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
    this->focusPoint = 0.0f;
    up = Triples();
    right = Triples();
    forward = Triples();
}
Camera::Camera(Triples point)
{
    this->pointing = point;
    position = Triples();
    rotation = Triples();
    scale = Triples();
    this->focusPoint = 0.0f;
    up = Triples();
    right = Triples();
    forward = Triples();
}
Camera::Camera(Triples point, Triples pos, Triples rot, Triples scal, float focus)
{
    this->pointing = point;
    this->position = pos;
    this->rotation = rot;
    this->scale = scal;
    this->focusPoint = focus;
}
Camera::Camera(Triples point, Triples pos, Triples rot, Triples scal, float focus, Triples u, Triples r, Triples f)
{
    this->pointing = point;
    this->position = pos;
    this->rotation = rot;
    this->scale = scal;
    this->up = u;
    this->right = r;
    this->forward = f;
    this->focusPoint = focus;
}

//Light objects
class Light : public Object
{
public:
    Light();
    float intensity;
    Triples color;
    Light(float intens);
    Light(float intens, Triples pos, Triples rot, Triples scal, Triples c);
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
            float intens = 0.0;
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
Light::Light(float intens)
{
    this->intensity = intens;
    position = Triples();
    rotation = Triples();
    scale = Triples();
}
Light::Light(float intens, Triples pos, Triples rot, Triples scal, Triples c)
{
    this->intensity = intens;
    this->position = pos;
    this->rotation = rot;
    this->scale = scal;
    this->color = c;
}

void CreateSprite(list<Object> ObjectList) {
    string name, Image;
    float posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ;

    cout << "What is the name of the Sprite?" << endl;
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
    float posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, pointX, pointY, pointZ;

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

    ObjectList.push_back(Camera(Triples(pointX, pointY, pointZ), Triples(posX, posY, posZ), Triples(rotX, rotY, rotZ), Triples(scaleX, scaleY, scaleZ), 0.0f));
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

    //ObjectList.push_back(Light(intens, Triples(posX, posY, posZ), Triples(rotX, rotY, rotZ), Triples(scaleX, scaleY, scaleZ)));
    return;
}


Object IterateList(list<Object>& ObjectList, string& name) {
    list<Object>::iterator it;
    for (it = ObjectList.begin(); it != ObjectList.end(); ++it) {
        if (it->name == name) {
            (*it).getName();
            return *it;
        }
    }
    //return;
}

void DeleteObject(list<Object>& ObjectList, string& name) {
    list<Object>::iterator it;
    for (it = ObjectList.begin(); it != ObjectList.end(); ++it) {
        if (it->name == name) {
            ObjectList.erase(it);
            return;
        }
    }
    cout << '\n';
}

void PrintObjects(list<Object>& ObjectList) {
    list<Object>::iterator it;
    for (it = ObjectList.begin(); it != ObjectList.end(); ++it) {
        (*it).printAllData();
    }
}


Object* Object1;
Object* Object2;
Object* Object3;
Camera* mainCamera;
Light* mainLight;


Object* Instantiate(string file)
{
    string currentText;
    Object* newObject = new Object(Triples(), Triples(),Triples());
    ifstream ReadFile("Prefabs/" + file + ".prefab");
    ofstream WriteFile;
    WriteFile.open("objects.obj", std::ios_base::app);
    while (getline(ReadFile, currentText)) 
    {
        newObject->ObjectData.append(currentText);
        WriteFile << currentText <<"\n";
    }
    WriteFile.close();
    ReadFile.close();

    return newObject;
}

float yPOS(float time)
{
    return 0.6f + 0.3f * sin(2 * time);
}
float Time()
{
    return (float)clock() / CLOCKS_PER_SEC;
}


void UpdateCamera()
{
    ofstream WriteFile;
    WriteFile.open("objects.obj", std::ios_base::app);
    WriteFile << "________________" << "\n";
    WriteFile << "v," << mainCamera->position.getTriple()<<","<<mainCamera->focusPoint << "," << "\n";
    WriteFile << "u," << mainCamera->up.getTriple() << "," << "\n";
    WriteFile << "r," << mainCamera->right.getTriple() << "," << "\n";
    WriteFile << "f," << mainCamera->forward.getTriple() << "," << "\n";
    WriteFile.close();
}

void UpdateLight()
{
    ofstream WriteFile;
    WriteFile.open("objects.obj", std::ios_base::app);
    WriteFile << "________________" << "\n";
    WriteFile << "l," << mainLight->color.getTriple() << "," << mainLight->intensity<< "," << "\n";
    WriteFile << "q," << mainLight->position.getTriple() << ",1"<< "," << "\n";
    WriteFile.close();
}

void ReadInput()
{
    ifstream InputLog("input.log");
    string currentText;
    while (getline(InputLog, currentText))
    {
        cout << currentText<<"\n";
    }
    InputLog.close();
}

void OutputOD(Object* Object, ofstream& WriteFile)
{
    stringstream OD(Object->ObjectData);
    string currentLine;
    while (getline(OD, currentLine)) 
    {
        WriteFile << currentLine << "," << "\n";
    }
}

void UpdateOBJs()
{
    ofstream ofs;
    ofs.open("objects.obj", std::ios_base::app);

    OutputOD(Object1, ofs);
    OutputOD(Object2, ofs);
    OutputOD(Object3, ofs);

    ofs.close();
}

void Update()
{
    Object2->position = Triples(0, yPOS(Time()), 0);
    //Object2->Update(Triples(0, yPOS(Time()), 0));
    //Object2->position.printTriple();

    /* Remove Only to see update to obj file, otherwise it no longer renders
    ofstream ofs;
    ofs.open("objects.obj", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ReadInput();

    UpdateOBJs();*/
    ReadInput();
    UpdateCamera();
    UpdateLight();
}



void Start()
{
    mainCamera = new Camera(Triples(), Triples(0.0f, 0.99f, 2.5f), Triples(), Triples(), 1.5f, Triples(0.0f,1.0f,0.0f), Triples(1.0f,0.0f,0.0f), Triples(0.0f,0.0f,-1.0f));
    mainLight = new Light(0.7f, Triples(0.0f,1.5f,1.2f), Triples(), Triples(), Triples(1.0f,1.0f,1.0f));

    UpdateCamera();
    UpdateLight();
    Object1 = Instantiate("Cube1");
    Object2 = Instantiate("Cube2");
    Object3 = Instantiate("Cube3");
    Object1->name = "AGK.Object1";
    Object2->name = "AGK.Object2";
    Object3->name = "AGK.Object3";
    cout<<Object1->name<<Object2->name<<Object3->name;


}



int main() //Has to be at end
{

    ofstream ofs;
    ofs.open("objects.obj", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    float interval = 0.1f;
    float time = Time();
    Start();
    Update();
    System("Direct3D.exe");
    while (true)
    {
        if (time < Time())
        {
            Update();
            time += interval;
            //cout << time << endl;
        }
    }
    return 0;

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
