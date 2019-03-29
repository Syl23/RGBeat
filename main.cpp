#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "niveau.h"
#include <string>
#include <math.h>

using namespace std;

#define NBP 2   //nombre de joueurs
#define NBB 100  //nombres de boules par joueur
#define COO 2   //nombre de coordonées : 2 si tout va bi1

#define COL1 500   //abcisses des collones
#define COL2 807
#define COL3 1113
#define COL4 1420

#define TOP 700

#define BOULESRAD 30 // rayon des boulles
#define FPS 60
#define SPEED 10

#define LVL u
#define MUSIQUE "bien.wav"







void affTab(float boules[NBP][NBB][COO]){

	cout<<"{"<<endl;
	for (int x = 0; x < NBP; x++){
		cout<<"{";

		for (int y = 0; y < NBB; y++){
			cout<<"{";

			for(int z = 0; z < COO; z++){

				cout<<boules[x][y][z]<<" ";
			}
			cout<<"}";
		}
		cout<<"}"<<endl;
	}
	cout<<"}"<<endl;
}

void resetBoules(float boules[NBP][NBB][COO]){


	// initialisation des COOs a -1 ou reset
	for (int x = 0; x < NBP; x++)
	for (int y = 0; y < NBB; y++)
	for(int z = 0; z < COO; z++)
	boules[x][y][z] = -1;
	//

}

void graphicUpdate(float boules[NBP][NBB][COO],sf::RenderWindow screen,sf::CircleShape rond){

    for (int x = 0; x < NBP; x++)
	for (int y = 0; y < NBB; y++)
	for (int z = 0; z < COO; z++){

        if (boules[x][y][0] != -1){



            if(y==0)
            rond.setFillColor(sf::Color(0, 0, 255, 150));
            else
            rond.setFillColor(sf::Color(255, 0, 0, 150));

            rond.setPosition(boules[x][y][0],boules[x][y][1]);
            screen.draw(rond);
        }
	}
}

void updatePoses(float boules[NBP][NBB][COO], float speed,int *score){

    for (int x = 0; x < NBP; x++){
        for (int y = 0; y < NBB; y++){
            if (boules[x][y][0]!=-1){
                boules[x][y][1]=boules[x][y][1]+speed;
            }
            if (boules[x][y][1]>1080){
                boules[x][y][0]=-1;
                boules[x][y][1]=-1;
                *score -=5;
            }
        }
    }

}

void updateBoulesLevel(float boules[NBP][NBB][COO],int time,int *index,int niveau[][3],int tailleNiveau){

    int i = *index;



    while(i<tailleNiveau && niveau[i][0] <= time+1200*(TOP/(FPS*SPEED))){

        int freeBoule = 0;

        while(boules[niveau[i][2]-1] [freeBoule][0] != -1 && freeBoule<tailleNiveau) freeBoule++;


        if(niveau[i][1] == 1)
        boules[niveau[i][2]-1][freeBoule][0] = COL1-BOULESRAD;

        if(niveau[i][1] == 2)
        boules[niveau[i][2]-1][freeBoule][0] = COL2-BOULESRAD;

        if(niveau[i][1] == 3)
        boules[niveau[i][2]-1][freeBoule][0] = COL3-BOULESRAD;

        if(niveau[i][1] == 4)
        boules[niveau[i][2]-1][freeBoule][0] = COL4-BOULESRAD;


        boules[niveau[i][2]-1][freeBoule][1] = 0;


        i++;
    }

    *index = i;






}

void animate(sf::RenderWindow &window, int col, int x, int y, bool *animation) {
    *animation = true;
}

void drawCross(sf::RenderWindow &window, int x, int y) {

}

void clickBoule(int ymin, int ymax, int player, int x, float tab[NBP][NBB][COO], sf::RenderWindow &window, bool *animation,int *score) {
    for (int i = 0; i < NBB; i++) {
        if (x > tab[player][i][0]-BOULESRAD-5 && x < tab[player][i][0]+BOULESRAD+5) {
            if (tab[player][i][1] > ymin-BOULESRAD && tab[player][i][1] < ymax-BOULESRAD) {
                tab[player][i][0] = -1;
                tab[player][i][1] = -1;
                *score +=1;
                animate(window, COL1, 2, 2, animation);
            } else if ((tab[player][i][1] < ymin-BOULESRAD-15 && tab[player][i][1] > ymin-BOULESRAD-35) || (tab[player][i][1] > ymax-BOULESRAD+15 && tab[player][i][1] < ymax-BOULESRAD+35)) {
                tab[player][i][0] = -1;
                tab[player][i][1] = -1;
                //drawCross();
                //cout<<"error";
                *score -=2;
            }
        }
    }
}


