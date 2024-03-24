#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <nlohmann/json.hpp>

#include "GameObject.h"
#include "Scene.h"
#include "TileMap.h"
#include "Mapcollider.h"


int main()
{
    srand(time(NULL));
    Scene scene;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Ecospace");
    sf::View view;
    Maths::Vector2<float> Camera;

    GameObject* player = scene.PlayerAsset("Player", 160.f, 160.f);
    Camera = player->GetPosition();

    scene.Plante("Plante", 160.f, 160.f, 0, true);
    scene.Plante("Plante", 176.f, 160.f, 6, true);
    scene.Plante("Plante", 192.f, 160.f, 12, true);
    scene.Plante("Plante", 208.f, 160.f, 18, true);
    scene.Plante("Plante", 224.f, 160.f, 24, true);
    scene.Plante("Plante", 240.f, 160.f, 30, true);
    scene.Plante("Plante", 256.f, 160.f, 36, true);
    scene.Plante("Plante", 272.f, 160.f, 42, true);
    scene.Plante("Plante", 288.f, 160.f, 48, true);

    scene.Creature("Creature", 160.f, 176.f, 0, true);
    scene.Creature("Creature", 192.f, 208.f, 1, true);

    scene.CreateMenuPlante("MenuPlante", &window, &Camera, &view);
    scene.CreateMenuSave("MenuSave", &window, &Camera, &view);
    scene.CreateJournal("Journal", &window, &Camera, &view);
    window.setFramerateLimit(240);

    sf::Clock clock;

    // ------------------------------------------------------------------------------------- MAP ------------------------------------------------------------------------------------------------------
    TileMap tileMap;
    tileMap.loadmap("MAP");

    // ----------------------------------------------------------------------------------- MUSIQUE ---------------------------------------------------------------------------------------------------
    sf::Music music;
    if (!music.openFromFile("assets/sound/music.ogg"))
    {
        std::cout << "Couldnt load music." << std::endl;
    }
    music.play();
    
    

    // ------------------------------------------------------------------------------------- BOUCLE ------------------------------------------------------------------------------------------------------

    while (window.isOpen())
    {
        sf::Time start = clock.restart();
        float deltaTime = start.asSeconds();

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // ------------------------------------------------------------------------------- CAMERA ----------------------------------------------------------------------------------------------------
        view.setSize(240, 135);
        Camera = player->GetPosition();
        Camera.x += 12;
        Camera.y += 12;
        if (Camera.x < 120)
        {
            Camera.x = 120;
        }
        if (Camera.x > 360)
        {
            Camera.x = 360;
        }
        if (Camera.y < 67.5)
        {
            Camera.y = 67.5;
        }
        if (Camera.y > 252.5)
        {
            Camera.y = 252.5;
        }
        view.setCenter(Camera.x, Camera.y);
        window.setView(view);

        // ------------------------------------------------------------------------------- DRAW ----------------------------------------------------------------------------------------------------
        scene.Update(deltaTime, event);
        window.clear(sf::Color::Black);
        window.draw(tileMap);
        scene.Render(&window);
        window.display();
    }


    return 0;
}