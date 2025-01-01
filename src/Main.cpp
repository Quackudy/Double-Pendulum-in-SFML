#include <SFML/Graphics.hpp>

class pendulum {
private:

    double strength;
    double mass1{ 1 };
    double mass2{ 1 };
    double accel1{ 0 };
    double accel2{ 0 };
    double vel1{ 0 };
    double vel2{ 0 };
    double pos1;
    double pos2;
    sf::Vector2f posXY1;
    sf::Vector2f posXY2;
    double length1;
    double length2;
    double normalize;
    sf::Vector2f origin;

    sf::CircleShape m1;
    sf::CircleShape m2;
    sf::CircleShape originm;
    sf::Vertex line1[2];
    sf::Vertex line2[2];
    sf::Vector2f center;

public:
    pendulum(double str, double posf, double poss, double len1, double len2, float ori1, float ori2)
        : strength(str), pos1(posf), pos2(poss), length1(len1), length2(len2) {
        origin = { ori1, ori2 };
        mass1 = 10; // Assign mass values
        mass2 = 10;
        normalize = 2 * mass1 + mass2 - mass2 * cos(2 * pos1 - 2 * pos2);
        center = { 20, 20 };

        update();

        m1.setPosition(posXY1);
        m1.setFillColor(sf::Color::Black);
        m1.setRadius(20);

        m2.setPosition(posXY2);
        m2.setFillColor(sf::Color::Black);
        m2.setRadius(20);

        originm.setPosition(sf::Vector2f{ ori1, ori2 });
        originm.setFillColor(sf::Color::White);
        originm.setRadius(1);

        line1[0].position = origin;
        line1[0].color = sf::Color::Black;
        line1[1].position = posXY1 + center;
        line1[1].color = sf::Color::Black;

        line2[0].position = posXY1 + center;
        line2[0].color = sf::Color::Black;
        line2[1].position = posXY2 + center;
        line2[1].color = sf::Color::Black;
    }


    double accel1Cal() {
        double num1 = -strength * (2 * mass1 + mass2) * sin(pos1);
        double num2 = -mass2 * strength * sin(pos1 - 2 * pos2);
        double num3 = -2 * sin(pos1 - pos2) * mass2 * (vel2 * vel2 * length2 + vel1 * vel1 * length1 * cos(pos1 - pos2));
        double acc = (num1 + num2 + num3) / (length1 * normalize);
        return acc;
    }

    double accel2Cal() {
        double num1 = 2 * sin(pos1 - pos2);
        double num2 = (vel1 * vel1 * length1 * (mass1 + mass2));
        double num3 = strength * (mass1 + mass2) * cos(pos1);
        double num4 = vel2 * vel2 * length2 * mass2 * cos(pos1 - pos2);
        double acc = (num1 * (num2 + num3 + num4)) / (length2 * normalize);
        return acc;
    }

    void updateRK4() {
        double dt = 0.5;

        double k1_pos1, k2_pos1, k3_pos1, k4_pos1;
        double k1_pos2, k2_pos2, k3_pos2, k4_pos2;
        double k1_vel1, k2_vel1, k3_vel1, k4_vel1;
        double k1_vel2, k2_vel2, k3_vel2, k4_vel2;

        k1_vel1 = accel1Cal();
        k1_vel2 = accel2Cal();
        k1_pos1 = vel1;
        k1_pos2 = vel2;

        vel1 += 0.5 * dt * k1_vel1;
        vel2 += 0.5 * dt * k1_vel2;
        pos1 += 0.5 * dt * k1_pos1;
        pos2 += 0.5 * dt * k1_pos2;

        k2_vel1 = accel1Cal();
        k2_vel2 = accel2Cal();
        k2_pos1 = vel1;
        k2_pos2 = vel2;

        vel1 += 0.5 * dt * k2_vel1 - 0.5 * dt * k1_vel1;
        vel2 += 0.5 * dt * k2_vel2 - 0.5 * dt * k1_vel2;
        pos1 += 0.5 * dt * k2_pos1 - 0.5 * dt * k1_pos1;
        pos2 += 0.5 * dt * k2_pos2 - 0.5 * dt * k1_pos2;

        k3_vel1 = accel1Cal();
        k3_vel2 = accel2Cal();
        k3_pos1 = vel1;
        k3_pos2 = vel2;

        vel1 += dt * k3_vel1 - 0.5 * dt * k2_vel1;
        vel2 += dt * k3_vel2 - 0.5 * dt * k2_vel2;
        pos1 += dt * k3_pos1 - 0.5 * dt * k2_pos1;
        pos2 += dt * k3_pos2 - 0.5 * dt * k2_pos2;

        k4_vel1 = accel1Cal();
        k4_vel2 = accel2Cal();
        k4_pos1 = vel1;
        k4_pos2 = vel2;

        vel1 += dt / 6.0 * (k1_vel1 + 2 * k2_vel1 + 2 * k3_vel1 + k4_vel1);
        vel2 += dt / 6.0 * (k1_vel2 + 2 * k2_vel2 + 2 * k3_vel2 + k4_vel2);
        pos1 += dt / 6.0 * (k1_pos1 + 2 * k2_pos1 + 2 * k3_pos1 + k4_pos1);
        pos2 += dt / 6.0 * (k1_pos2 + 2 * k2_pos2 + 2 * k3_pos2 + k4_pos2);

    }


    void update() {
        posXY1.x = origin.x + length1 * sin(pos1);
        posXY1.y = origin.y + length1 * cos(pos1);
        posXY2.x = origin.x + length1 * sin(pos1) + length2 * sin(pos2);
        posXY2.y = origin.y + length1 * cos(pos1) + length2 * cos(pos2);
    }

    void render(sf::RenderWindow& wind) {
        m1.setPosition(posXY1);
        m2.setPosition(posXY2);

        line1[0].position = origin;
        line1[1].position = posXY1 + center;

        line2[0].position = posXY1 + center;
        line2[1].position = posXY2 + center;

        wind.draw(line1, 2, sf::Lines);
        wind.draw(line2, 2, sf::Lines);
        wind.draw(m1);
        wind.draw(m2);
        wind.draw(originm);


    }
};



int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "quackudy");
    window.setFramerateLimit(60);

    pendulum pendulum(0.5, 1.5, 3, 200, 150, 800, 500);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        pendulum.updateRK4(); // Update using RK4
        pendulum.update();    // Update positions
        pendulum.render(window); // Render pendulum

        window.display();
    }


    return 0;
}