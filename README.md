# VGA ex_01 — OpenGL + Qt Quick cheat sheet

Tento projekt renderuje 3D objekty přes OpenGL pod QML vrstvou. Každý objekt má vlastní geometrii, transformaci a volitelnou animaci řízenou z QML.

---

## Architektura (přehled)

```
QML (main.qml)
  └─ OpenGLScene (QQuickItem, UI thread)
       └─ sync() ──kopíruje hodnoty──> OpenGLSceneRenderer (render thread)
            ├─ init()   — vytvoří buffery a objekty (jen jednou)
            └─ paint()  — syncAnimations() + draw() pro každý objekt
```

Datový tok animace: `QML NumberAnimation` → `Q_PROPERTY` → `sync()` → `renderer setter` → `AnimatedMeshObject::syncAnimations()` → `Transform` → `draw()`.

---

## Jak přidat nový objekt (celý postup)

### 1. Definovat vrcholy — `src/objects/SceneObjects.h` + `.cpp`

```cpp
// SceneObjects.h — přidat deklaraci
std::vector<Vertex> buildMojeGeometrieVertices();

// SceneObjects.cpp — přidat implementaci
std::vector<Vertex> buildMojeGeometrieVertices()
{
    // Vertex format: { {x, y, z}, {r, g, b} }
    // x = doleva/doprava, y = dolů/nahoru, z = dozadu/dopředu
    // r, g, b = 0.0 – 1.0
    return {
        Vertex{ {-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f} },
        Vertex{ { 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f} },
        Vertex{ { 0.0f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f} },
    };
}
```

Pravidlo kreslení: vrcholy po trojicích, obličej je vidět z fronty (counter-clockwise).

---

### 2. Vytvořit buffer — `OpenGLSceneRenderer::init()`

```cpp
MeshBuffer* mojBuffer = new MeshBuffer(buildMojeGeometrieVertices());
m_buffers.push_back(mojBuffer);   // renderer si ho bude spravovat
```

Jeden buffer lze sdílet mezi více objekty (stejná geometrie, různé transformace).

---

### 3. Vytvořit objekt a nastavit transformaci

```cpp
// Statický objekt (bez animace)
auto* obj = new MeshObject(m_shader, mojBuffer);
obj->transform.position = {0.0f, 0.0f, -2.0f};
obj->transform.rotation = {0.0f, 45.0f, 0.0f};  // stupně (X, Y, Z)
obj->transform.scale    = {1.0f, 1.0f, 1.0f};
obj->setDrawMode(GL_TRIANGLES);   // nebo GL_LINE_STRIP, GL_POINTS, …
m_objects.push_back(obj);

// Animovaný objekt
auto* obj = new AnimatedMeshObject(m_shader, mojBuffer);
obj->transform.position = {0.0f, 0.0f, -2.0f};
// … bindování viz sekce Animace
m_objects.push_back(obj);
```

---

### 4. Přidat animační kanál (pokud je potřeba nová animace)

Každý kanál prochází čtyřmi místy:

| Místo | Soubor |
|---|---|
| `qreal m_novyKanal` — privátní člen | `OpenGLScene.h` (obě třídy) |
| `Q_PROPERTY` + getter + setter + signal | `OpenGLScene.h` (třída `OpenGLScene`) |
| `setNovyKanal()` implementace | `OpenGLScene.cpp` |
| `m_renderer->setNovyKanal(m_novyKanal)` v `sync()` | `OpenGLScene.cpp` |

Šablona pro `OpenGLScene.h`:
```cpp
// --- přidat do Q_PROPERTY bloku ---
Q_PROPERTY(qreal novyKanal READ novyKanal WRITE setNovyKanal NOTIFY novyKanalChanged)

// --- přidat getter ---
qreal novyKanal() const { return m_novyKanal; }

// --- přidat setter deklaraci ---
void setNovyKanal(qreal t);

// --- přidat signal ---
void novyKanalChanged();

// --- přidat privátní člen ---
qreal m_novyKanal = 0;
```

Šablona pro `OpenGLScene.cpp`:
```cpp
// setter
void OpenGLScene::setNovyKanal(qreal t) {
    if (m_novyKanal == t) return;
    m_novyKanal = t;
    emit novyKanalChanged();
    if (window()) window()->update();
}

// do sync():
m_renderer->setNovyKanal(m_novyKanal);
```

