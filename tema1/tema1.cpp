#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <string> 


#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/geometrics.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    tr = new gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
    tr->Load(window->props.selfDir + "\\assets\\fonts\\Hack-Bold.ttf", 128);
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    if (randomDirection == 1) {
        angle = 3 * angle;
    }

    glm::vec3 corner = glm::vec3(0, 0, 0);
    glm::vec3 wingCorner = glm::vec3(0, 1, 1);
    float squareSide = 100;

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

    Mesh* life = geometrics::CreateCircle("life", 0, 1, 10, glm::vec3(1, 0, 0), true);
    AddMeshToList(life);

    Mesh* bullet = geometrics::CreateRectangle("bullet", corner, 10, glm::vec3(0.412f, 0.412f, 0.412f), 1, false);
    AddMeshToList(bullet);

    Mesh* score = geometrics::CreateRectangle("score", corner, 100, glm::vec3(0.412f, 0.412f, 0.412f), 5, false);
    AddMeshToList(score);

    Mesh* score_point = geometrics::CreateRectangle("score_point", corner, 1, glm::vec3(0, 0.749f, 1), 5, true);
    AddMeshToList(score_point);

    Mesh* eye_black = geometrics::CreateCircle("eye_black", 0, 1, 3, glm::vec3(0, 0, 0), true);
    AddMeshToList(eye_black);

    Mesh* eye_white = geometrics::CreateCircle("eye_white", 0, 1, 8, glm::vec3(1, 1, 1), true);
    AddMeshToList(eye_white);

    Mesh* grass = geometrics::CreateRectangle("grass", corner, 1400, glm::vec3(0, 0.39f, 0), 10, true);
    AddMeshToList(grass);

    Mesh* body = geometrics::CreateTriangle("body", corner, 50, glm::vec3(0.54, 0.27, 0.078), true);
    AddMeshToList(body);

    Mesh* wing_up = geometrics::CreateTriangle("wing_up", corner, 35, glm::vec3(0.54, 0.27, 0.078), true);
    AddMeshToList(wing_up);

    Mesh* wing_down = geometrics::CreateTriangle("wing_down", corner, -35, glm::vec3(0.54, 0.27, 0.078), true);
    AddMeshToList(wing_down);

    Mesh* head = geometrics::CreateCircle("head", 0, 1, 45, glm::vec3(0, 0.39f, 0), true);
    AddMeshToList(head);

    Mesh* beak = geometrics::CreateTriangle("beak", corner, 15, glm::vec3(0.85, 0.64, 0.125), true);
    AddMeshToList(beak);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

}

