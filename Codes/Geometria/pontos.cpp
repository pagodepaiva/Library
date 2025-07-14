#include<bits/stdc++.h>
#define pt Point
#define int long long

using namespace std;

/*
Biblioteca de Geometria:
Ideia: Ter boa parte das funções usadas em geometria competitiva nesse codigo (Não conter algoritmos, deixar isso separado)
Já temos:

- Operações basicas em complexos(+, -, *, /, ==, !=, cout)
- operacoes em pontos (cross, dot, abs)
- translacao, rotacao
- ordenar por angulo

*/

const long double pi = acos(-1);
typedef int T;

struct Point{
    T x, y;
    Point operator+=(const Point p){
        this->x += p.x;
        this->y += p.y;
        return *this;
    }
    Point operator-=(const Point p){
        this->x -= p.x;
        this->y -= p.y;
        return *this;
    }
};

pt operator+(const pt a, const pt b){
    return {a.x+b.x, a.y+b.y};
}

pt operator-(const pt a, const pt b){
    return {a.x-b.x, a.y-b.y};
}

pt operator*(const pt a, const T d){
    return {a.x*d, a.y*d};
}

pt operator/(const pt a, const T d){
    return {a.x/d, a.y/d};
}

bool operator==(const Point a, const Point b){
    return (a.x == b.x and a.y == b.y);
}

bool operator!=(const Point a, const Point b){
    return !(a == b);
}

T abs(Point p){
    return p.x*p.x + p.y*p.y;
}

T sq_abs(Point p){
    return sqrt(abs(p));
}

ostream& operator<<(ostream& os, Point p){
    return os << "(" << p.x << "," << p.y << ")";
}

istream& operator>>(istream& is, Point& p){
    is >> p.x >> p.y;
    return is;
}

pt translate(pt v, pt p){
    // Transladar um ponto por um vetor
    return p+v;
}

pt scale(pt c, T factor, pt p){
    // Escalonar um ponto P por um ponto C com fator factor (Homotetia)
    // EM DUVIDA SE FACTOR EH T OU long double, MEXA NESSA FUNCAO CASO FOR USAR ELA
    return c + (p-c)*factor;
}

pt rot(pt p, long double a){
    // Rotacionar um ponto p por um angulo a pela origem
    return {p.x*cos(a) - p.y*sin(a), p.x*sin(a) + p.y*cos(a)};
}

pt perp(pt p){
    // Rotacionar p por 90 graus pela origem
    return {-p.y, p.x};
}

T dot(pt v, pt w){
    /*
    Dot product
    equivalente a sq_abs(v)*sq_abs(w)*cos(theta), onde theta eh o angulo formado pelos vetores v e w partindo da origem (0, 0)
    pode ser interpretado como sq_abs(v)*(magnitude da projecao de w em v)
    podemos calcular sinal de cos(theta)
    */
    return v.x*w.x + v.y*w.y;
}

bool isperp(pt v, pt w){
    // retorna se os vetores v, w sao perpendiculares
    return dot(v, w) == 0;
}

long double angle(pt v, pt w){
    // retorna o angulo formado por v e w
    long double cosTheta = (dot(v, w) / (sq_abs(v)*sq_abs(w)));
    return acos(max((long double)-1.0, min((long double) 1.0, cosTheta)));
}

T cross(pt v, pt w){
    /*
    Cross product
    equivalente a sq_abs(v)*sq_abs(w)*sin(theta)
    pode ser interpretado como sq_abs(v)*(distancia entre w e o vetor v)
    podemos calcular sinal de sin(theta) (assim, conseguimos descobrir se w esta a esquerda, a direira, ou colinear com (0, 0)v)
    */
    return v.x*w.y-v.y*w.x;
}

T orient(pt a, pt b, pt c){
    /*
    retorna a orientacao de (a, b, c):
    > 0 significa countercloclwise
    == 0 significa colineares
    < 0 significa clockwise
    */
    return cross(b-a, c-a);
}

bool in_angle(pt a, pt b, pt c, pt p){
    // retorna se p esta no angulo bac
    if(orient(a, b, c) == 0){
        return orient(a, b, p) == 0;
    }
    if(orient(a, b, c) < 0)
        swap(b, c);
    return orient(a, b, p) >= 0 and orient(a, c, p) <= 0;
}

long double oriented_angle(pt a, pt b, pt c){
    // retorna angulo bac orientado
    if(orient(a, b, c) >= 0){
        return angle(b-a, c-a);
    }
    else{
        return 2*pi - angle(b-a, c-a);
    }
}

bool is_convex(vector <pt> p){
    // retorna se um poligono eh convexo
    // seus pontos tem que estar em ordem consecutivas
    bool hasPos = false, hasNeg = false;
    for(int i = 0, n = p.size();i < n;i++){
        int o = orient(p[i], p[(i+1)%n],p[(i+2)%n]);
        if(o > 0) hasPos = true;
        if(o < 0) hasNeg = true;
    }
    return !(hasPos && hasNeg);
}

/*

caso voce queira trocar o half da ordenacao

pt v = {qualquer valor}

bool half(pt p) {
    return cross(v,p) < 0 || (cross(v,p) == 0 && dot(v,p) <
    0);
}

*/

bool half(pt p){
    // true se p esta acima do eixo x ou se p esta no eixo x e a esquerda do eixo y
    return p.y > 0 or (p.y == 0 and p.x <= 0);
}

void polar_sort(vector <pt> &v){
    // ordena os pontos pelo seu angulo
    // comparador retorna true se w esta acima de x e v embaixo, ou se eles estao na mesma regiao e cross(v, w) > 0, ou seja, se v vem antes de w
    // desempate pela magnitude
    sort(v.begin(), v.end(), [](pt v, pt w){
        return make_tuple(half(v), 0, abs(v)) < make_tuple(half(w), cross(v, w), abs(w));
    });
}

void polar_sort_around(pt o, vector <pt> &v){
    // ordena os pontos pelo angulo na origem o
    for(auto &x : v){
        x -= o;
    }
    polar_sort(v);
    for(auto &x : v){
        x += o;
    }
}