Do rendereru přidat setter a člen stejným vzorem jako ostatní kanály.

---

### 5. Navázat kanál na objekt — `bindXxx()`

```cpp
obj->bindRotationY(&m_obj0Animation);          // rotace kolem Y
obj->bindRotationX(&m_obj0RotX);               // rotace kolem X
obj->bindRotationZ(&m_obj0RotZ);               // rotace kolem Z
obj->bindTranslationX(&m_objMoveX, -4.5f);     // pohyb X, výchozí X = -4.5
obj->bindTranslationY(&m_objMoveY, 0.0f);      // pohyb Y
obj->bindTranslationZ(&m_objMoveZ, -2.0f);     // pohyb Z
obj->bindScaleUniform(&m_objScale, 1.0f);      // uniform scale (X=Y=Z)
obj->bindScaleX(&m_sx, 1.0f);                  // scale jen v ose X
obj->bindScaleY(&m_sy, 1.0f);
obj->bindScaleZ(&m_sz, 1.0f);
```

`base` (druhý parametr) je výchozí hodnota; kanál se k ní přičítá.

---

### 6. Přidat QML animaci — `qml/main.qml`

```qml
OpenGLScene {
    id: openglScene

    // Plynulá rotace 0 → 360 za 3 s, opakuje se
    SequentialAnimation on obj0Animation {
        loops: Animation.Infinite
        NumberAnimation { to: 360; duration: 3000; easing.type: Easing.Linear }
        NumberAnimation { to: 0;   duration: 0 }
    }

    // Pulzování scale: 1.0 → 1.35 → 0.8 → 1.0
    SequentialAnimation on objScale {
        loops: Animation.Infinite
        NumberAnimation { from: 0.0;   to: 0.35;  duration: 1200; easing.type: Easing.InOutSine }
        NumberAnimation { from: 0.35;  to: -0.20; duration: 1200; easing.type: Easing.InOutSine }
        NumberAnimation { from: -0.20; to: 0.0;   duration: 1200; easing.type: Easing.InOutSine }
    }

    // Lineární pohyb sem a tam
    SequentialAnimation on objMoveX {
        loops: Animation.Infinite
        NumberAnimation { from: -2.0; to: 2.0; duration: 2000; easing.type: Easing.InOutQuad }
        NumberAnimation { from: 2.0;  to: -2.0; duration: 2000; easing.type: Easing.InOutQuad }
    }
}
```

---

## Animace — přehled typů

### Rotace

```qml
// Nekonečná rotace kolem osy Y
SequentialAnimation on obj0Animation {
    loops: Animation.Infinite
    NumberAnimation { to: 360; duration: 3000; easing.type: Easing.Linear }
    NumberAnimation { to: 0;   duration: 0 }     // reset bez animace
}
```

C++ strana: `obj->bindRotationY(&m_obj0Animation)` — kanál se rovnou zapíše do `transform.rotation.y`.

---

### Pohyb (translace)

```qml
// Kyvadlo v ose X
SequentialAnimation on objMoveX {
    loops: Animation.Infinite
    NumberAnimation { from: -2.0; to: 2.0;  duration: 1500; easing.type: Easing.InOutSine }
    NumberAnimation { from: 2.0;  to: -2.0; duration: 1500; easing.type: Easing.InOutSine }
}
```

C++ strana: `obj->bindTranslationX(&m_objMoveX, baze)` — výsledná X pozice = `baze + hodnota_kanálu`.

---

### Škálování (scale)

```qml
// Pulzování (base = 1.0, kanál přidává offset)
SequentialAnimation on objScale {
    loops: Animation.Infinite
    NumberAnimation { from: 0.0; to: 0.5;  duration: 800; easing.type: Easing.InOutSine }
    NumberAnimation { from: 0.5; to: 0.0;  duration: 800; easing.type: Easing.InOutSine }
}
```

C++ strana: `obj->bindScaleUniform(&m_objScale, 1.0f)` — výsledek = `(1.0 + kanál)` ve všech osách.

---

### Kombinace více os

Jeden objekt může mít navázáno více kanálů najednou:

```cpp
obj->bindRotationX(&m_obj0RotX);       // vlastní kanál pro X
obj->bindRotationY(&m_obj0Animation);  // jiný kanál pro Y
obj->bindRotationZ(&m_obj0RotZ);       // jiný kanál pro Z
```

QML pak animuje každý kanál nezávisle (různé rychlosti, různé easing).

---

## Easing — nejčastější typy

| Typ | Chování |
|---|---|
| `Easing.Linear` | konstantní rychlost |
| `Easing.InOutSine` | plynulé zpomalení na krajích |
| `Easing.InOutQuad` | silnější zpomalení na krajích |
| `Easing.InOutElastic` | odskočení za cíl |
| `Easing.InOutBounce` | odraz od cíle |

---

## Kamera

Preset se přepíná přes `cameraView` (int):

| Hodnota | Pozice kamery |
|---|---|
| `0` (výchozí) | šikmý pohled z pravého horního rohu |
| `1` | pohled zepředu |
| `2` | pohled z pravého boku |
| `3` | pohled shora (bird's eye) |

Zoom: `cameraZoom` — rozsah `0.4` (přiblíženo) až `3.0` (oddáleno), výchozí `1.0`.

---

## Struktury dat

### `Vertex` (`src/data/Vertex.h`)

```cpp
struct Vertex {
    GLfloat position[3];  // x, y, z
    GLfloat color[3];     // r, g, b  (0.0 – 1.0)
};
```

### `Transform` (`src/data/Transform.h`)

```cpp
struct Transform {
    QVector3D position = {0, 0, 0};    // světová pozice
    QVector3D rotation = {0, 0, 0};    // Eulerovy úhly ve stupních
    QVector3D scale    = {1, 1, 1};    // měřítko
};
```

Pořadí aplikace v `toMatrix()`: `translate → rotateX → rotateY → rotateZ → scale`.

---

## Draw módy (`setDrawMode`)

| Mód | Popis |
|---|---|
| `GL_TRIANGLES` | každé 3 vrcholy = jeden trojúhelník (výchozí) |
| `GL_LINE_STRIP` | vrcholy spojené čárou |
| `GL_LINE_LOOP` | čára uzavřená zpět na první vrchol |
| `GL_POINTS` | každý vrchol jako bod |
| `GL_TRIANGLE_STRIP` | pás trojúhelníků (úspornější paměť) |

---

## Shadery (`shaders/`)

**Vertex shader** (`shader.vert`): přijme `posAttr` a `colAttr`, předá barvu do `col`, vypočte `gl_Position = matrix * posAttr`.

**Fragment shader** (`shader.frag`): interpolovanou `col` zapíše do `gl_FragColor`.

Matice `matrix` je MVP = `Projection × View × Model` — sestavuje se v `MeshObject::draw()`.

---

## Soubory — mapa projektu

```
src/
  main.cpp                        — vstupní bod, nastaví OpenGL backend, spustí QML
  core/
    GameObject.h/.cpp             — základní třída: shader, buffer, transform, drawMode
    MeshObject.h/.cpp             — implementuje draw() (bind shader, atributy, glDrawArrays)
    AnimatedMeshObject.h/.cpp     — přidává bindXxx() a syncAnimations()
    MeshBuffer.h/.cpp             — vytvoří VBO z vektoru Vertex
    VertexBuffer.h/.cpp           — obaluje QOpenGLBuffer
  data/
    Vertex.h                      — struct Vertex {position[3], color[3]}
    Transform.h                   — struct Transform {position, rotation, scale, toMatrix()}
  graphics/
    OpenGLScene.h/.cpp            — QQuickItem (UI thread) + OpenGLSceneRenderer (render thread)
    ShaderProgram.h/.cpp          — načte a zkompiluje GLSL shadery
    openglwidget.h/.cpp           — pomocný widget (nepoužívá se v hlavní scéně)
  objects/
    SceneObjects.h/.cpp           — buildXxxVertices() — zde se definuje geometrie

qml/
  main.qml                        — QML strom, animace, UI překryv

shaders/
  shader.vert                     — vertex shader (MVP transformace)
  shader.frag                     — fragment shader (předá barvu)
```