void Tema1::CreateDuck() 
{
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Translate(centerX, centerY);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Translate(-centerX, -centerY);
    modelMatrix *= transform2D::Translate(centerX + 20, centerY + 10);
    RenderMesh2D(meshes["eye_black"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);

    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Translate(centerX, centerY);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Translate(-centerX, -centerY);
    modelMatrix *= transform2D::Translate(centerX + 20, centerY + 10);

    RenderMesh2D(meshes["eye_white"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    //modelMatrix *= transform2D::Translate(centerX, centerY);

    modelMatrix *= transform2D::Translate(translateX, translateY);

    modelMatrix *= transform2D::Translate(centerX, centerY);
    modelMatrix *= transform2D::Rotate(angle);
    //modelMatrix *= transform2D::Translate(-centerX, -centerY);


    RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Translate(centerX, centerY);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Translate(-centerX, -centerY);
    modelMatrix *= transform2D::Translate(centerX - 170, centerY - 50);

    RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(translateX, translateY);

    modelMatrix *= transform2D::Translate(centerX, centerY);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Translate(-centerX, -centerY);
    modelMatrix *= transform2D::Translate(centerX + 40, centerY - 10);

    RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);

    modelMatrix *= transform2D::Translate(translateX, translateY);

    modelMatrix *= transform2D::Translate(centerX, centerY);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Translate(-centerX, -centerY);

    modelMatrix *= transform2D::Translate(centerX - 160, centerY - 10);

    modelMatrix *= transform2D::Translate(square / 2, square / 2);
    modelMatrix *= transform2D::Rotate(M_PI_2 + angularStep);
    modelMatrix *= transform2D::Translate(-square / 2, -square / 2);

    RenderMesh2D(meshes["wing_up"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);

    modelMatrix *= transform2D::Translate(translateX, translateY);


    modelMatrix *= transform2D::Translate(centerX, centerY);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Translate(-centerX, -centerY);

    modelMatrix *= transform2D::Translate(centerX - 240, centerY);

    modelMatrix *= transform2D::Translate(square / 2, square / 2);
    modelMatrix *= transform2D::Rotate(M_PI_2 + angularStep);
    modelMatrix *= transform2D::Translate(-square / 2, -square / 2);

    //modelMatrix *= transform2D::Translate(translateX, translateY);
    RenderMesh2D(meshes["wing_down"], shaders["VertexColor"], modelMatrix);
}
void Tema1::RenderDuck()
{
    modelMatrix = glm::mat3(1);

    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);


    for (int i = 0; i < lifes; i++) {
        modelMatrix = glm::mat3(1);
        int translateLifeX = 930 + 40 * i;
        int translateLifeY = 670;
        modelMatrix *= transform2D::Translate(translateLifeX, translateLifeY);
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
    }

    for (int i = 0; i < bullets; i++) {
        modelMatrix = glm::mat3(1);
        int transltateBulletX = 1050 + 40 * i;
        int translateBulletY = 660;

        modelMatrix *= transform2D::Translate(transltateBulletX, translateBulletY);

        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(930, 600);
    RenderMesh2D(meshes["score"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(930, 600);

    if (score != 0 && score <= 100) {
        modelMatrix *= transform2D::Scale(score, 100);
    }

    RenderMesh2D(meshes["score_point"], shaders["VertexColor"], modelMatrix);

    CreateDuck();
}

void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();
    int resolutionX = resolution.x;
    int resolutionY = resolution.y;

    time += deltaTimeSeconds;
    if ((time > 20 || bullets == 0) && escape == 0 && isHit == 0) {
        lifes--;
        escape = 1;
        angle = M_PI_2;
    }

    if (dead == 0) {
        if (translateY + centerY > resolutionY && translateX + centerX < resolutionX && escape == 0) { //tavan
            if (angle > 0 && angle < M_PI_2) {
                angle = 2 * M_PI - angle;
            }
            else if (angle > M_PI_2 && angle < M_PI) {
                angle = 2 * M_PI - angle;
            }
        }
        else if (translateX + centerX > resolutionX && translateY + centerY < resolutionY) { // perete dreapta
            if (angle > 0 && angle < M_PI_2) {
                angle = M_PI - angle;
            }
            else if (angle > 3 * M_PI / 2 && angle < 2 * M_PI) {
                angle = 3 * M_PI - angle;
            }
        }
        else if (translateX + centerX < 0 && translateY + centerY < resolutionY) { // perete stanga
            if (angle > M_PI / 2 && angle < M_PI) {
                angle = M_PI - angle;
            }
            else if (angle > M_PI && angle < 3 * M_PI_2) {
                angle = 3 * M_PI - angle;
            }
        }
        else if (translateY + centerY < 0 && translateX + centerX < resolutionX) { // podea
            if (angle > 3 * M_PI_2 && angle < 2 * M_PI) {
                angle = 2 * M_PI - angle;
            }
            else if (angle > M_PI && angle < 3 * M_PI / 2) {
                angle = 2 * M_PI - angle;
            }
        }
    }

    translateX += speed * deltaTimeSeconds * cos(angle);
    translateY += speed * deltaTimeSeconds * sin(angle);

    if (up == 1) {
        angularStep += deltaTimeSeconds;
        if (angularStep > M_PI_4 / 3) {
            up = 0;
        }
    }
    else {
        angularStep -= deltaTimeSeconds;
        if (angularStep < 0) {
            angularStep = 0;
            up = 1;
        }
    }

    RenderDuck();

    if ((dead == 1 || escape == 1) && timeOutside < 4) {
        timeOutside += deltaTimeSeconds;
    }
    else if (timeOutside >= 4) {
        translateX = 0;
        translateY = 0;
        angle = M_PI_4;
        dead = 0;
        time = 0;
        escape = 0;
        bullets = 3;
        timeOutside = 0;
        number_Ducks++;
        isHit = 0;
        randomDirection = rand() % 2;
        if (randomDirection == 1) {
            angle = 3 * angle;
        }
    }
    
    string levelName = "Level " + to_string(level);
    tr->RenderText(levelName, 500, 50, 0.3);
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    glm::ivec2 resolution = window->GetResolution();
    clickX = mouseX;
    clickY = resolution.y - mouseY;
    cout << clickX << " " << clickY << endl;

    hitBoxLow.x = centerX - 173;
    hitBoxLow.y = centerY - 91;

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Translate(centerX, centerY);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= transform2D::Translate(-centerX, -centerY);
    hitBoxLow = modelMatrix * hitBoxLow;

    height = 180;
    width = 250;

    modelMatrix = glm::mat3(1);
    glm::vec3 pointClick = glm::vec3(clickX, clickY, 1);
    modelMatrix *= transform2D::Rotate(-angle);
    modelMatrix *= transform2D::Translate(-hitBoxLow.x, -hitBoxLow.y);
    pointClick = modelMatrix * pointClick;

    cout << pointClick.x << " " << pointClick.y << "\n";
    if (pointClick.x >= 0 && pointClick.x <= width && pointClick.y >= 0
        && pointClick.y <= height && bullets > 0) {
        dead = 1;
        score += 20;
        angle = 3 * M_PI_2;
        isHit = 1;
    }
    else {
        isHit = 0;
    }

    if (bullets > 0) {
        bullets--;
    }

    if (number_Ducks % 5 == 0) {
        speed = speed_Initial + (number_Ducks / 5) * speed_Initial / 5;
        level++;
        score = 0;
        lifes = 3;
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
