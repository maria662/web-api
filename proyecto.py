import sys
sys.path.append('/usr/lib/python3/dist-packages')
import requests
import json
from datetime import date
from datetime import datetime
from pyspark.sql import SparkSession


spark = SparkSession.builder.appName('Proyecto final Almacenamiento').getOrCreate()
sc = spark.sparkContext


def getDate(msj):
	print(msj)
	dateInput=(raw_input("Ingresa la fecha con el siguiente formato (YYYY-MM-DD): "))
	Fecha = False
	try:
		fecha=datetime.strptime(dateInput,"%Y-%m-%d")
	except Exception as e:
		print("Algo salio mal, ingresaste valores correctos?. Error: ",e)
	return  fecha

def validateDate(f_i,f_f):
	if f_i>f_f:
		print("La fehca incial no puede ser mayor que la fecha final")
		return False
	else:
		return True

def getData(url):
	#url = "http://144.202.34.148:3132/interruptores"
	response = requests.get(url)
	data = response.text
	parsed = json.loads(data)
	return sc.parallelize(parsed['data']['Interruptores'])

def getPorcentaje(total,cantidad):
	return (cantidad*100)/total

def procesar(data):
    datosI1 = data.filter(lambda x: x['estado'] == True).collect()
    datosI2 =  data.filter(lambda x: x['estado'] == False).collect()
    suma =  data.filter(lambda x: x['temperatura'] != False).collect()
    avg_temp = 0.0;
    #print suma
    for tmp in suma:
       avg_temp = avg_temp + tmp['temperatura']
    avg_temp = avg_temp/len(suma)
    total = data.count()
    print "El porcentaje de verdadero es",getPorcentaje(total,len(datosI1))
    print "El porcentaje de falso es",getPorcentaje(total,len(datosI2))
    print "Temperatura promedio",avg_temp


def main():
	print("###################################")
	print("###Proyecto FINAL ALMACENAMIENTO###")
	print("###################################")
	run = True
	while run:
		T = input("Para realizar una consulta\nPulsa 1 para consulta total\nCualquier otra tecla para fechas\nR: ")
		if T ==1:
			interruptores = getData("http://144.202.17.134:3320/interruptores")
			procesar(interruptores)
			R = input("Quieres probar nuevamente?\nPulsa 1 para continuar\nPara salir pulsa cualquier otro numero\nR: ")
			if(R!=1):
				run=False
		else:
			fecha_inicial = getDate("Fecha incial:\n")
			fecha_final = getDate("Fecha final:\n")
			if(validateDate(fecha_inicial,fecha_final)):
				interruptores = getData("http://144.202.17.134:3320/interruptores/"+fecha_inicial.strftime("%Y-%m-%d")+"/"+fecha_final.strftime("%Y-%m-%d"))
				procesar(interruptores)
				R = input("Quieres probar nuevamente?\nPulsa 1 para continuar\nPara salir pulsa cualquier otro numero\nR: ")
				if(R!=1):
					run=False

if __name__ == '__main__':
	main()