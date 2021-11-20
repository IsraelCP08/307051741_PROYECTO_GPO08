// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL incluye
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Matemáticas
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Librerias
#include "SOIL2/SOIL2.h"
#include "stb_image.h"
// Propiedades
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Prototipos de funciones
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camara
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
// variables para rotar
float rot = 0.0f;
float rotl = 0.0f;
float rotsi = 0.0f;
float rotavi = 0.0f;
float rotven = 0.0f;
float rotbo = 0.0f;
float movsix = 0.0f;
float movavx = 0.0f;
float movavz = 0.0f;
float movboz = 0.0f;
float movboy = 0.0f;
// variables para activar animaciones
bool bolanim1;
bool bolanim;
bool avionmov;
bool venanim;
bool lamanim;
bool sillamov;
bool activanim;

//recorridos de objetos
bool recsi1 = true;
bool recsi2 = false;

bool avion1 = true;
bool avion2 = false;
bool avion3 = false;

bool bola1 = true;
bool bola2 = false;
bool bola3 = false;
bool bola4 = false;
bool bola5 = false;

 

int main( )
{
    // Iniciar GLFW
    glfwInit( );
    // Configure todas las opciones necesarias para GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Cree un objeto GLFWwindow que podamos usar para las funciones de GLFW
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Proyecto", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Establecer las funciones de devolución de llamada necesarias
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // Opciones de  GLFW
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Establezca esto en verdadero para que GLEW sepa utilizar un enfoque moderno para recuperar punteros de función y extensiones
    glewExperimental = GL_TRUE;
    // Inicialice GLEW para configurar los punteros de la función OpenGL
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Definir las dimensiones de la ventana gráfica
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // Opciones de OpenGL
    glEnable( GL_DEPTH_TEST );
    
    // Configurar y compilar nuestros sombreadores
    Shader shader( "Shaders/modelLoading.vs", "Shaders/modelLoading.frag" );
    Shader lampshader( "Shaders/lamp.vs", "Shaders/lamp.frag" );
    



    // Modelos a cargar
    Model casa((char*)"Models/casa/casa.obj");
    Model pasto((char*)"Models/pasto/pasto.obj");
    Model sofa((char*)"Models/sofa/sofa.obj");
    Model mesac((char*)"Models/mesacajones/mesa.obj");
    Model banco((char*)"Models/banco/banco.obj");
    Model planta((char*)"Models/planta/planta.obj");
    Model mesat((char*)"Models/mesate/mesate.obj");
    Model librero((char*)"Models/librero/librero.obj");
    Model libro((char*)"Models/libro/libro.obj");
    Model mesacir((char*)"Models/mesac/mesa.obj");
    Model cuadro1((char*)"Models/cuadros/cuadro1.obj");
    Model cuadro2((char*)"Models/cuadros/cuadro2.obj");
    Model cojin((char*)"Models/cojin/cojin1.obj");
    Model arbol((char*)"Models/arbol/arbol.obj");
    Model silla((char*)"Models/silla/silla.obj");
    Model venti1((char*)"Models/ventilador/venti1.obj");
    Model venti2((char*)"Models/ventilador/venti2.obj");
    Model lam2((char*)"Models/lampara/lam2.obj");
    Model lam1((char*)"Models/lampara/lam1.obj");
    Model avion((char*)"Models/avion/avios.obj");
    Model bola((char*)"Models/esfera/esfera.obj");
    
    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
    GLfloat vertices[] =
    {
        // posiciones          // colores          // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 

    };

    GLuint indices[] =
    {  // comenzamos desde 0
        0,1,3,
        1,2,3

    };

    // Primero, configure la VAO del contenedor (y VBO)
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Posicion del atributo
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // color del atributo
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // atributo de coordinación de textura
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Cargar texturas

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int textureWidth, textureHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  
    image = stbi_load("images/goku.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(image);


    // Bucle de juego
    while (!glfwWindowShouldClose(window))
    {
        // Establecer tiempo
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Consultar y llamar a eventos
        glfwPollEvents();
        DoMovement();

        // Borrar el colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Dibuja el model
        // Modelo casa
        glm::mat4 model(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        casa.Draw(shader);
        //modelo pasto
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pasto.Draw(shader);
        //modelo sofa
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.65f, 0.65f, 0.65f));
        model = glm::translate(model, glm::vec3(9.15f, 0.55f, 7.75f));
        model = glm::rotate(model, glm::radians(-173.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        sofa.Draw(shader);
        // modelo mesa con cajones
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.45f, 0.45f, 0.45f));
        model = glm::translate(model, glm::vec3(7.5f, 0.35f, 6.5f));
        model = glm::rotate(model, glm::radians(150.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        mesac.Draw(shader);
        //modelo banco para sentarse
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.7f, 0.85f, 0.7f));
        model = glm::translate(model, glm::vec3(4.5f, 0.17f, 4.0f));
        model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        banco.Draw(shader);
        //modelo de planta
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(6.5f, 5.0f, 6.5f));
        model = glm::translate(model, glm::vec3(1.02f, 0.034f, 0.4f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        planta.Draw(shader);
        // modelo mesa cuadrada
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(6.4f, 0.135f, 4.3f));
        model = glm::rotate(model, glm::radians(-50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        mesat.Draw(shader);
        // modelo librero
        model = glm::mat4(1);
        model = glm::scale(model, glm::vec3(0.45f, 0.44f, 0.45f));
        model = glm::translate(model, glm::vec3(9.0f, 0.29f, 11.75f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        librero.Draw(shader);
        //modelo mesa circular
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(4.5f, 0.155f, 5.3f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        mesacir.Draw(shader);
        // modelo cuadro rojo
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(4.5f, 2.0f, 5.7f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cuadro1.Draw(shader);
        // modelo cuadro gris
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(6.85f, 2.0f, 1.7f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cuadro2.Draw(shader);
        // modelo libro
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(6.25f, 0.61f, 4.4f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        libro.Draw(shader);
        //modelo cojin 
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(5.5f, 0.69f, 5.25f));
        model = glm::rotate(model, glm::radians(-rot), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cojin.Draw(shader);
        //modelo arbol 1
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-11.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        arbol.Draw(shader);
        //modelo arbol2
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-11.0f, 0.0f, -11.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        arbol.Draw(shader);
        //modelo silla
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.0f+movsix, 0.6f, 1.5f));
        model = glm::rotate(model, glm::radians(rotsi), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        silla.Draw(shader);
        //modelo ventilador de techo parte de arriba
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(4.0f, 2.02f, 3.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        venti1.Draw(shader);
        //modelo ventilador de techo parte de abajo
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(4.0f, 2.02f, 3.0f));
        model = glm::rotate(model, glm::radians(rotven), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        venti2.Draw(shader);
        //modelo lampara parte de abajo
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(6.5f, 0.8f, 4.3f));
        model = glm::rotate(model, glm::radians(110.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lam2.Draw(shader);
        //modelo lampara parte de arriba
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(6.5f, 0.8f, 4.3f));
        model = glm::rotate(model, glm::radians(110.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotl), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lam1.Draw(shader);
        // modelo de avion
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(11.0f+movavx, 8.0f, 11.0f+movavz));
        model = glm::rotate(model, glm::radians(rotavi), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        avion.Draw(shader);
        //MODELO DE BOLA
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(4.6f, 0.608f+movboy, 5.3f+movboz));
        model = glm::rotate(model, glm::radians(rotbo), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        bola.Draw(shader);

        glBindVertexArray(0);

        // Intercambiar los búferes
        glfwSwapBuffers( window );
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate( );
    return 0;
}


// Mueve / altera las posiciones de la cámara según la entrada del usuario
void DoMovement( )
{
    // Controles de camara
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }

    if (activanim) //limitar movimiento de cojin
    {   
        if (rot < 45.0f) 
        {
            rot += 0.1f;
        }
    }
    else if (!activanim)
    {
            if (rot > 0.0f) 
            {
                rot -= 0.1f;
            }

    }
    // limitar trayectiria de silla
    if (sillamov) {
        if (recsi1) {
            if (movsix > 4.0f) {
                recsi1 = false;
                recsi2 = true;
            }
            else {
                movsix += 0.01;
            }
        }

        if (recsi2) {
            if (movsix < -2.0f) {
                recsi2 = false;
                recsi1 = true;
            }
            else {
                movsix -= 0.01;
            }
        }

    }
    //delimitar movimiento dde ventilador 
    if (venanim) {
        rotven += 0.1f;
    }
    else if (!venanim) {
        rotven += 0.0f;
    }
    //delimitar movimiento de lampara
    if (lamanim)
    {
        if (rotl < 90)
        {
            rotl += 0.1f;
        }
    }
    else if (!lamanim)
    {
        if (rotl > -15)
        {
            rotl -= 0.1f;
        }

    }
    //delimitar movimiento del avion
    if (avionmov) {
        if (avion1) {
            if (movavz < -22) {
                avion1 = false;
                avion2 = true;
                rotavi = 135.0f;
            }
            else {
                movavz -= 0.01f;
            }
        }

        if (avion2) {
            if (movavx < -22.0f) {
                avion2 = false;
                avion3 = true;
                rotavi = 270.0f;
            }
            else {
                movavz += 0.01f;
                movavx -= 0.01f;
            }
        }

        if (avion3) {
            if (movavx > 0.0f) {
                avion3 = false;
                avion1 = true;
                rotavi = 0.0f;
            }
            else {
                movavx += 0.01f;
            }
        }
    }

    //delimitar movimiento de bola 
    if (bolanim) {
        rotbo += 0.1f;
    }
    else if (!venanim) {
        rotbo += 0.0f;
    }
    // delimitar trayectoria de bola
    if (bolanim1) {
        if (bola1) {
            if (movboz < -0.5f) {
                bola1 = false;
                bola2 = true;
            }
            else {
                movboz -= 0.01;
            }
        }

        if (bola2) {
            if (movboz < -0.95f) {
                bola2 = false;
                bola3 = true;
            }
            else {
                movboz -= 0.01;
                movboy -= 0.01;
            }
        }

        if (bola3) {
            if (movboz < -1.8f) {
                bola3 = false;
                bola4 = true;

            }
            else {
                movboz -= 0.01;
            }
        }

        if (bola4) {
            if (movboz > 0.0f) {
                bola4 = false;
                bola5 = true;
            }
            else {
                movboz += 0.01;
                movboy += 0.01;
            }
        }

        if (bola5) {
            if (movboy < 0.0f) {
                bola5 = false;
                bola1 = true;
            }
            else {
                movboy -= 0.01;
            }
        }

    }
}

// Se llama cada vez que se presiona / suelta una tecla a través de GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }

    if (keys[GLFW_KEY_O])
    {
        activanim = !activanim;

    }
 
    if (keys[GLFW_KEY_P])
    {
        sillamov = !sillamov;
    }
 
    if (keys[GLFW_KEY_I])
    {
        venanim = !venanim;
    }

    if (keys[GLFW_KEY_U])
    {
        lamanim = !lamanim;
    }

    if (keys[GLFW_KEY_Y])
    {
        avionmov = !avionmov;
    }

    if (keys[GLFW_KEY_L])
    {
        bolanim = !bolanim;
        bolanim1 = !bolanim1;
    }
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Invertido porque las coordenadas y van de abajo a izquierda
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

