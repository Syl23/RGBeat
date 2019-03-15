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

#define BOULESRAD 20 // rayon des boulles
#define FPS 60
#define SPEED 1



struct NivBoul{
    int clicTime;
    int col;
    int joueur;
};




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
            rond.setFillColor(sf::Color(0, 0, 255));
            else
            rond.setFillColor(sf::Color(255, 0, 0));

            rond.setPosition(boules[x][y][0],boules[x][y][1]);
            screen.draw(rond);
        }
	}
}

void updatePoses(float boules[NBP][NBB][COO], float speed){

    for (int x = 0; x < NBP; x++)
	for (int y = 0; y < NBB; y++){


    if (boules[x][y][1]!=-1)
	boules[x][y][1]=boules[x][y][1]+speed;

	if (boules[x][y][1]>1080)
	boules[x][y][0]=-1;
	boules[x][y][1]=-1;

	}

}

void updateBoulesLevel(float boules[NBP][NBB][COO],int time,int *index,NivBoul niveau[]){

    int i = *index;


    while(i<sizeof(niveau) && niveau[i].clicTime <= time+(1080/(FPS*SPEED/1000))){

        int freeBoule = 0;

        while(boules[niveau[i].joueur-1][freeBoule][0] != -1) freeBoule++;


        if(niveau[i].col == 1);
        boules[niveau[i].joueur-1][freeBoule][0] = COL1;

        if(niveau[i].col == 2);
        boules[niveau[i].joueur-1][freeBoule][0] = COL2;

        if(niveau[i].col == 3);
        boules[niveau[i].joueur-1][freeBoule][0] = COL3;

        if(niveau[i].col == 4);
        boules[niveau[i].joueur-1][freeBoule][0] = COL4;




        boules[niveau[i].joueur-1][freeBoule][1] = 0;



        i++;
    }

    *index = i;






}

void clickBoule(int ymin, int ymax, int player, int x, float tab[NBP][NBB][COO]) {
    for (int i = 0; i < sizeof(tab[player]); i++) {
        if (x > tab[player][i][0]-30 && x < tab[player][i][0]+30) {
            if (tab[player][i][1] > ymin && tab[player][i][1] < ymax) {
                tab[player][i][1] = 0;
            }
        }
    }
}






int main()
{


    NivBoul niveau[] = {{0,1,1},{500,2,1},{1000,3,1},{1500,4,1},{500,1,2},{1000,2,2},{1500,3,2},{2000,4,2}}; // un niveau a la con pour tester

    int time=0;
    int index =0;


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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) clickBoule(700, 1000, 0, COL1, boules);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) clickBoule(700, 1000, 0, COL2, boules);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) clickBoule(700, 1000, 0, COL3, boules);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) clickBoule(700, 1000, 0, COL4, boules);

    // Joueur 2

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U)) clickBoule(700, 1000, 1, COL1, boules);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) clickBoule(700, 1000, 1, COL2, boules);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) clickBoule(700, 1000, 1, COL3, boules);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) clickBoule(700, 1000, 1, COL4, boules);



















    sf::CircleShape shape(BOULESRAD);
    app.clear(sf::Color::Black);


    updateBoulesLevel(boules,time,&index,niveau); // le core dupde viens de la
    updatePoses(boules,1);



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




    for (int x = 0; x < NBP; x++)
	for (int y = 0; y < NBB; y++)
	for (int z = 0; z < COO; z++)
    {

        if (boules[x][y][0] != -1){
            if(x==0)
            shape.setFillColor(sf::Color(0, 0, 255));
            else
            shape.setFillColor(sf::Color(255, 0, 0));

            shape.setPosition(boules[x][y][0],boules[x][y][1]);
            app.draw(shape);
        }
    }






        // Update the window
    app.display();
    }

    return EXIT_SUCCESS;
}
