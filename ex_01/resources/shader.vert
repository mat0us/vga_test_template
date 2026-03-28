// ---- Vertex Shader ----
// Spouští se paralelně na GPU pro každý jednotlivý vrchol (Vertex).
// Vstupní data přichází z VBO přes setAttributeBuffer() z C++ kódu.

// Atribut: 3D pozice tohoto vrcholu (X, Y, Z) z VBO
attribute highp vec4 posAttr;

// Atribut: RGB barva tohoto vrcholu z VBO
attribute lowp vec4 colAttr;

// Varying: výstup do Fragment Shaderu — barva se interpoluje přes celý trojúhelník
varying lowp vec4 col;

// Uniform: MVP matice (Model * View * Projection), stejná pro všechny vrcholy jednoho draw callu
// Posíláme ji z C++ přes setUniformValue()
uniform highp mat4 matrix;

void main()
{
    // Předáme barvu dál do Fragment Shaderu — GPU ji interpoluje přes povrch trojúhelníku
    col = colAttr;

    // Transformujeme pozici vrcholu z 3D světového prostoru do 2D prostoru obrazovky.
    // gl_Position je vestavěný výstup vertex shaderu — určuje finální polohu pixelu.
    gl_Position = matrix * posAttr;
}
