# Plán: Transformace, Composite a zjednodušení kódu

Stav: odsouhlaseno, neimplementováno. Budeme dělat postupně.

## Rozhodnutí

- `Transformation` = abstraktní rodičovská třída; potomci `Translation`, `RotationY`, `RotationPlaneXY`, `Scale`, `CompositeTransformation`.
- `DrawableObject` vlastní transformace přes `std::unique_ptr` (nesdílí se, žádné `shared_ptr`).
- Statická transformace = zdědí prázdný `update()`; dynamická `update()` přepíše a mění svou hodnotu podle `deltaTime`.
- Zachovat stávající formuli `T · Rxy · Ry · S` → pořadí listů v composite `[Translation, RotationPlaneXY, RotationY, Scale]`.
- Zjednodušit: pryč mapa v `ShaderProgram`, pryč `deque` ve `Scene`, pryč `draw2()` a staré uniformy.
- Zrušit hromadné metody ve `Scene`.
- Zrušit veškeré ovládání klávesami (W/A/S/D, Q/E, Z/C, R/F).

## Koncepty (procvičit)

- **Dědičnost**: potomek přebírá členy rodiče, může přepisovat (`override`).
- **Virtuální / čistě virtuální funkce**: `virtual ... = 0` → abstraktní třída, nelze instancovat.
- **Virtuální destruktor**: nutný, protože přes `unique_ptr<Transformation>` se mažou potomci.
- **Polymorfismus**: volání `getMatrix()` na `Transformation*` vybere verzi podle skutečného typu objektu.
- **Composite**: `CompositeTransformation` je sám `Transformation`, ale drží seznam dalších transformací → kombinace je „jedna transformace" a lze vnořovat.
- **Statické vs dynamické**: statická zdědí prázdný `update()`, dynamická ho přepíše (např. přičte `angularSpeed_ * dt`).

## Pořadí násobení (zachovat formuli)

```
M = I * T = T
M = T * Rxy
M = T * Rxy * Ry
M = T * Rxy * Ry * S
```

## `Transformation.h/.cpp`

- Abstraktní `Transformation`:
  - `virtual ~Transformation() = default;`
  - `virtual glm::mat4 getMatrix() const = 0;`
  - `virtual void update(float deltaTime) {}`
  - `virtual bool isDynamic() const { return false; }`
- Listy `Translation`, `RotationY`, `RotationPlaneXY`, `Scale` – každý drží svůj parametr a vrací jednu matici (`glm::translate` / `glm::rotate` / `glm::scale`).
- `RotationY` / `RotationPlaneXY`: `angle_` + `angularSpeed_`; `update` přičte `angularSpeed_ * dt`.
- `CompositeTransformation`: `std::vector<std::unique_ptr<Transformation>>`; `getMatrix()` násobí v pořadí, `update()` propaguje na potomky.
- Výchozí úhly `180°` / `30°` přesunout do defaultů `RotationY` / `RotationPlaneXY`.
- Odstranit nevyužitý člen `M`.

## `DrawableObject.h/.cpp`

- `std::unique_ptr<CompositeTransformation> transformations_;`
- Konstruktor sestaví `[Translation, RotationPlaneXY, RotationY, Scale]` z `offset` / `scale` → stejné chování jako teď.
- `void addTransformation(std::unique_ptr<Transformation>)`, `void setTransformation(std::unique_ptr<Transformation>)`.
- `glm::mat4 getModelMatrix() const` = `transformations_->getMatrix()`.
- `void update(float dt)` = `transformations_->update(dt)` (bez hardcode).
- `draw()` posílá `modelMatrix` + `fragmentColor`.
- Smazat `draw2()`.

## `Scene.h/.cpp`

- `std::deque<ShaderProgram>` → `std::vector<ShaderProgram>` s `programs_.reserve(8);` (aby ukazatele v objektech zůstaly platné při `push_back`).
- Smazat `translateAll` / `rotateYAll` / `rotatePlaneXYAll` / `scaleAll`.
- `addDrawableObject` vracet `DrawableObject&` (aby šlo v `createScenes` přidat dynamickou transformaci).

## `ShaderProgram.h/.cpp`

- Smazat `uniformLocations_` mapu a pomocnou `uniformLocation()`.
- Smazat includes `<unordered_map>` a `<string>`.
- `setUniform` přímo: `glGetUniformLocation(id_, name)` + `glUniform...`.

## `Application.cpp`

- Zapnout `scene.update(deltaTime);`.
- `processInput`: ponechat jen ESC a přepínání scén 1–9; zbytek (W/A/S/D, Q/E, Z/C, R/F) smazat.
- `createScenes`: přes vrácenou referenci ukázkově přidat dynamickou rotaci.

## Shadery

- Převést `basic3.vert`, `basic2.vert`, `login.vert` na:
  - `uniform mat4 modelMatrix;`
  - `gl_Position = modelMatrix * vec4(position, 1.0);`
- `basic.vert` je už hotový.
- Fragment shadery beze změny.

## Dopad na chování

- Zrušením hromadných metod zmizí i ovládání klávesami; pohyb vzniká jen z dynamických transformací objektů (aktualizovaných každý snímek přes `scene.update`).
- Ovládání klávesami se již nevrací.
