// ---- Fragment Shader ----
// Spouští se paralelně na GPU pro každý jednotlivý pixel (fragment) pokrytý trojúhelníky.
// GPU před tím automaticky interpolovala barvy ze tří vrcholů trojúhelníku
// pomocí hardwarového rasterizéru — výsledkem je plynulý barevný přechod (gradient).

// Varying: interpolovaná barva pixelu (přichází z Vertex Shaderu přes rasterizér)
varying lowp vec4 col;

void main()
{
    // Výsledná barva pixelu — rovnou dosadíme interpolovanou barvu
    gl_FragColor = col;
}
