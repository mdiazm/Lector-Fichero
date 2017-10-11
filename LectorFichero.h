//
//  LectorFichero.h
//  Practica 1 - Metaheuristicas
//
//  Created by Miguel Díaz Medina on 2/10/17.
//  Copyright © 2017 Miguel Díaz Medina. All rights reserved.
//

#include <string>
#include <vector>



#ifndef LectorFichero_h
#define LectorFichero_h


class LectorFichero {
    std::string rutaTransmisores; // var.txt
    std::string rutaFrecuencias; // dom.txt
    std::string rutaRestricciones; // ctr.txt
    
    std::vector<int> transmisores; // En cada posición del vector se guardará su rango.
    std::vector<std::vector<int> > frecuencias; // Cada posición del vector será el rango, y el cjto de frecuencias.
    
    std::vector<std::vector<std::pair<int, int> > > restricciones; // Se guarda un par: diferencia | coste 
    
public:
    LectorFichero(std::string _transmisores = "",
                  std::string _frecuencias = "",
                  std::string _restricciones = "");
    ~LectorFichero();
    
    void leeFicheroTransmisores();
    void leeFicheroFrecuencias();
    void leeFicheroRestricciones();
    
    std::vector<int> getTransistores();
    std::vector<std::vector<int> >& getFrecuencias();
    std::vector<std::vector<std::pair<int,int> > > getRestricciones();
    
};

#endif /* LectorFichero_h */
