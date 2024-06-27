#include <iostream>
using namespace std;
#include "TablaHash.h"

int main()
{
    Piloto piloto1("","","P12345678","",600,"");
    Piloto piloto2("","","P87654321","",500,"");
    Piloto piloto3("","","P10101019","",650,"");
    Piloto piloto4("","","P14521378","",320,"");
    Piloto piloto5("","","A01010104","",321,"");

    TablaHash miTabla;
    miTabla.Insertar(piloto1);
    miTabla.Insertar(piloto2);
    miTabla.Insertar(piloto3);
    miTabla.Insertar(piloto4);
    miTabla.Insertar(piloto5);
    miTabla.imprimirTabla();
    
    
    return 0;
}
