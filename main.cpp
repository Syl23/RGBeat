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
	for (int y = 0; y < NBB; y++)
    if (boules[x][y][1]!=-1)
	boules[x][y][1]=boules[x][y][1]+speed;

}

int main()
{
    // Create the main window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow app(sf::VideoMode(800, 1000), "SFML shapes", sf::Style::Fullscreen, settings);

	// Start the game loop

	float boules[NBP][NBB][COO];
    resetBoules(boules);

    boules[0][0][0] = COL1-BOULESRAD;
    boules[0][0][1] = 0;

    boules[0][1][0] = COL2-BOULESRAD;
    boules[0][1][1] = 0;

    boules[1][0][0] = COL3-BOULESRAD;
    boules[1][0][1] = 0;

    boules[1][1][0] = COL4-BOULESRAD;
    boules[1][1][1] = 0;

    const string titre = "yodel.ogg";

    sf::Music music;

    if (!music.openFromFile(titre))
        return -1;

    music.play();





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











    sf::CircleShape shape(BOULESRAD);
    app.clear(sf::Color::Black);



    updatePoses(boules,0.1);






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
