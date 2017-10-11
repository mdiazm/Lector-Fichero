//
//  LectorFichero.cpp
//  Practica 1 - Metaheuristicas
//
//  Created by Miguel Díaz Medina on 2/10/17.
//  Copyright © 2017 Miguel Díaz Medina. All rights reserved.
//

#include <fstream>
#include <stdexcept>
#include <iostream>

#include "LectorFichero.h"

LectorFichero::LectorFichero(std::string _transmisores,
                             std::string _frecuencias,
                             std::string _restricciones): restricciones(),
transmisores(),
frecuencias(),
rutaFrecuencias(_frecuencias),
rutaTransmisores(_transmisores),
rutaRestricciones(_restricciones) {
    
    transmisores.push_back(0); // Se inserta un cero en el primer elemento, para que coloque las lecturas a partir de la posición 1.
    // Y podamos acceder a las posiciones transmisores[1], transmisores[2], ..., obteniendo el rango.
    
    frecuencias.resize(10); // Asumimos que no hay más de 10 rangos.
    
    leeFicheroFrecuencias();
    leeFicheroTransmisores();
    leeFicheroRestricciones();    
    
}

LectorFichero::~LectorFichero(){
    
}

void LectorFichero::leeFicheroTransmisores(){
    std::string lineaActual = "";
    
    try {
        std::ifstream inputStream;
        inputStream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
        inputStream.open(rutaTransmisores);
        
        while(!inputStream.eof()){
            getline(inputStream >> std::ws, lineaActual);
            
            int pos = (int) lineaActual.find(' ');
            
            
            
            
            std::string rango = lineaActual.substr(pos,lineaActual.length());
            
            transmisores.push_back(std::stoi(rango)); // Se carga en cada posición (transmisor) el rango asociado.
        }
        inputStream.close();
        
    } catch(std::ifstream::failure &e){
        std::cerr << //e.what() <<
		std::endl;
    }
}


void LectorFichero::leeFicheroFrecuencias(){
    std::string lineaActual = "";
    
    try {
        std::ifstream inputStream;
        inputStream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
        inputStream.open(rutaFrecuencias);
        std::vector<int> aux;
        int posVector = 0;
        std::string lineaAux;
        
        while(!inputStream.eof()){
            getline(inputStream >> std::ws, lineaActual);
            
            int pos = (int) lineaActual.find(' ');
            
            posVector = std::stoi(lineaActual.substr(0,pos));
			for(int i = pos; lineaActual[i] == ' '; i++){
				pos = i;
			}
            lineaAux = lineaActual.substr(pos+1, lineaActual.length()-pos-1);
            lineaActual = lineaAux;
            // modificar código: recortar líneas correctamente para no dejar espacios en blanco al principio.
            std::string frec = "";
            // Se va leyendo frecuencia a frecuencia.
            while(pos != std::string::npos){
                pos = (int) lineaActual.find(' ');
                
                frec = lineaActual.substr(0,pos);
                for(int i = pos; lineaActual[i] == ' '; i++){
                    pos = i;
                }
                lineaAux = lineaActual.substr(pos+1, lineaActual.length()-pos+1);
                lineaActual = lineaAux;
                if(frec == "")
					break;
                aux.push_back(std::stoi(frec));
            }
            
            frecuencias[posVector] = aux; // Copiamos el vector a la posición de su rango.
			aux.clear(); // faltaba, y replicaba elementos en posiciones siguientes al vector.
        }
        
        inputStream.close();
        
    } catch(std::ifstream::failure &e){
        std::cerr << //e.what() <<
		std::endl;
    }
}

void LectorFichero::leeFicheroRestricciones(){
    std::string lineaActual = "";
    
    try {
        std::ifstream inputStream;
        inputStream.exceptions(std::ifstream::badbit | std::ifstream::failbit);
        inputStream.open(rutaRestricciones);
        std::string lineaAux = "";
        restricciones.resize(transmisores.size());
		for(int i = 0; i < transmisores.size(); i++)
			restricciones[i].resize(transmisores.size());
        int pos = 0;
        while(!inputStream.eof()){
            getline(inputStream >> std::ws, lineaActual);
            
            pos = (int) lineaActual.find(' ');
            
            int tr1 = std::stoi(lineaActual.substr(0,pos+1)); // índice del transmisor 1
            for(int i = pos; lineaActual[i] == ' '; i++){
                pos = i;
            }
            lineaAux = lineaActual.substr(pos+1, lineaActual.length()-pos);
            lineaActual = lineaAux;
            
            pos = (int) lineaActual.find(' ');
            
            int tr2 = std::stoi(lineaActual.substr(0,pos+1)); // índice del transmisor 2
            for(int i = pos; lineaActual[i] == ' '; i++){
                pos = i;
            }
			
			
			lineaAux = lineaActual.substr(pos+1, lineaActual.length()-pos);
            lineaActual = lineaAux;
			int coste;
			int restriccion;
            if(lineaActual[0] != 'D'){ // Descartamos las restricciones con 'D'
                pos = (int) lineaActual.find_last_of(' ');
                coste = std::stoi(lineaActual.substr(pos+1, lineaActual.length()-pos)); // coste de la función objetivo
                for(int i = pos; lineaActual[i] == ' '; i++)
                    pos = i;
				
				int posNum = (int)lineaActual.find('>');
				restriccion = std::stoi(lineaActual.substr(posNum+2,pos-posNum-2)); // Restricción impuesta.
				restricciones[tr1][tr2] = std::pair<int, int>(restriccion,coste);
                
            }
            
			
			
			
        }
        
        inputStream.close();
        
    } catch(std::ifstream::failure &e){
        std::cout << //e.what() <<
		std::endl;
    }

}

std::vector<int> LectorFichero::getTransistores(){
	return transmisores;
}


std::vector<std::vector<int> >& LectorFichero::getFrecuencias(){
	return frecuencias;
}


std::vector<std::vector<std::pair<int,int> > > LectorFichero::getRestricciones(){
	return restricciones;
}


