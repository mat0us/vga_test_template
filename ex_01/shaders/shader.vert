// Spousti se pro kazdy vrchol.

attribute highp vec4 posAttr;

attribute lowp vec4 colAttr;

// Predava se do fragment shaderu (interpolovane).
varying lowp vec4 col;

// Stejna matice pro vsechny vrcholy v jednom draw callu.
uniform highp mat4 matrix;

void main()
{
    // Preda barvu do dalsi faze pipeline.
    col = colAttr;

    // Transformuje vrchol do clip space.
    gl_Position = matrix * posAttr;
}
