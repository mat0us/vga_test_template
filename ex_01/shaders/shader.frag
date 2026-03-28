// Spousti se pro kazdy fragment (kandidat na pixel).

// Interpolovana barva z vertex shaderu.
varying lowp vec4 col;

void main()
{
    // Vystupni barva pixelu.
    gl_FragColor = col;
}
