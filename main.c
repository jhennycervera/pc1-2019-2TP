/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Admin
 *
 * Created on 11 de abril de 2020, 11:21
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAYOR LONG_MAX //cual es el mayor valor real?
#define MAYOR_ENTERO INT_MAX
/*
 * 
 */
void imprimirRep(int clientesEstadistica1, double clientesEstadistica2, double clientesEstadistica3, int clienteMayorConsumo, int clienteMenosConsumo,
                  int clienteEstadistica5 ){
    printf("eL NUMERO DE CLIENTES QUE RESIDE EN LAS CIUDADES 21,45,67 DEL PAIS 3: %d\n", clientesEstadistica1);
    printf("el porcentaje de clientes que tiene menos de 5 años de servicios y que pagan en promedio mas de 50.00 diario: %.2lf%%\n",clientesEstadistica2 );
    printf("La tarifa promedio de los clientes qye viene en la ciudad  60 y que ingresaron al servicio antes de 1/07/2004: %.4lf\n", clientesEstadistica3);
    printf("El cliente que mas pagó y el que menos pago por su consumo promedio:\n mas: %d \n Menos: %d\n",clienteMayorConsumo, clienteMenosConsumo);
    printf("El cliente con mayor tiempo promedio en llamadas con menor tarifa: %d\n",clienteEstadistica5);
}

int  cumpleEstadistica1(int num){
    int pais, ciudad;
    pais= num/100000000;
    ciudad= (num/ 1000000)-pais*100;
    if(pais==3){
        if(ciudad==21 || ciudad==45 || ciudad==67) return 1;
    }
    return 0;
}

int cumpleEstadistica2(int fecha, double timeMin, double tarifa){
    int fechaHace5anhos=20150411;
    if(timeMin*tarifa > 50 && fecha>fechaHace5anhos){
        return 1;
    }
    return 0;
}

void acumulaEstadistica3(int fecha,int num,double tarifa, int *contEstadist3, double *sumaTarifa){
    int ciudad, pais;
    pais=num/100000000;
    ciudad=num/1000000 -(pais*100);
    if(fecha<20040701 && ciudad==60){
        (*contEstadist3)++;
        (*sumaTarifa)+=tarifa;
    }
}
/*
void EstadisticaDelConsumoPromedio(double tarifa,double timeMin,int dni,int *clienteMayorConsumo,int*clienteMenosConsumo){
    double consumoMayor=0, consumoMenor=MAYOR;
    double consumo;
    consumo=tarifa*timeMin;
    if(consumo > consumoMayor){ 
        consumoMayor=consumo;
        (*clienteMayorConsumo)=dni;  
    }
    if(consumo <consumoMenor){
        consumoMenor=consumo;
        (*clienteMenosConsumo)=dni;
    }
}
*/
void cumpleEstadistica5(int *clienteEstadistica5, double timeMin, double tarifa, int dni){
    double mayorTiempo=0;
    double menorTarifa=MAYOR;
    if(timeMin>mayorTiempo){
        mayorTiempo=timeMin;
        if(tarifa<menorTarifa){
            menorTarifa=tarifa;
            (*clienteEstadistica5)=dni; //se tiene que actualizar cada vez que entra a esta funcion, no devolver un valor cada vez que entra
        }
    }
}

int main(int argc, char** argv) {
    int clientesEstadistica1=0, clienteMayorConsumo,clienteMenosConsumo,clienteEstadistica5, totalClientes=0, contEstadist2=0,contEstadist3=0;
    double clientesEstadistica2,clientesEstadistica3,timeMin, sumaTarifa=0; 
                  
    int dni, anho, dia,mes, num,hora,min, seg, fecha;
    // long int dni
    double tarifa;
    double consumoMayor=0, consumoMenor=MAYOR,consumo,mayorTiempo=0,menorTarifa=MAYOR;;
    while(1){
        scanf("%d %d/%d/%d %d %d:%d:%d %lf",&dni, &dia,&mes,&anho,  &num, &hora,&min, &seg, &tarifa);
        printf("\n");
        printf("%d %d/%d/%d %d %d:%d:%d %lf\n",dni, dia,mes,anho,  num, hora,min, seg, tarifa);
        if(dni==0) break;
        fecha=(anho*10000)+ mes*100 + dia;
        timeMin= hora*60 + min + seg/60.0;
        clientesEstadistica1+= cumpleEstadistica1(num);
        contEstadist2+=cumpleEstadistica2(fecha, timeMin, tarifa);
        acumulaEstadistica3(fecha,num,tarifa, &contEstadist3, &sumaTarifa); //void pues me modifica 2 cantidades, no devuelve un valor
        totalClientes++;
        //Hallando el consumo mayor y menor
        consumo=tarifa*timeMin;
        if(consumo > consumoMayor){ 
            consumoMayor=consumo;
            (clienteMayorConsumo)=dni;  
        }
        if(consumo <consumoMenor){
            consumoMenor=consumo;
            (clienteMenosConsumo)=dni;
        }
        //Estadistica 5
        if(timeMin>mayorTiempo){
            mayorTiempo=timeMin;
            if(tarifa<menorTarifa){
                menorTarifa=tarifa;
                (clienteEstadistica5)=dni; 
            }
        }

    }
    clientesEstadistica2= contEstadist2*100.0/totalClientes;
    clientesEstadistica3=sumaTarifa/contEstadist3;
    imprimirRep(clientesEstadistica1, clientesEstadistica2,clientesEstadistica3,clienteMayorConsumo, clienteMenosConsumo,
                 clienteEstadistica5 );
    
    
    return (EXIT_SUCCESS);
}

