#!/usr/bin/python

import sys


def productor(cultivos, restricciones):
    cultivos = open(cultivos, "r")
    restricciones = open(restricciones,'r')

    cultivosXTrimestre = {}
    restriccionesXCultivo = {}
    plantaciones = {}

    # Organizo los cultivos por trimestre
    for linea in cultivos:
        cultivo = linea.split(',')
        trimestre = int(cultivo[1])
        datos = (cultivo[0].strip(),int(cultivo[2]))

        if not trimestre in cultivosXTrimestre:
            cultivosXTrimestre[trimestre] = [datos]
        else:
            cultivosXTrimestre[trimestre].append(datos)

    # Organizo las restricciones por cultivo
    for linea in restricciones:
        restricion = linea.split(',')
        c = restricion[0].strip()
        r = restricion[1].strip()

        if not c in restriccionesXCultivo:
            restriccionesXCultivo[c] = [r]
        else:
            restriccionesXCultivo[c].append(r)

    # Inicializo las plantanciones del primer trimestre (supongo que siempre esta el trimestre 1)
    plantaciones[1] = []
    for cultivo in cultivosXTrimestre[1]:
        plantaciones[1].append((cultivo[1],[cultivo[0]])) # Tupla con lista de cultivos

    # Calculo las plantanciones de los trimestres
    for trimestre in cultivosXTrimestre:
        if trimestre == 1:
            continue

        cultivosDelTrimestre = cultivosXTrimestre[trimestre]

        for cultivo in cultivosDelTrimestre:
            ganancia = 0
            cultivosDeMayorGanancia = []

            for cultivoAnteriorTrimestre in plantaciones[trimestre-1]:
                # La restriccion la tengo con respecto al último cultivo del trimestre anterior
                if cultivo[0] == cultivoAnteriorTrimestre[1][len(cultivoAnteriorTrimestre[1])-1]:
                    continue
                if cultivoAnteriorTrimestre[1][len(cultivoAnteriorTrimestre[1])-1] in restriccionesXCultivo:
                    if cultivo[0] in restriccionesXCultivo[cultivoAnteriorTrimestre[1][len(cultivoAnteriorTrimestre[1])-1]]:
                        continue

                gananciaAcumulada = cultivoAnteriorTrimestre[0] + cultivo[1]

                if gananciaAcumulada > ganancia:
                    ganancia = gananciaAcumulada
                    cultivosDeMayorGanancia = cultivoAnteriorTrimestre[1] + [cultivo[0]]

            if not trimestre in plantaciones:
                plantaciones[trimestre] = [(ganancia,cultivosDeMayorGanancia)]
            else:
                plantaciones[trimestre].append((ganancia,cultivosDeMayorGanancia))

    # Comparo las plantaciones del último trimestre
    mayorGanancia = 0
    plantacionMayorGanancia = []
    for plantacion in plantaciones[len(plantaciones)]:
        if plantacion[0] > mayorGanancia:
            mayorGanancia = plantacion[0]
            plantacionMayorGanancia = plantacion[1]

    cultivos.close()
    restricciones.close()

    return plantacionMayorGanancia


def main():
    print(productor(sys.argv[1], sys.argv[2]))


main()


