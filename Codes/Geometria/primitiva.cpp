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
 
const double pi = acos(-1);
typedef int T; // A ideia eh trocar por int ou double quando precisar. Nem todas as funcoes aceitam int, entao tome cuidado
 
T sign(T t){
    if(t < 0)
        return -1;
    if(t == 0)
        return 0;
    return 1;
} 

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
    // EM DUVIDA SE FACTOR EH T OU double, MEXA NESSA FUNCAO CASO FOR USAR ELA
    return c + (p-c)*factor;
}
 
pt rot(pt p, double a){
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
 
double angle(pt v, pt w){
    // retorna o angulo formado por v e w
    double cosTheta = (dot(v, w) / (sq_abs(v)*sq_abs(w)));
    return acos(max((double)-1.0, min((double) 1.0, cosTheta)));
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
    // retorna se p esta no angulo bac estritamente
    if(orient(a, b, c) == 0){
        return false;
    }
    if(orient(a, b, c) < 0)
        swap(b, c);
    return orient(a, b, p) > 0 and orient(a, c, p) < 0;
}
 
double oriented_angle(pt a, pt b, pt c){
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
 
bool inside_triangle(pt x, pt a, pt b, pt c){
    // retorna se x esta no triangulo abc
    if(in_angle(a, b, c, x) and in_angle(b, c, a, x) and in_angle(c, a, b, x))
        return true;
    else
        return false;
}
 
struct line{
    pt v; T c;
    // Definimos linha como o vetor diretor v e o offset c (v*x = c)
    line(pt v, T c) : v(v), c(c) {}
    // Com a equacao (ax+by = c) -> cross((b, -a), (x, y)) = c
    line(T a, T b, T c) : v({b, -a}), c(c) {}
    // Se eu tenho dois pontos P,Q, a reta esta definida (v = PQ e C = cross(v, p))
    line(pt p, pt q) : v(q-p), c(cross(v, p)) {}
    T side(pt p){        
        /*
        Para saber onde o ponto esta em relacao a uma reta
        se > 0 -> esta do lado esquerdo
        Se < 0 -> esta do lado direto
        Se = 0 -> esta na reta
        */
        return cross(v, p) - c;
    }
    double dist(pt p){
        /*
        distancia de ponto a reta. Como v aponta na direcao da reta, cross(v, p) = sq_ans(v)*(magnitude da distancia da projecao de v a p)
        */
        return abs(side(p)) / abs(v);
    }
    line perp_through(pt p){
        // Linha que passa por p e eh perpendicular a l. Basta ela passar por p e por p + perp(v)
        return {p, p + perp(v)};
    }
    bool cmpProj(pt p, pt q){
        // Ordena pontos na linha l
        return dot(v, p) < dot(v, q);
    }
    line translate(pt t){
        // translada a linha l por t
        return {v, c + cross(v, t)};
    }
    bool inter(line l1, line l2, pt &out) {
        // retorna se elas se interssectam ou nao, e out eh a intercessao
        T d = cross(l1.v, l2.v);
        if (d == 0) return false;
        out = (l2.v*l1.c - l1.v*l2.c) / d; // requires floating-point
        return true;
    }
    pt proj(pt p){
        // retorna qual ponto eh a projecao de p em l
        return p - (perp(v)*side(p))/abs(v);
    }
    pt refl(pt p){
        // retorna o reflexo de p por l
        return p - (perp(v)*(2*side(p)))/abs(v);
    }
};
 
line bisector(line l1, line l2, bool interior){
    // retorna a linha que bissecta o angulo l1 l2
    // perceba que l1 e l2 nao podem ser paralelas, podemos checkar isso com o assert
    assert(cross(l1.v, l2.v) != 0);
    double sign = interior ? 1 : -1;
    return {l2.v/abs(l2.v) + l1.v/abs(l1.v) * sign, l2.c/abs(l2.v) + l1.c/abs(l1.v) * sign};
}
 
bool in_disk(pt p, pt a, pt b){
    // checka se p esta no circulo de diametro ab. usamos potencia de ponto para isso 
    return dot(a-p, b-p) <= 0;
}
 
bool on_segment(pt p, pt a, pt b){
    // checka se p esta no segmento ab. checkamos se p esta na circunferencia de ab e se abp sao colineares
    return orient(a, b, p) == 0 and in_disk(p, a, b);
}

bool proper_inter(pt a, pt b, pt c, pt d, pt &out){
    // checka se segmentos ab e cd se intersectam. se sim, colocamos em out
    // checkamos isso vendo se a esta de um lado e b do outro da reta cd. mesma coisa para c e d em ab
    T oa = sign(orient(c, d, a)), ob = sign(orient(c, d, b)), oc = sign(orient(a, b, c)), od = sign(orient(a, b, d));
    if(on_segment(a, c, d) or on_segment(b, c, d) or on_segment(c, a, b) or on_segment(d, a, b))
        return true;
    if(oa*ob < 0 and oc*od < 0){
        if(ob == oa){
            out = {0, 0};
        }
        else{
            out = (a*ob-b*oa)/(ob-oa);
        }
        return true;
    }
    return false;
}
 
double seg_point(pt p, pt a, pt b){
    // retorna a distancia do ponto p para o segmento ab
    if(a != b){
        line l(a, b);
        if(l.cmpProj(a, p) and l.cmpProj(p, b)){
            return l.dist(p);
        }
    }
    return min(abs(p-a), abs(p-b));
}
 
double seg_seg(pt a, pt b, pt c, pt d){
    // retorna a distancia do segmento ab para o segmento cd
    pt dummy;
    if(proper_inter(a, b, c, d, dummy))
        return 0;
    return min({seg_point(c, a, b), seg_point(d, a, b), seg_point(a, c, d), seg_point(b, c, d)});
}

T area_polygon(vector <pt> p){
    // calcula 2*(a area de um poligono simples)
    T area = 0;
    for(int i = 0, n = p.size();i < n;i++){
        area += cross(p[i], p[(i+1)%n]);
    }
    return abs(area);
}

bool above(pt a, pt b){
    // checka se a esta acima de b
    return a.y >= b.y;
}

int crosses_ray(pt p, pt a, pt b){ 
    // checka se a reta ab cruza o ray p -> inf
    return ((above(a, p) - above(b, p))*orient(p, a, b)) > 0;
}

bool inside_polygon(pt p, vector <pt> v){
    // checka se p esta dento do poligono v
    int crossing = 0;
    for(int i = 0, n = v.size(); i < n;i++){
        if(on_segment(p, v[i], v[(i+1)%n])){
            return true;
        }
        crossing += crosses_ray(p, v[i], v[(i+1)%n]);
    }
    return crossing&1;
}
 
int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}
