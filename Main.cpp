#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
using namespace sf;
using namespace std;

//tamano de pantalla
int puntaje = 0;
int N = 30, M = 20;
int Tamano = 25;
int pos = 150;
//Tamano 
int w = Tamano * N;
int h = Tamano * M;
bool arriba=true, abajo=true, derecha=true, izquierda=true;

int dir, num = 4;

//snake
struct Snake
{
	int x, y;
}  s[100];

//comida
struct Fruct
{
	int x, y;
} f;

struct Menu {
	int pos[255];
	int x;
	int y;

};
void moverserpiente()
{

	//Union de piezas del snake
	for (int i = num; i > 0; --i)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	// Lee teclas presionadas validacion
	if (dir == 0) {
		s[0].y += 1;
	}
	if (dir == 1) {
		s[0].x -= 1;
	}
	if (dir == 2) {
		s[0].x += 1;
	}
	if (dir == 3) {
		s[0].y -= 1;
	}

	//tamano de snake cuando come comida
	if ((s[0].x == f.x) && (s[0].y == f.y))
	{
		//Funcion random para Comida
		puntaje++;
		num++;
		f.x = rand() % N;
		f.y = rand() % M;
		cout << puntaje;
	}


	//Validacion entre paredes
	if (s[0].x > N) s[0].x = 0;  if (s[0].x < 0) s[0].x = N;
	if (s[0].y > M) s[0].y = 0;  if (s[0].y < 0) s[0].y = M;


	// validacion de piezas que se remueven al tocarse el mismo

}
bool death(void)
{
	for (int i = 1; i < num; i++)
	{
		if (s[0].x == s[i].x && s[0].y == s[i].y)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(w, h), "Snake");
	Texture t1, t2, t3, t4, t5, t6, t7, t8;
	t1.loadFromFile("C:\\Users\\Mauricio\\Desktop\\J1.PNG");
	t3.loadFromFile("C:\\Users\\Mauricio\\Desktop\\e1.PNG");
	t4.loadFromFile("C:\\Users\\Mauricio\\Desktop\\s1.PNG");
	t5.loadFromFile("C:\\Users\\Mauricio\\Desktop\\sn1.PNG");
	t6.loadFromFile("C:\\Users\\Mauricio\\Desktop\\f1.PNG");
	t7.loadFromFile("C:\\Users\\Mauricio\\Desktop\\c1.PNG");
	t2.loadFromFile("C:\\Users\\Mauricio\\source\\repos\\Sna\\images\\green.png");
	t8.loadFromFile("C:\\Users\\Mauricio\\Desktop\\g1.PNG");
	//carga imagenes al sprite
	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite sprite3(t3);
	Sprite sprite4(t4);
	Sprite sprite5(t5);
	Sprite sprite6(t6);
	Sprite sprite7(t7);
	Sprite sprite8(t8);
	Clock clock;
	float tiempo = 0, delay = 0.1;
	//posicion de comida
	f.x = 20;
	f.y = 10;
	//Ventana Abierta
		while (window.isOpen())
		{
			Event e;
			while (window.pollEvent(e))
			{
				if (e.type == Event::Closed)
					window.close();
				sprite1.setPosition(275, 150);
				sprite3.setPosition(270, 185);
				sprite4.setPosition(260, 230);
				sprite5.setPosition(250, 85);
				//sprite6.setPosition(200, pos);

				std::cout << pos << " ";
				window.draw(sprite5);
				window.draw(sprite3);
				window.draw(sprite4);
				window.draw(sprite1);
				window.display();
				window.clear();
				if (Keyboard::isKeyPressed(Keyboard::Down) && pos < 201) {
					pos += 50;
					sprite6.setPosition(200, pos);
					window.draw(sprite6);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Up) && pos > 150) {
					pos -= 50;
					sprite6.setPosition(200, pos);
					window.draw(sprite6);
				}
				if (Keyboard::isKeyPressed(Keyboard::Space) && pos == 150)
				{
					RenderWindow window2(VideoMode(w, h), "Snakee");
					window2.clear();
					window.clear();
					while (window2.isOpen())
					{
						float time = clock.getElapsedTime().asSeconds();
						clock.restart();
						tiempo += time;


						Event e;//Creacion de eventos
						Event o;

						while (window2.pollEvent(o))
						{
							if (o.type == Event::Closed)
								window2.close();
						}
						//Manejo de teclas.
						if (Keyboard::isKeyPressed(Keyboard::Left) && izquierda) {
							derecha = false;
							abajo = true;
							arriba = true;
							dir = 1;
						}
						if (Keyboard::isKeyPressed(Keyboard::Right) && derecha) {
							izquierda = false;
							abajo = true;
							arriba = true;
							dir = 2;
						}
						if (Keyboard::isKeyPressed(Keyboard::Up) && arriba) {
							izquierda = true;
							derecha = true;
							abajo = false;
							dir = 3;
						}
						if (Keyboard::isKeyPressed(Keyboard::Down) && abajo) {
							dir = 0;
							derecha = true;
							izquierda = true;
							arriba = false;
						}
						if (Keyboard::isKeyPressed(Keyboard::Enter))
						{
							system("pause");
						}
						

						//Andir movimiento
						if (tiempo > delay) {

							//movimiento snake
							tiempo = 0;
							// algoritmo de movimiento
							moverserpiente();

							if (death())
							{
								cout << "Moriste";
								exit(EXIT_SUCCESS);
							}
						}

						window2.clear();


						// Compilacion de juego 

						for (int i = 0; i < num; i++)
						{
							if (s[i].x != s[i].y)
							{

							}
							else {
								break;
							}
						}
						for (int i = 0; i < num; i++)
						{
							//Spawnear Serpiente
							sprite8.setPosition(s[0].x*Tamano, s[0].y*Tamano);
							
							sprite2.setPosition(s[i].x*Tamano, s[i].y*Tamano);
							window.draw(sprite8);
							window2.draw(sprite2);
						}
						//Spawnear la comida
						sprite2.setPosition(f.x*Tamano, f.y*Tamano);  window2.draw(sprite2);
						window2.display();
					}
					cout << "entre";
				}
				if (Keyboard::isKeyPressed(Keyboard::Space) && pos == 200)
				{
					cout << "entre2";
				}
				if (Keyboard::isKeyPressed(Keyboard::Space) && pos == 250)
				{
					exit(EXIT_SUCCESS);
				}
			}
		}
	}

	