int main()
{
    int score = 0;
    int len = 0;


    //int niveau[][3] = u;

    int time=0;
    int index =0;

    bool animating = false;

    std::vector<sf::CircleShape> shapes(8);


    // Create the main window
    sf::ContextSettings settings;
    //settings.antialiasingLevel = 8;
    sf::RenderWindow app(sf::VideoMode(1920, 1080), "SFML shapes", sf::Style::Fullscreen, settings);

    app.setFramerateLimit(FPS);

	// Start the game loop

	float boules[NBP][NBB][COO];
    resetBoules(boules);


    const string titre = MUSIQUE;

    sf::Music music;

    if (!music.openFromFile(titre))
        return -1;


    music.play();
    len = music.getDuration().asMilliseconds();
    //cout<<len<<endl;

    sf::Clock clock;



    while (app.isOpen())
    {
        // Process events

        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }
    //touche pas trop ce qu'il y a avant ça stp

    time = clock.getElapsedTime().asMilliseconds();

    // Joueur 1



    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) clickBoule(TOP, 1000, 0, COL1, boules, app, &animating,&score);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) clickBoule(TOP, 1000, 0, COL2, boules, app, &animating,&score);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) clickBoule(TOP, 1000, 0, COL3, boules, app, &animating,&score);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) clickBoule(TOP, 1000, 0, COL4, boules, app, &animating,&score);

    // Joueur 2

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U)) clickBoule(TOP, 1000, 1, COL1, boules, app, &animating,&score);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) clickBoule(TOP, 1000, 1, COL2, boules, app, &animating,&score);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) clickBoule(TOP, 1000, 1, COL3, boules, app, &animating,&score);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) clickBoule(TOP, 1000, 1, COL4, boules, app, &animating,&score);





    sf::CircleShape shape(BOULESRAD);
    app.clear(sf::Color(50, 50, 50));


    updateBoulesLevel(boules,time,&index,LVL,sizeof(LVL)/12);
    //updateBoulesLevel(boules,time,&index,niveau,sizeof(niveau)/3);
    updatePoses(boules,SPEED,&score);



    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(COL1, 0)),
        sf::Vertex(sf::Vector2f(COL1, 1080)),
        sf::Vertex(sf::Vector2f(COL2, 0)),
        sf::Vertex(sf::Vector2f(COL2, 1080)),
        sf::Vertex(sf::Vector2f(COL3, 0)),
        sf::Vertex(sf::Vector2f(COL3, 1080)),
        sf::Vertex(sf::Vector2f(COL4, 0)),
        sf::Vertex(sf::Vector2f(COL4, 1080))
    };


    app.draw(line, 8, sf::Lines);

    sf::Vertex fond[] =
    {
        sf::Vertex(sf::Vector2f(COL1-BOULESRAD-15, TOP-5)),
        sf::Vertex(sf::Vector2f(COL1+BOULESRAD+15, TOP-5)),
        sf::Vertex(sf::Vector2f(COL1+BOULESRAD+15, TOP+2*BOULESRAD+25)),            // Rectangle 1
        sf::Vertex(sf::Vector2f(COL1-BOULESRAD-15, TOP+2*BOULESRAD+25)),

        sf::Vertex(sf::Vector2f(COL2-BOULESRAD-15, TOP-5)),
        sf::Vertex(sf::Vector2f(COL2+BOULESRAD+15, TOP-5)),
        sf::Vertex(sf::Vector2f(COL2+BOULESRAD+15, TOP+2*BOULESRAD+25)),            // Rectangle 2
        sf::Vertex(sf::Vector2f(COL2-BOULESRAD-15, TOP+2*BOULESRAD+25)),

        sf::Vertex(sf::Vector2f(COL3-BOULESRAD-15, TOP-5)),
        sf::Vertex(sf::Vector2f(COL3+BOULESRAD+15, TOP-5)),
        sf::Vertex(sf::Vector2f(COL3+BOULESRAD+15, TOP+2*BOULESRAD+25)),            // Rectangle 3
        sf::Vertex(sf::Vector2f(COL3-BOULESRAD-15, TOP+2*BOULESRAD+25)),

        sf::Vertex(sf::Vector2f(COL4-BOULESRAD-15, TOP-5)),
        sf::Vertex(sf::Vector2f(COL4+BOULESRAD+15, TOP-5)),
        sf::Vertex(sf::Vector2f(COL4+BOULESRAD+15, TOP+2*BOULESRAD+25)),            // Rectangle 4
        sf::Vertex(sf::Vector2f(COL4-BOULESRAD-15, TOP+2*BOULESRAD+25))
    };

    for (int i = 0; i < 16; i++) {
        fond[i].color = sf::Color(0, 0, 0);
    }

    app.draw(fond, 16, sf::Quads);





    for (int x = 0; x < NBP; x++)
	for (int y = 0; y < NBB; y++)
	for (int z = 0; z < COO; z++)
    {

        if (boules[x][y][0] != -1){
            if(x==0)
            shape.setFillColor(sf::Color(0, 0, 255));
            else
            shape.setFillColor(sf::Color(255, 0, 0, 80));

            shape.setPosition(boules[x][y][0],boules[x][y][1]);
            app.draw(shape);
        }
    }

    sf::Vertex vitre[] =
    {
        sf::Vertex(sf::Vector2f(COL1-BOULESRAD-10, TOP)),
        sf::Vertex(sf::Vector2f(COL1+BOULESRAD+10, TOP)),
        sf::Vertex(sf::Vector2f(COL1+BOULESRAD+10, TOP+2*BOULESRAD+20)),            // Rectangle 1
        sf::Vertex(sf::Vector2f(COL1-BOULESRAD-10, TOP+2*BOULESRAD+20)),

        sf::Vertex(sf::Vector2f(COL2-BOULESRAD-10, TOP)),
        sf::Vertex(sf::Vector2f(COL2+BOULESRAD+10, TOP)),
        sf::Vertex(sf::Vector2f(COL2+BOULESRAD+10, TOP+2*BOULESRAD+20)),            // Rectangle 2
        sf::Vertex(sf::Vector2f(COL2-BOULESRAD-10, TOP+2*BOULESRAD+20)),

        sf::Vertex(sf::Vector2f(COL3-BOULESRAD-10, TOP)),
        sf::Vertex(sf::Vector2f(COL3+BOULESRAD+10, TOP)),
        sf::Vertex(sf::Vector2f(COL3+BOULESRAD+10, TOP+2*BOULESRAD+20)),            // Rectangle 3
        sf::Vertex(sf::Vector2f(COL3-BOULESRAD-10, TOP+2*BOULESRAD+20)),

        sf::Vertex(sf::Vector2f(COL4-BOULESRAD-10, TOP)),
        sf::Vertex(sf::Vector2f(COL4+BOULESRAD+10, TOP)),
        sf::Vertex(sf::Vector2f(COL4+BOULESRAD+10, TOP+2*BOULESRAD+20)),            // Rectangle 4
        sf::Vertex(sf::Vector2f(COL4-BOULESRAD-10, TOP+2*BOULESRAD+20))
    };


    for (int i = 0; i < 16; i+=2) {
        vitre[i].color = sf::Color(0, 0, 200, 100);
        vitre[i+1].color = sf::Color(150, 150, 200, 150);
    }

    app.draw(vitre, 16, sf::Quads);



    if (animating) {
        shapes[0].setFillColor(sf::Color(255, 255, 255));
        shapes[0].setPosition(15, 15);
        shapes[0].setRadius(BOULESRAD);
        app.draw(shapes[0]);
    }

    sf::Font font;
    font.loadFromFile("arial.ttf");
    // Create a text
    sf::Text text(std::to_string(score), font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);
    // Draw it
    app.draw(text);





    if(0<time){


        app.clear(sf::Color(10*2, 10*2, 10*2));
            // Declare and load a font
        sf::Font font;
        font.loadFromFile("/auto_home/sleclerc/Documents/RGBeat/RGBeat/FONTS/traveling_typewriter/TravelingTypewriter.ttf");
        // Create a text
        sf::Text text("Ton score : "+std::to_string(score), font);
        text.setCharacterSize(100);
        text.setFillColor(sf::Color::White);
        text.setPosition(1920/2-int(log10(abs(score)))*50-12*25,1080/2-150-100);
        app.draw(text);

        text.setString("Le score max est : "+std::to_string(sizeof(u)/12));
        text.setCharacterSize(100);
        text.setFillColor(sf::Color::White);
        text.setPosition(1920/2-23*25,1080/2-100);
        app.draw(text);

        text.setString("Le score min est : -"+std::to_string((sizeof(u)/12)*5));
        text.setCharacterSize(100);
        text.setFillColor(sf::Color::White);
        text.setPosition(1920/2-23*25,1080/2+100-100);
        app.draw(text);

        text.setString("R");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Red);
        text.setPosition(0,0);
        app.draw(text);

        text.setString("G");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Green);
        text.setPosition(30,0);
        app.draw(text);

        text.setString("B");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Blue);
        text.setPosition(60,0);
        app.draw(text);

        text.setString("eat");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color(255,0,255));
        text.setPosition(90,0);
        app.draw(text);

        text.setString("Merci Kellian et Sylvain");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color(255,255,0));
        text.setPosition(10,1080-75);
        app.draw(text);

        text.setString("Developed by Kellian et Sylvain using SFML and no fucking ide");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color(255,255,0));
        text.setPosition(10,1080-75-50);
        app.draw(text);




    }







        // Update the window
    app.display();
    }

    return EXIT_SUCCESS;
}
