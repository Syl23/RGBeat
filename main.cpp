#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;

#define NBP 2   //nombre de joueurs
#define NBB 10  //nombres de boules par joueur
#define COO 2   //nombre de coordonées : 2 si tout va bi1

#define COL1 500   //abcisses des collones
#define COL2 807
#define COL3 1113
#define COL4 1420
#define TOP 700

#define BOULESRAD 20 // rayon des boulles
#define FPS 60
#define SPEED 1







/* nemo
le niveau est stocké dans un tableau, chaque boule est identifiée par un temps en millisecondes ou autre(moment ou elle doit etre faite cliquer)
pour mettre a jour les boules qui sont presentement afficher à l'écran on a un index qui corespond à la derniere boule qui a été affichée
on scan le tableau depuis l'index jusqu'a ce que le temps soit superieurs à l'index
dés qu'on trouve un temps superieur a l'index on met l'index a l'index de cette valeur et on arrete de parcourir le tableau

le joueur 1 est bleu
*/


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

void updatePoses(float boules[NBP][NBB][COO], float speed){

    for (int x = 0; x < NBP; x++)
	for (int y = 0; y < NBB; y++){


    if (boules[x][y][0]!=-1)
	boules[x][y][1]=boules[x][y][1]+speed;

	if (boules[x][y][1]>1080){
        boules[x][y][0]=-1;
        boules[x][y][1]=-1;
	}

	}

}

void updateBoulesLevel(float boules[NBP][NBB][COO],int time,int *index,int niveau[8][3],int tailleNiveau){

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

void clickBoule(int ymin, int ymax, int player, int x, float tab[NBP][NBB][COO], sf::RenderWindow &window, bool *animation) {
    for (int i = 0; i < NBB; i++) {
        if (x > tab[player][i][0]-BOULESRAD-5 && x < tab[player][i][0]+BOULESRAD+5) {
            if (tab[player][i][1] > ymin-BOULESRAD && tab[player][i][1] < ymax-BOULESRAD) {
                tab[player][i][0] = -1;
                tab[player][i][1] = -1;
                animate(window, COL1, 2, 2, animation);
            } else if ((tab[player][i][1] < ymin-BOULESRAD-15 && tab[player][i][1] > ymin-BOULESRAD-35) || (tab[player][i][1] > ymax-BOULESRAD+15 && tab[player][i][1] < ymax-BOULESRAD+35)) {
                tab[player][i][0] = -1;
                tab[player][i][1] = -1;
                //drawCross();
                cout<<"error";
            }
        }
    }
}


int main()
{


    int niveau[][3] = {{7089,1,1},{7556,4,1},{8055,3,1},{8521,2,2},{8755,2,2},{9039,2,1},{9240,2,2},{9471,2,2},{9722,2,2},{9955,4,1},{10222,4,2},{10490,4,2},{10738,1,1},{11138,2,2},{11389,2,2},{11656,2,1},{11756,2,2},{11872,2,1},{12106,1,2},{12306,1,2},{12522,2,1},{12640,2,2},{12722,2,1},{12856,2,2},{12973,2,1},{13089,2,2},{13423,4,2},{13706,4,2},{14306,1,1},{14522,1,1},{14590,2,1},{14673,3,1},{14706,4,1},{14956,2,2},{15206,2,2},{15474,1,1},{15507,2,1},{15558,3,1},{15641,4,1},{15990,1,1},{16023,2,1},{16124,3,1},{16124,4,1},{16390,1,1},{16440,2,1},{16490,3,1},{16573,4,1},{16723,2,2},{16907,2,2},{17056,2,2},{17323,3,1},{17557,3,1},{17791,3,1},{17957,4,1},{18024,1,1},{18140,3,1},{18140,2,1},{18240,4,1},{18689,2,2},{18941,2,2},{19241,1,1},{19323,2,1},{19357,3,1},{19474,4,1},{19690,2,2},{19940,2,2},{20207,1,1},{20274,2,1},{20291,3,1},{20374,4,1},{20623,2,2},{20889,2,2},{21141,1,1},{21191,2,1},{21257,3,1},{21358,4,1},{21624,2,2},{21874,2,2},{22091,1,1},{22141,2,1},{22141,3,1},{22241,4,1},{22525,1,2},{22759,1,2},{22974,1,1},{23024,2,1},{23091,3,1},{23141,4,1},{23558,4,2},{23708,4,2},{23875,4,2},{24041,4,2},{24174,4,2},{24441,3,2},{24708,3,2},{24925,2,1},{25009,1,1},{25042,3,1},{25092,4,1},{25725,2,2},{25891,2,2},{26059,2,2},{26209,2,2},{26808,1,1},{26892,2,1},{26992,3,1},{27043,4,1},{27341,1,2},{27525,1,2},{27709,1,2},{27942,1,2},{28058,1,2},{28242,1,2},{28592,1,1},{28643,2,1},{28759,3,1},{28759,4,1},{29559,2,2},{29726,2,2},{29892,2,2},{30060,2,2},{30743,1,1},{30809,2,1},{30910,3,1},{30960,4,1},{31159,3,2},{31358,3,2},{31509,3,2},{31643,1,1},{31693,2,1},{31792,3,1},{31843,4,1},{32176,2,2},{32443,2,2},{32711,2,2},{33443,1,1},{33494,2,1},{33527,3,1},{33711,4,1},{33926,3,2}}; // un niveau a la con pour tester

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


    const string titre = "yodel.ogg";

    sf::Music music;

    if (!music.openFromFile(titre))
        return -1;


    music.play();

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



    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) clickBoule(700, 1000, 0, COL1, boules, app, &animating);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) clickBoule(700, 1000, 0, COL2, boules, app, &animating);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) clickBoule(700, 1000, 0, COL3, boules, app, &animating);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) clickBoule(700, 1000, 0, COL4, boules, app, &animating);

    // Joueur 2

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U)) clickBoule(700, 1000, 1, COL1, boules, app, &animating);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) clickBoule(700, 1000, 1, COL2, boules, app, &animating);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) clickBoule(700, 1000, 1, COL3, boules, app, &animating);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) clickBoule(700, 1000, 1, COL4, boules, app, &animating);





    sf::CircleShape shape(BOULESRAD);
    app.clear(sf::Color(50, 50, 50));


    updateBoulesLevel(boules,time,&index,niveau,8);
    updatePoses(boules,5);



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
            shape.setFillColor(sf::Color(0, 0, 255, 128));
            else
            shape.setFillColor(sf::Color(255, 0, 0, 128));

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




        // Update the window
    app.display();
    }

    return EXIT_SUCCESS;
}
